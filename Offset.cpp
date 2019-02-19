#include "DLLmain.h"

BOOL WriteBytes(LPVOID pAddr, VOID * pData, DWORD dwLen)
{
	DWORD dwOld;

	if (!VirtualProtect(pAddr, dwLen, PAGE_READWRITE, &dwOld))
		return FALSE;

	::memcpy(pAddr, pData, dwLen);
	return VirtualProtect(pAddr, dwLen, dwOld, &dwOld);
}

DWORD GetDllOffset(const char *dll, int offset)
{
	HMODULE hmod = GetModuleHandle(dll);
	if (!hmod)
		hmod = LoadLibrary(dll);
	if (!hmod) return 0;
	if (offset < 0)
		return (DWORD)GetProcAddress(hmod, (LPCSTR)(-offset));

	return ((DWORD)hmod) + offset;
}

void Patch(BYTE bInst, char* pDll, DWORD pAddr, DWORD pFunc, DWORD dwLen, char* Type)
{
	pAddr = GetDllOffset(pDll, pAddr);

	BYTE *bCode = new BYTE[dwLen];
	if (bInst)
	{
		::memset(bCode, 0x90, dwLen);
		bCode[0] = bInst;
		if (pFunc)
		{
			if (bInst == 0xE8 || bInst == 0xE9)
			{
				DWORD dwFunc = pFunc - (pAddr + 5);
				*(DWORD*)&bCode[1] = dwFunc;
			}
			else
			if (bInst == 0x68 || bInst == 0x05 || bInst == 0x5B)
			{
				*(LPDWORD)&bCode[1] = pFunc;
			}
			else
			if (bInst == 0x83)
			{
				*(WORD*)&bCode[1] = (WORD)pFunc;
			}
			else
			{
				bCode[1] = (BYTE)pFunc;
			}
		}
	}
	else
	{
		if (dwLen == 6)
		{
			::memset(bCode, 0x00, dwLen);
			*(DWORD*)&bCode[0] = pFunc;
		}
		else if (dwLen == 4)
			*(DWORD*)&bCode[0] = pFunc;
		else if (dwLen == 2)
			*(WORD*)&bCode[0] = (WORD)pFunc;
		else if (dwLen == 1)
			*(BYTE*)&bCode[0] = (BYTE)pFunc;
	}

	if (!WriteBytes((void*)pAddr, bCode, dwLen))
	{
		delete[] bCode;
		D2ERROR("Error while patching game's %s with %d byte(s)", Type, dwLen);
	}
	delete[] bCode;
}

BOOL WriteDword(DWORD* lpAddr, DWORD lpBuffer)
{
	DWORD dwOldProtect;
	if (!VirtualProtect(lpAddr, 4, PAGE_READWRITE, &dwOldProtect))
	{
		D2ERROR("Failed to patch %d with %d", lpAddr, lpBuffer)
	}
	*lpAddr = lpBuffer;

	if (!VirtualProtect(lpAddr, 4, dwOldProtect, &dwOldProtect))
	{
		D2ERROR("Failed to patch %d with %d", lpAddr, lpBuffer)
	}
	return TRUE;
}

void ShowMsgBox(char * Msg, ...)
{
	va_list arguments;
	va_start(arguments, Msg);

	int len = _vscprintf(Msg, arguments) + 1;
	char * text = new char[len];
	vsprintf_s(text, len, Msg, arguments);
	va_end(arguments);

	MessageBoxA(0, text, "Warning", 0);

	delete[] text;
}
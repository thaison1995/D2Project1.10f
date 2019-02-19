#include "DLLmain.h"

BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin)
{
	if (dwVal == 0 || dwMaxVal == 0)
		return NULL;

	BYTE iRes = (BYTE)((double)dwVal / (double)dwMaxVal * 100.0);

	if (iRes > 100)
		iRes = 100;

	return max(iRes, iMin);
}

int GetClass(char* txt)
{
	if (!_strcmpi("Ama", txt) || !_strcmpi("Amazon", txt) || !_strcmpi("ama", txt))
		return 0;
	else if (!_strcmpi("Sor", txt) || !_strcmpi("Sorceress", txt) || !_strcmpi("sor", txt))
		return 1;
	else if (!_strcmpi("Nec", txt) || !_strcmpi("Necromancer", txt) || !_strcmpi("nec", txt))
		return 2;
	else if (!_strcmpi("Pal", txt) || !_strcmpi("Paladin", txt) || !_strcmpi("pal", txt))
		return 3;
	else if (!_strcmpi("Bar", txt) || !_strcmpi("Barbarian", txt) || !_strcmpi("bar", txt))
		return 4;
	else if (!_strcmpi("Dru", txt) || !_strcmpi("Druid", txt) || !_strcmpi("dru", txt))
		return 5;
	else if (!_strcmpi("Ass", txt) || !_strcmpi("Assassin", txt) || !_strcmpi("ass", txt))
		return 6;

	return -1;
}

char* GetCharClass(int ID)
{
	if (ID == 0)
		return "Ama";
	else if (ID == 1)
		return "Sor";
	else if (ID == 2)
		return "Nec";
	else if (ID == 3)
		return "Pal";
	else if (ID == 4)
		return "Bar";
	else if (ID == 5)
		return "Dru";
	else if (ID == 6)
		return "Ass";

	return "Mana";
}

void Misc_CharToWide(wstring& Dest, const string Source)
{
	Dest.assign(Source.begin(), Source.end());
}

const char* S_compileTxtFile = "compileTxtFile";
const char* S_errorReadTxtFile = "pbData";
NAKED void* STDCALL compileTxtFile(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	__asm
	{
		SUB ESP, 0x210
		PUSH EBX
		PUSH EBP
		MOV EBP, DWORD PTR SS : [ESP + 0x220]
		PUSH ESI
		PUSH EDI
		MOV DWORD PTR SS : [ESP + 0x10], 0

		MOV EBX, wsprintf
		PUSH EBP
		LEA EAX, DWORD PTR SS : [ESP + 0x20]
		PUSH EAX
		CALL EBX
		ADD ESP, 8

		LEA EDX, DWORD PTR SS : [ESP + 0x10]
		PUSH 0
		PUSH S_compileTxtFile
		PUSH EDX
		MOV ECX, DWORD PTR SS : [ESP + 0x230]
		LEA EDX, DWORD PTR SS : [ESP + 0x28]
		CALL D2COMMON_D2ReadFile
		TEST EAX, EAX
		JNZ continue_compileTxtFile
		PUSH 0
		PUSH S_compileTxtFile
		PUSH S_errorReadTxtFile
		CALL FOG_D2FogAssertOld
		PUSH - 1
		CALL exit
		continue_compileTxtFile :
		MOV ECX, D2COMMON_CompileTxt
		ADD ECX, 0x2ED
		JMP ECX
	}
}

LONG WINAPI GameWindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEMOVE:
		{
			bool block_msgs = false;
			for each (auto i in Controls)
			{
				if (i->isPressed(uMsg, wParam))
				block_msgs = true;
			}
			if (block_msgs) return 0;
		}
		break;
	};

	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == DamageHotKeyPlayer)
		{
			if (DamageEnabledPlayer == 1)
			{
				DamageEnabledPlayer = 0;
				Print(4, "Damage Playerÿc0: ÿc1Disabled");
			}
			else if (DamageEnabledPlayer == 0)
			{
				DamageEnabledPlayer = 1;
				Print(4, "Damage Playerÿc0: ÿc2Enabled");
			}
		}

		if (wParam == DamageHotKeyMon)
		{
			if (DamageEnabledMon == 1)
			{
				DamageEnabledMon = 0;
				Print(4, "Damage Monÿc0: ÿc1Disabled");
			}
			else if (DamageEnabledMon == 0)
			{
				DamageEnabledMon = 1;
				Print(4, "Damage Monÿc0: ÿc2Enabled");
			}
		}
	}

	return (LONG)CallWindowProcA(OldWNDPROC, hWnd, uMsg, wParam, lParam);
}

wstring ConvertTickToTime(DWORD nTick)
{
	if (nTick == 0) return L"00:00";
	nTick /= 1000;
	wchar_t wTime[70] = { 0 };
	swprintf_s(wTime, 70, L"%.2d:%.2d:%.2d", nTick / 3600, (nTick / 60) % 60, nTick % 60);
	return wTime;
}

void __stdcall D2CLIENT_DrawGZBox(int X1, int Y1, int X2, int Y2)
{
	RECT * r = new RECT;
	r->left = X1;
	r->top = Y1;
	r->right = X2;
	r->bottom = Y2;
	D2CLIENT_DrawGZBOX_I(r);
	delete r;
}

void TextCenter(INT X, INT Y, DWORD Color, INT Font, INT Trans, LPSTR Text, ...)
{
	POINT nPos = { X, Y };
	DWORD dwOldSize, wWidth, dwFileNo;

	CHAR szBuffer[800] = "";
	va_list Args;
	va_start(Args, Text);
	vsprintf_s(szBuffer, Text, Args);
	va_end(Args);

	WCHAR wBuffer[0x200];
	MultiByteToWideChar(0, 1, szBuffer, 200, wBuffer, 200);

	dwOldSize = D2WIN_SetTextSize(Font);

	D2WIN_GetTextWidthFileNo(wBuffer, &wWidth, &dwFileNo);
	nPos.x -= (wWidth >> 1);

	D2WIN_D2DrawTextEx(wBuffer, nPos.x, nPos.y, Color, -1, Trans);
	D2WIN_SetTextSize(dwOldSize);
}

bool Print(INT Color, CHAR * Format, ...)
{
	if (strlen(Format) <= NULL)
		return FALSE;

	CHAR *szString = new CHAR[8192];
	::memset(szString, 0, 8192);
	va_list vaArgs;

	va_start(vaArgs, Format);
	vsprintf(szString, Format, vaArgs);
	va_end(vaArgs);

	WCHAR Buffer[8192] = L"";
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szString, (INT)strlen(szString), Buffer, (INT)strlen(szString));

	D2CLIENT_PrintGameString(Buffer, Color);

	delete[] szString;
	return TRUE;
}


#define LOG_FILE "Debug.log"
void Log(char* Msg...)
{
	va_list arguments;
	va_start(arguments, Msg);

	int len = _vscprintf(Msg, arguments) + 1;
	char * text = new char[len];
	vsprintf_s(text, len, Msg, arguments);
	va_end(arguments);

	char sTime[9];
	_strtime_s(sTime, 9);
	FILE* plik;
	fopen_s(&plik, LOG_FILE, "a");
	if (plik)
	{
		fprintf(plik, "[%s] %s\n", sTime, text);
		fclose(plik);
	}
	delete[] text;
}

int Misc::round(double a)
{
	return int(a + 0.5);
}

wstring string2wString(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}
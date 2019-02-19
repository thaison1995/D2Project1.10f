#include "DLLmain.h"

void NewTxt::Files()
{
	Orb::LoadTXT();
	ExBuffs::LoadTXT();
}

NAKED void __fastcall NewTxt::Files_STUB()
{
	__asm
	{
		call NewTxt::Files
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		ADD ESP, 0x130
		RETN
	}
}

void __fastcall NewTxt::FreeFiles()
{
	Orb::FreeTXT();
	ExBuffs::FreeTXT();
}

NAKED void __fastcall NewTxt::FreeFiles_STUB()
{
	__asm
	{
		CALL NewTxt::FreeFiles
		jmp FOG_D2Fog10212
	}
}

void NewTxt::OnPatch()
{
	Patch(JUMP, "D2Common.dll", 0x2F7F7, (DWORD)NewTxt::Files_STUB, 11, "LoadTXT");
	Patch(CALL, "D2Common.dll", 0x10373, (DWORD)NewTxt::FreeFiles_STUB, 5, "FreeTXT");
}
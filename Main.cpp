#include "DLLmain.h"

bool SetGameWindowEvent = 1;
void MainScreen()
{
	if (SetGameWindowEvent && D2GFX_GetHwnd())
	{
		OldWNDPROC = (WNDPROC)GetWindowLong(D2GFX_GetHwnd(), GWL_WNDPROC);
		SetWindowLong(D2GFX_GetHwnd(), GWL_WNDPROC, (LONG)GameWindowEvent);
		SetGameWindowEvent = 0;
	}
}

void OnExit()
{
	fnRendererCallbacks * fns = *D2GFX_pfnDriverCallback;
	D2ASSERT(fns, "GFX deinit error - driver ptr is null!");

	fns->Release();
	UnregisterClass("Diablo II", *D2GFX_hInstance);

	D2ASSERT(!(*D2GFX_bInitSucceed), "A critical error has occurred while initializing GFX system for %d renderer", gRenderer);
	if (*D2GFX_hDriverModHandle)
	{
		FreeLibrary(*D2GFX_hDriverModHandle);
		*D2GFX_hDriverModHandle = 0;
		*D2GFX_pfnDriverCallback = 0;
	}

	ExBuff::Clear();
	for (auto i = 0; (unsigned int) i < Controls.size(); ++i) delete Controls.at(i);
}

void OnGameLeave()
{
	fnRendererCallbacks * fns = *D2GFX_pfnDriverCallback;
	fns->ClearCaches();

	ExBuff::Clear();
	PartyUI::Clear();
	PartyUI::ClearRoster();
	LifeOrbDC6 = ManaOrbDC6 = OverLapDC6 = LifeOrbPoiDC6 = NULL;
}

NAKED void MainScreen_STUB()
{
	__asm
	{
		call MainScreen
		POP EDI
		POP ESI
		POP EBX
		ADD ESP, 0x20
		RETN
	}
}

void __stdcall Display()
{
	for (auto i = Controls.cbegin(); i != Controls.cend(); ++i) (*i)->Draw();
	Damage::OnDraw();

	D2WIN_SetTextSize(1);
}

NAKED void __fastcall ScreenHook()
{
	__asm
	{
		pushad
		call Display
		popad
		jmp Screen_Call
		ret
	}
}

void Patch_MainScreen()
{
	Patch(JUMP, "D2Launch.dll", 0x9741, (DWORD)MainScreen_STUB, 5, "Main Screen Hook");
	Patch(CALL, "D2Client.dll", 0x8211E, (DWORD)ScreenHook, 5, "Screen Hook");
	Patch(JUMP, "D2Win.dll", 0xCF20, (DWORD)OnGameLeave, 5, "On Leave Game Hook");
	Patch(JUMP, "D2Gfx.dll", -10001, (DWORD)OnExit, 5, "D2GFX_Finish Hook");
}
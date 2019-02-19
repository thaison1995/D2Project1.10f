#include "DLLmain.h"

void __fastcall Arena::ProcessKill(Game* pGame, UnitAny* pAttacker, UnitAny* pDefender)
{
	if (!pGame || !pAttacker || !pDefender)
		return;

	
}

void Arena::OnPatch()
{
	Patch(JUMP, "D2Game.dll", 0x1190, (DWORD)Arena::ProcessKill, 5, "Arena Process Kill");
}
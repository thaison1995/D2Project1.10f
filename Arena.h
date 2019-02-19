#pragma once

#ifndef _ARENA_H
#define _ARENA_H

namespace Arena
{
	void __fastcall ProcessKill(Game* pGame, UnitAny* pAttacker, UnitAny* pDefender);
	
	void OnPatch();
}

#endif
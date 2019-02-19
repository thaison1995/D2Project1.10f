#pragma once

#ifndef _LRosterData_H__
#define _LRosterData_H__

namespace LRoster
{
	void SyncClient(Game *ptGame, Client* ptClient);
	void SyncClient(Game *ptGame, DWORD UnitId, LRosterData* pRoster);
	LRosterData* Find(Game * ptGame, char* szName);
	void UpdateRoster(Game * ptGame, char * szName, BYTE Type);
	void Clear(Game * ptGame);
}

void __fastcall OnGameDestroy(Game* ptGame);
void __fastcall D2GAME_GameDestroy_STUB();

#endif
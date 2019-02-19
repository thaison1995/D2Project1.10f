#include "DLLmain.h"

void __fastcall OnGameDestroy(Game* ptGame)
{
	LRoster::Clear(ptGame);
}

NAKED void __fastcall D2GAME_GameDestroy_STUB()
{
	__asm
	{
		call FreePartyMem_I
		push ecx
		mov ecx, edi
		call OnGameDestroy
		pop ecx
		retn
	}
}

void LRoster::SyncClient(Game *ptGame, Client* ptClient)
{
	if (!ptGame || !ptClient)
		return;
	if (!(ptClient->InitStatus & 4))
		return;

	for (Client * pClientList = ptGame->ptClient; pClientList; pClientList = pClientList->ptPrevious)
	{
		if (pClientList->InitStatus & 4)
		{
			LRosterData * pRoster = LRoster::Find(ptGame, pClientList->CharName);
			if (!pRoster) continue;

			Srv2Clt::p0x66 pVKInfo = { 0x66, pClientList->pPlayerUnit->dwUnitId, 1, pRoster->Kills };
			Srv2Clt::p0x66 pVDInfo = { 0x66, pClientList->pPlayerUnit->dwUnitId, 2, pRoster->Deaths };
			Srv2Clt::p0x66 pVAInfo = { 0x66, pClientList->pPlayerUnit->dwUnitId, 3, pRoster->Assists };

			D2GAME_SendPacket(ptClient, &pVKInfo, sizeof(Srv2Clt::p0x66));
			D2GAME_SendPacket(ptClient, &pVDInfo, sizeof(Srv2Clt::p0x66));
			D2GAME_SendPacket(ptClient, &pVAInfo, sizeof(Srv2Clt::p0x66));
		}
	}
}

void LRoster::SyncClient(Game *ptGame, DWORD UnitId, LRosterData* pRoster)
{
	if (!ptGame || !pRoster) return;

	Srv2Clt::p0x66 pVKInfo = { 0x66, UnitId, 1, pRoster->Kills };
	Srv2Clt::p0x66 pVDInfo = { 0x66, UnitId, 2, pRoster->Deaths };
	Srv2Clt::p0x66 pVAInfo = { 0x66, UnitId, 3, pRoster->Assists };

	for (Client * pClientList = ptGame->ptClient; pClientList; pClientList = pClientList->ptPrevious)
	{
		if (pClientList->InitStatus & 4)
		{
			D2GAME_SendPacket(pClientList, &pVKInfo, sizeof(Srv2Clt::p0x66));
			D2GAME_SendPacket(pClientList, &pVDInfo, sizeof(Srv2Clt::p0x66));
			D2GAME_SendPacket(pClientList, &pVAInfo, sizeof(Srv2Clt::p0x66));
		}
	}
}

LRosterData * LRoster::Find(Game * ptGame, char* szName)
{
	for (LRosterData * LR = ptGame->pLRosterData; LR; LR = LR->ptNext)
	{
		if (_stricmp(LR->szName, szName) == 0) return LR;
	}
	return 0;
}

void LRoster::UpdateRoster(Game* ptGame, char * szName, BYTE Type)
{
	if (!ptGame) return;

	LRosterData *Player = LRoster::Find(ptGame, szName);
	if (!Player)
	{
		Player = (LRosterData*)FOG_AllocServerMemory(ptGame->pMemPools, sizeof(LRosterData), __FILE__, __LINE__, NULL);
		memset(Player, 0, sizeof(LRosterData));
		Player->ptNext = ptGame->pLRosterData;
		ptGame->pLRosterData = Player;
		strcpy_s(Player->szName, 16, szName);
	}
	switch (Type)
	{
		case 3: { ++Player->Assists; break; }
		case 2: { ++Player->Deaths; break; }
		case 1:	{ ++Player->Kills; break; }
	}
}

void LRoster::Clear(Game * ptGame)
{
	LRosterData * LR = ptGame->pLRosterData;
	while (LR)
	{
		LRosterData * Next = LR->ptNext;
		FOG_FreeServerMemory(ptGame->pMemPools, LR, __FILE__, __LINE__, NULL);
		LR = Next;
	}
	ptGame->pLRosterData = 0;
}
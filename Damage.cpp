#include "DLLmain.h"

#pragma pack(push, 1)
struct DamageText
{
	BYTE Type;
	int Dmg;
	DWORD timer;
	DWORD UnitID;
};
#pragma pack(pop)

vector<DamageText> DamageVector;
static const DWORD DISPLAY_TIME = 500;
int nYOffsets[] = { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

int __fastcall Damage::ReceivedPacket(Srv2Clt::p0x45* Dane)
{
	switch (Dane->Type)
	{
		case 1:
		{
			if (DamageEnabledMon == 1)
			{
				DamageText e = { 1, Dane->Amount >> 8, GetTickCount(), Dane->dwUnitId };
				DamageVector.push_back(e);
			}
		}
		break;

		case 2:
		{
			if (DamageEnabledPlayer == 1)
			{
				DamageText e = { 2, Dane->Amount >> 8, GetTickCount(), Dane->dwUnitId };
				DamageVector.push_back(e);
			}
		}
		break;
	}
	return TRUE;
}

void Damage::OnDraw()
{
	if (DamageVector.empty()) return;

	for (vector<DamageText>::iterator it = DamageVector.begin(); it != DamageVector.end(); ++it)
	{
		const int TransTable[] = { 0, 1, 2, 5 };
		switch (it->Type)
		{
		case 1:
		{
				  if (DamageEnabledMon == 1)
				  {
					  int dwRemainingTicks = (it->timer + DISPLAY_TIME) - GetTickCount();
					  if (dwRemainingTicks > 0 && it->Dmg > 0)
					  {
						  UnitAny* Unit = D2CLIENT_GetUnitById(it->UnitID, UNIT_MONSTER);
						  if (!Unit) break;

						  POINT Pos = { D2COMMON_GetUnitXOffset(Unit), D2COMMON_GetUnitYOffset(Unit) };
						  Pos.x -= *D2CLIENT_PlayerX - *D2CLIENT_ScreenXShift;
						  Pos.y -= *D2CLIENT_PlayerY + 70;

						  int nY = Pos.y - nYOffsets[dwRemainingTicks / (DISPLAY_TIME / (ARRAY_SIZE(nYOffsets) - 1))];
						  TextCenter(Pos.x, nY, DamageColorMon, DamageFontMon, (dwRemainingTicks <= 200 ? TransTable[dwRemainingTicks / 60] : 7), "%d", it->Dmg);

					  }
				  }
		}
			break;

		case 2:
		{
				  if (DamageEnabledPlayer == 1)
				  {
					  int dwRemainingTicks = (it->timer + DISPLAY_TIME) - GetTickCount();
					  if (dwRemainingTicks > 0 && it->Dmg > 0)
					  {
						  POINT Pos = { D2COMMON_GetUnitXOffset(D2CLIENT_GetPlayerUnit()), D2COMMON_GetUnitYOffset(D2CLIENT_GetPlayerUnit()) };
						  Pos.x -= *D2CLIENT_PlayerX - *D2CLIENT_ScreenXShift;
						  Pos.y -= *D2CLIENT_PlayerY + 70;

						  int nY = Pos.y - nYOffsets[dwRemainingTicks / (DISPLAY_TIME / (ARRAY_SIZE(nYOffsets) - 1))];
						  TextCenter(Pos.x, nY, DamageColorPlayer, DamageFontPlayer, (dwRemainingTicks <= 200 ? TransTable[dwRemainingTicks / 60] : 7), "%d", it->Dmg, 0);
					  }
				  }
		}
			break;
		}
	}
}

void __fastcall Damage::SendPacket0x45(DamageData* pDmg, UnitAny* UnitId, UnitAny* pUnit, int Type)
{
	Client* pClient = pUnit->pPlayerData->ptNetClient;
	if (!pClient) return;

	Srv2Clt::p0x45 aPacket;
	memset(&aPacket, 0, sizeof(aPacket));

	int Dmg = pDmg->dwDmgTotal;

	if (Dmg > 0)
	{
		aPacket.P_45 = 0x45;
		aPacket.Type = Type;
		aPacket.dwUnitId = UnitId->dwUnitId;
		aPacket.Amount = pDmg->dwDmgTotal;

		D2GAME_SendPacket(pClient, &aPacket, sizeof(Srv2Clt::p0x45));
	}
}

void __fastcall Damage::Assist(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender)
{
	if (D2COMMON_GetUnitStat(pDefender, STATS_HP, 0) <= 0)
	{
		if ((GetTickCount() - pDefender->pPlayerData->LastDamageTick < 5000) && pDefender->pPlayerData->LastDamageId != 0 && pDefender->pPlayerData->LastDamageId != pAttacker->dwUnitId)
		{
			UnitAny* pAssister = D2GAME_FindUnit(pAttacker->ptGame, UNIT_PLAYER, pDefender->pPlayerData->LastDamageId);
			if (pAssister)
			{
				LRoster::UpdateRoster(pAttacker->ptGame, pAssister->pPlayerData->name, 3);
				LRosterData * AssRoster = LRoster::Find(pAttacker->ptGame, pAssister->pPlayerData->name);
				if (AssRoster) LRoster::SyncClient(pAttacker->ptGame, pDefender->pPlayerData->LastDamageId, AssRoster);
			}
		}
		pDefender->pPlayerData->LastDamage = 0;
		pDefender->pPlayerData->LastDamageId = 0;
		pDefender->pPlayerData->LastDamageTick = 0;
	}
	else
	{
		int Percent = ((((int)pDmg->dwDmgTotal >> 8) * 100) / (D2COMMON_GetUnitStat(pDefender, STATS_MAXHP, 0) >> 8));
		if (pDefender->pPlayerData->LastDamageTick && (GetTickCount() - pDefender->pPlayerData->LastDamageTick < 5000))
			pDefender->pPlayerData->LastDamage += Percent;
		else
			pDefender->pPlayerData->LastDamage = Percent;
		pDefender->pPlayerData->LastDamageId = pAttacker->dwUnitId;
		pDefender->pPlayerData->LastDamageTick = GetTickCount();
	}
}

void __fastcall Damage::Handler(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender, Game* pGame)
{
	if (pAttacker->dwType == UNIT_MONSTER)
	{
		UnitAny* ptOwner = D2GAME_D2GetMinonOwner(pAttacker);
		if (ptOwner != NULL && ptOwner->dwType == UNIT_PLAYER)
			pAttacker = ptOwner;
	}

	if (pDefender->dwType)
		return;

	if (pAttacker->dwType == UNIT_PLAYER)
		LRoster::UpdateRoster(pGame, pAttacker->pPlayerData->name, 1);
	LRoster::UpdateRoster(pGame, pDefender->pPlayerData->name, 2);

	if (pAttacker->dwType == UNIT_PLAYER)
	{
		LRosterData * VictimRoster = LRoster::Find(pGame, pDefender->pPlayerData->name);
		LRosterData * KillerRoster = LRoster::Find(pGame, pAttacker->pPlayerData->name);
		if (VictimRoster) LRoster::SyncClient(pGame, pDefender->dwUnitId, VictimRoster);
		if (KillerRoster) LRoster::SyncClient(pGame, pAttacker->dwUnitId, KillerRoster);
		Print(0, "[Def] Kills : %d | Deaths : %d | Assists : %d", VictimRoster->Kills, VictimRoster->Deaths, VictimRoster->Assists);
		Print(0, "[Att] Kills : %d | Deaths : %d | Assists : %d", KillerRoster->Kills, KillerRoster->Deaths, KillerRoster->Assists);

		pGame->LastKiller = pAttacker->pPlayerData->ptNetClient->ClientID;
		pGame->LastVictim = pDefender->pPlayerData->ptNetClient->ClientID;
	}

	/*if (pAttacker->dwType == UNIT_MONSTER)
	{
		UnitAny* ptParent = D2GAME_D2GetMinonOwner(pAttacker);
		if (ptParent)
		if (ptParent->dwType == UNIT_PLAYER)
			pAttacker = ptParent;
	}

	if (pAttacker->dwType == UNIT_PLAYER && pDefender->dwType == UNIT_MONSTER)
	{
		Damage::SendPacket0x45(pDmg, pDefender, pAttacker, 1);
	}
	if (pAttacker->dwType == UNIT_MONSTER && pDefender->dwType == UNIT_PLAYER)
	{
		Damage::SendPacket0x45(pDmg, pAttacker, pDefender, 2);
	}
	if (pAttacker->dwType == UNIT_PLAYER && pDefender->dwType == UNIT_PLAYER)
	{
		Damage::Assist(pDmg, pAttacker, pDefender);
	}*/
}

NAKED void __fastcall Damage::Handler_STUB(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender, int nDamage)
{
	__asm
	{
		PUSH EBP
		PUSH ESI
		MOV EDX, EBX
		MOV ECX, EDI
		CALL Damage::Handler
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		ADD ESP, 0x14
		RETN 0x0C
	}
}

void Damage::OnPatch()
{
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x45].CallBack, (DWORD)&Damage::ReceivedPacket);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x45].PacketLen, sizeof(Srv2Clt::p0x45));
	WriteDword((DWORD*)&D2NET_PacketHandler[0x45], sizeof(Srv2Clt::p0x45));
	
	Patch(JUMP, "D2Game.dll", 0x905C1, (DWORD)Damage::Handler_STUB, 10, "Dmg Handler");
}
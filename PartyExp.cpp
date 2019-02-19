#include "DLLmain.h"

struct PartyExp
{
	UnitAny *pMonster;
	UnitAny *pPartyMembers[64];
	int nPartyLevels[64];
	int nMembers;
	int nLvlSum;
};

typedef void(__fastcall * ExpCallback_t)(Game *pGame, UnitAny *pUnit, PartyExp *hParty);
D2FUNC(D2GAME, ForEachInParty, void, __fastcall, (Game* pGame, UnitAny* pPlayer, ExpCallback_t pCallback, PartyExp *hPartyExp), 0x8A190)
D2FUNC(D2GAME, GetExpGained, int, __fastcall, (Game* pGame, UnitAny* pPlayer, int PlayerLv, int MonsterLv, int PlayerExp), 0x92EC0)
D2FUNC(D2GAME, AddExp, void, __fastcall, (Game* pGame, UnitAny* pPlayer, int PlayerLvl, int ExpGained), 0x93170)
D2FUNC(D2GAME, ExpCallback, void, __fastcall, (Game *pGame, UnitAny *pUnit, PartyExp *hParty), 0x93200)
D2FUNC(D2GAME, sub_6FCBA5F0, signed __int16, __fastcall, (Game *pGame, UnitAny *pUnit), 0x8E2E5)
D2FUNC(D2GAME, sub_6FCCF320, UnitAny*, __fastcall, (UnitAny *pUnit), 0x9F320)//__thiscall
D2FUNC(D2GAME, sub_6FC7E8B0, UnitAny*, __fastcall, (Game *pGame, UnitAny *pUnit, int, int), 0x4E8B0)
D2FUNC(D2GAME, sub_6FCBBB00, UnitAny*, __fastcall, (Game *pGame, int, int), 0x8BB00)
D2FUNC(D2GAME, sub_6FCC3360, void, __fastcall, (Game*, UnitAny*, UnitAny*, int, int), 0x93360)
D2FUNC(D2GAME, GetUnitX, int, __fastcall, (UnitAny* ptUnit), 0x3510)
D2FUNC(D2GAME, GetUnitY, int, __fastcall, (UnitAny* ptUnit), 0x3540)

D2FUNC(D2COMMON, GetOwnerType, int, __stdcall, (StatList*), -10471)
D2FUNC(D2COMMON, GetOwnerGUID, int, __stdcall, (StatList*), -10472)
D2FUNC(D2COMMON, GetStatListFromUnitAndFlag, StatList*, __stdcall, (UnitAny *pUnit, int nFlag), -10481)
D2FUNC(D2COMMON, CheckStateMaskExpOnUnit, BOOL, __stdcall, (UnitAny *pUnit), -10552)
D2FUNC(D2COMMON, GetStatSigned, int, __stdcall, (UnitAny *ptUnit, int nStat, int nLayer), -10519)

signed __int16 __fastcall sub_6FCBE2D0(Game *pGame, UnitAny *pPlayer)
{
	if ( pPlayer && pGame != 0 && !pPlayer->dwType )
		return D2GAME_sub_6FCBA5F0(pGame, pPlayer);
	else
		return -1;
}

void __fastcall ExpCallback(Game *pGame, UnitAny *pUnit, PartyExp *hParty)
{
	if (pUnit && !((pUnit->dwFlags) & UNITFLAG_DEAD))
	if ((pUnit->dwType == UNIT_MONSTER && pUnit->dwMode != NPC_MODE_DEATH && pUnit->dwMode != NPC_MODE_DEAD) ||
		(pUnit->dwType == UNIT_PLAYER && pUnit->dwMode != PLAYER_MODE_DEATH && pUnit->dwMode != PLAYER_MODE_DEAD))
	{

		UnitAny* pMonster = hParty->pMonster;
		int mX = D2GAME_GetUnitX(pMonster);
		int mY = D2GAME_GetUnitY(pMonster);

		int pX = D2GAME_GetUnitX(pUnit);
		int pY = D2GAME_GetUnitY(pUnit);

		if (GetRange(pX, pY, mX, mY) > 6400 && 6400 != -1) return;

		int nMembers = hParty->nMembers;
		if (nMembers > 64)
		{
			D2ERROR("nMember > 64")
		}
		hParty->pPartyMembers[nMembers] = pUnit;
		hParty->nPartyLevels[nMembers] = D2COMMON_GetStatSigned(pUnit, 12, 0);
		hParty->nLvlSum += hParty->nPartyLevels[nMembers];
		hParty->nMembers++;
		return;
	}
}

void __fastcall PartyExpShare(Game* pGame, UnitAny* pPlayer, UnitAny* pMonster)
{
	UnitAny *pPlayer_1; // esi@1
	UnitAny *pMonster_1; // edi@2
	UnitAny *v6; // ebp@8
	int v8; // esi@13
	int v9; // eax@13
	UnitAny *v10; // eax@18
	UnitAny *pPlayer_3; // edi@18
	int PlayerLvl_1; // ebp@19
	int Gain; // eax@19
	int PlayerLvl; // ebp@22
	int PLvl; // ebp@27
	UnitAny *pMember; // edi@27
	int ExpGained; // eax@27
	int v19; // eax@29
	int PlayerExp; // [sp+50h] [bp-58h]@5
	int MonsterLvl; // [sp+54h] [bp-54h]@18
	UnitAny *pPlayer_2; // [sp+58h] [bp-50h]@1
	PartyExp hPartyExp; // [sp+5Ch] [bp-4Ch]@23

	pPlayer_1 = pPlayer;
	pPlayer_2 = pPlayer;

	if (!pPlayer)
		return;

	pMonster_1 = pMonster;

	if (!pMonster || pPlayer->dwType && pPlayer->dwType != 1 )
		return;

	PlayerExp = D2COMMON_GetUnitBaseStat(pMonster, 13, 0);
	if (PlayerExp <= 0)
		return;

	if (pPlayer_1->dwType)
	{
		if (pPlayer_1->dwType != 1)
			return;

		v6 = D2GAME_sub_6FCCF320(pPlayer_1);
		StatList* pStatList = 0;
		if (D2COMMON_CheckStateMaskExpOnUnit(pPlayer_1))
			pStatList = D2COMMON_GetStatListFromUnitAndFlag(pPlayer_1, 2048);
		if (D2COMMON_CheckStateMaskExpOnUnit(pMonster))
			pStatList = D2COMMON_GetStatListFromUnitAndFlag(pMonster, 2048);
		if (pStatList)
		{
			v8 = D2COMMON_GetOwnerType(pStatList);
			v9 = D2COMMON_GetOwnerGUID(pStatList);
			v6 = D2GAME_sub_6FCBBB00(pGame, v8, v9);
		}
		if (!v6 || v6->dwType)
		  return;

		pMonster_1 = pMonster;
		pPlayer_1 = v6;
	}
	if (!pPlayer_1)
		return;

	MonsterLvl = D2COMMON_GetUnitBaseStat(pMonster_1, 12, 0);

	v10 = D2GAME_sub_6FC7E8B0(pGame, pPlayer_1, 7, 0);
	pPlayer_3 = v10;
	if (v10)
	{
		PlayerLvl_1 = D2COMMON_GetUnitBaseStat(v10, 12, 0);
		Gain = D2GAME_GetExpGained(pGame, pPlayer_3, PlayerLvl_1, MonsterLvl, PlayerExp);
		if (pPlayer_2 != pPlayer_3)
			Gain = 86 * Gain / 256;
		D2GAME_sub_6FCC3360(pGame, pPlayer_1, pPlayer_3, PlayerLvl_1, Gain);
	}

	PlayerLvl = D2COMMON_GetUnitBaseStat(pPlayer, 12, 0);
	if (sub_6FCBE2D0(pGame, pPlayer) == -1)
		goto LABEL_32;

	memset(&hPartyExp, 0, sizeof(hPartyExp));
	hPartyExp.pMonster = pMonster;
	D2GAME_ForEachInParty(pGame, pPlayer, &ExpCallback, &hPartyExp);
	if (hPartyExp.nMembers <= 0 || hPartyExp.nLvlSum <= 0 )
		return;

	if (hPartyExp.nMembers == 1)
	{
	LABEL_32:
		v19 = D2GAME_GetExpGained(pGame, pPlayer_1, PlayerLvl, MonsterLvl, PlayerExp);
		D2GAME_AddExp(pGame, pPlayer_1, PlayerLvl, v19);
		return;
	}
	int i = 0;
	for (float pPlayer_2a = (float)(PlayerExp + 89 * PlayerExp * (hPartyExp.nMembers - 1) / 256) / (float)hPartyExp.nLvlSum;
		i < hPartyExp.nMembers;
		++i)
	{
		PLvl = hPartyExp.nPartyLevels[i];
		pMember = hPartyExp.pPartyMembers[i];
		ExpGained = D2GAME_GetExpGained(pGame, pMember, PLvl, MonsterLvl, (signed __int64)((double)hPartyExp.nPartyLevels[i] * pPlayer_2a));
		D2GAME_AddExp(pGame, pMember, PLvl, ExpGained);

	}
}

int __fastcall EXPFormula(int nPlayers)
{
	return 50 * (nPlayers - 1);
}

int __fastcall HPFormula(int nPlayers)
{
	return 50 * ((nPlayers > 16 ? 16 : nPlayers) - 1);
}

NAKED void __fastcall D2GAME_SendKillsNULL_STUB()
{
	__asm
	{
		ret 4
	}
}

void D2PartyExp::OnPatch()
{
	V_SetPlayers = 64;

	Patch(0, "D2Client.dll", 0xCB05, sizeof(Game), 4, "Extend Game Struct");
	Patch(CUSTOM, "D2Common.dll", 0x8037C + 1, sizeof(PlayerData), 4, "Extend PlayerData Struct");
	Patch(CUSTOM, "D2Common.dll", 0x80388 + 1, (sizeof(PlayerData) / 4), 4, "Extend PlayerData Struct");

	Patch(JUMP, "D2Game.dll", 0xF5E0, (DWORD)D2GAME_SendKillsNULL_STUB, 8, "Null Original S->C 0x66");
	Patch(CALL, "D2Game.dll", 0x74EC, (DWORD)D2GAME_GameDestroy_STUB, 5, "Game Destroy Wrapper");

	//Patch(CALL, "D2Game.dll", 0xAF897, (DWORD)EXPFormula, 5, "Exp Increase Fix");
	//Patch(JUMP, "D2Game.dll", 0xAF5F0, (DWORD)HPFormula, 5, "Hp Increase Fix");

	//UnitNodes::OnPatch();

	Patch(CUSTOM, "D2Multi.dll", 0x10903, V_SetPlayers + 1, 1, "Player Count Set I");
	Patch(CUSTOM, "D2Multi.dll", 0x10F3B, V_SetPlayers, 1, "Player Count Set II");
	Patch(CUSTOM, "D2Multi.dll", 0x1123A, V_SetPlayers, 1, "Player Count Set III");
	Patch(CUSTOM, "D2Multi.dll", 0x1124A, V_SetPlayers, 1, "Player Count Set IV");
	Patch(CUSTOM, "D2Multi.dll", 0x1124E, V_SetPlayers, 1, "Player Count Set V");

	Patch(CUSTOM, "D2Client.dll", 0x9F321, V_SetPlayers, 1, "Player Count Set VI");
	Patch(CUSTOM, "D2Client.dll", 0x62102, V_SetPlayers, 1, "Player Count Set VII");
	Patch(CUSTOM, "D2Client.dll", 0x9F302, V_SetPlayers, 1, "Player Count Set VI");

	Patch(JUMP, "D2Game.dll", 0x92C70, (DWORD)PartyExpShare, 5, "Party Exp formula Fix");
}

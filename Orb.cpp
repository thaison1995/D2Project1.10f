#include "DLLmain.h"

#pragma pack(push, 1)
struct OrbTxt
{
	char Class[16];
	char LifeDir[255];
	char LifePoiDir[255];
	char ManaDir[255];
	char OverLapDir[255];
};
#pragma pack(pop)

OrbTxt* pOrbTxt;
DWORD pOrbRecs;

void Orb::LoadTXT()
{
	BINField OrbTxtTable[] =
	{
		{ "Class",					FIELDTYPE_DATA_ASCII,	15,		offsetof(OrbTxt, Class),			0 },
		{ "CellFile Life",			FIELDTYPE_DATA_ASCII,	254,	offsetof(OrbTxt, LifeDir),			0 },
		{ "CellFile Life Poison",	FIELDTYPE_DATA_ASCII,	254,	offsetof(OrbTxt, LifePoiDir),		0 },
		{ "CellFile Mana",			FIELDTYPE_DATA_ASCII,	254,	offsetof(OrbTxt, ManaDir),			0 },
		{ "CellFile OverLap",		FIELDTYPE_DATA_ASCII,	254,	offsetof(OrbTxt, OverLapDir),		0 },
		{ "end",					FIELDTYPE_DATA_NULL,	0,		sizeof(OrbTxt),						0 },
	};

	pOrbTxt = (OrbTxt*)D2COMMON_CompileTxt(NULL, "Orb", OrbTxtTable, &pOrbRecs, sizeof(OrbTxt));
	D2ASSERT(pOrbTxt, "Error Opening File Orb.txt");
}

void Orb::FreeTXT()
{
	if (pOrbTxt)
	{
		FOG_FreeClientMemory(pOrbTxt, __FILE__, __LINE__, 0);
		pOrbTxt = NULL;
	}
}

void Orb::OnDraw()
{
	int x = *D2CLIENT_ScreenWidth;
	int y = *D2CLIENT_ScreenHeight;
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	char szBuffer[256] = {};
	DWORD StatePoion = D2COMMON_GetUnitState(pPlayer, STATE_POISON);

	int nPosX = x - 120;
	int nPosY = y + 5;

	
	for (DWORD i = 0; i < pOrbRecs; i++)
	{
		if (pPlayer->dwTxtFileNo == GetClass(pOrbTxt[i].Class))
		{
			int LifeSize = CalcPercent((D2COMMON_GetUnitStat(pPlayer, STATS_HP, 0) >> 8), (D2COMMON_GetUnitStat(pPlayer, STATS_MAXHP, 0) >> 8));

			//Life
			if (LifeOrbDC6 == NULL)
			{
				sprintf(szBuffer, "data\\global\\ui\\Orb\\%s", pOrbTxt[i].LifeDir);
				LifeOrbDC6 = D2CLIENT_LoadCellFile(szBuffer, CELLFILETYPE_DC6);
			}

			if (LifeOrbPoiDC6 == NULL)
			{
				sprintf(szBuffer, "data\\global\\ui\\Orb\\%s", pOrbTxt[i].LifePoiDir);
				LifeOrbPoiDC6 = D2CLIENT_LoadCellFile(szBuffer, CELLFILETYPE_DC6);
			}

			CellContext CellLife = {};
			CellLife.pCellFile = StatePoion ? LifeOrbPoiDC6 : LifeOrbDC6;
			CellLife.nFrame = (GetTickCount() >> 6) % LifeOrbDC6->numcells;

			D2GFX_DrawVerticalCropImage(&CellLife, 0, nPosY, 0, LifeSize, DRAWMODE_NORMAL);

			//Mana
			int ManaSize = CalcPercent((D2COMMON_GetUnitStat(pPlayer, STATS_MANA, 0) >> 8), (D2COMMON_GetUnitStat(pPlayer, STATS_MAXMANA, 0) >> 8));
			
			if (ManaOrbDC6 == NULL)
			{
				sprintf(szBuffer, "data\\global\\ui\\Orb\\%s", pOrbTxt[i].ManaDir);
				ManaOrbDC6 = D2CLIENT_LoadCellFile(szBuffer, CELLFILETYPE_DC6);
			}

			CellContext CellMana = {};
			CellMana.pCellFile = ManaOrbDC6;
			CellMana.nFrame = (GetTickCount() >> 6) % ManaOrbDC6->numcells;

			D2GFX_DrawVerticalCropImage(&CellMana, nPosX, nPosY, 0, ManaSize, DRAWMODE_NORMAL);

			//OverLap
			if (OverLapDC6 == NULL)
			{
				sprintf(szBuffer, "data\\global\\ui\\Orb\\%s", pOrbTxt[i].OverLapDir);
				OverLapDC6 = D2CLIENT_LoadCellFile(szBuffer, CELLFILETYPE_DC6);
			}

			CellContext OverLap = {};
			OverLap.pCellFile = OverLapDC6;

			//Life
			OverLap.nFrame = 0;
			D2GFX_DrawCellContext(&OverLap, 0, nPosY, -1, 5, 0);

			//Mana
			OverLap.nFrame = 1;
			D2GFX_DrawCellContext(&OverLap, nPosX, nPosY, -1, 5, 0);
		}
	}
}

void Orb::OnPatch()
{
	Patch(JUMP, "D2Client.dll", 0x5F9D0, (DWORD)OnDraw, 5, "Orb Draw Life");
	Patch(JUMP, "D2Client.dll", 0x5FB60, (DWORD)OnDraw, 5, "Orb Draw Mana");
}
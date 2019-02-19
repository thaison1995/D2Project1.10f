#pragma once

#ifndef _D2STRUCTS_H
#define _D2STRUCTS_H

#include <string>
#include "D2DataTables.h"
#pragma pack(1)

struct UnitAny;
struct CellContext;
struct BINField;
struct D2PacketTable;
struct Skill;
struct DamageData;
struct Client;
struct Game;
struct UnitNode;
struct StatList;
struct RosterUnit;
struct Path;
struct Room1;
struct Room2;

struct BnetData
{
	DWORD dwId;					//0x00
	DWORD dwId2;				//0x04
	DWORD _1[3];				//0x08
	DWORD dwId3;				//0x14
	WORD Unk3;					//0x18
	char szGameName[22];		//0x1A
	char szGameIP[16];			//0x30
	DWORD _2[16];				//0x40
	DWORD dwId4;				//0x80
	DWORD _3;					//0x84
	char szAccountName[48];		//0x88
	char szPlayerName[24];		//0xB8
	char szRealmName[8];		//0xD0
	BYTE _4[273];				//0xD8
	BYTE nCharClass;			//0x1E9
	BYTE nCharFlags;			//0x1EA
	BYTE nMaxDiff;				//0x1EB
	BYTE _5[31];				//0x1EC
	BYTE nDifficulty;			//0x20B
	void *_6;					//0x20C
	DWORD _7[5];				//0x210
	WORD _8;					//0x224
	BYTE _9;					//0x226
	char szRealmName2[24];		//0x227
	char szGamePass[24];		//0x23F
	char szGameDesc[256];		//0x257
	WORD _10;					//0x348
	BYTE _11;					//0x34B
};

struct RosterInfo
{
	DWORD dwUnitId;
	DWORD fFlags;  //0x02 - ignore, 0x04 - squelch, 0x08 hostile
	RosterInfo *ptNext;
};

//struct RosterInfo								//sizeof 0x14  
//{
//	DWORD                    dwUnitId;					// +00
//	union
//	{
//		struct
//		{
//			DWORD			fLoot : 1;
//			DWORD			fNoHear : 1;
//			DWORD			fSquelched : 1;
//			DWORD			fHostile : 1;
//		}fStatusFlags;                               // +04
//		DWORD				fFlags;
//	};
//	DWORD					dwHostileTimestamp;		// +08
//	union
//	{
//		struct
//		{
//			DWORD			fInParty : 1;
//			DWORD			fInvitedYou : 1;
//			DWORD			fYouInvited : 1;
//		}fPartyStatus;                               // +0C
//		DWORD				fStatus;
//	};
//	RosterInfo*          ptNext;					// +10
//};

struct RosterUnit
{
	char szName[16];				//0x00
	DWORD dwUnitId;					//0x10
	DWORD dwPartyLife;				//0x14
	DWORD _1;						//0x18
	DWORD dwClassId;                //0x1C
	WORD wLevel;					//0x20
	WORD wPartyId;  				//0x22
	DWORD dwLevelId;                //0x24
	DWORD Xpos;						//0x28
	DWORD Ypos;						//0x2C
	DWORD dwPartyFlags;				//0x30
	RosterInfo** ptInfo;			//0x34
	void* pMinions;					//0x38
	DWORD dwSrcPortalGUID;			//0x3C
	DWORD dwDstPortalGUID;			//0x40
	WORD __44;						//0x44
	char szClanTag[4];				//0x46
	BYTE __04A[28];					//0x4A
	char szName2[16];				//0x66
	WORD _8;						//0x76
	DWORD _9[2];					//0x78
	RosterUnit* pNext;				//0x80
};

struct D2Seed
{
	DWORD nLowSeed;
	DWORD nHiSeed;
};

struct UnitNode
{
	UnitAny* pUnit;        //0x00
	DWORD dwArg;        //0x04
	UnitNode* pNext;    //0x08
	UnitNode* pPrev;    //0x0C
};
struct LRosterData
{
	char szName[16];
	int Assists;
	int Kills;
	int Deaths;
	LRosterData *ptNext;
};

struct LSpectator
{
	DWORD WatcherUID;
	DWORD UnitUID;
	LSpectator *pNext;
	LSpectator *pPrev;
};

struct PlayerObservation
{
	DWORD ObservatorId;
	DWORD UnitId;
};

struct Game
{
	DWORD _1[3];				//0x00
	DWORD * ptGameData8;		//0x0C
	Game * pNext;				//0x10
	DWORD _1c;					//0x14
	CRITICAL_SECTION* ptLock;	//0x18
	union
	{
		DWORD  pMemPool;		//0x1C - not used, always NULL
		void * pMemPools;		//0x1C - not used, always NULL
	};
	void * pGameData;			//0x20
	DWORD _2;					//0x24
	WORD  wServerToken;			//0x28 called 'Server Ticket' aswell
	char szGameName[16];		//0x2A
	char szGamePass[16];		//0x3A
	char szGameDesc[32];		//0x4A
	BYTE bGameType;				//0x6A - whenever this is single player (etc)
	BYTE _3a[2];				//0x6B _3a[0] - Arena's _2;
	BYTE difficultyLevel;		//0x6D
	BYTE _4[2];					//0x6E
	DWORD LODFlag;				//0x70
	DWORD dwGameType;			//0x74
	WORD  wItemFormat;			//0x78
	WORD  _5;					//0x7A
	DWORD InitSeed;				//0x7C
	DWORD ObjSeed;				//0x80 - seed used for object spawning
	DWORD InitSeed2;			//0x84 (another instance, dunno why)
	Client * ptClient;			//0x88 - (pClient structure of last player that entered the game)
	DWORD nClients;				//0x8C
	DWORD nUnits[6];			//0x90 - array of 6 counters, one for each unit type, this is the next GUID used too
	DWORD GameFrame;			//0xA8 - the current frame of the game, used for timers (buff duration etc)
	DWORD _6[3];				//0xAC
	void* pTimerQueue;	//0xB8 a queue of all current active and inactive timers
	void * pDrlgAct[5];			//0xBC
	union {
		DWORD GameSeed[2];				//0xD0
		__int64 GameSeed64;				//0xD0
		D2Seed hSeed;					//0xD0
	};
	void* pDrlgRoomList[5];		//0xD8
	DWORD dwMonSeed;			//0xEC - seed used for monster spawning
	void* pMonsterRegion[1024];//0xF0 - one pointer for each of the 1024 possible levels
	void* pObjectRegion;		//0x10F0 - a controller holding all object region structs
	void* pQuestControl;//0x10F4 - a controller holding all quest info
	UnitNode* pUnitNodes[10];	//0x10F8 - ten lists of unit node lists, this is used by the AI target seeking code (and other stuff)
	UnitAny* pUnitList[5][128];	//0x1120 - 5 lists of 128 lists of units (see pUnit documentation), second index is GUID & 127, BEWARE: since ever, missiles are array #4 and items are array #3 (so type3=index4 and type4=index3)
	DWORD* pTileList;			//0x1B20 - a list for all VisTile units
	DWORD dwUniqueFlags[128];	//0x1B24 - 128 DWORDS worth of flags that control if a unique item got spawned [room for 4096]
	void* pNpcControl;		//0x1D24 - a controller holding all npc info (like store inventories, merc list)
	void * pArenaControl;//0x1D28 - a controller for arena stuff, functional and also used in game init
	void* pPartyControl;//0x1D2C - a controller for all party related stuff
	BYTE nBossFlagList[64];		//0x1D30 - 64 bytes for handling 512 super unique monsters (if they were spawned etc)
	DWORD dwMonModeData[17];	//0x1D70 - related to monsters changing mode
	DWORD nMonModeData;			//0x1DB4 - counter related to the above
	DWORD _7;					//0x1DB8
	DWORD nCreateTick;			//0x1DBC
	DWORD _8;					//0x1DC0
	DWORD nSyncTimer;			//0x1DC4 - used to sync events
	DWORD _9[8];				//0x1DC8
	BOOL bKilledBaal;			//0x1DE8 - killed uber baal
	BOOL bKilledDia;			//0x1DEC - killed uber diablo
	BOOL bKilledMeph;			//0x1DF0 - killed uber mephisto
	//Additions to original struct
	LRosterData *pLRosterData;	//0x1DF4 added by me
	DWORD dwKillCount;			//0x1DF8 
	DWORD dwGameState;			//0x1DFC 
	UnitNode* pNewNodes[130];	//0x1E00
	DWORD LastKiller;				//0x2018
	DWORD LastVictim;				//0x201C
};

struct Client
{
	DWORD ClientID;                 //0x00 
	DWORD InitStatus;			   //0x04 Flag 0x4 - player is in game
	WORD ClassId;                   //0x08 Something with Arena, also could be equivalent of ClassId
	union {								//+0A
		WORD	PlayerStatus;
		struct {
			WORD f1 : 1;
			WORD f2 : 1;
			WORD isHardCoreGame : 1;
		};
	};
	BYTE ClassId2;				   //0x0C
	char CharName[16];			   //0x0D 
	char AccountName[16];		   //0x1D 
	BYTE _3[51];                    //0x2D 
	DWORD _3b;					   //0x60
	DWORD _4;		               //0x64
	void* pGameData;				   //0x68
	DWORD _5[64];                   //0x6C 
	DWORD UnitType;				   //0x16C
	DWORD UnitId;                   //0x170
	UnitAny* pPlayerUnit;           //0x174
	DWORD _6;	                   //0x178 some bool
	void * ptSaveFile;			   //0x17C
	DWORD nOpenSize;				   //0x180
	size_t nSaveCurrentSize;        //0x184
	size_t nFileSize;               //0x188
	void * pSavePacketList;         //0x18C D2PacketListStrc
	DWORD _190[2];                  //0x190
	int nAttachedUnitType;          //0x198
	DWORD dwAttachedUnitGUID;       //0x19C
	DWORD _1A0[2];                  //0x1A0
	Game * pGame;				   //0x1A8 
	DWORD ActNo;					   //0x1AC
	DWORD _8;	                   //0x1B0
	Room1 * ptRoom;				   //0x1B4
	PacketData* Packet[3];		   //0x1B8
	DWORD _10[132];				   //0x1C4
	DWORD dwFlags;				   //0x3D4
	DWORD LastPacketTime;		   //0x3D8 GetTickCount()
	struct
	{
		WORD SkillId;
		WORD SkillUnk;
		DWORD SkillFlags;
	} ClientHotKeys[16];  		   //0x3DC 
	DWORD bWeaponSwitch;			   //0x45C
	DWORD _11[11];				   //0x460
	DWORD InactivityTime;		   //0x48C (seconds)
	WORD CurrentLife;			   //0x490
	WORD CurrentMana;			   //0x492
	WORD CurrentStamina;			   //0x494
	BYTE LifePotionPercent;		   //0x496
	BYTE ManaPotionPercent;		   //0x497
	WORD xPos;					   //0x498
	WORD yPos;					   //0x49A
	WORD xTargetOffset;			   //0x49C send by packets 0x96, 0x95, 0x18 (last arg) its converted to BYTE
	WORD yTargetOffset;			   //0x49E like above
	DWORD BodyGold;				   //0x4A0
	DWORD CurrentExp;			   //0x4A4
	Client * ptPrevious;  			//0x4A8 
	Client * ptNextByID;				//0x4AC 
	Client * ptNextByName;			//0x4B0
	DWORD _12[19];				   //0x4B4
	DWORD SentPings;				   //0x500 Increasing every 10 secs
	DWORD bNeedToKnow;			   //0x504 u can set this true by packet 0x70
	DWORD ExpLoss;				   //0x508 its temp value, dont use
	DWORD LocaleID;				   //0x50C
	DWORD _13[2];                   //0x510 2 last elements are unused
};

struct DamageData
{
	DWORD dwHitFlags;			//0x00
	WORD wResultFlags;			//0x04
	WORD fExtra;				//0x06
	DWORD dwPhysDamage;			//0x08
	DWORD dwEnDmgPct;			//0x0C
	DWORD dwFireDamage;			//0x10
	DWORD dwBurnDamage;			//0x14
	DWORD dwBurnLen;			//0x18
	DWORD dwLtngDamage;			//0x1C
	DWORD dwMagDamage;			//0x20
	DWORD dwColdDamage;			//0x24
	DWORD dwPoisDamage;			//0x28
	DWORD dwPoisLen;			//0x2C
	DWORD dwColdLen;			//0x30
	DWORD dwFrzLen;				//0x34
	DWORD dwLifeLeech;			//0x38
	DWORD dwManaLeech;			//0x3C
	DWORD dwStamLeech;			//0x40
	DWORD dwStunLen;			//0x44
	DWORD dwAbsLife;			//0x48
	DWORD dwDmgTotal;			//0x4C
	DWORD unk0x50;				//0x50
	DWORD dwPiercePct;			//0x54
	DWORD dwDamageRate;			//0x58
	DWORD unk0x5C;				//0x5C
	DWORD dwHitClass;			//0x60
	BYTE bHitClassActiveSet;		//0x64
	char nConvType;				//0x65
	BYTE unk0x66[2];			//0x66
	DWORD dwConvPct;			//0x68
	BYTE unk0x6C[4];			//0x6C
};

struct Skill
{
	SkillsTxt* pSkillsTxt;			//0x00
	Skill* pNextSkill;				//0x04
	DWORD SkillMode;				//0x08
	DWORD _1[7];					//0x0C
	DWORD dwSkillLevel;				//0x28
	DWORD _2[2];					//0x2C
	DWORD dwFlags;					//0x30
};

struct BitBuffer // Taken from Nefarius @PhrozenKeep, thx
{
	BYTE *pBuffer;			//0x00
	DWORD bitsInBuffer;		//0x04
	DWORD bufferPos;			//0x08
	DWORD bitsAtPos;			//0x0C num bits already read or written at cur pos
	DWORD unk;				//0x10 could be a bit bucket
};

struct D2PacketTable
{
	BOOL(__fastcall *CallBack)(BYTE* aPacket);
	int PacketLen;
	BOOL(__fastcall *CallBack2)(UnitAny * ptUnit, BYTE* aPacket);
};

struct D2POINT
{
	unsigned int x;
	unsigned int y;
};

struct PlayerData //size 0x16C , copied from serverside, dunno if everything is the same on client
{
	char name[16];					//0x00
	void *ptQuest[3];			//0x10
	void *pWaypointData[3];		//0x1C
	void* ptAiGeneral;				//0x28
	DWORD _1[2];					//0x2C
	void* pArenaUnit;	//0x34 Monster
	void* pPartyData;	//0x38
	DWORD MPSourcePortalUniqueID;	//0x3C	Source Portal Unique_ID  
	DWORD MPDestPortalUniqueID;		//0x40	Destination Portal Unique_ID 
	DWORD _2;						//0x44
	DWORD dwTownPortalGUID;			//0x48 mby InactivityTime
	DWORD dwTradeTick;				//0x4C mby InactivityTime
	DWORD nTradeState;				//0x50
	DWORD _3;						//0x54
	DWORD dwAcceptTradeTick;		//0x58
	void* pTrade;					//0x5C
	DWORD _4[3];					//0x60
	DWORD dwBoughtItemId;			//0x6C
	DWORD dwRightSkill;				//0x70
	DWORD dwLeftSkill;				//0x74
	DWORD dwRightSkillFlags;		//0x78
	DWORD dwLeftSkillFlags;			//0x7C
	DWORD dwSwitchRightSkill;		//0x80
	DWORD dwSwitchLeftSkill;		//0x84
	DWORD dwSwitchRightSkillFlags;	//0x88
	DWORD dwSwitchLeftSkillFlags;	//0x8C
	DWORD _5[3];					//0x90
	Client* ptNetClient;			//0x9C
	BYTE  bTelportCount;			//0xA0
	BYTE  _7[3];					//0xA1
	DWORD dwTeleportTick;			//0xA4
	D2POINT hTeleportHistory[20];	//0xA8
	DWORD dwLastTeleportX;			//0x148 These two are set when you've been just teleported
	DWORD dwLastTeleportY;			//0x14C
	DWORD _7c;						//0x150
	DWORD _7d;						//0x154
	DWORD _7e;						//0x158
	DWORD _7f;						//0x15C
	DWORD dwHostileDelay;			//0x160
	DWORD _8;						//0x164
	DWORD GameFrame;				//0x168
	//---My additions to original struct
	DWORD LastDamage;				//0x184
	DWORD LastDamageId;				//0x188
	DWORD LastDamageTick;			//0x18C
};

struct RoomCoords // sizeof(0x20) 32 bytes of Room1+4C
{
	DWORD dwXStart;					//0x00
	DWORD dwYStart;					//0x04
	DWORD dwXSize;					//0x08
	DWORD dwYSize;					//0x0C
	WORD wTileX;					//0x10
	WORD _1b;						//0x12
	WORD wTileY;					//0x14
	WORD _2b;						//0x16
	DWORD _3;						//0x18
	DWORD _4;						//0x1C
};

struct CollMap
{
	DWORD dwPosGameX;				//0x00
	DWORD dwPosGameY;				//0x04
	DWORD dwSizeGameX;				//0x08
	DWORD dwSizeGameY;				//0x0C
	DWORD dwPosRoomX;				//0x10
	DWORD dwPosRoomY;				//0x14
	DWORD dwSizeRoomX;				//0x18
	DWORD dwSizeRoomY;				//0x1C
	WORD *pMapStart;				//0x20
	WORD *pMapEnd;					//0x22
};

struct DRLGCoords
{
	//these coords and sizes are expanded by 5
	DWORD dwSubtilesLeft;     //+00
	DWORD dwSubtilesTop;      //+04
	DWORD dwSubtilesWidth;    //+08
	DWORD dwSubtilesHeight;   //+0C
	DWORD dwTilesLeft;        //+10
	DWORD dwTilesTop;         //+14
	DWORD dwTilesWidth;       //+18
	DWORD dwTilesHeight;      //+1C
};

struct DRLGCoord	//sizeof 0x10
{
	int nXpos;		//+00
	int nYpos;		//+04
	int nWidth;		//+08
	int nHeight;	//+0C
};

struct Level
{
	//DWORD dwDrlgType;				//0x00 1 - maze, 2 - preset, 3 - wilderness
	//DWORD dwLevelFlags;				//0x04
	//DWORD _1[2];					//0x08
	//Room2 *pRoom2First;				//0x10
	//union 
	//{
	//	void* pMazeTxt;    		//     for dwDrlgType == 1 (RANDOM MAZE)
	//	void* pPreset;			//     for dwDrlgType == 2 (PRESET MAP)
	//	void* pWilderness;	//     for dwDrlgType == 3 (RANDOM AREA WITH PRESET SIZE)
	//}; // 0x14
	//DWORD _2;						//0x18
	//DWORD dwPosX;					//0x1C
	//DWORD dwPosY;					//0x20
	//DWORD dwSizeX;					//0x24
	//DWORD dwSizeY;					//0x28
	//DWORD _3[96];					//0x2C
	//Level *pNextLevel;				//0x1AC
	//DWORD _4;						//0x1B0
	//void *pMisc;					//0x1B4
	//DWORD _5[2];					//0x1B8
	//DWORD dwLevelType;				//0x1C0
	//D2Seed hSeed;					//0x1C4
	//void* pLevelPresets;		//0x1CC
	//DWORD dwLevelNo;				//0x1D0
	//DWORD _6[3];					//0x1D4
	//union {
	//	DWORD RoomCenterX[9];
	//	DWORD WarpX[9];
	//};								//0x1E0
	//union {
	//	DWORD RoomCenterY[9];
	//	DWORD WarpY[9];
	//};								//0x204
	//DWORD dwRoomEntries;			//0x228
	//DWORD _7;						//0x22C

	void*   pMisc;					//+00
	int         nLevel;					//+04
	int			nLevelType;				//+08
	int			nDRLGType;				//+0C
	DWORD		fFlags;					//+10
	D2Seed  pSeed;					//+14
	DWORD       dwStartSeed;			//+1C
	union
	{
		struct
		{
			int         nXpos;          //+20
			int         nYpos;          //+24
			int         nWidth;         //+28
			int         nHeight;        //+2C
		};

		DRLGCoord pLevelCoords;			//+20
	};
	Room2* pFirstRoomEx;			//+30
	int			nRooms;					//+34
	union
	{
		void*     pPreset;
		void*    pOutdoors;
		void* pMaze;
	};									//+38       
	void*	pCurrentMap;			//+3C
	int			nCoordLists;			//+40
};

struct Room1
{
	//Room1** pRoomsNear; 	//0x00
	//DWORD _1;				//0x04
	//void *_1s;				//0x08
	//DWORD _1b;				//0x0C
	//Room2* pRoom2;			//0x10
	//DWORD _2[2];			//0x14
	//UnitAny**pUnitChanged;	//0x1C
	//CollMap* Coll;			//0x20
	//DWORD dwRoomsNear;		//0x24
	//DWORD nPlayerUnits;		//0x28
	//void *pAct;				//0x2C
	//DWORD _4;				//0x30
	//DWORD nUnknown;			//0x34
	//DWORD _5[4];			//0x38
	//Client **pClients;		//0x48
	//RoomCoords hCoords;		//0x4C
	//D2Seed hSeed;			//0x6C
	//UnitAny* pUnitFirst;	//0x74
	//DWORD nNumClients;		//0x78
	//Room1* pRoomNext;		//0x7C

	union
	{
		struct
		{
			DWORD nSubTileXpos;					//+00
			DWORD nSubTileYpos;					//+04
			DWORD nSubTileWidth;				//+08
			DWORD nSubTileHeight;				//+0C

			DWORD nTileXpos;                  //+10
			DWORD nTileYpos;                  //+14
			DWORD nTileWidth;                 //+18
			DWORD nTileHeight;                //+1C
		};
		DRLGCoords pCoords;					//+00
	};

	void* pTileGrid;			//+20
	Room1** ppRoomsNear;				//+24
	DWORD nRoomsNear;					//+28
	UnitAny* pUnitFirst;				//+2C
	UnitAny* pUnitUpdate;			//+30
	void* pCollisionGrid;//+34
	Room2* pRoom2;				//+38
	D2Seed pSeed;					//+3C
	void* pDelete;				//+44
	DWORD fRoomFlags;					//+48
	Client** pClients;			//+4C
	int nMaxClients;					//+50
	int nClients;						//+54
	int nTileCount;						//+58
	int nAllies;						//+5C
	DWORD dw;							//+60
	DWORD dwCurrentDeathIndex;			//+64
	DWORD pLastDeadGUIDs[4];			//+68 / +6C / +70 / +74
	UnitAny* pUnits;					//+78		
	Room1* pNext;					//+7C
};

struct Room2//D2RoomExStrc
{
	Level* pLevel;							//+00
};

struct Path
{
	WORD xOffset;					//0x00
	WORD xPos;						//0x02
	WORD yOffset;					//0x04
	WORD yPos;						//0x06
	DWORD xUnknown;					//0x08  16 * (wInitX - wInitY) <- Mby AutomapX
	DWORD yUnknown;					//0x0C  8 * (wInitX + wInitY + 1) <- Mby AutoampY
	WORD xTarget;					//0x10
	WORD yTarget;					//0x12
	DWORD _2[2];					//0x14
	Room1 *pRoom1;					//0x1C
	Room1 *pRoomUnk;				//0x20
	DWORD _3[3];					//0x24
	UnitAny*pUnit;					//0x30
	DWORD dwFlags;					//0x34
	DWORD _4;						//0x38
	DWORD dwPathType;				//0x3C
	DWORD dwPrevPathType;			//0x40
	DWORD dwUnitSize;				//0x44
	DWORD _5[2];					//0x48
	DWORD dwCollisionFlag;			//0x50  0x1804 <- bFlying, 0x3401 <- bOpenDoors, 0x3C01 <- Cannot Open Doors, 0x804 <- Ghost, 0x1C09 <- Player
	DWORD _5d;						//0x54
	UnitAny*pTargetUnit;			//0x58
	DWORD dwTargetType;				//0x5C
	DWORD dwTargetId;				//0x60
	BYTE bDirection;				//0x64
};

struct UnitAny
{
	DWORD	dwType;					//+00	
	DWORD	dwTxtFileNo;			//+04
	DWORD	nUnitId;				//+08
	DWORD	dwUnitId;				//+0C		
	DWORD	dwMode;					//+10
	union
	{
		PlayerData*		pPlayerData;
		void*	pMonsterData;
		void*		pObjectData;
		void*	pMissileData;
		void*		pItemData;
	};								//+14
	DWORD	dwAct;					//+18
	void*	pAct;					//+1C
	D2Seed	Seed;					//+20
	DWORD	dwInitSeed;				//+28
	union
	{
		Path*	pPath;
		void*	pStaticPath;
		void*	pItemPath;
		void*	pObjectPath;
	};								//+2C
	void*		pAnimSeq;           //+30
	DWORD		dwSeqFrameCount;    //+34
	DWORD		dwSeqFrame;         //+38
	DWORD		dwSeqAnimRate;      //+3C
	DWORD		dwSeqMode;          //+40
	DWORD		dwGfxFrame;			//+44
	DWORD		dwFrameRemain;		//+48
	WORD		wFrameRate;			//+4C
	WORD		actionFlag;			//+4E
	void*ptAnimData;		//+50 //D2AnimDataStrc*
	void*	pGfxInfo;			//+54
	DWORD		dwOutlineFrame;		//+58
	union
	{
		StatList*	pStatList;
		void* pStatsEx;
	};								//+5C
	void*	pInventory;			//+60
	union
	{
		struct                                  //Server Unit
		{
			DWORD	 dwInteractGUID;            //0x064
			DWORD	 dwInteractType;            //0x068
			WORD	 nInteract;                 //0x06C
			WORD	 nUpdateType;               //0x06E
			UnitAny* pUpdateUnit;               //0x070
			void* pQuestEventList;       //0x074
			BOOL	 bSparkChest;               //0x078
			void*	 pTimerArgs;				//0x07C //TimerArg
			Game*	 ptGame;                    //0x080
			DWORD	 __084[3];                  //0x084
			void*	 pSrvTimerList;				//0x090 //Timer
		};

		struct                                  //Client Unit
		{
			void*	pLight;                     //0x064
			DWORD	dwStartLight;               //0x068
			int		nPaletteIndex;              //0x06C
			BOOL	bUnitSfx;                   //0x070
			DWORD	dwSfxMode;                  //0x074
			void*	pUnitSfxData;               //0x078
			DWORD	dwSfxTicks;                 //0x07C
			DWORD	dwSfxAsyncTicks;            //0x080
			DWORD	dwSfxStepTicks;             //0x084
			BOOL	bHasActiveSound;            //0x088
			WORD	nLastClickX;                //0x08C
			WORD	nLastClickY;                //0x08E
			void*	pCltTimerList;              //0x090
		};
	};
	union
	{
		struct						//Server Unit
		{
			DWORD dwOwnerType;      //0x094
			DWORD dwOwnerGUID;      //0x098
		};

		struct						//Client Unit
		{
			DWORD dwLinkType;       //0x094
			DWORD dwLinkGUID;		//0x098
		};
	};
	DWORD		dwKillerType;       //0x09C
	DWORD		dwKillerGUID;       //0x0A0
	void*		pHoverText;			//0xA4
	void*		pSkills;			//0xA8			
	void*		ptCombat;			//0xAC
	DWORD		dwLastHitClass;		//0xB0
	DWORD		unk0xB4;			//0xB4
	DWORD		dwDropItemCode;		//0xB8
	DWORD		unk0xBC[2];			//0xBC
	DWORD		dwFlags;			//0xC4
	union
	{
		DWORD		dwFlagEx;		//+C8	//flags
		struct
		{
			DWORD	ukf1 : 25;
			DWORD	isLod : 1;
		};
	};
	union							//0xCC
	{
		void* pSrvQuestData;		//Server pUnit
		void* pCltQuestData;		//Client pUnit
	};
	DWORD dwNodeIndex;				//0xD0
	DWORD dwTickCount;				//0xD4
	union							//0xD8
	{
		DWORD dwSrvTickCount;		//Server pUnit
		void* pParticleStream;		//Client pUnit		
	};
	void*		pTimer;				//0xDC
	UnitAny*	ptFirstMonster;		//0xE0
	UnitAny*	pRoomNext;			//0xE4
	UnitAny*	pListNext;			//0xE8 -> 0xD8
	void*		pMsgFirst;			//0xEC
	void*		pMsgLast;			//0xF0
};

struct GfxCell
{
	DWORD flags;					//0x00
	DWORD width;					//0x04
	DWORD height;					//0x08
	DWORD xoffs;					//0x0C
	DWORD yoffs;					//0x10
	DWORD _2;						//0x14
	DWORD lpParent;					//0x18
	DWORD length;					//0x1C
	BYTE cols;						//0x20
};

struct CellFile
{
	DWORD dwVersion;				//0x00
	struct {
		WORD dwFlags;
		BYTE mylastcol;
		BYTE mytabno : 1;
	};								//0x04
	DWORD eFormat;					//0x08
	DWORD termination;				//0x0C
	DWORD numdirs;					//0x10
	DWORD numcells;					//0x14
	GfxCell *cells[1];				//0x18
};

struct CellContext
{
	GfxCell* pCellInit;    //+00
	CellFile* pCellFile;   //+04
	union                //+08
	{
		DWORD nCellNo;
		DWORD nFrame;
	};
	DWORD nDirection;            //+0C
	int nMaxDirections;            //+10
	int nMaxFrames;                //+14
	DWORD fFlags;                //+18
	BYTE fState;                //+1C
	union
	{
		BYTE nComponent;            //+1D
		BYTE fItemFlags;            //+1D
	};
	BYTE bUnk1E;                //+1E - padding no doubt
	BYTE bUnk1F;                //+1F
	int nUnitType;                //+20
	int nUnitIndex;                //+24
	int nMode;                    //+28
	int nOverlay;                //+2C
	union
	{
		// [token][component][type][mode][hitclass]
		struct
		{
			DWORD dwToken;                //+30
			DWORD dwComponent;            //+34
			DWORD dwArmorType;            //+38 - lit, med , hvy
			DWORD dwMode;                //+3C
			DWORD dwHitClass;            //+40
		};
		DWORD dwName[5];                //+30
	};
	const char* pName;                //+44
};

struct BINField
{
	char*	fieldName;
	int		type;
	DWORD	strLength;
	DWORD	offset;
	void*	lookup;
};

struct Stat
{
	union
	{
		struct
		{
			WORD	nParam;			//+00   
			WORD	nStat;			//+02
		};
		DWORD		dwStat;         //+00
	};

	DWORD			nValue;			//+04
};

struct StatEx	//size 0x8
{
	Stat* pStat;					//0x00 An Array[wStatCount]
	WORD wStatCount;				//0x04
	WORD wnBitSize;					//0x06
};

struct StatList //0x40
{
	UnitAny* pMemPool;					//0x00
	UnitAny* pUnit;					//0x04
	DWORD dwOwnerType;				//0x08
	DWORD dwOwnerId;				//0x0C
	DWORD dwFlags;					//0x10
	DWORD dwStateNo;				//0x14
	DWORD ExpireFrame;				//0x18
	DWORD SkillNo;					//0x1C
	DWORD sLvl;						//0x20
	StatEx Stats;					//0x24
	StatList *pPrevLink;			//0x2C
	StatList *pNextLink;			//0x30
	StatList *pPrev;				//0x34
	void *fpStatRemove;				//0x38
	StatList *pNext;				//0x3C
};

struct DT1SubBlock
{
	WORD xPos;						//0x00
	WORD yPos;						//0x02
	WORD _1;						//0x04
	BYTE gridX;						//0x06
	BYTE gridY;						//0x07
	WORD wTileFormat;				//0x08
	DWORD dwSubLength;				//0x0A
	WORD _2;						//0x0E
	DWORD* pDataOffset;				//0x10
};

struct TileContext // *.dt1
{
	DWORD dwDirection;				//0x00
	WORD wRoofIndex;				//0x04
	BYTE bSound;					//0x06
	BYTE bAnimated;					//0x07
	DWORD dwSizeY;					//0x08
	DWORD dwSizeX;					//0x0C
	DWORD dwZeros1;					//0x10
	DWORD dwOrientation;			//0x14
	DWORD dwMainIndex;				//0x18
	DWORD dwSubIndex;				//0x1C
	DWORD dwFrame;					//0x20
	BYTE  _1a;						//0x24 DT1's unknown_a ... 
	BYTE  _1c;						//0x25
	BYTE  _1b;						//0x26
	BYTE  _1d;						//0x27
	BYTE  bFlags[25];				//0x28 For each tile <not sure>
	BYTE  _2;						//0x39
	WORD sCacheIndex;				//0x40
	DWORD _18;						//0x44
	DWORD dwDataPtr;				//0x48 pointer to sub-block headers
	DWORD dwSize;					//0x4C length of the sub-blocks
	DWORD dwSubBlocks;				//0x50 
	DT1SubBlock* pBlocks;			//0x54
	char* szTileName;				//0x58
	DWORD **ptBlock;				//0x5C <not sure - maybe its a struct>
};

struct GFXSettings // size 0x18
{
	DWORD bPerspectiveEnable; // 0
	DWORD bPerspectiveCapable; // 1
	DWORD bLowQuality; //2
	DWORD dwGammaValue; //3
	DWORD bVSync; //4
	DWORD bBlendedShadows; // 5
};

struct GFXHelpers
{
	void(__fastcall *FillYBufferTable)(void *ppvBits, int nWidth, int nHeight, int aZero);
	void(__fastcall *DrawVisTile)(int a1, int a2, int a3);
	void(__fastcall *f3)(int a1, int a2, int a3, int a4);
	void(__fastcall *DrawGroundTile)(TileContext* tc, int xPos, int yPos, int* pLight);
	void(__fastcall *DrawWallTile)(int a1, int a2, int a3, int a4);
	void(__fastcall *DrawBlendedVisTile)(int a1, int a2, int a3, int a4);
	void(__fastcall *DrawRoofTile)(int a1, int a2, int a3, int a4, int a5);
};

struct D2RGB
{
	BYTE r;
	BYTE g;
	BYTE b;
};

struct fnRendererCallbacks
{
	BOOL(__fastcall *InitWindow)(HINSTANCE); // 0
	BOOL(__fastcall *InitPerspective)(GFXSettings* pgfxSettings, GFXHelpers* pfnHelpers); // 1
	BOOL(__fastcall *Release)(); // 2
	BOOL(__fastcall *Init)(HANDLE hWnd, int nResolution); // 3
	BOOL(__fastcall *Shutdown)(); // 4
	BOOL(__fastcall *EndCutscene)(HANDLE hWnd, int nResolution, int); // 5
	BOOL(__fastcall *BeginScene)(BOOL bClear, BYTE nRed, BYTE nGreen, BYTE nBlue); // 6
	BOOL(__fastcall *EndScene1)(); // 7
	BOOL(__fastcall *EndScene2)(); // 8
	BOOL(__fastcall *ResizeWin)(HANDLE HWND, int bResolution); // 9
	BOOL(__fastcall *GetBackBuffer)(D2RGB* pBuffer); // 10
	BOOL(__fastcall *ActivateWindow)(int Unk, int Contrast); // 11
	BOOL(__fastcall *SetOption)(int nOption, int nValue); // 12
	BOOL(__fastcall *BeginCutscene)(); // 13
	BOOL(__fastcall *PlayCutscene)(const char* szFile, int nResolution, void *pfframe); // 14
	BOOL(__fastcall *CheckCutscene)(); // 15
	BOOL(__fastcall *DecodeSmacker)(const char *szsmacker, BYTE *pbuffer, int nVersion); // 16
	BOOL(__fastcall *PlaySmacker)(void *pcontext); // 17
	BOOL(__fastcall *CloseSmacker)(void *pcontext); // 18
	int(__fastcall *GetRenderStats)(); // 19
	void(__fastcall *GetScreenSize)(int *pwidth, int *pheight); // 20
	void(__fastcall *SetScaleFactor)(int nFactor); // 21
	BOOL(__fastcall *SetGamma)(int nGamma); // 22
	BOOL(__fastcall *CheckGamma)(); // 23
	BOOL(__fastcall *SetPerspectiveScale)(); // 24
	BOOL(__fastcall *AdjustPerspective)(int nXpos, int nYpos, int nBais, int *pxadjust, int *pyadjust); // 25
	BOOL(__fastcall *ScalePerspectivepos)(int nXpos, int nYpos, int nAngle, int *pxpos, int *pypos, BOOL bOrder); // 26
	BOOL(__fastcall *SetDefperspectivefactor)(); // 27
	void(__fastcall *SetPalette)(BYTE* pPalette); // 28
	BOOL(__fastcall *SetPalettetable)(BYTE** pPalette); // 29
	BOOL(__fastcall *SetGlobalLight)(BYTE nRed, BYTE nGreen, BYTE nBlue); // 30
	BOOL(__fastcall *DrawGroundTile)(TileContext* pTile, DWORD** pLight, int nXpos, int nYpos, int nWorldXpos, int nWorldYpos, BYTE nAlpha, int nScreenPanels, BOOL bOne); // 31
	BOOL(__fastcall *DrawPerspectiveImage)(CellContext* pData, unsigned int nXpos, unsigned int nYpos, BYTE dwGamma, D2C_DrawModes nDrawMode, int nScreenMode, BYTE* pPalette); // 32
	BOOL(__fastcall *DrawImage)(CellContext* pData, unsigned int nXpos, unsigned int nYpos, BYTE dwGamma, D2C_DrawModes nDrawMode, BYTE* pPalette); // 33
	BOOL(__fastcall *DrawColouredImage)(CellContext* pData, int nXpos, int nYpos, BYTE dwGamma, D2C_DrawModes nDrawMode, int nColor); // 34
	BOOL(__fastcall *DrawVerticalCropImage)(CellContext* pData, int nXpos, int nYpos, int nSkipLines, int nDrawLines, D2C_DrawModes nDrawMode); // 35
	BOOL(__fastcall *DrawShadows)(CellContext* pData, int nXpos, int nYpos); // 36
	BOOL(__fastcall *DrawImageFast)(CellContext* pData, int nXpos, int nYpos, BYTE nPaletteIndex); // 37
	BOOL(__fastcall *DrawClippedImage)(CellContext* pData, int nXpos, int nYpos, void* pCropRect, D2C_DrawModes nDrawMode); // 38
	BOOL(__fastcall *DrawWallTile)(TileContext* pTile, int nXpos, int nYpos, DWORD** pLight, int nScreenPanels); // 39
	BOOL(__fastcall *DrawRoofTile)(TileContext* pTile, int nXpos, int nYpos, DWORD** pLight, int nScreenPanels, BYTE nAlpha); // 40
	BOOL(__fastcall *DrawVisTile)(TileContext* pTile, int nXpos, int nYpos, D2C_DrawModes nDrawMode, int nScreenPanels); // 41
	BOOL(__fastcall *DrawRect)(RECT *Prect, BYTE nColor); // 42
	BOOL(__fastcall *DrawRectEx)(RECT *Prect, BYTE nColor); // 43
	BOOL(__fastcall *DrawSolidRect)(RECT *Prect, BYTE nColor); // 44
	BOOL(__fastcall *DrawSquare)(POINT *pos, int nSize, BYTE nColor); // 45
	BOOL(__fastcall *DrawSolidRectEx)(int nXStart, int nYStart, int nXEnd, int nYEnd, BYTE nColor, D2C_DrawModes nDrawMode); // 46
	BOOL(__fastcall *DrawSolidRectAlpha)(int nXStart, int nYStart, int nXEnd, int nYEnd, BYTE nColor, BYTE nAlpha); // 47
	BOOL(__fastcall *DrawLine)(int nXStart, int nYStart, int nXEnd, int nYEnd, BYTE nColor, BYTE nAlpha); // 48
	BOOL(__fastcall *ClearScreen)(BOOL bPartial); // 49
	BOOL(__fastcall *DrawString)(int nXpos, int nYpos, const char *msg, ...); // 50
	BOOL(__fastcall *DrawLight)(DWORD *plight, DWORD *pplayerlight, int nXpos, int nYpos); // 51
	BOOL(__fastcall *DebugFillBackBuffer)(int xPos, int yPos); // 52
	BOOL(__fastcall *ClearCaches)(); // 53
};
#pragma pack()
#endif
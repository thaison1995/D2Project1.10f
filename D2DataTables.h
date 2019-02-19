/********************************************************
*	D2DataTables.h										*
*														*
*	Same deal as D2Structs.h except it's meant			*
*	to declare all txt file structs. There are			*
*	a lot of them and I always thought that having		*
*	them in a separated declaration file helped with	*
*	the organization									*
*														*
*********************************************************/

#pragma pack(1)
struct SkillsTxt;

struct SkillsTxt
{
	DWORD dwSkillId; 					//0x00
	DWORD dwFlags[2];					//0x04
	DWORD dwClassId;					//0x0C
	BYTE nAnim;							//0x10
	BYTE nMonAnim;						//0x11
	BYTE nSeqTrans;						//0x12
	BYTE nSeqNum;						//0x13
	BYTE nRange;						//0x14
	BYTE nSelectProc;					//0x15
	BYTE nSeqInput;						//0x16
	BYTE unk0x17;						//0x17
	WORD wITypeA1;						//0x18
	WORD wITypeA2;						//0x1A
	WORD wITypeA3;						//0x1C
	WORD wITypeB1;						//0x1E
	WORD wITypeB2;						//0x20
	WORD wITypeB3;						//0x22
	WORD wETypeA1;						//0x24
	WORD wETypeA2;						//0x26
	WORD wETypeB1;						//0x28
	WORD wETypeB2;						//0x2A
	WORD wSrvStartFunc;					//0x2C
	WORD wSrvDoFunc;					//0x2E
	WORD wSrvPrgFunc1;					//0x30
	WORD wSrvPrgFunc2;					//0x32
	WORD wSrvPrgFunc3;					//0x34
	WORD unk0x36;						//0x36
	DWORD dwPrgCalc1;					//0x38
	DWORD dwPrgCalc2;					//0x3C
	DWORD dwPrgCalc3;					//0x40
	WORD wPrgDamage;					//0x44
	WORD wSrvMissile;					//0x46
	WORD wSrvMissileA;					//0x48
	WORD wSrvMissileB;					//0x4A
	WORD wSrvMissileC;					//0x4C
	WORD wSrvOverlay;					//0x4E
	DWORD dwAuraFilter;					//0x50
	WORD wAuraStat1;					//0x54
	WORD wAuraStat2;					//0x56
	WORD wAuraStat3;					//0x58
	WORD wAuraStat4;					//0x5A
	WORD wAuraStat5;					//0x5C
	WORD wAuraStat6;					//0x5E
	DWORD dwAuraLenCalc;				//0x60
	DWORD dwAuraRangeCalc;				//0x64
	DWORD dwAuraStatCalc1;				//0x68
	DWORD dwAuraStatCalc2;				//0x6C
	DWORD dwAuraStatCalc3;				//0x70
	DWORD dwAuraStatCalc4;				//0x74
	DWORD dwAuraStatCalc5;				//0x78
	DWORD dwAuraStatCalc6;				//0x7C
	WORD wAuraState;					//0x80
	WORD wAuraTargetState;				//0x82
	WORD wAuraEvent1;					//0x84
	WORD wAuraEvent2;					//0x86
	WORD wAuraEvent3;					//0x88
	WORD wAuraEventFunc1;				//0x8A
	WORD wAuraEventFunc2;				//0x8C
	WORD wAuraEventFunc3;				//0x8E
	WORD wAuraTgtEvent;					//0x90
	WORD wAuraTgtEventFunc;				//0x92
	WORD wPassiveState;					//0x94
	WORD wPassiveIType;					//0x96
	WORD wPassiveStat1;					//0x98
	WORD wPassiveStat2;					//0x9A
	WORD wPassiveStat3;					//0x9C
	WORD wPassiveStat4;					//0x9E
	WORD wPassiveStat5;					//0xA0
	WORD unk0xA2;						//0xA2
	DWORD dwPassiveCalc1;				//0xA4
	DWORD dwPassiveCalc2;				//0xA8
	DWORD dwPassiveCalc3;				//0xAC
	DWORD dwPassiveCalc4;				//0xB0
	DWORD dwPassiveCalc5;				//0xB4
	WORD wPassiveEvent;					//0xB8
	WORD wPassiveEventFunc;				//0xBA
	WORD wSummon;						//0xBC
	BYTE nPetType;						//0xBE
	BYTE nSumMode;						//0xBF
	DWORD dwPetMax;						//0xC0
	WORD wSumSkill1;					//0xC4
	WORD wSumSkill2;					//0xC6
	WORD wSumSkill3;					//0xC8
	WORD wSumSkill4;					//0xCA
	WORD wSumSkill5;					//0xCC
	WORD unk0xCE;						//0xCE
	DWORD dwSumSkCalc1;					//0xD0
	DWORD dwSumSkCalc2;					//0xD4
	DWORD dwSumSkCalc3;					//0xD8
	DWORD dwSumSkCalc4;					//0xDC
	DWORD dwSumSkCalc5;					//0xE0
	WORD wSumUMod;						//0xE4
	WORD wSumOverlay;					//0xE6
	WORD wCltMissile;					//0xE8
	WORD wCltMissileA;					//0xEA
	WORD wCltMissileB;					//0xEC
	WORD wCltMissileC;					//0xEE
	WORD wCltMissileD;					//0xF0
	WORD wCltStFunc;					//0xF2
	WORD wCltDoFunc;					//0xF4
	WORD wCltPrgFunc1;					//0xF6
	WORD wCltPrgFunc2;					//0xF8
	WORD wCltPrgFunc3;					//0xFA
	WORD wStSound;						//0xFC
	WORD unk0xFE;						//0xFE
	WORD wDoSound;						//0x100
	WORD wDoSoundA;						//0x102
	WORD wDoSoundB;						//0x104
	WORD wCastOverlay;					//0x106
	WORD wTgtOverlay;					//0x108
	WORD wTgtSound;						//0x10A
	WORD wPrgOverlay;					//0x10C
	WORD wPrgSound;						//0x10E
	WORD wCltOverlayA;					//0x110
	WORD wCltOverlayB;					//0x112
	DWORD dwCltCalc1;					//0x114
	DWORD dwCltCalc2;					//0x118
	DWORD dwCltCalc3;					//0x11C
	WORD wItemTarget;					//0x120
	WORD wItemCastSound;				//0x122
	DWORD wItemCastOverlay;				//0x124
	DWORD dwPerDelay;					//0x128
	WORD wMaxLvl;						//0x12C
	WORD wResultFlags;					//0x12E
	DWORD dwHitFlags;					//0x130
	DWORD dwHitClass;					//0x134
	DWORD dwCalc1;						//0x138
	DWORD dwCalc2;						//0x13C
	DWORD dwCalc3;						//0x140
	DWORD dwCalc4;						//0x144
	DWORD dwParam1;						//0x148
	DWORD dwParam2;						//0x14C
	DWORD dwParam3;						//0x150
	DWORD dwParam4;						//0x154
	DWORD dwParam5;						//0x158
	DWORD dwParam6;						//0x15C
	DWORD dwParam7;						//0x160
	DWORD dwParam8;						//0x164
	WORD wWeapSel;						//0x168
	WORD wItemEffect;					//0x16A
	DWORD wItemCltEffect;				//0x16C
	DWORD dwSkPoints;					//0x170
	WORD wReqLevel;						//0x174
	WORD wReqStr;						//0x176
	WORD wReqDex;						//0x178
	WORD wReqInt;						//0x17A
	WORD wReqVit;						//0x17C
	WORD wReqSkill1;					//0x17E
	WORD wReqSkill2;					//0x180
	WORD wReqSkill3;					//0x182
	WORD wStartMana;					//0x184
	WORD wMinMana;						//0x186
	WORD wManaShift;					//0x188
	WORD wMana;							//0x18A
	WORD wLevelMana;					//0x18C
	BYTE nAttackRank;					//0x18E
	BYTE nLineOfSight;					//0x18F
	DWORD dwDelay;						//0x190
	DWORD wSkillDesc;					//0x194
	DWORD dwToHit;						//0x198
	DWORD dwLevToHit;					//0x19C
	DWORD dwToHitCalc;					//0x1A0
	BYTE nToHitShift;					//0x1A4
	BYTE nSrcDam;						//0x1A5
	WORD unk0x1A6;						//0x1A6
	DWORD dwMinDam;						//0x1A8
	DWORD dwMaxDam;						//0x1AC
	DWORD dwMinLvlDam1;					//0x1B0
	DWORD dwMinLvlDam2;					//0x1B4
	DWORD dwMinLvlDam3;					//0x1B8
	DWORD dwMinLvlDam4;					//0x1BC
	DWORD dwMinLvlDam5;					//0x1C0
	DWORD dwMaxLvlDam1;					//0x1C4
	DWORD dwMaxLvlDam2;					//0x1C8
	DWORD dwMaxLvlDam3;					//0x1CC
	DWORD dwMaxLvlDam4;					//0x1D0
	DWORD dwMaxLvlDam5;					//0x1D4
	DWORD dwDmgSymPerCalc;				//0x1D8
	WORD wEType;						//0x1DC
	WORD unk0x1DE;						//0x1DE
	DWORD dwEMin;						//0x1E0
	DWORD dwEMax;						//0x1E4
	DWORD dwEMinLev1;					//0x1E8
	DWORD dwEMinLev2;					//0x1EC
	DWORD dwEMinLev3;					//0x1F0
	DWORD dwEMinLev4;					//0x1F4
	DWORD dwEMinLev5;					//0x1F8
	DWORD dwEMaxLev1;					//0x1FC
	DWORD dwEMaxLev2;					//0x200
	DWORD dwEMaxLev3;					//0x204
	DWORD dwEMaxLev4;					//0x208
	DWORD dwEMaxLev5;					//0x20C
	DWORD dwEDmgSymPerCalc;				//0x210
	DWORD dwELen;						//0x214
	DWORD dwELevLen1;					//0x218
	DWORD dwELevLen2;					//0x21C
	DWORD dwELevLen3;					//0x220
	DWORD dwELenSymPerCalc;				//0x224
	WORD wRestrict;						//0x228
	WORD wState1;						//0x22A
	WORD wState2;						//0x22C
	WORD wState3;						//0x22E
	WORD wAiType;						//0x230
	WORD wAiBonus;						//0x232
	DWORD dwCostMult;					//0x234
	DWORD dwCostAdd;					//0x238
};

struct BodyLocsTxt
{
	union
	{
		DWORD dwCode;					//0x00
		char szCode[4];					//0x00
	};
};

struct MonStatsTxt
{
	WORD	wId;						//0x00
	WORD	wBaseId;					//0x02
	WORD	wNextInClass;				//0x04
	WORD	wNameStr;					//0x06
	WORD	wDescStr;					//0x08
	WORD	unk0x0A;					//0x0A
	DWORD dwMonStatsFlags;				//0x0C
	DWORD	dwCode;						//0x10
	WORD	wMonSound;					//0x14
	WORD	wUMonSound;					//0x16
	WORD	wMonStatsEx;				//0x18
	WORD	wMonProp;					//0x1A
	WORD	wMonType;					//0x1C
	WORD	wAI;						//0x1E
	WORD	wSpawn;						//0x20
	BYTE	bSpawnX;					//0x22
	BYTE	bSpawnY;					//0x23
	WORD	bSpawnMode;					//0x24
	WORD	wMinion1;					//0x26
	WORD	wMinion2;					//0x28
	WORD	unk0x2A;					//0x2A
	BYTE	bPartyMin;					//0x2C
	BYTE	bPartyMax;					//0x2D
	BYTE	bRarity;					//0x2E
	BYTE	bMinGrp;					//0x2F
	BYTE	bMaxGrp;					//0x30
	BYTE	bSparsePopulate;			//0x31
	WORD	wVelocity;					//0x32
	WORD	wRun;						//0x34
	WORD	unk0x36;					//0x36
	WORD	unk0x38;					//0x38
	WORD	wMissA1;					//0x3A
	WORD	wMissA2;					//0x3C
	WORD	wMissS1;					//0x3E
	WORD	wMissS2;					//0x40
	WORD	wMissS3;					//0x42
	WORD	wMissS4;					//0x44
	WORD	wMissC;						//0x46
	WORD	wMissSQ;					//0x48
	WORD	unk0x4A;					//0x4A
	BYTE	bAlign;						//0x4C
	BYTE	bTransLvl;					//0x4D
	BYTE	bThreat;					//0x4E
	BYTE	bAIdel;						//0x4F
	BYTE	bAIdel_N;					//0x50
	BYTE	bAIdel_H;					//0x51
	BYTE	bAiDist;					//0x52
	BYTE	bAiDist_N;					//0x53
	WORD	bAiDist_H;					//0x54
	WORD	wAiP1;						//0x56
	WORD	wAiP1_N;					//0x58
	WORD	wAiP1_H;					//0x5A
	WORD	wAiP2;						//0x5C
	WORD	wAiP2_N;					//0x5E
	WORD	wAiP2_H;					//0x60
	WORD	wAiP3;						//0x62
	WORD	wAiP3_N;					//0x64
	WORD	wAiP3_H;					//0x66
	WORD	wAiP4;						//0x68
	WORD	wAiP4_N;					//0x6A
	WORD	wAiP4_H;					//0x6C
	WORD	wAiP5;						//0x6E
	WORD	wAiP5_N;					//0x70
	WORD	wAiP5_H;					//0x72
	WORD	wAiP6;						//0x74
	WORD	wAiP6_N;					//0x76
	WORD	wAiP6_H;					//0x78
	WORD	wAiP7;						//0x7A
	WORD	wAiP7_N;					//0x7C
	WORD	wAiP7_H;					//0x7E
	WORD	wAiP8;						//0x80
	WORD	wAiP8_N;					//0x82
	WORD	wAiP8_H;					//0x84
	WORD	wTreasureClass1;			//0x86
	WORD	wTreasureClass2;			//0x88
	WORD	wTreasureClass3;			//0x8A
	WORD	wTreasureClass4;			//0x8C
	WORD	wTreasureClass1_N;			//0x8E
	WORD	wTreasureClass2_N;			//0x90
	WORD	wTreasureClass3_N;			//0x92
	WORD	wTreasureClass4_N;			//0x94
	WORD	wTreasureClass1_H;			//0x96
	WORD	wTreasureClass2_H;			//0x98
	WORD	wTreasureClass3_H;			//0x9A
	WORD	wTreasureClass4_H;			//0x9C
	BYTE	bTCQuestId;					//0x9E
	BYTE	bTCQuestCP;					//0x9F
	BYTE	bDrain;						//0xA0
	BYTE	bDrain_N;					//0xA1
	BYTE	bDrain_H;					//0xA2
	BYTE	bToBlock;					//0xA3
	BYTE	bToBlock_N;					//0xA4
	BYTE	bToBlock_H;					//0xA5
	WORD	bCrit;						//0xA6
	WORD	wSkillDamage;				//0xA8
	WORD	wLevel;						//0xAA
	WORD	wLevel_N;					//0xAC
	WORD	wLevel_H;					//0xAE
	WORD	wMinHP;						//0xB0
	WORD	wMinHP_N;					//0xB2
	WORD	wMinHP_H;					//0xB4
	WORD	wMaxHP;						//0xB6
	WORD	wMaxHP_N;					//0xB8
	WORD	wMaxHP_H;					//0xBA
	WORD	wAC;						//0xBC
	WORD	wAC_N;						//0xBE
	WORD	wAC_H;						//0xC0
	WORD	wA1TH;						//0xC2
	WORD	wA1TH_N;					//0xC4
	WORD	wA1TH_H;					//0xC6
	WORD	wA2TH;						//0xC8
	WORD	wA2TH_N;					//0xCA
	WORD	wA2TH_H;					//0xCC
	WORD	wS1TH;						//0xCE
	WORD	wS1TH_N;					//0xD0
	WORD	wS1TH_H;					//0xD2
	WORD	wExp;						//0xD4
	WORD	wExp_N;						//0xD6
	WORD	wExp_H;						//0xD8
	WORD	wA1MinD;					//0xDA
	WORD	wA1MinD_N;					//0xDC
	WORD	wA1MinD_H;					//0xDE
	WORD	wA1MaxD;					//0xE0
	WORD	wA1MaxD_N;					//0xE2
	WORD	wA1MaxD_H;					//0xE4
	WORD	wA2MinD;					//0xE6
	WORD	wA2MinD_N;					//0xE8
	WORD	wA2MinD_H;					//0xEA
	WORD	wA2MaxD;					//0xEC
	WORD	wA2MaxD_N;					//0xEE
	WORD	wA2MaxD_H;					//0xF0
	WORD	wS1MinD;					//0xF2
	WORD	wS1MinD_N;					//0xF4
	WORD	wS1MinD_H;					//0xF6
	WORD	wS1MaxD;					//0xF8
	WORD	wS1MaxD_N;					//0xFA
	WORD	wS1MaxD_H;					//0xFC
	BYTE	bEl1Mode;					//0xFE
	BYTE	bEl2Mode;					//0xFF
	BYTE	bEl3Mode;					//0x100
	BYTE	bEl1Type;					//0x101
	BYTE	bEl2Type;					//0x102
	BYTE	bEl3Type;					//0x103
	BYTE	bEl1Pct;					//0x104
	BYTE	bEl1Pct_N;					//0x105
	BYTE	bEl1Pct_H;					//0x106
	BYTE	bEl2Pct;					//0x107
	BYTE	bEl2Pct_N;					//0x108
	BYTE	bEl2Pct_H;					//0x109
	BYTE	bEl3Pct;					//0x10A
	BYTE	bEl3Pct_N;					//0x10B
	BYTE	bEl3Pct_H;					//0x10C
	BYTE	unk0x10D;					//0x10D
	WORD	wEl1MinD;					//0x10E
	WORD	wEl1MinD_N;					//0x110
	WORD	wEl1MinD_H;					//0x112
	WORD	wEl2MinD;					//0x114
	WORD	wEl2MinD_N;					//0x116
	WORD	wEl2MinD_H;					//0x118
	WORD	wEl3MinD;					//0x11A
	WORD	wEl3MinD_N;					//0x11C
	WORD	wEl3MinD_H;					//0x11E
	WORD	wEl1MaxD;					//0x120
	WORD	wEl1MaxD_N;					//0x122
	WORD	wEl1MaxD_H;					//0x124
	WORD	wEl2MaxD;					//0x126
	WORD	wEl2MaxD_N;					//0x128
	WORD	wEl2MaxD_H;					//0x12A
	WORD	wEl3MaxD;					//0x12C
	WORD	wEl3MaxD_N;					//0x12E
	WORD	wEl3MaxD_H;					//0x130
	WORD	wEl1Dur;					//0x132
	WORD	wEl1Dur_N;					//0x134
	WORD	wEl1Dur_H;					//0x136
	WORD	wEl2Dur;					//0x138
	WORD	wEl2Dur_N;					//0x13A
	WORD	wEl2Dur_H;					//0x13C
	WORD	wEl3Dur;					//0x13E
	WORD	wEl3Dur_N;					//0x140
	WORD	wEl3Dur_H;					//0x142
	WORD	wResDmg;					//0x144
	WORD	wResDmg_N;					//0x146
	WORD	wResDmg_H;					//0x148
	WORD	wResMagic;					//0x14A
	WORD	wResMagic_N;				//0x14C
	WORD	wResMagic_H;				//0x14E
	WORD	wResFire;					//0x150
	WORD	wResFire_N;					//0x152
	WORD	wResFire_H;					//0x154
	WORD	wResLight;					//0x156
	WORD	wResLight_N;				//0x158
	WORD	wResLight_H;				//0x15A
	WORD	wResCold;					//0x15C
	WORD	wResCold_N;					//0x15E
	WORD	wResCold_H;					//0x160
	WORD	wResPoison;					//0x162
	WORD	wResPoison_N;				//0x164
	WORD	wResPoiosn_H;				//0x166
	BYTE	bColdEffect;				//0x168
	BYTE	bColdEffect_N;				//0x169
	WORD	bColdEffect_H;				//0x16A
	DWORD	dwSendSkills;				//0x16C
	WORD	wSkill1;					//0x170
	WORD	wSkill2;					//0x172
	WORD	wSkill3;					//0x174
	WORD	wSkill4;					//0x176
	WORD	wSkill5;					//0x178
	WORD	wSkill6;					//0x17A
	WORD	wSkill7;					//0x17C
	WORD	wSkill8;					//0x17E
	DWORD   unk0x180[6];				//0x180
	BYTE	bSk1lvl;					//0x198
	BYTE	bSk2lvl;					//0x199
	BYTE	bSk3lvl;					//0x19A
	BYTE	bSk4lvl;					//0x19B
	BYTE	bSk5lvl;					//0x19C
	BYTE	bSk6lvl;					//0x19D
	BYTE	bSk7lvl;					//0x19E
	BYTE	bSk8lvl;					//0x19F
	DWORD	dwDamageRegen;				//0x1A0
	BYTE	bSplEndDeath;				//0x1A4
	BYTE	bSplGetModeChart;			//0x1A5
	BYTE	bSplEndGeneric;				//0x1A6
	BYTE	bSplClientEnd;				//0x1A7
};

struct MissilesTxt
{
	DWORD dwId;							//0x00
	DWORD dwMissileFlags;				//0x04
	WORD wCltDoFunc;					//0x08
	WORD wCltHitFunc;					//0x0A
	WORD wSrvDoFunc;					//0x0C
	WORD wSrvHitFunc;					//0x0E
	WORD wSrvDmgFunc;					//0x10
	WORD wTravelSound;					//0x12
	WORD wHitSound;						//0x14
	WORD wExplosionMissile;				//0x16
	WORD wSubMissile[3];				//0x18
	WORD wCltSubMissile[3];				//0x1E
	WORD wHitSubMissile[4];				//0x24
	WORD wCltHitSubMissile[4];			//0x2C
	WORD wProgSound;					//0x34
	WORD wProgOverlay;					//0x36
	DWORD dwParam[5];					//0x38
	DWORD dwHitPar[3];					//0x4C
	DWORD dwCltParam[5];				//0x58
	DWORD dwCltHitPar[3];				//0x6C
	DWORD dwDmgParam[2];				//0x78
	DWORD dwSrvCalc;					//0x80
	DWORD dwCltCalc;					//0x84
	DWORD dwHitCalc;					//0x88
	DWORD dwCltHitCalc;					//0x8C
	DWORD dwDmgCalc;					//0x90
	WORD wHitClass;						//0x94
	WORD wRange;						//0x96
	WORD wLevRange;						//0x98
	BYTE nVel;							//0x9A
	BYTE nVelLev;						//0x9B
	WORD wMaxVel;						//0x9C
	WORD wAccel;						//0x9E
	WORD wAnimRate;						//0xA0
	WORD wXoffset;						//0xA2
	WORD wYoffset;						//0xA4
	WORD wZoffset;						//0xA6
	DWORD dwHitFlags;					//0xA8
	WORD wResultFlags;					//0xAC
	WORD wKnockBack;					//0xAE
	DWORD dwMinDamage;					//0xB0
	DWORD dwMaxDamage;					//0xB4
	DWORD dwMinLevDam[5];				//0xB8
	DWORD dwMaxLevDam[5];				//0xCC
	DWORD dwDmgSymPerCalc;				//0xE0
	DWORD dwElemType;					//0xE4
	DWORD dwElemMin;					//0xE8
	DWORD dwElemMax;					//0xEC
	DWORD dwMinElemLev[5];				//0xF0
	DWORD dwMaxElemLev[5];				//0x104
	DWORD dwElemDmgSymPerCalc;			//0x118
	DWORD dwElemLen;					//0x11C
	DWORD dwElemLevLen[3];				//0x120
	BYTE unk0x12C;						//0x12C
	BYTE nSrcDamage;					//0x12D
	BYTE nSrcMissDmg;					//0x12E
	BYTE nHoly;							//0x12F
	BYTE nLight;						//0x130
	BYTE nFlicker;						//0x131
	BYTE nRGB[3];						//0x132
	BYTE nInitSteps;					//0x135
	BYTE nActivate;						//0x136
	BYTE nLoopAnim;						//0x137
	char szCelFile[64];					//0x138
	DWORD dwAnimLen;					//0x178
	DWORD dwRandStart;					//0x17C
	BYTE nSubLoop;						//0x180
	BYTE nSubStart;						//0x181
	BYTE nSubStop;						//0x182
	BYTE nCollideType;					//0x183
	BYTE nCollision;					//0x184
	BYTE nClientCol;					//0x185
	BYTE nCollideKill;					//0x186
	BYTE nCollideFriend;				//0x187
	BYTE nNextHit;						//0x188
	BYTE nNextDelay;					//0x189
	BYTE nSize;							//0x18A
	BYTE nToHit;						//0x18B
	BYTE nAlwaysExplode;				//0x18C
	BYTE nTrans;						//0x18D
	WORD wQty;							//0x18E
	DWORD dwSpecialSetup;				//0x190
	WORD wSkill;						//0x194
	BYTE nHitShift;						//0x196
	BYTE unk0x197[5];					//0x197
	DWORD dwDamageRate;					//0x19C
	BYTE nNumDirections;				//0x1A0
	BYTE nAnimSpeed;					//0x1A1
	BYTE nLocalBlood;					//0x1A2
	BYTE unk;							//0x1A3
};

struct D2CharItemStrc
{
	union
	{
		DWORD dwItemCode;				//0x00
		char szItemCode[4];				//0x00
	};
	char nBodyLoc;						//0x04
	char nItemCount;					//0x05
	WORD unk0x6;						//0x06
};

struct CharStatsTxt
{
	wchar_t wszName[16];				//0x00
	char szName[16];					//0x20
	BYTE nStr;							//0x30
	BYTE nDex;							//0x31
	BYTE nEne;							//0x32
	BYTE nVita;							//0x33
	BYTE nStamina;						//0x34
	BYTE nHpAdd;						//0x35
	BYTE nPercentStr;					//0x36
	BYTE nPercentInt;					//0x37
	BYTE nPercentDex;					//0x38
	BYTE nPercentVit;					//0x39
	BYTE nManaRecovery;					//0x3A
	BYTE unk0x3B;						//0x3B
	DWORD dwToHitFactor;				//0x3C
	BYTE nWalkSpeed;					//0x40
	BYTE nRunSpeed;						//0x41
	BYTE nRunDrain;						//0x42
	BYTE nLifePerLevel;					//0x43
	BYTE nStaminaPerLevel;				//0x44
	BYTE nManaPerLevel;					//0x45
	BYTE nLifePerVitality;				//0x46
	BYTE nStaminaPerVitality;			//0x47
	BYTE nManaPerMagic;					//0x48
	BYTE nBlockFactor;					//0x49
	WORD unk0x4A;						//0x4A
	DWORD dwWeaponClassCode;			//0x4C
	BYTE nStatsPerLevel;				//0x50
	BYTE unk0x51;						//0x51
	WORD wAllSkills;					//0x52
	WORD wSkillTab[3];					//0x54
	WORD wClassSkills;					//0x5A
	D2CharItemStrc pItems[10];			//0x5C
	WORD nStartSkill;					//0xAC
	WORD nBaseSkill[10];				//0xAE
	WORD unk0xC2;						//0xC2
};

struct ItemStatCostTxt  //size 0x144
{
	WORD	wStat;				//0x00
	WORD 	_1;					//0x02
	struct
	{
		BYTE	bSendOther : 1;			//1
		BYTE	bSigned : 1;			//2
		BYTE	bDamageRelated : 1;		//3
		BYTE	bItemSpecific : 1;		//4
		BYTE	bDirect : 1;			//5
		BYTE	_1 : 1;					//6
		BYTE    _2 : 1;					//7
		BYTE    _3 : 1;					//8
		BYTE    _4 : 1;					//9	
		BYTE	bUpdateanimrate : 1;	//10
		BYTE	bFmin : 1;				//11
		BYTE	bFcallback : 1;			//12
		BYTE	bSaved : 1;				//13
		BYTE	bCsvsigned : 1;			//14
		BYTE	_6 : 1;					//15
		BYTE	_7 : 1;					//16
	} bItemStatFlags; 		 //0x04
	WORD 	_2;			  		 //0x06
	BYTE	bSendBits;			//0x08
	BYTE	bSendParamBits;		//0x09
	BYTE	bCsvBits;			//0x0A
	BYTE	bCsvParam;			//0x0B
	DWORD	dwDivide;			//0x0C
	DWORD	dwMultiply;			//0x10
	DWORD	dwAdd;				//0x14
	BYTE	bValShift;			//0x18
	BYTE	bSaveBits;			//0x19
	BYTE	b09SaveBits;		//0x1A
	BYTE	_3;					//0x1B
	DWORD	dwSaveAdd;			//0x1C
	DWORD	dw09SaveAdd;		//0x20
	DWORD	dwSaveParamBits;	//0x24
	DWORD 	_4;					//0x28
	DWORD	dwMinAccr;			//0x2C
	BYTE	bEncode;			//0x30
	BYTE	_5;					//0x31
	WORD	wMaxAtat;			//0x32
	WORD	wDescPriority;		//0x34
	BYTE	bDescFunc;			//0x36
	BYTE	bDescVal;			//0x37
	WORD	wDescStrPos;		//0x38
	WORD	wDescStrNeg;		//0x3A
	WORD	wDescStr2;			//0x3C
	WORD	wDGrp;				//0x3E
	BYTE	bDGrpFunc;			//0x40
	BYTE	bDGrpVal;			//0x41
	WORD	wDGrpStrPos;		//0x42
	WORD	wDGrpStrNeg;		//0x44
	WORD	wDGrpStr2;			//0x46
	WORD	wItemEvent1;		//0x48
	WORD	wItemEvent2;		//0x4A
	WORD	wItemEventFunc1;	//0x4C
	WORD	wItemEventFunc2;	//0x4E
	DWORD	bKeepZero;			//0x50
	BYTE	bOp;				//0x54
	BYTE	bOpParam;			//0x55
	WORD	wOpBase;			//0x56
	WORD	wOpStat1;			//0x58
	WORD	wOpStat2;			//0x5A
	WORD	wOpStat3;			//0x5C
	BYTE 	_Stuff[230];		//0x5E
};

struct DifficultyLevelsTxt
{
	DWORD dwResistPenalty;				//0x00
	DWORD dwDeathExpPenalty;			//0x04
	DWORD dwUberCodeOddsNorm;			//0x08
	DWORD dwUberCodeOddsGood;			//0x0C
	DWORD dwMonsterSkillBonus;			//0x10
	DWORD dwMonsterFreezeDiv;			//0x14
	DWORD dwMonsterColdDiv;				//0x18
	DWORD dwAiCurseDiv;					//0x1C
	DWORD dwUltraCodeOddsNorm;			//0x20
	DWORD dwUltraCodeOddsGood;			//0x24
	DWORD dwLifeStealDiv;				//0x28
	DWORD dwManaStealDiv;				//0x2C
	DWORD dwUniqueDmgBonus;				//0x30
	DWORD dwChampionDmgBonus;			//0x34
	DWORD dwHireableBossDmgPercent;		//0x38
	DWORD dwMonsterCEDmgPercent;		//0x3C
	DWORD dwStaticFieldMin;				//0x40
	DWORD dwGambleRare;					//0x44
	DWORD dwGambleSet;					//0x48
	DWORD dwGambleUniq;					//0x4C
	DWORD dwGambleUber;					//0x50
	DWORD dwGambleUltra;				//0x54
};

struct ArenaTxt
{
	DWORD dwSuicide;					//0x00
	DWORD dwPlayerKill;					//0x04
	DWORD dwPlayerKillPercent;			//0x08
	DWORD dwMonsterKill;				//0x0C
	DWORD dwPlayerDeath;				//0x10
	DWORD dwPlayerDeathPercent;			//0x14
	DWORD dwMonsterDeath;				//0x18
};

struct D2CubeInputItem
{
	BYTE nInputFlags;					//0x00
	BYTE nItemType;						//0x01
	WORD wItem;							//0x02
	WORD wItemID;						//0x04
	BYTE nQuality;						//0x06
	BYTE nQuantity;						//0x07
};

struct D2CubeOutputItem
{
	BYTE nItemFlags;					//0x00
	BYTE nItemType;						//0x01
	WORD wItem;							//0x02
	WORD wItemID;						//0x04
	BYTE nQuality;						//0x06
	BYTE nQuantity;						//0x07
	BYTE nType;							//0x08
	BYTE nLvl;							//0x09
	BYTE nPLvl;							//0x0A
	BYTE nILvl;							//0x0B
	WORD wPrefixId;						//0x0C
	WORD unk0x0E;						//0x0E
	WORD unk0x10;						//0x10
	WORD wSuffixId;						//0x12
	DWORD unk0x14;						//0x14
	struct
	{
		DWORD	dwMod;			//0x00
		WORD	wModParam;		//0x04
		WORD	wModMin;		//0x06
		WORD	wModMax;		//0x08
		WORD	wModChance;		//0x0A
	} sMods[5]; 						//0x18	
};

struct CubeMainTxt
{
	BYTE nEnabled;						//0x00
	BYTE nLadder;						//0x01
	BYTE nMindiff;						//0x02
	BYTE nClass;						//0x03
	DWORD dwOp;							//0x04
	DWORD dwParam;						//0x08
	DWORD dwValue;						//0x0C
	WORD wNumInputs;					//0x10
	WORD wVersion;						//0x12
	D2CubeInputItem pInputItem[7];		//0x14
	D2CubeOutputItem pOutputItem[3];	//0x4C
};

struct SkillDescTxt
{
	WORD wSkillDesc;               //0x00
	BYTE bSkillPage;               //0x02
	BYTE bSkillRow;                  //0x03
	BYTE bSkillColumn;               //0x04
	BYTE bListRow;                  //0x05
	BYTE bListPool;                  //0x06
	BYTE bIconCel;                  //0x07
	WORD wStrName;                  //0x08
	WORD wStrShort;                  //0x0A
	WORD wStrLong;                  //0x0C
	WORD wStrAlt;                  //0x0E
	WORD wStrMana;                  //0x10
	WORD wDescDam;                  //0x12
	WORD wDescAtt;                  //0x14
	WORD _1;					  //0x16
	DWORD dwDamCalc[2];               //0x18
	BYTE bPrgDamElem[4];            //0x20
	DWORD dwProgDmgMin[3];            //0x24
	DWORD dwProgDmgMax[3];            //0x30
	WORD wDescMissile[3];            //0x3C
	BYTE bDescLine[18];               //0x42
	WORD wDescTextA[17];            //0x54
	WORD wDescTextB[17];            //0x76
	DWORD dwDescCalcA[17];            //0x98
	DWORD dwDescCalcB[17];            //0xDC
};

struct PropertiesTxt
{
	WORD wProp;                   //0x00
	BYTE nSet[8];                 //0x02
	WORD wVal[7];                 //0x0A
	BYTE nFunc[8];                //0x18
	WORD wStat[7];                //0x20
};

struct sgptDataTable
{
	BYTE*	pPlayerClass;			//0x00
	DWORD	dwPlayerClassRecords;	//0x04
	BodyLocsTxt*	pBodyLocs;		//0x08
	DWORD	dwBodyLocsRecords;		//0x0C
	BYTE*	pStorePage;				//0x10
	DWORD	dwStorePageRecords;		//0x14
	BYTE*	pElemTypes;				//0x18
	DWORD	dwElemTypesRecords;		//0x1C
	BYTE*	pHitClass;				//0x20
	DWORD	dwHitClassRecords;		//0x24
	BYTE*	pMonMode;				//0x28
	DWORD	dwMonModeTxt;			//0x2C
	BYTE*	pPlrMode;				//0x30
	DWORD	dwPlrModeRecords;		//0x34
	BYTE*	pSkillCalc;				//0x38
	DWORD	dwSkillCalcRecords;		//0x3C
	BYTE*	pSkillCalcCache;		//0x40
	DWORD	dwSkillCalcCacheRecs;	//0x44
	DWORD	dwSkillCalcCacheDelta;	//0x48
	BYTE*	pSkillDescCalcCache;	//0x4C
	DWORD	dwSkillDescCalcCacheRecs;//0x50
	DWORD	dwSkillDescCalcCacheDelta;//0x54
	BYTE*	pMissCalc;				//0x58
	DWORD	dwMissCalcRecords;		//0x5C
	BYTE*	pMissCalcCache;			//0x60
	DWORD	dwMissCalcCacheRecs;	//0x64
	DWORD	dwMissCalcCacheDelta;	//0x68
	BYTE*	pSkillCodes;			//0x6C
	DWORD	dwSkillCodesRecs;		//0x70
	BYTE*	pEvents;				//0x74
	DWORD	dwEventsRecs;			//0x78
	BYTE*	pCompCodes;				//0x7C
	DWORD	dwCompCodesRecs;		//0x80
	DWORD	dwCompCodes;			//0x84
	BYTE*	pMonAi;					//0x88
	DWORD	dwMonAiRecs;			//0x8C
	DWORD	dwMonAi;				//0x90
	BYTE*	pItem;					//0x94
	BYTE*	pItemCalcCache;			//0x98
	DWORD	dwItemCalcCacheRecs;	//0x9C
	DWORD	dwItemCalcCache;		//0xA0
	PropertiesTxt*	pPropertiesTxt;	//0xA4
	BYTE*	dwProperties;			//0xA8
	DWORD	dwProportiesRecs;		//0xAC
	BYTE*	pRunes;					//0xB0
	BYTE*	pHireDescs;				//0xB4
	DWORD	dwHireDescsRecs;		//0xB8
	void*	pStatesTxt;			//0xBC
	DWORD	dwStatesTxtRecs;		//0xC0
	DWORD	dwStates;				//0xC4
	BYTE*	pStateMaskFirst;		//0xC8
	BYTE*	pStateMaskArr[40];		//0xCC
	BYTE*	pProgressiveStates;		//0x16C
	DWORD	dwProgressiveStatesRecs;//0x170
	BYTE*	pCurseStates;			//0x174
	DWORD	dwCurseStatesRecs;		//0x178
	BYTE*	pTransStates;			//0x17C
	DWORD	dwTransStatesRecs;		//0x180
	BYTE*	pActionStates;			//0x184
	DWORD	dwActionStatesRecs;		//0x188
	BYTE*	pColorStates;			//0x18C
	DWORD	dwColorStatesRecs;		//0x190
	BYTE*	pSoundCodes;			//0x194
	BYTE*	pSoundCodesTxt;			//0x198
	DWORD	dwSoundCodesRecs;		//0x19C
	BYTE*	pHirelings;				//0x1A0
	DWORD	dwHirelingsRecs;		//0x1A4
	DWORD	HireNameStart[256];		//0x1A8
	DWORD	HireNameEnd[256];		//0x5A8
	BYTE*	pNpcs;					//0x9A8
	DWORD	dwNpcsRecs;				//0x9AC
	BYTE*	pColorsTxt;				//0x9B0
	BYTE*	pColors;				//0x9B4
	BYTE*	pTreasureClassEx;		//0x9B8
	BYTE*	pTreasureClassExTxt;	//0x9BC
	DWORD	dwTreasureClassExRecs;	//0x9C0
	BYTE*	pChestTreasureClassLst[45];	//0x9C4
	MonStatsTxt* pMonStatsTxt;		//0xA78
	BYTE*	pMonStats;				//0xA7C
	DWORD	dwMonStatsRecs;			//0xA80
	BYTE*	pMonSoundsTxt;			//0xA84
	BYTE*	pMonSounds;				//0xA88
	DWORD	dwMonSoundsRecs;		//0xA8C
	BYTE*	pMonStats2Txt;			//0xA90
	BYTE*	pMonStats2;				//0xA94
	DWORD	dwMonStats2Recs;		//0xA98
	BYTE*	pMonPlaceTxt;			//0xA9C
	BYTE*	pMonPlace;				//0xAA0
	DWORD	dwMonPlaceRecs;			//0xAA4
	BYTE*	pMonPresetTxt;			//0xAA8
	BYTE*	pMonPresetActLst[5];	//0xAAC
	DWORD	dwMonPresetActRecs[5];	//0xAC0
	BYTE*	pSuperUniquesTxt;		//0xAD4
	BYTE*	pSuperUniques;			//0xAD8
	DWORD	dwSuperUniquesRecs;		//0xADC
	WORD	SuperUniqeIdxList[66];	//0xAE0
	MissilesTxt*	pMissilesTxt;	//0xB64
	BYTE*	pMissiles;				//0xB68
	DWORD	dwMissilesRecs;			//0xB6C
	BYTE*	pMonLvl;				//0xB70
	DWORD	dwMonLvlRecs;			//0xB74
	BYTE*	pMonSeqTxt;				//0xB78
	BYTE*	pMonSeq;				//0xB7C
	DWORD	dwMonSeqRecs;			//0xB80
	BYTE*	pMonSequences;			//0xB84
	DWORD	dwMonSequencesRecs;		//0xB88
	SkillDescTxt*	pSkillDescTxt;	//0xB8C
	BYTE*	pSkillDesc;				//0xB90
	DWORD	dwSkillDescRecs;		//0xB94
	SkillsTxt* pSkillsTxt;			//0xB98
	BYTE*	pSkills;				//0xB9C
	DWORD	dwSkillsRecs;			//0xBA0
	BYTE*	pPlayerSkillCount;		//0xBA4
	DWORD	dwPlayerSkillCount;		//0xBA8
	BYTE*	pPlayerSkillList;		//0xBAC
	DWORD	dwPassiveSkillCount;	//0xBB0
	BYTE*	pPasssiveSkillList;		//0xBB4
	BYTE*	pOverlayTxt;			//0xBB8
	BYTE*	pOverlay;				//0xBBC
	DWORD	dwOverlayRecs;			//0xBC0
	CharStatsTxt*	pCharStatsTxt;	//0xBC4
	DWORD	dwCharsStatsRecs;		//0xBC8
	ItemStatCostTxt*pItemStatCostTxt;//0xBCC
	BYTE*	pItemStatCost;			//0xBD0
	DWORD	dwItemStatCostRecs;		//0xBD4
	BYTE*	pOpStatNesting;			//0xBD8
	DWORD	dwOpStatNestingRecs;	//0xBDC
	BYTE*	pMonEquip;				//0xBE0
	DWORD	dwMonEquipRecs;			//0xBE4
	BYTE*	pPetTypesTxt;			//0xBE8
	BYTE*	pPetTypes;				//0xBEC
	DWORD	dwPetTypesRecs;			//0xBF0
	BYTE*	pItemsType;				//0xBF4
	BYTE*	pItemsTypeTxt;			//0xBF8
	DWORD	dwItemsTypeRecs;		//0xBFC
	DWORD	dwItemsTypeNesting;		//0xC00
	BYTE*	pItemsTypeNesting;		//0xC04
	BYTE*	pSets;					//0xC08
	BYTE*	pSetsTxt;				//0xC0C
	DWORD	dwSetsRecs;				//0xC10
	BYTE*	pSetItems;				//0xC14
	void* pSetItemsTxt;		//0xC18
	DWORD	dwSetItemsRecs;			//0xC1C
	BYTE*	pUniqueItems;			//0xC20
	void*	pUniqueItemsTxt;//0xC24
	DWORD	dwUniqItemsRecs;		//0xC28
	BYTE*	pMonProp;				//0xC2C
	BYTE*	pMonPropTxt;			//0xC30
	DWORD	dwMonPropRecs;			//0xC34
	BYTE*	pMonType;				//0xC38
	BYTE*	pMonTypeTxt;			//0xC3C
	DWORD	dwMonTypeRecs;			//0xC40
	BYTE*	pMonTypeNesting;		//0xC44
	DWORD	dwMonTypeNestingRecs;	//0xC48
	BYTE*	pMonUMod;				//0xC4C
	BYTE*	pMonUModTxt;			//0xC50
	DWORD	dwMonUModRecs;			//0xC54
	void*	pLevelsTxt;			//0xC58
	DWORD	dwLevelsRecs;			//0xC5C
	BYTE*	pLvlDefs;				//0xC60
	BYTE*	pLvlPrest;				//0xC64
	DWORD	dwLvlPrestRecs;			//0xC68
	DWORD	ItemStatCostStuff[2];	//0xC6C
	BYTE*	pAnimTables;			//0xC74
	BYTE*	pExperience;			//0xC78
	DifficultyLevelsTxt*pDiffLvlsTxt;//0xC7C
	DWORD	dwDiffLvlsRecs;			//0xC80
	BYTE*	pExpFieldD2;			//0xC84
	DWORD	ExpFieldData[10];		//0xC88
	BYTE*	pLvlSubExtra;			//0xCB0
	DWORD	dwLvlSubExtraRecs;		//0xCB4
	BYTE*	pCharTemp;				//0xCB8
	DWORD	dwCharTempRecs;			//0xCBC
	ArenaTxt*pArena;				//0xCC0
	BYTE*	pLvlTypes;				//0xCC4
	BYTE*	pWaypoints;				//0xCC8
	DWORD	dwWaypointsRecs;		//0xCCC
	DWORD	dwLvlTypes;				//0xCD0
	BYTE*	pLvlWarp;				//0xCD4
	DWORD	dwLvlWarpRecs;			//0xCD8
	void*	pLvlMaze;			//0xCDC
	DWORD	dwLvlMazeRecs;			//0xCE0
	BYTE*	pLvlSub;				//0xCE4
	DWORD	dwLvlSubRecs;			//0xCE8
	BYTE*	pLvlSubCache;			//0xCEC
	DWORD	_1[3];					//0xCF0
	BYTE*	pMapCache;				//0xCFC
	DWORD	dwMapCacheRecs;			//0xD00
	CubeMainTxt*	pCubeMain;		//0xD04
	DWORD	dwCubeMainRecs;			//0xD08
	BOOL	bWriteBinFiles;			//0xD0C
};

#pragma pack()
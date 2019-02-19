#include "DLLmain.h"
#include <memory>

typedef std::shared_ptr<ExBuff> pExBuff;
static map<int, pExBuff> Buffs;

wstring GetSkillLvl(int SkillLvl)
{
	wostringstream text;
	text << "" << SkillLvl;
	return text.str();
}

enum BuffType { BUFF_GOOD = 0x84, BUFF_BAD = 0xA, BUFF_AURA = 0x97 };

ExBuff::ExBuff(WORD SkillNo, WORD StateNo, int ImageId, short DefaultLvl, DWORD aType, bool isTimed) : ExControl((24 * Buffs.size()) + 115, *D2CLIENT_ScreenViewHeight - 10, 24, 24, 0)
{
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	D2ASSERT(pPlayer, "%s: UnitAny* not found!", __FUNCTION__)
	SkillLen = 0;
	WORD SkillLvl = DefaultLvl;
	StateId = StateNo;
	SkillId = SkillNo;
	SkillExpire = 0;

	if (SkillId)
	{
		if (!DefaultLvl)
		{
			Skill* pSkill = D2COMMON_GetSkillFromUnit(pPlayer, SkillId);
			if (pSkill)
				SkillLvl = D2COMMON_GetSkillLevel(pPlayer, pSkill, 1);
		}
		SkillsTxt* pTxt = &(*D2COMMON_sgptDataTables)->pSkillsTxt[SkillId];
		if (!pTxt) isTimed = false;
		else
		{
			SkillLen = isTimed ? (D2COMMON_EvaluateSkill(pPlayer, pTxt->dwAuraLenCalc, SkillId, SkillLvl) / 25) * 1000 : 0;
			SkillExpire = GetTickCount() + SkillLen;
		}
	}

	if (Buffs.find(StateId) != Buffs.end()) Buffs.erase(StateId);
	this->SetX((24 * Buffs.size()) + 115);

	BuffImage = new ExImage(this->GetX(), this->GetY(), 2, ImageId, "data\\global\\ui\\BuffIcon\\Buffs");
	BuffTime = new ExRectangle(this->GetX(), this->GetY() - this->GetHeight(), this->GetWidth(), this->GetHeight(), aType, 0);

	if (SkillLvl > 0 && SkillId)
		BuffInfo = new ExTextBox(this->GetX() + 5, this->GetY(), 0, 0, GetSkillLvl(SkillLvl), 0, 0);
	else 
		BuffInfo = 0;
}

ExBuff::~ExBuff()
{
	delete BuffInfo;
	delete BuffTime;
	delete BuffImage;
}

void ExBuff::Draw()
{
	Check();
}

wchar_t* ExBuffs::GetSkillName(unsigned short SkillId)
{
	sgptDataTable* pDataTable = *D2COMMON_sgptDataTables;
	if (!SkillId || !pDataTable)
		return L"?";

	SkillDescTxt* pSkillDesc = pDataTable->pSkillDescTxt;
	if (SkillId > pDataTable->dwSkillsRecs)
		return L"?";

	SkillsTxt* pTxt = pDataTable->pSkillsTxt;
	int nRow = pTxt[SkillId].wSkillDesc;
	if (!nRow)
		return L"?";

	return D2LANG_GetLocaleText(pSkillDesc[nRow].wStrName);
}

int GetSkillLvlByStat(short SkillNo, int nStat, int nValue)
{
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	D2ASSERT(pPlayer, "!pPlayer")
	SkillsTxt *pTxt = &(*D2COMMON_sgptDataTables)->pSkillsTxt[SkillNo];
	D2ASSERT(pTxt, "!pTxt")
	DWORD CalcId = 0;

	if (pTxt->wAuraStat1 == nStat) CalcId = pTxt->dwAuraStatCalc1;
	else if (pTxt->wAuraStat2 == nStat) CalcId = pTxt->dwAuraStatCalc2;
	else if (pTxt->wAuraStat3 == nStat) CalcId = pTxt->dwAuraStatCalc3;
	else if (pTxt->wAuraStat4 == nStat) CalcId = pTxt->dwAuraStatCalc4;
	else if (pTxt->wAuraStat5 == nStat) CalcId = pTxt->dwAuraStatCalc5;
	else if (pTxt->wAuraStat6 == nStat) CalcId = pTxt->dwAuraStatCalc6;

	for (int i = 1; i < 55; i++) 
	{
		int val = D2COMMON_EvaluateSkill(pPlayer, CalcId, SkillNo, i);
		if (val == nValue) return i;
	}
	return 0;
}

int GetStateStatValue(int nStatNo, BYTE* StateData, int PacketLen)
{
	//Stat Reading
	BitBuffer pBitBuffer;
	memset(&pBitBuffer, 0, sizeof(pBitBuffer));
	FOG_InitBitBuffer(&pBitBuffer,StateData,PacketLen-8);

	for(unsigned short nStat = FOG_ReadBits(&pBitBuffer, 9); nStat >= 0; nStat = FOG_ReadBits(&pBitBuffer, 9))
	{
		signed short nParam = 0;
		signed int nValue = 0;

		if (nStat >= 511) break;
		if (nStat >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs) break;

		ItemStatCostTxt * pTxt = &(*D2COMMON_sgptDataTables)->pItemStatCostTxt[nStat];
		BYTE SendBits = pTxt->bSendBits;
		BYTE SendParam = pTxt->bSendParamBits;

		if(SendBits == 0) break;
		if(SendParam) nParam = FOG_ReadBitsSigned(&pBitBuffer, SendParam);
		if(SendBits <= 32)
		{
			if(pTxt->bItemStatFlags.bSigned) 
				nValue = FOG_ReadBitsSigned(&pBitBuffer, SendBits);
			else 
				nValue = FOG_ReadBits(&pBitBuffer, SendBits);
		}

		if(nStat == nStatNo) return nValue;
	}
	return 0;
}

#pragma pack(push, 1)
struct p0xa8
{
	BYTE Header;
	BYTE UnitType;
	DWORD UnitId;
	BYTE PacketLen;
	BYTE StateNo;
	BYTE Data[1];  // Random size
};

struct BuffIcon
{
	WORD SkillID;
	WORD StateID;
	DWORD Frame;
	char Type[7];
	char Timer[7];
};
#pragma pack(pop)

BuffIcon* pBuffIcon;
DWORD pBuffIconRecs;

void ExBuffs::LoadTXT()
{
	BINField BuffIconTable[] =
	{
		{ "Skill ID",	FIELDTYPE_DATA_WORD,	0,	offsetof(BuffIcon, SkillID), 0 },
		{ "State ID",	FIELDTYPE_DATA_WORD,	0,	offsetof(BuffIcon, StateID), 0 },
		{ "Frame",		FIELDTYPE_DATA_DWORD,	0,	offsetof(BuffIcon, Frame), 0 },
		{ "Type",		FIELDTYPE_DATA_ASCII,	6,	offsetof(BuffIcon, Type), 0 },
		{ "Timer",		FIELDTYPE_DATA_ASCII,	6,	offsetof(BuffIcon, Timer), 0 },
		{ "end",		FIELDTYPE_DATA_NULL,	0,	sizeof(BuffIcon), 0 }
	};

	pBuffIcon = (BuffIcon*)D2COMMON_CompileTxt(NULL, "BuffIcon", BuffIconTable, &pBuffIconRecs, sizeof(BuffIcon));
	D2ASSERT(pBuffIcon, "Error Opening File BuffIcon.txt");
}

void ExBuffs::FreeTXT()
{
	if (pBuffIcon)
	{
		FOG_FreeClientMemory(pBuffIcon, __FILE__, __LINE__, 0);
		pBuffIcon = NULL;
	}
}

void ExBuffs::OnPatch()
{
	BuffsEnabled = true;
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0xA8].CallBack, (DWORD)&ExBuffs::OnSetState);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0xA9].CallBack, (DWORD)&ExBuffs::OnRemoveState);
}

DWORD __fastcall BuffIconType(char* txt)
{
	if (!_strcmpi("Aura", txt) || !_strcmpi("AURA", txt))
		return BuffType::BUFF_AURA;
	else if (!_strcmpi("Bad", txt) || !_strcmpi("BAD", txt))
		return BuffType::BUFF_BAD;
	else if (!_strcmpi("GOOD", txt) || !_strcmpi("Good", txt))
		return BuffType::BUFF_GOOD;

	return 0;
}

bool __fastcall BuffIconTimer(char* txt)
{
	if (!_strcmpi("True", txt) || !_strcmpi("1", txt) || !_strcmpi("TRUE", txt))
		return 1;
	else if (!_strcmpi("False", txt) || !_strcmpi("0", txt) || !_strcmpi("FALSE", txt))
		return 0;

	return 0;
}

BOOL __fastcall ExBuffs::OnSetState(BYTE* aPacket)
{
	if (BuffsEnabled)
	{
		p0xa8 *pSetState = (p0xa8*)aPacket;
		UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
		D2ASSERT(pPlayer, "!pPlayer");

		int UnitType = pSetState->UnitType;
		int UnitID = pSetState->UnitId;
		int StateNo = pSetState->StateNo;

		if (UnitType == UNIT_PLAYER && UnitID == pPlayer->dwUnitId)
		{
			BitBuffer pBitBuffer;
			memset(&pBitBuffer, 0, sizeof(pBitBuffer));
			FOG_InitBitBuffer(&pBitBuffer, pSetState->Data, pSetState->PacketLen - 8);
			for (DWORD i = 0; i < pBuffIconRecs; i++)
			{
				if (StateNo == pBuffIcon[i].StateID)
				{
					pExBuff pNewBuff(new ExBuff(pBuffIcon[i].SkillID, StateNo, pBuffIcon[i].Frame, 0, BuffIconType(pBuffIcon[i].Type), BuffIconTimer(pBuffIcon[i].Timer)));
					Buffs[StateNo] = pNewBuff; 
				}
			}
		}

	}
	return D2CLIENT_SetState_I(aPacket);
}


BOOL __fastcall ExBuffs::OnRemoveState(BYTE* aPacket)
{
	if (BuffsEnabled)
	{
		UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
		int UnitType = *(BYTE*)(aPacket + 1);
		int UnitId = *(DWORD*)(aPacket + 2);
		int StateNo = *(BYTE*)(aPacket + 6);
		if (UnitType == UNIT_PLAYER && UnitId == pPlayer->dwUnitId){ Buffs.erase(StateNo); }
	}
	return D2CLIENT_RemoveState_I(aPacket);
}


void ExBuff::UpdateYPos()
{
	for (auto it = Buffs.begin(); it != Buffs.end(); ++it)
	{
		it->second->SetY(*D2CLIENT_ScreenViewHeight - 10);
		if (it->second->BuffImage) it->second->BuffImage->SetY(it->second->GetY());
		if (it->second->BuffTime) it->second->BuffTime->SetY(it->second->GetY() - it->second->GetHeight());
		if (it->second->BuffInfo) it->second->BuffInfo->SetY(it->second->GetY());
	}
}

void ExBuff::Check()
{
	int i = 0;
	for (map<int, pExBuff>::iterator it = Buffs.begin(); it != Buffs.end(); ++it, ++i)
	{
		if (it->second->StateId == 0) continue;
		if (it->second->BuffImage) it->second->BuffImage->SetX((24 * i) + 115);
		if (it->second->BuffTime)
		{
			int timeLeft = (GetTickCount() - it->second->SkillExpire) / 1000;
			wstringstream wstr;

			if (it->second->SkillExpire)
			{
				int timeLeft = it->second->SkillExpire - GetTickCount();
				if (timeLeft > 0)
				{
					wstr << W_Color(COL_WHITE) << L"Duration: " << timeLeft / 1000 << L" sec(s)" << L"\n";
					wstr << W_Color(COL_WHITE) << L"Time remaining: " << ConvertTickToTime(timeLeft) << L" sec(s)" << L"\n";
				}
				int a = it->second->SkillExpire < GetTickCount() ? 0 : (timeLeft * 24) / (it->second->SkillLen ? it->second->SkillLen : 1);
				it->second->BuffTime->SetY(it->second->BuffImage->GetY() - a);
				it->second->BuffTime->SetHeight(a);
			}
			wstr << W_Color(COL_LIGHTGREEN) << ExBuffs::GetSkillName(it->second->SkillId);
			it->second->BuffImage->Hoover = wstr.str();
			it->second->BuffTime->SetX((24 * i) + 115);
		}
		if (it->second->BuffInfo) it->second->BuffInfo->SetX((24 * i) + 120);
	}
}

void ExBuff::Clear()
{
	Buffs.clear();
}


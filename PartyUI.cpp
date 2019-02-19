#include "DLLmain.h"

static int pOffset;

struct PlayerTable
{
	DWORD		UnitId;
	ExBox*		Frame;
	ExTextBox*	Level;
	ExTextBox*	Name;
	ExImage*	Class;
	ExTextBox*	Location;
	ExTextBox*	Kills;
	ExTextBox*	Assists;
	ExTextBox*	Deaths;

	ExButton*	Invite;
	ExButton*	Host;
	ExButton*	Loot;
	ExButton*	Squelch;
};

struct AccountBase
{
	string Name;
	int Kills;
	int Deaths;
	int Assists;
};

static list<PlayerTable> PlayerList;
static list<AccountBase> AccBase;
static ExWindow *	PartyScreen;
static vector<ExTextBox*> Group;
static int TeamOffset;
static ExButton * LeaveB;
static ExScrollBar * Scroll;

RosterUnit * GetRosterById(DWORD dwUnitId)
{
	for (RosterUnit* pRoster = *D2CLIENT_Roster; pRoster; pRoster = pRoster->pNext)
	{
		if (pRoster->dwUnitId == dwUnitId) return pRoster;
	}
	return 0;
}


enum
{
	D2STR_BARBARIAN = 4007,	// Barbarian
	D2STR_PALADIN = 4008,	// Paladin
	D2STR_NECROMANCER = 4009,	// Necromancer
	D2STR_SORCERESS = 4010,	// Sorceress
	D2STR_AMAZON = 4011,	// Amazon
	D2STR_DRUIDSTR_ = 4012,	// Druid
	D2STR_ASSASSINSTR = 4013,	// Assassin
};

wstring GetClassById(int ClassId)
{

	switch (ClassId)
	{
	case 0: return D2LANG_GetLocaleText(D2STR_AMAZON);
	case 1:	return D2LANG_GetLocaleText(D2STR_SORCERESS);
	case 2: return D2LANG_GetLocaleText(D2STR_NECROMANCER);
	case 3: return D2LANG_GetLocaleText(D2STR_PALADIN);
	case 4: return D2LANG_GetLocaleText(D2STR_BARBARIAN);
	case 5: return D2LANG_GetLocaleText(D2STR_DRUIDSTR_);
	case 6: return D2LANG_GetLocaleText(D2STR_ASSASSINSTR);
	}
	return L"???";
}

bool AccUnique(const AccountBase & first, const AccountBase & second)
{
	string f = first.Name;
	string s = second.Name;

	return f == s;
}

void PartyUI::AddAccount(string szName, string szAccount)
{
	AccountBase Base;
	Base.Name = szName;
	Base.Kills = 0;
	Base.Deaths = 0;
	Base.Assists = 0;
	AccBase.push_back(Base);
	AccBase.unique(&AccUnique);
}

int PartyUI::FindRoster(string szName, int Type)
{
	for (list<AccountBase>::iterator i = AccBase.begin(); i != AccBase.end(); ++i)
	{
		if (i->Name == szName)
		{
			switch (Type)
			{
				case 3: return i->Assists;
				case 2: return i->Deaths;
				case 0:
				case 1: return i->Kills;
			}
		}
	}
	return 0;
}

void PartyUI::ClearRoster()
{
	for (list<AccountBase>::iterator i = AccBase.begin(); i != AccBase.end(); ++i)
	{
		i->Deaths = 0;
		i->Kills = 0;
		i->Assists = 0;
	}
}

wstring GetPingFps(ExTextBox* pTextBox)
{
	wostringstream wPingFpsStr;
	wPingFpsStr << *D2CLIENT_FPS << L" fps, " << *D2CLIENT_Ping << L" ms";
	return wPingFpsStr.str();
}

BOOL Say(LPSTR Message, ...)
{
	CHAR szBuffer[0x400] = "";
	va_list Args;

	va_start(Args, Message);
	vsprintf_s(szBuffer, Message, Args);
	va_end(Args);

	if (strlen(Message) > 0)
	{
		if (D2CLIENT_GetPlayerUnit())
		{
			LPBYTE Packet = new BYTE[(INT)strlen(szBuffer) + 6];
			memset(Packet, 0, (INT)strlen(szBuffer) + 6);

			Packet[0] = 0x15;
			*(LPWORD)&Packet[1] = 1;
			::memcpy(Packet + 3, szBuffer, (INT)strlen(szBuffer));
			D2NET_SendPacket(0, Packet, (INT)strlen(szBuffer) + 6);
			delete[] Packet;
		}

		/*else
		{
			::memcpy((CHAR *)D2MULTI_ChatBoxMsg, szBuffer, strlen(szBuffer) + 1);
			D2MULTI_DoChat();
		}*/
	}

	return TRUE;
}

void SharePing(ExControl * tt)
{
	Say("My ping : %d ms / %d fps", *D2CLIENT_Ping, *D2CLIENT_FPS);
}

DWORD GetPvpFlagsEx(DWORD dwUnitId)
{
	DWORD dwFlags = 0;
	RosterUnit* ptPlayer = GetRosterById(dwUnitId);

	if (!ptPlayer) return 0;
	if (!D2CLIENT_GetPlayerUnit()) return 0;

	if (dwUnitId == D2CLIENT_GetPlayerUnit()->dwUnitId)
	{
		if (ptPlayer->wPartyId != 0xFFFF)
			dwFlags |= PVP_ALLIED_WITH_YOU;
		return dwFlags;
	}

	if (D2CLIENT_TestPvPFlag(dwUnitId, D2CLIENT_GetPlayerUnit()->dwUnitId, 8))
		dwFlags |= PVP_HOSTILED_YOU;

	if (D2CLIENT_TestPvPFlag(D2CLIENT_GetPlayerUnit()->dwUnitId, dwUnitId, 8))
		dwFlags |= PVP_HOSTILED_BY_YOU;

	if (ptPlayer->dwPartyFlags & 2)
		dwFlags |= PVP_INVITED_YOU;

	if (ptPlayer->dwPartyFlags & 4)
		dwFlags |= PVP_INVITED_BY_YOU;

	if (ptPlayer->wPartyId != 0xFFFF && ptPlayer->dwPartyFlags & 1)
	{
		RosterUnit* pMe = GetRosterById(D2CLIENT_GetPlayerUnit()->dwUnitId);
		if (!pMe) return 0;

		if (pMe->wPartyId == ptPlayer->wPartyId) dwFlags |= PVP_ALLIED_WITH_YOU;
		else dwFlags |= PVP_ALLIED;
	}

	return dwFlags;
}

int GetFrameColor(DWORD dwUnitId)
{
	DWORD Flaga = GetPvpFlagsEx(dwUnitId);
	if (Flaga & PVP_HOSTILED_BY_YOU || Flaga & PVP_HOSTILED_YOU) return 0x50;
	if (Flaga & PVP_ALLIED_WITH_YOU) return 0x74;
	if (Flaga & PVP_ALLIED) return 0x59;
	return 0x15;
}

int	GetPlayerCount()
{
	int i = 0;
	for (RosterUnit * pRoster = *D2CLIENT_Roster; pRoster; pRoster = pRoster->pNext)
		i++;
	return i;
}

wstring GetPartyCount(ExTextBox* pTextBox)
{
	wostringstream wPartyCount;
	wPartyCount << L'(' << GetPlayerCount() << L')';
	return wPartyCount.str();
}

void PartyClearScreen()
{
	if (D2CLIENT_UIModes[UI_CHARACTER] ||
		D2CLIENT_UIModes[UI_INVENTORY] ||
		D2CLIENT_UIModes[UI_MAINMENU] ||
		D2CLIENT_UIModes[UI_CUBE] ||
		D2CLIENT_UIModes[UI_QUEST] ||
		D2CLIENT_UIModes[UI_HELP] ||
		D2CLIENT_UIModes[UI_WPMENU] ||
		D2CLIENT_UIModes[UI_MSGS] ||
		D2CLIENT_UIModes[UI_MERC])
		D2CLIENT_ClearScreen2();
}

bool isOpen()
{
	if (PartyScreen) return true;
	return false;
}

RosterUnit * GetRosterByName(const char* szName)
{
	for (RosterUnit* pRoster = *D2CLIENT_Roster; pRoster; pRoster = pRoster->pNext)
	if (!strcmp(pRoster->szName, szName))
		return pRoster;
	return 0;
}

list<PlayerTable>::iterator GetPartyListEntry(DWORD UnitID)
{
	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
	{
		if (i->UnitId == UnitID) return i;
	}
	return PlayerList.end();
}

BOOL __fastcall PartyUI::OnPartyUpdate(BYTE *aPacket) //0x8C Relationship update
{
	D2CLIENT_PartyUpdate_I(aPacket);

	if (!isOpen()) return 0;
	PartyUI::Resort();
	PartyUI::Update();
	return 0;
}

BOOL __fastcall PartyUI::OnPartyUpdate2(BYTE *aPacket) //0x8b Player Relationship (Wants to party etc)
{
	D2CLIENT_PartyUpdate_II(aPacket);
	if (!isOpen()) return 0;
	PartyUI::Update();
	return 0;
}

BOOL __fastcall PartyUI::OnPartyUpdate3(BYTE *aPacket)  //0x8D Assign To Party
{
	D2CLIENT_PartyUpdate_IV(aPacket);

	if (!isOpen()) return 0;
	PartyUI::Resort();
	PartyUI::Update();
	return 0;
}

BOOL __fastcall PartyUI::GetRoster(BYTE* aPacket) //0x66 HANDLE SRV->CLT
{
	Srv2Clt::p0x66* p = (Srv2Clt::p0x66*)aPacket;
	RosterUnit * ptRoster = GetRosterById(p->dwPlayerID);
	if (!ptRoster)  return 0;
	string szName = ptRoster->szName;

	for (list<AccountBase>::iterator i = AccBase.begin(); i != AccBase.end(); i++)
	{
		if (i->Name == szName) 
		{
			switch (p->aType)
			{
				case 3: { i->Assists = p->aCount; break; }
				case 2: { i->Deaths = p->aCount; break; }
				case 0:
				case 1: { i->Kills = p->aCount; break; }
			}
			break;
		}
	}
	PartyUI::Update();
	return 0;
}

int GetPlayerArea(UnitAny* ptUnit)
{
	if (ptUnit)
	if (ptUnit->pPath)
	if (ptUnit->pPath->pRoom1)
	if (ptUnit->pPath->pRoom1->pRoom2)
	if (ptUnit->pPath->pRoom1->pRoom2->pLevel)
		return ptUnit->pPath->pRoom1->pRoom2->pLevel->nLevel;
	return 0;
}

bool isTownLvl(UnitAny* ptUnit)
{
	if (!ptUnit) return false;
	if (GetPlayerArea(ptUnit) == D2COMMON_GetTownLevel(ptUnit->dwAct)) return true;
	return false;
}

void Squelch(ExControl* ptControl)
{
	list<PlayerTable>::const_iterator Player = PlayerList.end();
	DWORD PlayerId = 0;
	DWORD Flaga = 0;
	for (list<PlayerTable>::const_iterator i = PlayerList.begin(); i != PlayerList.end(); i++)
	{
		if (i->Squelch == ptControl) { Player = i; PlayerId = i->UnitId; break; }
	}
	if (Player == PlayerList.end()) return;

	RosterUnit * ptRoster = GetRosterById(PlayerId);
	if (!ptRoster){ PartyUI::Update(); return; }

	for (RosterInfo* pInfo = *(*D2CLIENT_Roster)->ptInfo; pInfo; pInfo = pInfo->ptNext)
	{
		if (PlayerId == pInfo->dwUnitId) { Flaga = pInfo->fFlags; break; }
	}
	
	if (Flaga & 4)
	{
		Clt2Srv::p0x5D Packet = {};
		Packet.P_5D = 0x5D;
		Packet.nButton = PB_SQUELCH;
		Packet.nState = 0;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
	}
	else
	{
		Clt2Srv::p0x5D Packet = {};
		Packet.P_5D = 0x5D;
		Packet.nButton = PB_SQUELCH;
		Packet.nState = 1;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
	}
	*D2CLIENT_SentBytes += sizeof(Clt2Srv::p0x5D);
	*D2CLIENT_SentPackets++;
}

void Loot(ExControl* ptControl)
{
	list<PlayerTable>::iterator Player = PlayerList.end();;
	DWORD PlayerId = 0;
	DWORD Flaga = 0;
	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); i++)
	{
		if (i->Loot == ptControl) { Player = i; PlayerId = i->UnitId; break; }
	}
	if (Player == PlayerList.end()) return;

	RosterUnit * ptRoster = GetRosterById(PlayerId);
	if (!ptRoster){ PartyUI::Update(); return; }

	for (RosterInfo* pInfo = *(*D2CLIENT_Roster)->ptInfo; pInfo; pInfo = pInfo->ptNext)
	{
		if (PlayerId == pInfo->dwUnitId) { Flaga = pInfo->fFlags; break; }
	}

	if (Flaga & 1)
	{
		Clt2Srv::p0x5D Packet = {};
		Packet.P_5D = 0x5D;
		Packet.nButton = PB_LOOT;
		Packet.nState = 0;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
	}
	else
	{
		Clt2Srv::p0x5D Packet = {};
		Packet.P_5D = 0x5D;
		Packet.nButton = PB_LOOT;
		Packet.nState = 1;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
	}
	*D2CLIENT_SentBytes += sizeof(Clt2Srv::p0x5D);
	*D2CLIENT_SentPackets++;
}

void Host(ExControl* ptControl)
{
	static wchar_t* wStrTown = D2LANG_GetLocaleText(4121);

	list<PlayerTable>::iterator Player = PlayerList.end();
	DWORD PlayerId = 0;
	string szName;
	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); i++)
	{
		if (i->Host == ptControl) { Player = i; break; }
	}
	if (Player == PlayerList.end()) return;
	PlayerId = Player->UnitId;
	if (_wtoi(Player->Level->GetText().c_str()) < 9) return;
	UnitAny* ptUnit = D2CLIENT_GetPlayerUnit();
	if (isTownLvl(ptUnit))
	{
		DWORD Flaga = GetPvpFlagsEx(PlayerId);
		if (!(Flaga & PVP_HOSTILED_BY_YOU))
		{
			Clt2Srv::p0x5D Packet = {};
			Packet.P_5D = 0x5D;
			Packet.nButton = PB_HOSTILE;
			Packet.nState = 1;
			Packet.dwUnitId = PlayerId;

			D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
		}
		else
		{
			Clt2Srv::p0x5D Packet = {};
			Packet.P_5D = 0x5D;
			Packet.nButton = PB_HOSTILE;
			Packet.nState = 0;
			Packet.dwUnitId = PlayerId;

			D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5D));
		}
		*D2CLIENT_SentBytes += sizeof(Clt2Srv::p0x5D);
		*D2CLIENT_SentPackets++;
	}
	else
		D2CLIENT_PrintGameString(wStrTown, 1);
}

void Invite(ExControl* ptControl)
{
	list<PlayerTable>::iterator Player = PlayerList.end();;
	DWORD PlayerId = 0;
	string szName;
	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); i++)
	{
		if (i->Invite == ptControl) { Player = i; break; }
	}
	if (Player == PlayerList.end()) return;
	PlayerId = Player->UnitId;
	DWORD Flaga = GetPvpFlagsEx(PlayerId);

	if (!(Flaga & PVP_INVITED_BY_YOU) && !(Flaga & PVP_INVITED_YOU))
	{
		Clt2Srv::p0x5E Packet = {};
		Packet.P_5E = 0x5E;
		Packet.nButton = PB_INVITE_PLAYER;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5E));
	}
	else if (Flaga & PVP_INVITED_BY_YOU)
	{
		Clt2Srv::p0x5E Packet = {};
		Packet.P_5E = 0x5E;
		Packet.nButton = PB_INVITE_CANCEL;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5E));
	}
	else  if (Flaga & PVP_INVITED_YOU)
	{
		Clt2Srv::p0x5E Packet = {};
		Packet.P_5E = 0x5E;
		Packet.nButton = PB_INVITE_ACCEPT;
		Packet.dwUnitId = PlayerId;

		D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5E));
	}
	*D2CLIENT_SentBytes += sizeof(Clt2Srv::p0x5E);
	*D2CLIENT_SentPackets++;
}

void PartyUI::Clear()
{
	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
	{
		delete i->Frame;
		delete i->Level;
		delete i->Name;
		delete i->Class;
		delete i->Location;
		delete i->Kills;
		delete i->Assists;
		delete i->Deaths;
		delete i->Invite;
		delete i->Host;
		delete i->Loot;
		delete i->Squelch;
	}
	for each (auto i in Group) delete i;
	Group.clear();
	PlayerList.clear();
}

void PartyUI::Refresh(char * szSkip)
{
	if (!PartyScreen)
		return;

	PartyUI::Fill(szSkip);
}

void OnScroll(ExControl* ptControl)
{
	PartyUI::Refresh();
}

void Leave(ExControl * tt)
{
	Clt2Srv::p0x5E Packet = {};
	Packet.P_5E = 0x5E;
	Packet.nButton = PB_LEAVE_PARTY;
	Packet.dwUnitId = D2CLIENT_GetPlayerUnit()->dwUnitId;

	D2NET_SendPacket(1, (BYTE*)&Packet, sizeof(Clt2Srv::p0x5E));
	*D2CLIENT_SentBytes += sizeof(Clt2Srv::p0x5E);
	*D2CLIENT_SentPackets++;

	(*D2CLIENT_Roster)->wPartyId = -1;
	PartyUI::Refresh();
}

AccountBase* PartyUI::FindRoster(string szName)
{
	/*for (auto &i : AccBase)
	{
		if (i.Name == szName)
		{
			return &i;
		}
	}*/

	for each (auto i in AccBase)
	{
		if (i.Name == szName)
		{
			AccountBase* a = &i;
			return a;
		}
	}
	return 0;
}

bool ListCompare(const PlayerTable & first, const PlayerTable & second)
{
	RosterUnit * pRost1 = GetRosterById(first.UnitId);
	RosterUnit * pRost2 = GetRosterById(second.UnitId);

	if (!pRost1 || !pRost2) { return false; }

	if (pRost1->wPartyId == pRost2->wPartyId)
	{
		AccountBase* r1 = PartyUI::FindRoster(pRost1->szName);
		AccountBase* r2 = PartyUI::FindRoster(pRost2->szName);
		if (!r1 || !r2)
		{
			string f = pRost1->szName;
			string s = pRost2->szName;
			return f < s;
		}
		else
		{

			if (r1->Kills == r2->Kills)
			{
				if (r1->Deaths == r2->Deaths)
				{
					string f = pRost1->szName;
					string s = pRost2->szName;
					return f < s;
				}
				return r1->Deaths < r2->Deaths; // Less deaths = higher in roster
			}
			return r1->Kills > r2->Kills;
		}
	}

	return pRost1->wPartyId < pRost2->wPartyId;
}

wstring GetLvlNameEx(int LvlNo)
{
	wstring wTxt = D2CLIENT_GetLevelName(LvlNo);
	return wTxt;
}

string GetLevel(int Level)
{
	ostringstream text;
	text << "" << Level;
	return text.str();
}

string GetKDA(string szName, int Type)
{
	ostringstream text;

	if (Type == 1)
		text << "" << PartyUI::FindRoster(szName, Type);
	if (Type == 2)
		text << "" << PartyUI::FindRoster(szName, Type);
	if (Type == 3)
		text << "" << PartyUI::FindRoster(szName, Type);

	return text.str();
}

void PartyUI::Update()
{
	if (!PartyScreen) return;

	static wstring wStrHost1 = D2LANG_GetLocaleText(4106);
	static wstring wStrHost2 = D2LANG_GetLocaleText(4108);

	static wstring wStrInv1 = D2LANG_GetLocaleText(4100); //Invite
	static wstring wStrInv2 = D2LANG_GetLocaleText(4104); //Cancel invite

	static wstring wStrInv3;
	if (wStrInv3.empty())
	{
		wStrInv3 = D2LANG_GetLocaleText(4102);
		wStrInv3 += D2LANG_GetLocaleText(4103);
	}

	static wstring wStrLoot1; //Click To Allow Loot
	if (wStrLoot1.empty())
	{
		wStrLoot1 = D2LANG_GetLocaleText(4110);
		wStrLoot1 += L" ";
		wStrLoot1 += D2LANG_GetLocaleText(4111);
	}

	static wstring wStrLoot2; //Click To Disallow Loot
	if (wStrLoot2.empty())
	{
		wStrLoot2 = D2LANG_GetLocaleText(4112);
		wStrLoot2 += L" ";
		wStrLoot2 += D2LANG_GetLocaleText(4113);
	}

	static wstring wStrSquelch1 = D2LANG_GetLocaleText(4118);
	static wstring wStrSquelch2 = D2LANG_GetLocaleText(4119);

	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); i++)
	{
		RosterUnit* ptRoster = GetRosterById(i->UnitId);
		if (!ptRoster)
		{
			PartyUI::Refresh();
			return;
		}

		i->Frame->aColor = GetFrameColor(ptRoster->dwUnitId);
		i->Level->SetText(GetLevel(ptRoster->wLevel));
		i->Location->SetText(GetLvlNameEx(ptRoster->dwUnitId == D2CLIENT_GetPlayerUnit()->dwUnitId ? GetPlayerArea(D2CLIENT_GetPlayerUnit()) : ptRoster->dwLevelId));
		i->Kills->SetText(GetKDA(ptRoster->szName, 1));
		i->Deaths->SetText(GetKDA(ptRoster->szName, 2));
		i->Assists->SetText(GetKDA(ptRoster->szName, 3));

		DWORD Flaga = GetPvpFlagsEx(ptRoster->dwUnitId);

		if (i->Host)
		{
			UnitAny* ptUnit = D2CLIENT_GetPlayerUnit();

			if (isTownLvl(ptUnit))
				i->Host->cState = i->Host->VISIBLE;
			else
				i->Host->cState = i->Host->DISABLED;

			if (Flaga & 8)
			{
				i->Host->SetHoover(wStrHost2);
				i->Host->aFrame = 6;
			}
			else
			{
				i->Host->SetHoover(wStrHost1);
				i->Host->aFrame = 4;
			}
		}

		if (i->Invite)
		{
			if (Flaga & PVP_ALLIED || Flaga & PVP_ALLIED_WITH_YOU)
				i->Invite->cState = i->Invite->DISABLED;
			else
				i->Invite->cState = i->Invite->VISIBLE;

			if (!(Flaga & PVP_INVITED_BY_YOU) && !(Flaga & PVP_INVITED_YOU))
			{
				i->Invite->SetHoover(wStrInv1);
				i->Invite->SetColor(COL_WHITE);
			}
			else if (Flaga & PVP_INVITED_BY_YOU)
			{
				i->Invite->SetHoover(wStrInv2);
				i->Invite->SetColor(COL_DARKGREEN);
			}
			else if (Flaga & PVP_INVITED_YOU)
			{
				i->Invite->SetHoover(wStrInv3);
				i->Invite->SetColor(COL_LIGHTGREEN);
			}
		}

		if (i->Loot)
		{
			for (RosterInfo* pInfo = *(*D2CLIENT_Roster)->ptInfo; pInfo; pInfo = pInfo->ptNext)
			{
				if (ptRoster->dwUnitId == pInfo->dwUnitId)
				{
					Flaga = pInfo->fFlags;
					break;
				}
			}

			if ((*D2LAUNCH_BnData)->nCharFlags & 4)
				i->Loot->cState = i->Loot->VISIBLE;
			else
				i->Loot->cState = i->Loot->DISABLED;

			if (Flaga & 1)
			{
				i->Loot->SetHoover(wStrLoot2);
				i->Loot->aFrame = 14;
			}
			else
			{
				i->Loot->SetHoover(wStrLoot1);
				i->Loot->aFrame = 12;
			}
		}

		if (i->Squelch)
		{
			for (RosterInfo* pInfo = *(*D2CLIENT_Roster)->ptInfo; pInfo; pInfo = pInfo->ptNext)
			{
				if (ptRoster->dwUnitId == pInfo->dwUnitId) { Flaga = pInfo->fFlags; break; }
			}
			if (Flaga & 4)
			{
				i->Squelch->SetHoover(wStrSquelch2);
				i->Squelch->aFrame = 10;
			}
			else
			{
				i->Squelch->SetHoover(wStrSquelch1);
				i->Squelch->aFrame = 8;
			}
		}
	}
	if (LeaveB)
	{
		if (GetRosterById(D2CLIENT_GetPlayerUnit()->dwUnitId)->wPartyId == 0xFFFF)
			LeaveB->SetState(LeaveB->INVISIBLE);
		else
			LeaveB->SetState(LeaveB->VISIBLE);
	}
}

void PartyUI::Resort(char *szSkip)
{
	int z = 1, LastTeamId = 0;
	TeamOffset = 0;

	for each (auto i in Group) { PartyScreen->DeleteChild(i); delete i; }
	Group.clear();

	if (PlayerList.size() > 1) PlayerList.sort(&ListCompare);

	if (GetPlayerCount() > 15)
	{
		int j = 1;
		for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); ++j)
		{
			if (j - 1 < pOffset || j - pOffset > 15)
			{
				delete i->Frame;
				delete i->Level;
				delete i->Name;
				delete i->Class;
				delete i->Location;
				delete i->Kills;
				delete i->Assists;
				delete i->Deaths;
				delete i->Invite;
				delete i->Host;
				delete i->Loot;
				delete i->Squelch;
				i = PlayerList.erase(i);
				continue;
			}
			++i;
		}
	}

	for (list<PlayerTable>::iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
	{
		RosterUnit * ptRoster = GetRosterById(i->UnitId);
		if (!ptRoster) continue;

		int TextFont = 0;

		if (!LastTeamId || LastTeamId != ptRoster->wPartyId)
		{
			LastTeamId = ptRoster->wPartyId;
			TeamOffset += 20;
			wstring TeamId;
			wchar_t tt = (int)(64 + (TeamOffset / 20));
			if (LastTeamId != 0xFFFF)
			{
				TeamId = D2LANG_GetLocaleText(4016);
				TeamId.erase(TeamId.length() - 1);
				TeamId += tt;
			}
			else TeamId = D2LANG_GetLocaleText(4015);
			ExTextBox * ptGrp = new ExTextBox(i->Frame->GetX() + 5, 50 + (z * 25) + TeamOffset, 0, 0, TeamId, 0, 0);
			PartyScreen->AddChild(ptGrp);
			Group.push_back(ptGrp);
		}

		D2WIN_SetTextSize(TextFont);

		int yPos = 70 + (z * 25) + TeamOffset;
		int TextPos = ((yPos * 2) - 20 + D2WIN_GetFontHeight()) / 2;

		i->Frame->SetY(yPos - 20);
		i->Level->SetY(TextPos);
		i->Name->SetY(TextPos);
		i->Class->SetY(yPos);
		i->Location->SetY(TextPos);
		i->Deaths->SetY(TextPos);
		i->Kills->SetY(TextPos);
		i->Assists->SetY(TextPos);

		if (i->Invite) i->Invite->SetY(yPos);
		if (i->Host) i->Host->SetY(yPos);
		if (i->Loot) i->Loot->SetY(yPos);
		if (i->Squelch) i->Squelch->SetY(yPos);
		z++;
	}
	if (PartyScreen)
	{
		PartyScreen->Resize(PartyScreen->GetWidth(), ((75 + (PlayerList.size() * 25) + TeamOffset)));
		if (GetPlayerCount() > 15)
		{
			Scroll->SetState(Scroll->VISIBLE);
			Scroll->SetHeight(PartyScreen->GetHeight());
			if (Scroll->sMax != GetPlayerCount() - 15) pOffset = 0;
			Scroll->sMax = GetPlayerCount() - 15;
		}
		else
		{
			Scroll->SetState(Scroll->INVISIBLE);
		}
	}
}

wstring GetName(char* szName)
{
	wostringstream text;
	text << L"" << szName;
	return text.str();
}

void PartyUI::Fill(char *szSkip)
{
	PartyUI::Clear();
	int i = 1;
	string szName(szSkip ? szSkip : "");

	for (RosterUnit *ptRoster = *D2CLIENT_Roster; ptRoster; ptRoster = ptRoster->pNext, ++i)
	{
		if (szName == ptRoster->szName) { --i; continue; }

		PlayerTable Tbl = PlayerTable();

		int TextFont = 0;
		D2WIN_SetTextSize(TextFont);
		int yPos = 70 + (i * 25);
		int TextPos = ((yPos * 2) - 20 + D2WIN_GetFontHeight()) / 2;

		Tbl.UnitId = ptRoster->dwUnitId;

		Tbl.Frame = new ExBox(0, yPos, 437 + 35 + 80, 22, GetFrameColor(ptRoster->dwUnitId), 2);
		Tbl.Frame->SetAlign(Tbl.Frame->CENTER, Tbl.Frame->NONE);

		Tbl.Name = new ExTextBox(Tbl.Frame->GetX() + 10, TextPos, 0, TextFont, GetName(ptRoster->szName), 0, 0);

		Tbl.Class = new ExImage(Tbl.Frame->GetX() + 140, yPos, 5, ptRoster->dwClassId, CellFiles::Class);
		Tbl.Class->Hoover = GetClassById(ptRoster->dwClassId);

		Tbl.Level = new ExTextBox(Tbl.Frame->GetX() + 165, TextPos, COL_WHITE, 1, GetLevel(ptRoster->wLevel), 0, 0);

		Tbl.Location = new ExTextBox(Tbl.Frame->GetX() + 187, TextPos, COL_WHITE, TextFont, GetLvlNameEx(ptRoster->dwUnitId == D2CLIENT_GetPlayerUnit()->dwUnitId ? GetPlayerArea(D2CLIENT_GetPlayerUnit()) : ptRoster->dwLevelId), 0, 0);
		Tbl.Kills = new ExTextBox(Tbl.Frame->GetX() + 367, TextPos, COL_WHITE, 1, GetKDA(ptRoster->szName, 1), 0, 0);
		Tbl.Deaths = new ExTextBox(Tbl.Frame->GetX() + 402, TextPos, COL_WHITE, 1, GetKDA(ptRoster->szName, 2), 0, 0);
		Tbl.Assists = new ExTextBox(Tbl.Frame->GetX() + 437, TextPos, COL_WHITE, 1, GetKDA(ptRoster->szName, 3), 0, 0);

		PartyScreen->AddChild(Tbl.Frame);
		PartyScreen->AddChild(Tbl.Name);
		PartyScreen->AddChild(Tbl.Class);
		PartyScreen->AddChild(Tbl.Level);
		PartyScreen->AddChild(Tbl.Location);
		PartyScreen->AddChild(Tbl.Kills);
		PartyScreen->AddChild(Tbl.Deaths);
		PartyScreen->AddChild(Tbl.Assists);

		if (ptRoster->dwUnitId != D2CLIENT_GetPlayerUnit()->dwUnitId)
		{
			Tbl.Invite = new ExButton(Tbl.Frame->GetX() + 437 + 35, yPos, 0, 18, L"", CellFiles::PARTY, &Invite, 0);
			PartyScreen->AddChild(Tbl.Invite);
			
			Tbl.Host = new ExButton(Tbl.Frame->GetX() + 437 + 35 + 20, yPos, 0, 6, L"", CellFiles::PARTY, &Host, 0);
			PartyScreen->AddChild(Tbl.Host);

			Tbl.Loot = new ExButton(Tbl.Frame->GetX() + 437 + 35 + 40, yPos, 0, 14, L"", CellFiles::PARTY, &Loot, 0);
			PartyScreen->AddChild(Tbl.Loot);

			Tbl.Squelch = new ExButton(Tbl.Frame->GetX() + 437 + 35 + 60, yPos, 0, 8, L"", CellFiles::PARTY, &Squelch, 0);
			PartyScreen->AddChild(Tbl.Squelch);
		}
		else
			Tbl.Location->SetText(GetLvlNameEx(GetPlayerArea(D2CLIENT_GetPlayerUnit())));

		PlayerList.push_back(Tbl);
	}
	PartyUI::Resort(szSkip);
	PartyUI::Update();
}

void PartyUI::ShowHide()
{
	static ExTextBox * Charname;
	static ExTextBox * Class;
	static ExTextBox * PlayerCount;
	static ExTextBox * Pings;
	static ExTextBox * Location;
	static ExImage * Kills;
	static ExImage * Assists;
	static ExImage * Deaths;

	if (!PartyScreen)
	{
		pOffset = 0;
		PartyClearScreen();
		static wstring wPartyStr, wClassStr, wCharStr, wAccStr;
		if (!wPartyStr.length()) wPartyStr = D2LANG_GetLocaleText(3926);
		if (!wClassStr.length()) wClassStr = D2LANG_GetLocaleText(5322);
		if (!wCharStr.length()) wCharStr = D2LANG_GetLocaleText(5287);
		if (!wAccStr.length()) wAccStr = D2LANG_GetLocaleText(5224);

		PartyScreen = new ExWindow(0, 20, 437 + 35 + 80 + 30, 85 + (GetPlayerCount() * 25) + TeamOffset, false, wPartyStr);
		PartyScreen->SetAlign(PartyScreen->CENTER, PartyScreen->NONE);

		PlayerCount = new ExTextBox(PartyScreen->GetX() + 5, 101 - 30, 8, 1, &GetPartyCount, 0, 0);
		Charname = new ExTextBox(PartyScreen->GetX() + 28, 105 - 30, 0, 0, wCharStr, 0, 0);
		Class = new ExTextBox(PartyScreen->GetX() + 154, 105 - 30, 0, 0, wClassStr, 0, 0);
		Location = new ExTextBox(PartyScreen->GetX() + 237, 105 - 30, 0, 0, "Location", 0, 0);

		Kills = new ExImage(PartyScreen->GetX() + 377, 105 - 30, 5, 1, CellFiles::MONINDICATOR);
		Kills->Hoover = L"Kills";

		Deaths = new ExImage(PartyScreen->GetX() + 412, 105 - 30, 5, 0, CellFiles::MONINDICATOR);
		Deaths->Hoover = L"Deaths";

		Assists = new ExImage(PartyScreen->GetX() + 447, 105 - 30, 5, 2, CellFiles::MONINDICATOR);
		Assists->Hoover = L"Assists";

		Pings = new ExTextBox(PartyScreen->GetX() + 10, 64 - 30, 0, 0, &GetPingFps, &SharePing, 0);
		Pings->SetHoverable(false);

		LeaveB = new ExButton(PartyScreen->GetX() + 460, 105 - 30, 2, 0, D2LANG_GetLocaleText(4152), CellFiles::PARTYBUTTON, &Leave, 0);

		if (GetRosterById(D2CLIENT_GetPlayerUnit()->dwUnitId)->wPartyId == 0xFFFF)
			LeaveB->SetState(LeaveB->INVISIBLE);

		Scroll = new ExScrollBar(PartyScreen->GetX() + 530, PartyScreen->GetY(), 0, GetPlayerCount() - 15, PartyScreen->GetHeight(), &pOffset, &OnScroll);
		if (GetPlayerCount() < 15) Scroll->SetState(Scroll->INVISIBLE);

		PartyScreen->AddChild(PlayerCount);
		PartyScreen->AddChild(Charname);
		PartyScreen->AddChild(Class);
		PartyScreen->AddChild(Location);
		PartyScreen->AddChild(Kills);
		PartyScreen->AddChild(Deaths);
		PartyScreen->AddChild(Assists);
		PartyScreen->AddChild(Pings);
		PartyScreen->AddChild(LeaveB);
		PartyScreen->AddChild(Scroll);
		PartyUI::Fill();
	}
	else
	{
		delete Scroll;
		delete LeaveB;
		delete Pings;
		delete Charname;
		delete Location;
		delete Kills;
		delete Deaths;
		delete Assists;
		delete Class;
		delete PlayerCount;
		PartyUI::Clear();
		delete PartyScreen;
		PartyScreen = 0;
		Scroll = 0;
		LeaveB = 0;
	}
	D2CLIENT_UIModes[UI_PARTY] = PartyScreen ? 1 : 0;
}

void PartyUI::ClearScreenHandle()
{
	if (isOpen())
	{
		PartyUI::ShowHide();
		return;
	}
	D2CLIENT_ClearScreen2();
}

int __fastcall Packet0x5A(Srv2Clt::p0x5A* aPacket)
{
	switch (aPacket->MsgType)
	{
	case 0: //"%Name1(%Name2) dropped due to time out."
	case 1: //"%Name1(%Name2) dropped due to errors."
		PartyUI::Refresh(aPacket->Name1);
		break;
	case 7: // Player Relations (Bottom Left Text)
		PartyUI::Resort();
		PartyUI::Update();
		break;
	case 2: // "%Name1(%Name2) joined our world. Diablo's minions grow stronger."
	case 3: // "%Name1(%Name2) left our world. Diablo's minions weaken."
		PartyUI::AddAccount(aPacket->Name1, aPacket->Name2);
		PartyUI::Refresh();
		break;
	}
	return D2CLIENT_EventMsg_I(aPacket);
}

void PartyUI::OnPatch()
{
	Patch(0xC3, "D2Client.dll", 0x61F10, 0, 5, "Party Draw");

	Patch(CALL, "D2Client.dll", 0x83007, (DWORD)PartyUI::ShowHide, 5, "UI Party Fix On Destroy I");
	Patch(JUMP, "D2Client.dll", 0x828D9, (DWORD)PartyUI::ShowHide, 5, "UI Party Fix On Destroy I");

	//Patch(CALL, "D2Client.dll", 0xC24F8, (DWORD)PartyUI::ShowHide, 5, "UI Party Fix On Destroy I");
	//Patch(CALL, "D2Client.dll", 0x3C0E5, (DWORD)PartyUI::ShowHide, 5, "UI Party Fix On Destroy II");
	//Patch(JUMP, "D2Client.dll", 0xC1F1B, (DWORD)PartyUI::ShowHide, 5, "UI Party Fix On Show");
	//Patch(CALL, "D2Client.dll", 0x661AD, (DWORD)PartyUI::ShowHide, 5, "UI Minibar fix");

	//Patch(0x5B, "D2Client.dll", 0x661AD + 5, 0x90909090, 5, "UI Minibar fix");
	//Patch(0xC3, "D2Client.dll", 0x661AD + 10, 0, 1, "UI Minibar fix");

	WriteDword((DWORD*)&D2CLIENT_UIModesCallTree[UICall::PARTYSCREEN], (DWORD)&PartyUI::ShowHide);
	WriteDword((DWORD*)&D2CLIENT_UIModesCallTree[UICall::CLEARSCREEN], (DWORD)&PartyUI::ClearScreenHandle);

	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x5A].CallBack, (DWORD)&Packet0x5A);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x66].CallBack, (DWORD)&PartyUI::GetRoster);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x66].PacketLen, sizeof(Srv2Clt::p0x66));
	WriteDword((DWORD*)&D2NET_PacketHandler[0x66], sizeof(Srv2Clt::p0x66));

	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x8B].CallBack, (DWORD)&PartyUI::OnPartyUpdate2);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x8C].CallBack, (DWORD)&PartyUI::OnPartyUpdate);
	WriteDword((DWORD*)&D2CLIENT_PacketHandler[0x8D].CallBack, (DWORD)&PartyUI::OnPartyUpdate3);

	for (int i = 1; i < 38; ++i)
	{
		if (i == UI_PARTY) continue;
		int** Colls = D2CLIENT_UICollisions;
		Colls[i][UI_PARTY] = UICOLL_CLOSEOTHER;
	}

	static int PartyCollMap[38] =
	{
		UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_NONE,//UNK, INV, CHAR, MINISKI, SKILL, CHAT
		UICOLL_NONE, UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_CLOSEOTHER,	  //UNK, UNK, NPCMENU, MAINMENU, AUTOMAP, CONFIG
		UICOLL_ERROR, UICOLL_NONE, UICOLL_ERROR, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_NONE,		  //NPCSHOP, ALTDOWN, ANVILL, QUEST, BARKSCROLL, QUESTLOG
		UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER,	  //STATUS AREA, ESCMENUEX, WPMENU, MINIPANEL, PARTY, TRADE
		UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER,
		UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER, UICOLL_NONE, UICOLL_NONE,
		UICOLL_CLOSEOTHER, UICOLL_CLOSEOTHER
	};

	D2CLIENT_UICollisions[UI_PARTY] = PartyCollMap;
}
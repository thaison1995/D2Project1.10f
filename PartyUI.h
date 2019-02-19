#pragma once

#ifndef _PARTYUI_H
#define _PARTYUI_H

struct PlayerTable;
struct AccountBase;

namespace PartyUI
{
	void ShowHide();
	void Fill(char * szSkip = 0);
	void Resort(char * szSkip = 0);
	void Refresh(char * szSkip = 0);
	void Update();

	AccountBase* FindRoster(string szName);
	void AddAccount(string szName, string szAccount);

	BOOL __fastcall OnPartyUpdate(BYTE *aPacket);
	BOOL __fastcall OnPartyUpdate2(BYTE *aPacket);
	BOOL __fastcall OnPartyUpdate3(BYTE *aPacket);
	BOOL __fastcall GetRoster(BYTE* aPacket);

	void ClearRoster();
	void ClearScreenHandle();
	void Clear();
	int FindRoster(string szName, int Type);

	void OnPatch();
}

#endif
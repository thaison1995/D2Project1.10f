#pragma once

#ifndef _D2PACKETCLIENT_H
#define _D2PACKETCLIENT_H

#pragma pack(1)
namespace Clt2Srv
{
	struct p0x0B
	{
		BYTE P_0B;
		BYTE Type;
		DWORD Data;
	};

	struct p0x13 // Interact (click) entity
	{
		// 0x13 [DWORD entity kind] [DWORD id]

		BYTE P_13;
		DWORD dwUnitType;
		DWORD dwUnitId;
	};

	struct p0x18 // Insert item in buffer
	{
		// 0x18 [DWORD id] [DWORD xpos] [DWORD ypos] [DWORD buffer]

		BYTE P_18;
		DWORD itemId;
		DWORD x;
		DWORD y;
		DWORD bufferId;
	};

	struct p0x23 // Item to belt
	{
		// 0x23 [DWORD id] [WORD x] [WORD y]

		BYTE P_23;
		DWORD itemId;
		WORD wX;
		WORD wY;
	};

	struct p0x29 // Scroll to book
	{
		// 0x29 [DWORD scroll id] [DWORD book id]

		BYTE P_29;
		DWORD scrollId;
		DWORD bookId;
	};

	struct p0x3D // Highlight a door
	{
		// 0x3D [DWORD object id] (Logged as Mode(5) crash)

		BYTE P_3D;
		DWORD dwUnitId;
	};

	struct p0x44 // Staff in orifice
	{
		// 0x44 [DWORD orifice entity kind] [DWORD orifice id] [DWORD staff id] [DWORD entity state]

		BYTE P_44;
		DWORD dwHolderType;
		DWORD dwHolderId;
		DWORD dwItemId;	
		DWORD dwObjectState; // 2 -> Cancel, 3-> Accept
	};

	struct p0x49 // Take WP/Close WP
	{
		// 0x49 [DWORD wp id] [BYTE destination] 00 00 00

		BYTE P_49;
		DWORD ObjectId;
		WORD WpId;
		WORD _1;
	};

	struct p0x5D // Squelch/Hostile    
	{
		// 0x5D [BYTE button] [BYTE toggle on/off] [DWORD player id]

		BYTE P_5D;
		BYTE nButton;
		BYTE nState;
		DWORD dwUnitId;
	};

	struct p0x5E // Invite Party
	{
		// 0x5E [BYTE button] [DWORD player id]

		BYTE P_5E;
		BYTE nButton;
		DWORD dwUnitId;
	};

	struct p0x6C // Upload Save
	{
		// 0x6C [BYTE ChunkSize] [DWORD FullSize] [BYTE[ChunkSize] rawSave] [BYTE Unknown]

		BYTE	packID;
		BYTE	packSize;
		DWORD	finalSize : 31;
		DWORD	isCustom : 1;
		BYTE	type;
		BYTE	data[0xFF];
	};
}
#pragma pack()

#endif
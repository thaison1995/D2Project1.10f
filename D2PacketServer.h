#pragma once

#ifndef _D2PACKETSERVER_H
#define _D2PACKETSERVER_H

#pragma pack(1)
namespace Srv2Clt
{
	struct p0x0D // Player Stop
	{
		// 0x0D [BYTE Unit Type] [DWORD Unit Id] [BYTE  Unknown] [WORD Unit X] [WORD Unit Y] [BYTE Unknown] [BYTE Life]

		BYTE P_0D;
		BYTE UnitType;
		DWORD UnitId;
		BYTE Unknown;
		WORD wX;
		WORD wY;
		BYTE Unknown2;
		BYTE Life;
	};

	struct p0x15 // Reassign Player
	{
		// 0x15 [BYTE Unit Type] [DWORD Unit Id] [WORD  X] [WORD Y] [BYTE 0x01 = True || 0x00 = False]

		BYTE P_15;
		BYTE UnitType;
		DWORD UnitId;
		WORD wX;
		WORD wY;
		BYTE bFlash;
	};

	struct p0x2B
	{
		BYTE P_2B;
		DWORD dwSkill;
		DWORD dwFrame;
	};

	struct p0x2D
	{
		BYTE P_2D;
		WORD wName;
		DWORD Code;
		DWORD Quality;
		BOOL isSock;
		BOOL isEth;
	};

	struct p0x3F // Use Stackable Item   
	{
		// 0x3F [BYTE SellIcon] [DWORD ItemGid] [WORD SkillId]

		BYTE nHeader;
		BYTE nCursor;
		DWORD dwItemId;
		WORD nSkill;
	};

	struct p0x44
	{
		BYTE P_44;
		DWORD UnitId;
		BOOL LifeBar;
	};

	struct p0x45
	{
		BYTE P_45;
		BYTE Type;
		WORD Timer;
		DWORD dwUnitId;
		DWORD Amount;
		BYTE Unk;
	};

	struct p0x5A // Event Messages
	{
		// 0x5A [BYTE MessageType] [BYTE Color] [DWORD Arg] [BYTE ArgTypes] [NULLSTRING[16] Name1] [NULLSTRING[16] NAME2]

		BYTE P_5A;		//0x00
		BYTE MsgType;	//0x01
		BYTE Color;		//0x02
		DWORD Param1;	//0x03
		BYTE Param2;	//0x07
		char Name1[16]; //0x08
		char Name2[16]; //0x18
	};

	struct p0x62
	{
		// 0x62 [BYTE UnitType] [DWORD UnitGid] [BYTE Unused]

		BYTE nHeader;
		WORD Timer;
		DWORD aCount;
	};

	struct p0x66
	{
		BYTE nHeader;
		DWORD dwPlayerID;
		BYTE aType;
		int aCount;
	};

	struct p0x7C // Use Scroll              
	{
		BYTE nHeader;
		BYTE bUnitType;
		DWORD dwUnitGUID;
	};

	struct p0x7F // Ally Party Info
	{
		//  0x7F [BYTE Unit Type] [WORD Unit Life] [DWORD Unit Id] [DWORD Unit Area Id]

		BYTE Header;
		BYTE UnitType;
		WORD UnitLife;
		DWORD UnitId;
		WORD Location;
	};

	struct p0xA6
	{
		BYTE P_A6;
		BYTE MsgType;
		WORD PacketLen;
	};

	struct p0xA7 // Delayed State - State On
	{
		// 0xA7 [BYTE Unit Type] [DWORD Unit Id] [BYTE State]

		BYTE nHeader;
		BYTE nUnitType;
		DWORD dwUnitGUID;
		BYTE nState;
	};

	struct p0xA8 // Set State - State Update
	{
		// 0xA8 [BYTE Unit Type] [DWORD Unit Id] [BYTE PacketLength] [BYTE State] [VOID State Effects]

		BYTE Header;
		BYTE UnitType;
		DWORD UnitId;
		BYTE PacketLen;
		BYTE StateNo;
		BYTE Data[500];  // Random size
	};

	struct p0xA9 // Remove State - State Off
	{
		// 0xA9 [BYTE Unit Type] [DWORD Unit Id] [BYTE State]

		BYTE nHeader;
		BYTE nUnitType;
		DWORD dwUnitGUID;
		BYTE nState;
	};

	struct p0xAA // Add Unit - New Unit States
	{
		// 0xAA [BYTE Unit Type] [DWORD Unit Id] [BYTE PacketLength] [VOID State Info]

		BYTE nHeader;
		BYTE nUnitType;
		DWORD dwUnitGUID;
		BYTE nPacketLength;
		BYTE Stream[500];
	};

	struct p0xB3 // Download Save
	{
		// 0xB3 [BYTE ChunkSize] [BOOL FirstPart] [DWORD FullSize] [BYTE ChunkSize] [RawBytes]

		BYTE	packID;
		BYTE	packSize;
		BYTE	init;
		DWORD	finalSize : 31;
		DWORD	isCustom : 1;
		BYTE	type;
		BYTE	data[0xFF];
	};
}
#pragma pack()

#endif
#pragma once

#ifndef _D2PACKETDEF_H
#define _D2PACKETDEF_H

#pragma pack(1)

struct SkillTargetPacket
{
	BYTE Header;
	DWORD UnitType;
	DWORD UnitId;
};

struct SkillPacket
{
	BYTE Header;
	WORD xPos;
	WORD yPos;
};

struct PacketData
{
	DWORD ClientID;
	BYTE aPacket[512];
	PacketData* pNext;
};

#pragma pack()
#endif
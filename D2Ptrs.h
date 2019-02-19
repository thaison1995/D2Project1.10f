#pragma once

#ifndef _D2PTRS_H
#define _D2PTRS_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
//                                                                                                                                                                                              ///
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (CONV##* DLL##_##NAME##_t) ARGS; static DLL##_##NAME##_t DLL##_##NAME = (OFFSET < 0) ? ((DLL##_##NAME##_t)GetProcAddress((HMODULE)DLLBASE_##DLL, (LPCSTR)-(OFFSET))) : (DLL##_##NAME##_t)(DLLBASE_##DLL + OFFSET);        ///
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)(DLLBASE_##DLL + OFFSET);                                 ///
#define D2PTR(DLL, NAME, OFFSET) static DWORD NAME = (DLLBASE_##DLL + OFFSET);                                                                                                                  ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

D2VAR(D2LAUNCH, BnData, BnetData*, 0x2CD44)

D2VAR(D2NET, PacketHandler, DWORD, 0x8148)
D2FUNC(D2NET, SendPacket, void, __stdcall, (DWORD arg1, BYTE* buf, size_t len), -10005)

D2PTR(D2GAME, FreePartyMem_I, 0x89BA0)

D2FUNC(D2GAME, D2GetMinonOwner, UnitAny*, __fastcall, (UnitAny* pMonster), 0x9F320)
D2FUNC(D2GAME, SendPacket, DWORD, __fastcall, (Client* ptClient, void* pData, DWORD size), 0xC710)
D2FUNC(D2GAME, FindUnit, UnitAny*, __fastcall, (Game*, DWORD, DWORD), 0x8BB00)

D2PTR(D2CLIENT, DrawGZBOX_I, 0x81790)
D2PTR(D2CLIENT, Screen_Call, 0x7BA00)

D2VAR(D2CLIENT, ScreenHeight, int, 0xD40F0)
D2VAR(D2CLIENT, ScreenWidth, int, 0xD40F4)
//D2VAR(D2CLIENT, gnScreenWidth, int, 0xD40EC)
D2VAR(D2CLIENT, MouseX, int, 0x6FBC1AE4 - 0x6FAA0000)//121AE4
D2VAR(D2CLIENT, MouseY, int, 0x6FBC1AE8 - 0x6FAA0000)
D2VAR(D2CLIENT, PacketHandler, D2PacketTable, 0xD6270)
D2VAR(D2CLIENT, ScreenViewHeight, int, 0xFA700)
D2VAR(D2CLIENT, BlockScreen, BOOL, 0x6FBAB9F0 - 0x6FAA0000)
D2VAR(D2CLIENT, BlockedRect, RECT, 0x6FBAB9D8 - 0x6FAA0000)
D2VAR(D2CLIENT, ScreenXShift, int, 0x6FBAB9C8 - 0x6FAA0000)
D2VAR(D2CLIENT, PlayerX, int, 0x6FBAB9BC - 0x6FAA0000)
D2VAR(D2CLIENT, PlayerY, int, 0x6FBAB9B8 - 0x6FAA0000)
D2VAR(D2CLIENT, Roster, RosterUnit*, 0x10B994)
D2VAR(D2CLIENT, PlayerUnit, UnitAny*, 0x11C200)
D2VAR(D2CLIENT, UICollisions, int*, 0x6FB90310 - 0x6FAA0000)
D2VAR(D2CLIENT, UIModesCallTree, int, 0x6FB78978 - 0x6FAA0000)
D2VAR(D2CLIENT, UIModes, int, 0x6FBBA6A8 - 0x6FAA0000)

D2VAR(D2CLIENT, FPS, DWORD, 0x6FB9A96C - 0x6FAA0000)
D2VAR(D2CLIENT, Ping, DWORD, 0x6FBA7774 - 0x6FAA0000)
D2VAR(D2CLIENT, SentBytes, int, 0x6FBC1AF4 - 0x6FAA0000)
D2VAR(D2CLIENT, SentPackets, int, 0x6FBC1AFC - 0x6FAA0000)

D2FUNC(D2CLIENT, EventMsg_I, int, __fastcall, (Srv2Clt::p0x5A* aPacket), 0x13930)
D2FUNC(D2CLIENT, PartyUpdate_II, BOOL, __fastcall, (BYTE* aPacket), 0x14370)
D2FUNC(D2CLIENT, PartyUpdate_I, BOOL, __fastcall, (BYTE* aPacket), 0x14380)
D2FUNC(D2CLIENT, PartyUpdate_IV, BOOL, __fastcall, (BYTE* aPacket), 0x143A0)

D2FUNC(D2CLIENT, ClearScreen2, void, __stdcall, (void), 0x2B6E0)
D2FUNC(D2CLIENT, TestPvPFlag, DWORD, __fastcall, (DWORD Argument1, DWORD Argument2, DWORD Flag), 0xAB900)

D2FUNC(D2CLIENT, GetPlayerUnit, UnitAny*, __stdcall, (), 0x883D0)
D2FUNC(D2CLIENT, LoadCellFile, CellFile*, __fastcall, (const char* szFilename, int nCellFileType), 0x1000)
D2FUNC(D2CLIENT, SetState_I, BOOL, __fastcall, (BYTE* aPacket), 0x14750)
D2FUNC(D2CLIENT, RemoveState_I, BOOL, __fastcall, (BYTE* aPacket), 0x14900)
D2FUNC(D2CLIENT, GetUnitById, UnitAny*, __fastcall, (DWORD UnitID, DWORD UnitType), 0x869F0)
D2FUNC(D2CLIENT, PrintGameString, void, __fastcall, (wchar_t * Message, int Color), 0x7C600)
D2FUNC(D2CLIENT, PrintPartyString, void, __stdcall, (wchar_t * Message, int Color), 0x7D610)//Not Sure
D2FUNC(D2CLIENT, GetLevelName, wchar_t*, __fastcall, (int levelid), 0x839F0)
D2FUNC(D2CLIENT, DrawGZBOX_I, void, __fastcall, (RECT*), 0x81790)

D2VAR(D2COMMON, sgptDataTables, sgptDataTable*, 0x96A20)

D2FUNC(D2COMMON, GetUnitStat, DWORD, __stdcall, (UnitAny* Unit, DWORD Stat, DWORD Stat2), -10519)
D2FUNC(D2COMMON, GetUnitBaseStat, DWORD, __stdcall, (UnitAny* Unit, DWORD Stat, DWORD Stat2), -10521)
D2FUNC(D2COMMON, GetUnitState, DWORD, __stdcall, (UnitAny* Unit, DWORD State), -10487)
D2FUNC(D2COMMON, CompileTxt, void*, __stdcall, (void* MemPool, char* FileName, BINField*, DWORD* Record, DWORD size), -10578)
D2FUNC(D2COMMON, D2ReadFile, void*, __fastcall, (DWORD unused, char* filename, DWORD* size, const char*, DWORD), 0x84268)
D2FUNC(D2COMMON, D2LoadSuperuniques, void*, __stdcall, (DWORD unused), 0x29FA0)
D2FUNC(D2COMMON, GetSkillById, Skill*, __fastcall, (UnitAny *ptUnit, int SkillId, int SkillFlags), -10949)
D2FUNC(D2COMMON, GetSkillLevel, int, __stdcall, (UnitAny* ptUnit, Skill* ptSkill, int aType), -10968)
D2FUNC(D2COMMON, EvaluateSkill, int, __stdcall, (UnitAny* ptUnit, int FormulaNo, int SkillId, int SkillLvl), -11276)
D2FUNC(D2COMMON, GetSkillFromUnit, Skill*, __fastcall, (UnitAny*, int), -10950)
D2FUNC(D2COMMON, GetActNoFromLevelId, BYTE, __stdcall, (int nLevelId), -10001)
D2FUNC(D2COMMON, GetUnitXOffset, int, __stdcall, (UnitAny* pUnit), -10333)
D2FUNC(D2COMMON, GetUnitYOffset, int, __stdcall, (UnitAny* pUnit), -10334)
D2FUNC(D2COMMON, GetTownLevel, int, __stdcall, (int dwActNo), -10085)

D2VAR(D2GFX, hInstance, HINSTANCE, 0x6FA8D25C - 0x6FA70000)
D2VAR(D2GFX, bInitSucceed, BOOL, 0x6FA8D848 - 0x6FA70000)
D2VAR(D2GFX, hDriverModHandle, HMODULE, 0x6FA8D274 - 0x6FA70000)
D2VAR(D2GFX, pfnDriverCallback, fnRendererCallbacks*, 0x6FA8D258 - 0x6FA70000)

D2FUNC(D2GFX, GetHwnd, HWND, __stdcall, (), -10027)
D2FUNC(D2GFX, DrawVerticalCropImage, void, __stdcall, (CellContext* data, DWORD x, DWORD y, int nSkipLines, int nDrawLines, int nDrawMode), -10074)
D2FUNC(D2GFX, DrawCellContext, void, __stdcall, (CellContext *context, int nXpos, int nYpos, DWORD dwGamma, int nDrawMode, BYTE* pPalette), -10072)
D2FUNC(D2GFX, DrawCellContextEx, void, __stdcall, (CellContext *context, int Xpos, int Ypos, int dwl, int nTransLvl, BYTE Color), -10073)
D2FUNC(D2GFX, DrawRectangle, void, __stdcall, (int X1, int Y1, int X2, int Y2, int dwColor, int dwTrans), -10055)

D2VAR(D2WIN, CurrentFont, DWORD, 0x1DB24)

D2FUNC(D2WIN, SetTextSize, int, __fastcall, (int dwSize), -10127)
D2FUNC(D2WIN, D2DrawText, void, __fastcall, (const wchar_t * wStr, int X, int Y, int nColor, int Centered), -10117)
D2FUNC(D2WIN, D2DrawTextEx, void, __fastcall, (const wchar_t * wStr, int X, int Y, int nColor, int Centered, int TransLvl), -10118)
D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type), -10039)
D2FUNC(D2WIN, DrawFramedText, void, __fastcall, (const wchar_t * wStr, int X, int Y, int nColor, int Centered), -10129)
D2FUNC(D2WIN, GetFontHeight, short, __fastcall, (void), -10125)
D2FUNC(D2WIN, GetTextWidth, int, __fastcall, (const wchar_t * wStr), -10121)
D2FUNC(D2WIN, PrintVers, void, __fastcall, (DWORD, LPSTR, DWORD), -10046)
D2FUNC(D2WIN, GetTextWidthFileNo, DWORD, __fastcall, (wchar_t * wStr, DWORD* dwWidth, DWORD* dwFileNo), -10131)

D2FUNC(D2CMP, DeleteCellFile, void, __stdcall, (CellFile* cf), -10028)

D2FUNC(D2LANG, GetLocaleText, wchar_t*, __fastcall, (short nLocaleTxtNo), -10004)

D2FUNC(FOG, D2Fog10212, void, __stdcall, (DWORD unknow), -10212)
D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void*, char*, int, int), -10043)
D2FUNC(FOG, D2FogAssertOld, void, __stdcall, (const char* ptMessage, DWORD eip, DWORD line), -10023)
D2FUNC(FOG, InitBitBuffer, void, __stdcall, (BitBuffer *pBitBuffer, void *Source, int Size), -10126)
D2FUNC(FOG, ReadBits, unsigned int, __stdcall, (BitBuffer* ptBitBuffer, int nBits), -10130)
D2FUNC(FOG, ReadBitsSigned, signed int, __stdcall, (BitBuffer* ptBitBuffer, int nBits), -10129)
D2FUNC(FOG, AllocServerMemory, void*, __fastcall, (void*, size_t, char*, int, int), -10045)
D2FUNC(FOG, FreeServerMemory, BOOL, __fastcall, (void*, void*, char*, int, DWORD), -10046)

#endif
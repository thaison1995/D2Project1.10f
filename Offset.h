#pragma once

#ifndef _OFFSET_H
#define _OFFSET_H

static const DWORD CALL = 0xE8;
static const DWORD JUMP = 0xE9;
static const DWORD NOP = 0x90;
static const DWORD RET = 0xC3;
static const DWORD XOR = 0x33;
static const DWORD CUSTOM = 0;

void Patch(BYTE bInst, char* pDll, DWORD pAddr, DWORD pFunc, DWORD dwLen, char* Type);
void ShowMsgBox(char * Msg, ...);
BOOL WriteDword(DWORD* lpAddr, DWORD lpBuffer);

#endif
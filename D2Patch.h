#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include "D2PatchConst.h"

static const DLLPatchStrc gptTemplatePatches[] =
{
	//TCP/IP Delay fix - Hyperjoin Multiplayers
	{ D2DLL_D2CLIENT, 0xD73D + 1, 0x01, 0x00, FALSE },

	//FPS Fix
	{ D2DLL_D2CLIENT, 0xA2C9, 0x04, (DWORD)PATCH_NOPBLOCK, FALSE },

	//Fix Item lost and Remove corpses
	//{ D2DLL_D2GAME, 0x5077D + 1, 0x00, (DWORD)D2GAME_OnCreateCorpse, TRUE },
	//{ D2DLL_D2GAME, 0x51449 + 1, 0x00, (DWORD)D2GAME_OnCreateCorpse, TRUE },

    {D2DLL_INVALID}
};

#endif
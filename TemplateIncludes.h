#pragma once

#ifndef _TEMPLATEINCLUDES_H
#define _TEMPLATEINCLUDES_H

#include "Offset.h"
#include "D2Math.h"

#include "ExRectangle.h"
#include "ExCellFile.h"
#include "ExBox.h"
#include "ExTextBox.h"
#include "ExImage.h"
#include "ExButton.h"
#include "ExScrollBar.h"
#include "ExWindow.h"
#include "ExControl.h"
#include "LRoster.h"

#include "Config.h"
#include "NewTXT.h"
#include "Orb.h"
#include "Buff.h"
#include "Damage.h"
#include "PartyExp.h"
#include "UnitNode.h"
#include "PartyUI.h"
#include "Arena.h"

void Patch_MainScreen();

int __inline GetRange(int X1, int Y1, int X2, int Y2) { return ((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2)); }
#define ARRAY_SIZE(X)	(sizeof(X) / sizeof(X[0]))
#define D2ASSERT(e, format, ...) if(!e) { ShowWindow(D2GFX_GetHwnd(),SW_HIDE);   ShowMsgBox(format, ##__VA_ARGS__); exit(-1); }
#define D2ERROR(format, ...) { ShowWindow(D2GFX_GetHwnd(),SW_HIDE);   ShowMsgBox(format, ##__VA_ARGS__); exit(-1); }

#endif
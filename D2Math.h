#pragma once

#ifndef _D2MATH_H
#define _D2MATH_H

BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin = 0);
int GetClass(char* txt);
char* GetCharClass(int ID);
void* STDCALL compileTxtFile(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
void Misc_CharToWide(wstring& Dest, const string Source);
wstring ConvertTickToTime(DWORD nTick);
LONG WINAPI GameWindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void __stdcall D2CLIENT_DrawGZBox(int X1, int Y1, int X2, int Y2);
void TextCenter(INT X, INT Y, DWORD Color, INT Font, INT Trans, LPSTR Text, ...);
bool Print(INT Color, CHAR * Format, ...);
void Log(char* Msg...);
wstring string2wString(const string& s);

__forceinline wstring W_Color(int ColNo)
{
	wostringstream Result;
	Result << (wchar_t)0xff << 'c' << (wchar_t)(ColNo + '0');
	return Result.str();
}

namespace Misc
{
	int round(double a);
}

#endif


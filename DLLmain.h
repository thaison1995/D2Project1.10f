#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iosfwd>
#include <list>
#include <math.h>
#include <process.h>
#include <psapi.h>
#include <shlwapi.h>
#include <sstream>
#include <string>
#include <time.h>
#include <tlhelp32.h>
#include <valarray>
#include <vector>
#include <winbase.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>
#include <queue>
#include <direct.h>	
#include <errno.h>
#include <io.h>
#include <tchar.h>
#include <iomanip>
#include <unordered_map>
#include <random>
#include <iterator>
#include <algorithm>
#include <map>
#include <fstream>
#include <regex>
#include <deque>
#include <random>
#include <mbstring.h>
#include <malloc.h>
#include <wchar.h>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shlwapi.lib")

#define EXPORT __declspec(dllexport)
#define FASTCALL __fastcall
#define FUNCCALL __cdecl
#define IMPORT __declspec(dllimport)
#define NAKED __declspec(naked)
#define STDCALL __stdcall
using namespace std;

#pragma warning(disable : 4311)
#pragma warning(disable : 4312)

static const DWORD DLLBASE_BNCLIENT		=	(DWORD)LoadLibraryA("Bnclient.dll");
static const DWORD DLLBASE_D2CLIENT		=	(DWORD)LoadLibraryA("D2Client.dll");
static const DWORD DLLBASE_D2CMP		=	(DWORD)LoadLibraryA("D2CMP.dll");
static const DWORD DLLBASE_D2COMMON		=	(DWORD)LoadLibraryA("D2Common.dll");
static const DWORD DLLBASE_D2DDRAW		=	(DWORD)LoadLibraryA("D2DDraw.dll");
static const DWORD DLLBASE_D2DIRECT3D	=	(DWORD)LoadLibraryA("D2Direct3D.dll");
static const DWORD DLLBASE_D2GAME		=	(DWORD)LoadLibraryA("D2Game.dll");
static const DWORD DLLBASE_D2GDI		=	(DWORD)LoadLibraryA("D2Gdi.dll");
static const DWORD DLLBASE_D2GFX		=	(DWORD)LoadLibraryA("D2Gfx.dll");
static const DWORD DLLBASE_D2GLIDE		=	(DWORD)LoadLibraryA("D2Glide.dll");
static const DWORD DLLBASE_D2LANG		=	(DWORD)LoadLibraryA("D2Lang.dll");
static const DWORD DLLBASE_D2LAUNCH		=	(DWORD)LoadLibraryA("D2Launch.dll");
static const DWORD DLLBASE_D2MCPCLIENT	=	(DWORD)LoadLibraryA("D2MCPClient.dll");
static const DWORD DLLBASE_D2MULTI		=	(DWORD)LoadLibraryA("D2Multi.dll");
static const DWORD DLLBASE_D2NET		=	(DWORD)LoadLibraryA("D2Net.dll");
static const DWORD DLLBASE_D2SOUND		=	(DWORD)LoadLibraryA("D2Sound.dll");
static const DWORD DLLBASE_D2WIN		=	(DWORD)LoadLibraryA("D2Win.dll");
static const DWORD DLLBASE_FOG			=	(DWORD)LoadLibraryA("Fog.dll");
static const DWORD DLLBASE_STORM		=	(DWORD)LoadLibraryA("Storm.dll");
static const DWORD DLLBASE_IJL11		=	(DWORD)LoadLibraryA("ijl11.dll");
static const DWORD DLLBASE_BINKW32		=	(DWORD)LoadLibraryA("binkw32.dll");
static const DWORD DLLBASE_SMACKW32		=	(DWORD)LoadLibraryA("SmackW32.dll");

#include "D2PacketClient.h"
#include "D2PacketServer.h"
#include "D2PacketDef.h"
#include "D2Constants.h"
#include "D2Structs.h"
#include "D2Ptrs.h"
#include "D2Vars.h"

#include "TemplateIncludes.h"

struct DLLBaseStrc
{
    char* szName;
    DWORD dwAddress;
};

struct DLLPatchStrc
{
    int nDLL;
    DWORD dwAddress;
	size_t nPatchSize;
    DWORD dwData;
    BOOL bRelative;
};

enum D2TEMPLATE_DLL_FILES
{
    D2DLL_BINKW32,
    D2DLL_BNCLIENT,
    D2DLL_D2CLIENT,
    D2DLL_D2CMP,
    D2DLL_D2COMMON,
    D2DLL_D2DDRAW,
    D2DLL_D2DIRECT3D,
    D2DLL_D2GAME,
    D2DLL_D2GDI,
    D2DLL_D2GFX,
    D2DLL_D2GLIDE,
    D2DLL_D2LANG,
    D2DLL_D2LAUNCH,
    D2DLL_D2MCPCLIENT,
    D2DLL_D2MULTI,
    D2DLL_D2NET,
    D2DLL_D2SOUND,
    D2DLL_D2WIN,
    D2DLL_FOG,
    D2DLL_IJL11,
    D2DLL_SMACKW32,
    D2DLL_STORM,
    D2DLL_INVALID
};

static DLLBaseStrc gptDllFiles [] =
{
    {"Binkw32.dll",         NULL},
    {"BnClient.dll",        NULL},
    {"D2Client.dll",        NULL},
    {"D2CMP.dll",           NULL},
    {"D2Common.dll",        NULL},
    {"D2DDraw.dll",         NULL},
    {"D2Direct3D.dll",      NULL},
    {"D2Game.dll",          NULL},
    {"D2Gdi.dll",           NULL},
    {"D2Gfx.dll",           NULL},
    {"D2Glide.dll",         NULL},
    {"D2Lang.dll",          NULL},
    {"D2Launch.dll",        NULL},
    {"D2MCPClient.dll",     NULL},
    {"D2Multi.dll",         NULL},
    {"D2Net.dll",           NULL},
    {"D2Sound.dll",         NULL},
    {"D2Win.dll",           NULL},
    {"Fog.dll",             NULL},
    {"Ijl11.dll",           NULL},
    {"SmackW32.dll",        NULL},
    {"Storm.dll",           NULL},
};

void __fastcall D2TEMPLATE_FatalError(char* szMessage);
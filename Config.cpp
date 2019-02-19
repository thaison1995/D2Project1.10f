#include "DLLmain.h"

void Config::D2MOD()
{
	static std::string File;
	char filename[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, filename);
	File.assign(filename);
	File += "\\D2Mod.ini";

	DamageEnabledPlayer = GetPrivateProfileInt("Damage", "Enabled Player", 1, File.c_str());
	DamageEnabledMon = GetPrivateProfileInt("Damage", "Enabled Mon", 1, File.c_str());

	DamageHotKeyPlayer = GetPrivateProfileInt("Damage", "HotKey Player", VK_F7, File.c_str());
	DamageHotKeyMon = GetPrivateProfileInt("Damage", "HotKey Mon", VK_F8, File.c_str());

	DamageFontPlayer = GetPrivateProfileInt("Damage", "Font Player", 5, File.c_str());
	DamageColorPlayer = GetPrivateProfileInt("Damage", "Color Player", 1, File.c_str());

	DamageFontMon = GetPrivateProfileInt("Damage", "Font Mon", 5, File.c_str());
	DamageColorMon = GetPrivateProfileInt("Damage", "Color Mon", 0, File.c_str());
}
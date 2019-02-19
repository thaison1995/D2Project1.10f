#pragma once

#ifndef _DAMAGE_H
#define _DAMAGE_H

namespace Damage
{
	void __fastcall Handler(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender, Game* pGame);
	void __fastcall Handler_STUB(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender, int nDamage);
	void __fastcall SendPacket0x45(DamageData* pDmg, UnitAny* UnitId, UnitAny* pUnit, int Type);
	int __fastcall ReceivedPacket(Srv2Clt::p0x45* Dane);
	void __fastcall Assist(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender);

	void LoadTXT();
	void FreeTXT();

	void OnDraw();
	void OnPatch();
}

#endif
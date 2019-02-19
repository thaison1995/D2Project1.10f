#ifndef _EXBUFFS_H__
#define _EXBUFFS_H__

using namespace std;

class ExBuff : public ExControl
{
public:

	ExBuff(WORD SkillId, WORD StateNo, int ImageId, short DefaultLvl, DWORD aType, bool isTimed);
	~ExBuff();
	void Draw();

	static void Check(void);
	static void Clear(void);
	static void UpdateYPos(void);
	int	StateId;
	int SkillId;
	DWORD SkillLen;
	DWORD SkillExpire;
private:
	ExImage * BuffImage;
	ExRectangle * BuffTime;
	ExTextBox * BuffInfo;
};

namespace ExBuffs
{
	wchar_t* GetSkillName(unsigned short SkillId);
	BOOL __fastcall OnSetState(BYTE* aPacket);
	BOOL __fastcall OnRemoveState(BYTE* aPacket);

	void LoadTXT();
	void FreeTXT();

	void OnPatch();
}

#endif
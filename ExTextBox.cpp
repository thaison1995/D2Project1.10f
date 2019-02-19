#include "DLLmain.h"

ExTextBox::ExTextBox(int tX, int tY, int tTextColor, int tTextFont, wstring szLabel, void(*tevent_onClick)(ExControl*), ExControl* Parent) : ExControl(tX, tY, -1, -1, tevent_onClick)
{
	InitStatic(tX, tY, tTextColor, tTextFont, szLabel, tevent_onClick, Parent);
}

ExTextBox::ExTextBox(int tX, int tY, int tTextColor, int tTextFont, string sLabel, void(*tevent_onClick)(ExControl*), ExControl* Parent) : ExControl(tX, tY, -1, -1, tevent_onClick)
{
	wstring wLabel;
	Misc_CharToWide(wLabel, sLabel);
	InitStatic(tX, tY, tTextColor, tTextFont, wLabel, tevent_onClick, Parent);
}

ExTextBox::ExTextBox(int tX, int tY, int tTextColor, int tTextFont, wstring(*fLabel)(ExTextBox*), void(*tevent_onClick)(ExControl*), ExControl* Parent) : ExControl(tX, tY, -1, -1, tevent_onClick)
{
	InitDynamic(tX, tY, tTextColor, tTextFont, fLabel, tevent_onClick, Parent);
}

ExTextBox::ExTextBox(int tX, int tY, int tTextColor, int tTextFont, string(*fLabel)(ExTextBox*), void(*tevent_onClick)(ExControl*), ExControl* Parent) : ExControl(tX, tY, -1, -1, tevent_onClick)
{
	InitDynamic(tX, tY, tTextColor, tTextFont, 0, tevent_onClick, Parent);
	cfsLabel = fLabel;
}

bool ExTextBox::InitStatic(int tX, int tY, int tTextColor, int tTextFont, wstring szLabel, void(*tevent_onClick)(ExControl*), ExControl* Parent)
{
	if (szLabel.empty()) return false;
	TextColor = tTextColor;
	TransLvl = 5;
	aFont = tTextFont;
	ptParent = Parent;
	bHoverable = true;
	Hoover = L"";
	bWrapText = false;
	cfLabel = 0;
	cfsLabel = 0;
	SetText(szLabel);
	return true;
}


bool ExTextBox::InitDynamic(int tX, int tY, int tTextColor, int tTextFont, wstring(*fLabel)(ExTextBox*), void(*tevent_onClick)(ExControl*), ExControl* Parent)
{
	TextColor = tTextColor;
	TransLvl = 5;
	aFont = tTextFont;
	ptParent = Parent;
	bHoverable = true;
	Hoover = L"";
	bWrapText = false;
	wstring szLabel = fLabel ? L"" : L"Dynamic func not defined!";
	cfLabel = fLabel;
	cfsLabel = 0;
	return true;
}

void ExTextBox::SetText(wstring sLabel)
{
	bool erased = false;
	wstring szLabel = sLabel;
	int OldFont = *D2WIN_CurrentFont;
	D2WIN_SetTextSize(aFont);

	for (wstring::iterator temp = szLabel.end(); temp != szLabel.begin(); --temp)
	{
		cWidth = D2WIN_GetTextWidth(szLabel.c_str());
		if (cWidth <= (ptParent ? ptParent->GetWidth() : *D2CLIENT_ScreenWidth)) break;
		szLabel.erase(temp);
		erased = true;
	}
	if (erased) { szLabel.erase(szLabel.length() - 3); szLabel += L"..."; cWidth = D2WIN_GetTextWidth(szLabel.c_str()); }
	cHeight = D2WIN_GetFontHeight();
	Relocate();

	Label = szLabel;

	D2WIN_SetTextSize(OldFont);
}


void ExTextBox::SetText(string Text)
{
	wstring wText;
	Misc_CharToWide(wText, Text);
	SetText(wText);
}

void ExTextBox::SetTextSimple(wstring wText)
{
	Label = wText;
}

void ExTextBox::Relocate() //- Set control align
{
	if(ptParent) {
		if(wAlign == CENTER) cX=((ptParent->GetX()+ptParent->GetWidth()+ptParent->GetX())-cWidth)/2;
		else if(wAlign == RIGHT) cX=(ptParent->GetX()+ptParent->GetWidth()-cWidth);
		if(hAlign == CENTER) cY=((ptParent->GetY()+ptParent->GetHeight()+ptParent->GetY())+cHeight)/2;
		else if(hAlign == RIGHT) cY=ptParent->GetY()+ptParent->GetHeight();
	}
	else {
		if(wAlign == CENTER) cX=(*D2CLIENT_ScreenWidth-cWidth)/2;
		else if(wAlign == RIGHT) cX=(*D2CLIENT_ScreenWidth-cWidth);
		if(hAlign == CENTER) cY=(*D2CLIENT_ScreenHeight+cHeight)/2;
		else if(hAlign == RIGHT) cY=*D2CLIENT_ScreenHeight;
	}
}

bool ExTextBox::isCallBack()
{
	if (cfLabel || cfsLabel) return true;
	return false;
}


void ExTextBox::SetTransLvl(int aLevel)
{
	TransLvl = aLevel;
}

void ExTextBox::SetHoverable(bool how)
{
	bHoverable = how;
}

void ExTextBox::Draw()
{
	if (cState == INVISIBLE) return;

	if (cfLabel) SetText(cfLabel(this));
	else if (cfsLabel) SetText(cfsLabel(this));
	if (Label.empty()) return;

	D2WIN_SetTextSize(aFont);

	if (cState == VISIBLE)
	{
		D2WIN_D2DrawTextEx(Label.c_str(), cX, cY, bBeingPressed ? bBeingSelected ? COL_RED : COL_WHITE : (TextColor - (bHoverable ? bBeingSelected ? COL_RED : COL_WHITE : COL_WHITE)), 0, TransLvl);
		if (Hoover.empty()) return;
		if (!bBeingSelected) return;
		D2WIN_DrawFramedText(Hoover.c_str(), cX, cY - cHeight - 10, 0, 0);
	}
	else if (cState == DISABLED)
	{
		D2WIN_D2DrawTextEx(Label.c_str(), cX, cY, 5, 0, TransLvl);
	}
}

bool ExTextBox::isPressed(unsigned int Sender, WPARAM wParam)
{
	if (cState == VISIBLE)
	{
		switch (Sender)
		{
		case WM_MOUSEMOVE:
			if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= (cX + cWidth) && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= (cY - cHeight))
			{
				if (event_onClick)
				{
					bBeingSelected = true;
					if (wParam & MK_LBUTTON) bBeingPressed = true;
				}
			}
			else
			{
				if (wParam & MK_LBUTTON && bBeingPressed) bBeingPressed = false;
				bBeingSelected = false;
			}
			break;
		case WM_LBUTTONDOWN:
			if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= (cX + cWidth) && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= (cY - cHeight))
			{
				if (event_onClick)
				{
					//D2ASMFuncs::D2CLIENT_PlaySound(ExSounds::STAND_CLICK);
					bBeingPressed = true;
				}
				return true;
			}
			break;
		case WM_LBUTTONUP:
			if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= (cX + cWidth) && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= (cY - cHeight))
			{
				if (event_onClick)
				{
					event_onClick(this);
					bBeingPressed = false;
				}
				return true;
			}
			break;
		}
	}
	return false;
}

ExTextBox::~ExTextBox()
{
}
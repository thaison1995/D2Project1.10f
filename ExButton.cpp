#include "DLLmain.h"

ExButton::ExButton(int bX, int bY, int TextColor, unsigned int Frame, wstring szLabel, string szFile, void(*tevent_onClick)(ExControl*), bool LongButton) : ExControl(bX, bY, -1, -1, tevent_onClick)
{
	try
	{
		aCellFile = new ExCellFile(szFile);
	}
	catch (const CellLoadError&)
	{
		delete aCellFile;
		D2ERROR("Cannot create button because of missing or corrupted DC6 file!")
	}
	
	aTextBox = 0;
	Color = 0;
	bLongButton = LongButton;
	D2ASSERT(aCellFile->SetFrame(Frame), "SetFrame() failed!")
	else
	{
		cWidth = aCellFile->GetCF()->cells[Frame]->width;
		if (LongButton && aCellFile->GetCF()->numcells > Frame) cWidth += aCellFile->GetCF()->cells[Frame + 1]->width;
		cHeight = aCellFile->GetCF()->cells[Frame]->height;
	}
	Label = szLabel;
	Hoover = L"";
	aFrame = Frame;
	if (!szLabel.empty())
	{
		aTextBox = new ExTextBox(cX, cY, TextColor, 8, szLabel, 0, this);
	}
}

void ExButton::SetHoover(wstring wText)
{
	Hoover = wText;
}

void ExButton::FixText()
{
	aTextBox->SetX((cX + cX + cWidth - aTextBox->GetWidth()) / 2);
	aTextBox->SetY((cY + cY - cHeight + aTextBox->GetHeight()) / 2);
}

void ExButton::Draw()
{
	if (cState == INVISIBLE) return;
	if (bBeingPressed){
		aCellFile->Get()->nCellNo = bLongButton ? aFrame + 2 : aFrame + 1;
		if (aTextBox) { FixText(); aTextBox->SetY(aTextBox->GetY() + 1); aTextBox->SetX(aTextBox->GetX() + 2); }
	}
	else
	{
		aCellFile->Get()->nCellNo = aFrame;
		if (aTextBox) FixText();
	}
	D2GFX_DrawCellContextEx(aCellFile->Get(), cX, cY, -1, 5, cState == VISIBLE ? Color : COL_RED);
	if (bLongButton)
	{
		int aWid = aCellFile->Get()->pCellFile->cells[aFrame]->width;
		aCellFile->Get()->nCellNo++;
		D2GFX_DrawCellContextEx(aCellFile->Get(), cX + aWid, cY, -1, 5, cState == VISIBLE ? Color : COL_RED);
	}
	if (Hoover.empty()) return;
	if (!bBeingSelected) return;
	D2WIN_DrawFramedText(Hoover.c_str(), cX, cY - cHeight - 10, 0, 0);
}

void ExButton::SetColor(D2Colors nColor)
{
	Color = nColor;
}

void ExButton::SetState(ExControl::States aState)
{
	cState = aState;
	if (aTextBox) aTextBox->SetState(aState);
}

ExButton::~ExButton(void)
{
	delete aTextBox;
	delete aCellFile;
}

bool ExButton::isPressed(unsigned int Sender, WPARAM wParam)
{
	if (cState == INVISIBLE) return false;
	switch (Sender)
	{
	case WM_LBUTTONDOWN:
		if (cState == DISABLED) return false;
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= cY - cHeight)
		{
			bBeingPressed = true;
			return true;
		}
		break;
	case WM_LBUTTONUP:
		if (cState == DISABLED) return false;
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= cY - cHeight)
		{
			if (cState == VISIBLE && event_onClick) { /*D2ASMFuncs::D2CLIENT_PlaySound(ExSounds::STAND_CLICK);*/ event_onClick(this); }
			bBeingPressed = false;
			return true;
		}
		break;
	case WM_MOUSEMOVE:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY - cHeight && *D2CLIENT_MouseY <= cY)
			bBeingSelected = true;
		else
			bBeingSelected = false;
		if (cState == DISABLED) return false;
		if (!(Sender == WM_MOUSEMOVE && wParam & (MK_LBUTTON))) break;
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY - cHeight && *D2CLIENT_MouseY >= cY)
			bBeingPressed = true;
		else
			bBeingPressed = false;
		break;
	}
	return false;
}
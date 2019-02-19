#include "DLLmain.h"

void ExControl::SetMoveable(bool How){ bMoveable = How; }
void ExControl::SetWidth(int cW){ cWidth = cW; }
void ExControl::SetHeight(int cH){ cHeight = cH; }
void ExControl::SetX(int X){ cX = X; }
void ExControl::SetY(int Y){ cY = Y; }
void ExControl::SetState(States aState){ cState = aState; }

void ExControl::SetAlign(Align xAlign, Align yAlign)
{
	wAlign = xAlign;
	hAlign = yAlign;

	if(xAlign != NONE || yAlign != NONE) Relocate();
}


void ExControl::Relocate() //- Set control align
{
	if(ptParent) {
		if(wAlign == CENTER) cX=((ptParent->GetX()+ptParent->GetWidth()+ptParent->GetX())-cWidth)/2;
		else if(wAlign == RIGHT) cX=ptParent->GetX()+ptParent->GetWidth()-cWidth;
		if(hAlign == CENTER) cY=((ptParent->GetY()+ptParent->GetHeight()+ptParent->GetY())-cHeight)/2;
		else if(hAlign == RIGHT) cY=ptParent->GetY()+ptParent->GetHeight()-cHeight;
	}
	else {
		if(wAlign == CENTER) cX=(*D2CLIENT_ScreenWidth-cWidth)/2;
		else if(wAlign == RIGHT) cX=(*D2CLIENT_ScreenWidth-cWidth);
		if(hAlign == CENTER) cY=(*D2CLIENT_ScreenHeight-cHeight)/2;
		else if(hAlign == RIGHT) cY=*D2CLIENT_ScreenHeight-cHeight;
	}
}

ExControl::ExControl(int X, int Y, int X2, int Y2, void(*fevent_onClick)(ExControl*))
{
	ptParent = 0;
	cX = X;
	cY = Y;
	cWidth = X2;
	cHeight = Y2;
	OldX = OldY = aFont = 0;
	event_onClick = fevent_onClick;
	cState = VISIBLE;
	SetAlign(NONE, NONE);

	bMoveable = false;
	bBeingPressed = false;
	bBeingMoved = false;
	bBeingSelected = false;
	Controls.push_back(this);
}

ExControl::~ExControl(void)
{
	if (this->ptParent)
	{
		if (typeid(this->ptParent) == typeid(ExWindow*))
		{
			ExWindow * hParent = dynamic_cast<ExWindow*>(this->ptParent);
			hParent->DeleteChild(this);
		}
	}
	for(vector<ExControl*>::iterator i = Controls.begin(); i!=Controls.end(); ++i)
	if (*i == this) { Controls.erase(i);  return; }
}

void ExControl::Draw()
{
	if (cState != INVISIBLE)
	{
		D2GFX_DrawRectangle(cX, cY, cX + cWidth, cY + cHeight, 0xFF, 5);
		D2WIN_SetTextSize(aFont);
		D2WIN_D2DrawText(L"<NULL CONTROL>", cX, cY, 11, 0); // THIS NEVER HAPPEN
	}
}

bool ExControl::isPressed(unsigned int Sender, WPARAM wParam)
{
	switch (Sender)
	{
	case WM_LBUTTONDOWN:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY && *D2CLIENT_MouseY <= cY + cHeight)
		{
			bBeingPressed = true;
			return true;
		}
		break;
	case WM_LBUTTONUP:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY && *D2CLIENT_MouseY <= cY + cHeight)
		{
			if (cState == VISIBLE && event_onClick) event_onClick(this);
			bBeingPressed = false;
			return true;
		}
		break;
	case WM_MOUSEMOVE:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY && *D2CLIENT_MouseY <= cY + cHeight)
			bBeingSelected = true;
		else
			bBeingSelected = false;
		if (!(Sender == WM_MOUSEMOVE && wParam & (MK_LBUTTON))) break;
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY && *D2CLIENT_MouseY <= cY + cHeight)
			bBeingPressed = true;
		else
			bBeingPressed = false;
		break;
	}
	return false;
}
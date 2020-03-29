#include "Whip.h"

Whip::Whip()
{
	AddAnimation(600);
}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

void Whip::Render(int currentID)
{
	if (currentID >= 0)
		animations[0]->RenderWhip(currentID, nx, x, y);
	//animations[0]->Render(nx, x, y);
}

void Whip::SetPosWhip(D3DXVECTOR3 pos, bool isstanding)
{
	pos.x -= 90;
	if (!isstanding)
		pos.y += 15;
	SetPosition(pos.x, pos.y);
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
}

Whip::~Whip()
{
}

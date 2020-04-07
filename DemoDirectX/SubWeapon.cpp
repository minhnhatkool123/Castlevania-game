#include "SubWeapon.h"

SubWeapon::SubWeapon()
{

}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CGameObject::Update(dt);
	//x += dx;
	
}

void SubWeapon::SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding)
{
	if (!isstanding)
		pos.y += 25;
	else
		pos.y += 10;
	SetPosition(pos.x, pos.y);
}

void SubWeapon::Render()
{	
	animation_set->at(state)->Render(nx, x, y);
	RenderBoundingBox();
}

//void SubWeapon::Render(int currentID)
//{
//	animation_set->at(state)->RenderWhip(currentID, nx, x, y);
//}
//void SubWeapon::Render(int currentID)
//{
//	if (currentID >= 0)
//	{
//		animation_set->at(state)->RenderWhip(currentID, nx, x, y);
//
//	}
//}

void SubWeapon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
}




SubWeapon::~SubWeapon()
{
}

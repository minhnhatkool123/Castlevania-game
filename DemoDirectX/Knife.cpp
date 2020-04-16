#include "Knife.h"


Knife::Knife()
{
	isDone = true;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(knife_ani_set));
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	
	if (CheckPosKnife(POSX))
	{
		isDone = true;
		return;
	}
	

	SubWeapon::Update(dt, colliable_objects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);
	
	

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// kiểm tra va chạm với object
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.1f;		
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Candle *>(e->obj))
			{
				Candle *candle = dynamic_cast<Candle *>(e->obj);

				if (e->nx != 0)
				{
					listHit.push_back(CreateHit(candle->GetPositionX(), candle->GetPositionY() + 10));
					candle->SetState(break_candle);
					isDone = true;
				}					

			}

		}
	}	
}

Hit* Knife::CreateHit(float x, float y)
{
	return new Hit(x, y);
}
void Knife::Render()
{
	if(!isDone&&!CheckPosKnife(POSX))
		SubWeapon::Render();

	for (int i = 0; i < listHit.size(); i++)
		listHit[i]->Render();

	RenderBoundingBox();
	
}



void Knife::SetState(int State)
{
	CGameObject::SetState(State);

	if (nx > 0)
		vx = 0.5;
	else
		vx = -0.5;
	vy = 0;
}

void Knife::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + knife_box_width;
		bottom = top + knife_box_height;
	}

}

void Knife::SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding)
{
	SubWeapon::SetPosSubWeapon(D3DXVECTOR3(pos.x, pos.y, 0), isstanding);
	POSX = pos.x;
}

bool Knife::CheckPosKnife(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH/2) + 100))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH / 2) + 100))
			return true;
	}
	return false;
}
Knife::~Knife()
{
}

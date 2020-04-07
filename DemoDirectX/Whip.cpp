﻿#include "Whip.h"
#include"Candle.h"

Whip::Whip()
{
	
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(whip_ani_set));//truyền tất cả animation của whip vào


	state = whip_lv1;
}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);

			if (dynamic_cast<Candle*>(obj))
			{
				Candle * e = dynamic_cast<Candle*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->SetState(break_candle);

				}

			}
		}

}

void Whip::Render(int currentID)
{
	if (currentID >= 0)		
	{
		animation_set->at(state)->RenderWhip(currentID, nx, x, y);

	}
	//animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void Whip::Render()
{
	//animations[0]->Render(nx, x, y);
}

void Whip::SetPosWhip(D3DXVECTOR3 pos, bool isstanding)
{
	pos.x -= 90;
	if (!isstanding)
		pos.y += 15;
	SetPosition(pos.x, pos.y);
}


bool Whip::WhipCheckColli(float l_b, float t_b, float r_b, float b_b)
{
	float l_whip, t_whip, r_whip, b_whip;
	GetBoundingBox(l_whip, t_whip, r_whip, b_whip);

	if (CGameObject::AABBCheck(l_whip, t_whip, r_whip, b_whip, l_b, t_b, r_b, b_b))
		return true;
	else
		return false;
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	t = y + 15;
	b = t + 15;
	if (nx < 0)
	{
		l = x + 50;
	}
	else if (nx > 0)
	{
		l =  x+135;
	}

	r = l + 55;
}



Whip::~Whip()
{
}

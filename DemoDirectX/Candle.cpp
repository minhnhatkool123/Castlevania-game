#include "Candle.h"


Candle::Candle()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(candle_ani_set));
	isDone = false;
	
}
void Candle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == break_candle)
		isDone = true;
}

void Candle::Render()
{
	if (state != break_candle)
		animation_set->at(0)->Render(nx, x, y);
	else
		return;

	RenderBoundingBox();
}

void Candle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (state != break_candle)
	{
		l = x;
		t = y;
		r = l + 32;
		b = t + 64;
	}
}

void Candle::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case break_candle:
		break;
	}
}

Candle::~Candle()
{
}

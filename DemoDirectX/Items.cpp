#include "Items.h"
Items::Items()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(items_ani_set));

	timeStart = -1;	
	isDone = false;
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	if (timeStart == -1)
		timeStart = GetTickCount();
	else
	{
		if (GetTickCount() - timeStart > time_items_des)
		{
			isDone = true;
			return;
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		/*if (ny != 0)
		{
			vx = 0;
			vy = 0;
		}*/
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Items::Render()
{
	if (isDone)
		return;
	//int alpha = 255;
	/*if (GetTickCount() - timeStart > 1500)
		alpha=rand() % 100 + 1;*/
	
	
	animation_set->at(state)->Render(-1, x, y);
	RenderBoundingBox();
}

void Items::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDone)
	{
		switch (state)
		{
		case items_for_whip:
			l = x;
			t = y;
			r = l + 32;
			b = t + 32;
			break;
		case items_big_heart:
			l = x;
			t = y;
			r = l + 24;
			b = t + 20;
			break;
		case items_knife:
			l = x;
			t = y;
			r = l + 32;
			b = t + 18;
			break;
		case items_watch:
			l = x;
			t = y;
			r = l + 30;
			b = t + 32;
			break;
		}
	}
}

void Items::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case items_for_whip:
		vx = 0;
		vy = 0.15;
		break;
	case items_big_heart:
		vx = 0;
		vy = 0.15;
		break;
	case items_knife:
		vx = 0;
		vy = 0.15;
		break;
	case items_watch:
		vx = 0;
		vy = 0.15;
	}
}

Items::~Items()
{
	
}

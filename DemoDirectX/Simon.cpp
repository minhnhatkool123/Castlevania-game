#include "Simon.h"
#include"Ground.h"


Simon::Simon() 
{
	whip = new Whip();
	isGrounded = false;
	//state = simon_ani_idle;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += simon_gravity * dt;

	//whip->Update(dt, coObjects);
	whip->SetPosWhip(D3DXVECTOR3(this->x, this->y, 0), true);
	/*if (state == simon_ani_stand_hit && animations[simon_ani_stand_hit]->RenderOver(300))
	{
		if (!(isGrounded))
			SetState(simon_ani_jump);
		else
			SetState(simon_ani_idle);
	}*/



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

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground *>(e->obj))
			{
				Ground *ground = dynamic_cast<Ground *>(e->obj);

				if (e->ny < 0)
				{
					isGrounded = true;
				}
				
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) 
		delete coEvents[i];
}

void Simon::Render()
{
	animations[state]->Render(nx, x, y);
	if ((state == simon_ani_stand_hit || state == simon_ani_sit_hit))
		whip->Render(animations[state]->GetcurrentFrame());
	else
		whip->Render(-1);
	RenderBoundingBox();
}


void Simon::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case simon_ani_run:
		if (nx > 0)
			vx = simon_run;
		else
			vx = -simon_run;
		break;
	case simon_ani_idle:
		vx = 0;
		break;
	case simon_ani_jump:
		if (isGrounded)
		{
			isGrounded = false;
			vy = simon_jump;
		}
		break;
	case simon_ani_sit:
		vx = vy = 0;
		break;
	case simon_ani_stand_hit:
		animations[State]->ResetcurrentFrame();
		animations[State]->StartAni();
		break;
	case simon_ani_sit_hit:
		vx = 0;
		animations[State]->ResetcurrentFrame();
		animations[State]->StartAni();
		break;
	}

}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + 60;
	bottom = top + 62;
}

Simon::~Simon()
{
}

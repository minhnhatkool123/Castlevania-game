﻿#include "Simon.h"
#include"Ground.h"


Simon::Simon() 
{
	whip = new Whip();
	knife = new Knife();
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(simon_ani_set));
	currentWeapon = -1;
	isGrounded = false;
	//state = simon_ani_idle;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += simon_gravity * dt;

	if (x < -11)
		x = -11;

	if(state==simon_ani_sit_hit)
		whip->SetPosWhip(D3DXVECTOR3(this->x, this->y, 0), false);
	else
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
	animation_set->at(state)->Render(nx, x, y);

	if (nx > 0)
	{
		whip->SetNx(1);
		//if(isHitSubWeapon)
			//knife->SetNx(1);
	}
	else
	{
		whip->SetNx(-1);
		//if (isHitSubWeapon)
			//knife->SetNx(-1);
	}

	if ((state == simon_ani_stand_hit || state == simon_ani_sit_hit)&&!isHitSubWeapon||(isHitSubWeapon&&currentWeapon==-1))	
	{		
		whip->Render(animation_set->at(state)->GetcurrentFrame());		
	}
	else
		whip->Render(-1);
	

	//if (isHitSubWeapon&&currentWeapon != -1)
	if(currentWeapon!=-1)
	{
		
		knife->Render();
	}
		
	
	
	//RenderBoundingBox();
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
		vx = 0;
		break;
	case simon_ani_stand_hit:
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_sit_hit:
		vx = 0;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_led:
		vx = 0;
		animation_set->at(State)->StartAni();
		break;
	}

}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+15;
	top = y;
	right = left + 33;
	bottom = top + 62;
}

void Simon::SimonColliWithItems(vector<LPGAMEOBJECT> *listitems)//hàm này để tránh việc ko xét va chạm dc khi 2 simon trùng với items
{
	float l_items, t_items, r_items, b_items, l_simon, t_simon, r_simon, b_simon;
	GetBoundingBox(l_simon, t_simon, r_simon, b_simon);

	for (UINT i = 0; i < listitems->size(); i++)
	{
		LPGAMEOBJECT e = listitems->at(i);
		e->GetBoundingBox(l_items, t_items, r_items, b_items);
		if (CGameObject::AABBCheck(l_simon, t_simon, r_simon, b_simon, l_items, t_items, r_items, b_items))
		{
			if (e->GetState() == items_for_whip)
			{
				SetState(simon_ani_led);
				e->isDone = true;
				if (whip->GetState() == whip_lv1)
					whip->SetState(whip_lv2);
				else if (whip->GetState() == whip_lv2)
					whip->SetState(whip_lv3);
				

			}
			else if (e->GetState() == items_big_heart)
			{
				e->isDone = true;
			}
			else if (e->GetState() == items_knife)
			{
				e->isDone = true;
				currentWeapon = 0;
				//e->SetState(knife_ani);
				
			}
		}
		



	}
}

Simon::~Simon()
{

}

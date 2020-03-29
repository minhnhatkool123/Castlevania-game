#pragma once

#include "GameObject.h"
#include "Whip.h"

#define simon_jump -0.5f
#define simon_run 0.2f
#define simon_gravity 0.0015f

#define simon_ani_idle 0
#define simon_ani_run  1
#define simon_ani_jump 2
#define simon_ani_sit  3
#define simon_ani_stand_hit 4
#define simon_ani_sit_hit   5


class Simon :public CGameObject
{
	Whip *whip;
	
public:
	bool isGrounded;
	Simon();
	~Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int SetState);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


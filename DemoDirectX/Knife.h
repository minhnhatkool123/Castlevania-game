#pragma once
#include"SubWeapon.h"

#define knife_ani 0
#define knife_ani_set 6

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class Knife :public SubWeapon
{
	float POSX;
public:
	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	//void Render(int currentID = -1);
	void SetState(int SetState);
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


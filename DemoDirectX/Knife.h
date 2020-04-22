#pragma once
#include"SubWeapon.h"
#include "Hit.h"
#include"Gate.h"
#include"Ground.h"
#define knife_ani 0
#define knife_ani_set 6

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define knife_box_width 34
#define knife_box_height 18
class Knife :public SubWeapon
{
	float POSX;
	vector<LPHIT> listHit;
public:
	Hit* CreateHit(float x, float y);
	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	//void Render(int currentID = -1);
	void SetState(int SetState);
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


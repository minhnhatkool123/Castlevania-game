#pragma once
#include"GameObject.h"
#include"Candle.h"

#define weapon_knfie 0
#define weapon_watch 1
class SubWeapon :public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	//void Render(int currentID = -1);
	virtual void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	//void SetState(int SetState);
	//void attack(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	SubWeapon();
	~SubWeapon();
};


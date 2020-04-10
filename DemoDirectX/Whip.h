#pragma once
#include"GameObject.h"
#include"Hit.h"
#define whip_lv1 0
#define whip_lv2 1
#define whip_lv3 2

#define whip_ani_set 4

class Whip :public CGameObject
{
	vector<LPHIT> listHit;
public:
	Whip();
	~Whip();
	Hit* CreateHit(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(int currentID = -1);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetPosWhip(D3DXVECTOR3 pos, bool isstanding);
	bool WhipCheckColli(float l_b, float t_b, float r_b, float b_b);
	void SetLvWhip(int state)
	{
		this->state = state;
	}


};


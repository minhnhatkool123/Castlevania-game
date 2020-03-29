#pragma once
#include"GameObject.h"

class Whip :public CGameObject
{
public:
	Whip();
	~Whip();
	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(int currendID = -1);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetPosWhip(D3DXVECTOR3 pos, bool isstanding);

};


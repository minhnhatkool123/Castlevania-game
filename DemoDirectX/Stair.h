#pragma once
#include"GameObject.h"
class Stair :public CGameObject
{
public:
	Stair();
	~Stair();
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};


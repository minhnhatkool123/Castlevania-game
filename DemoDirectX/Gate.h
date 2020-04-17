#pragma once
#include"GameObject.h"
#define gate_box_width 50
#define gate_box_height 100

class Gate:public CGameObject
{
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Gate();
	~Gate();
};


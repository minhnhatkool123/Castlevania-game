#pragma once
#include"GameObject.h"
#define break_candle 3

#define candle_ani_set 3
class Candle :public CGameObject
{
public:
	Candle();
	~Candle();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


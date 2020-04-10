#pragma once
#include"Animation.h"
#include"Sprites.h"
#define hit_ani 91
#define time_hit_des 100
class Hit;
typedef Hit* LPHIT;

class Hit
{
	DWORD timestart=-1;
	float x, y;
	LPANIMATION hit;
public:
	
	Hit(float x, float y);
	~Hit();
	void Render();
	bool timedestroy();
};


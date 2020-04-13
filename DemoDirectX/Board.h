#pragma once
#include"Animation.h"
#include"Sprites.h"
#include"HealthBar.h"
#define board_ani_set 8
#define board_ani 0

#define board_sprite 125

class Board
{
	//LPANIMATION board;
	LPANIMATION_SET board;
	//LPSPRITE board;
	//float posx, posy;
	HealthBar *healsimon;
	HealthBar *heallost;
	HealthBar *healboss;


public:
	Board(int healsimon,int healboss);
	~Board();
	void Update(int currentheal,int healboss);
	void Render(int idmap, int camx, int camy);
};


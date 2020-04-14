#pragma once
#include"Animation.h"
#include"Sprites.h"
#include"HealthBar.h"
#include"Simon.h"
#include"Number.h"
#include<string>
#include<time.h>

#define board_ani_set 8
#define board_ani 0

#define board_sprite 125

#define max_num_time 4
#define max_num_score 6
#define max_num_mana 2
#define max_num_stage 2
#define max_num_life 2
class Board
{
	//LPANIMATION board;
	LPANIMATION_SET board;
	//LPSPRITE board;
	//float posx, posy;
	HealthBar *healsimon;
	HealthBar *heallost;
	HealthBar *healboss;
	Number numb;

	string FillNumber(string s, UINT MaxNumber);
	vector<LPSPRITE> subweapon;

	int time, timeremain;

public:
	Board(int healsimon,int healboss);
	~Board();
	void Update(DWORD dt,int currentheal,int healboss);
	void Render(int idmap, int camx, int camy, Simon* simon);
};


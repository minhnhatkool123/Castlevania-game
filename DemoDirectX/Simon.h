#pragma once

#include "GameObject.h"
#include "Whip.h"
#include "Items.h"
#include "SubWeapon.h"
#include "Knife.h"

#define simon_jump -0.5f
#define simon_run 0.15f
#define simon_gravity 0.0015f

#define simon_ani_idle 0
#define simon_ani_run  1
#define simon_ani_jump 2
#define simon_ani_sit  3
#define simon_ani_stand_hit 4
#define simon_ani_sit_hit   5
#define simon_ani_led 6

#define simon_ani_set 1

#define simon_max_health 16
class Simon :public CGameObject
{
	Whip *whip;

	SubWeapon *knife;

	int health;
	int score;
	int mana;
	int life;

	
public:
	//bool isFighting;
	bool isGrounded;
	bool isHitSubWeapon;
	int currentWeapon;
	Simon();
	~Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int SetState);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Whip* GetWhip()
	{
		return whip;
	}
	SubWeapon *GetKnife()
	{
		return knife;
	}
	int getcurrentweapon() { return currentWeapon; }
	int getscore() { return score; }
	int getmana() { return mana; }
	int getlife() { return life; }
	void usemana(int a) { mana -= a; }
	void SimonColliWithItems(vector<LPGAMEOBJECT> *listitems);
	int GetHealth() { return health; }
};


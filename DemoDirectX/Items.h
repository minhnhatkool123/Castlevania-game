#pragma once
#include"GameObject.h"
#define time_items_des 3000
#define items_for_whip 0
#define items_big_heart 1
#define items_knife 2
#define items_watch 3
#define items_ani_set 5

#define items_whip_box_width 32
#define items_whip_box_height 32
#define items_bigheart_box_width 24
#define items_bigheart_box_height 20
#define items_knife_box_width 32
#define items_knife_box_height 18
#define items_watch_box_width 30
#define items_watch_box_height 32
class Items :public CGameObject
{
	DWORD timeStart;
	

public:
	//bool isDone;
	//int idItems;
	Items();
	~Items();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int SetState);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};


#include "Hit.h"



Hit::Hit(float x,float y)
{
	this->x = x;
	this->y = y;
	timestart = -1;
	hit = CAnimations::GetInstance()->Get(hit_ani);
}

bool Hit::timedestroy()
{
	if (timestart == -1)
		timestart = GetTickCount();
	else
	{
		if (GetTickCount() - timestart > time_hit_des)
		{
			return true;
		}

	}
	return false;
}

void Hit::Render()
{
	if(!timedestroy())
		hit->Render(1, x, y);
}
Hit::~Hit()
{
}

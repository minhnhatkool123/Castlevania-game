#include "Stair.h"


Stair::Stair()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(10));
	state = 0;
}
void Stair::Render()
{
	animation_set->at(state)->Render(-1, x, y);
	RenderBoundingBox();
}


void Stair::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + 32;
	b = t + 32;
}
Stair::~Stair()
{
}

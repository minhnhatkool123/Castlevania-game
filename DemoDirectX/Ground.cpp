#include "Ground.h"

Ground::Ground()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ground_ani_set));
}

void Ground::Render()
{
	animation_set->at(ground_ani)->Render(nx, x, y);
	RenderBoundingBox();
}

void Ground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + 32;
	b = t + 32;
}

Ground::~Ground()
{
}

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
	r = l + ground_box_width;
	b = t + ground_box_height;
}

Ground::~Ground()
{
}

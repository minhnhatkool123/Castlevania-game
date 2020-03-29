#include "Ground.h"

Ground::Ground()
{
	AddAnimation(500);
}

void Ground::Render()
{
	animations[0]->Render(nx, x, y);
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

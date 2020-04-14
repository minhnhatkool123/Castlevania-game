#include "Number.h"



Number::Number()
{
}

void Number::Render(float x, float y, string &a)
{
	for (UINT i = 0; i < a.size(); i++)
	{
		if (a[i] == ' ')
			continue;

		if (a[i] == '0')
		{
			num = CSprites::GetInstance()->Get(129);
		}
		else if (a[i] == '1')
		{
			num = CSprites::GetInstance()->Get(130);
		}
		else if (a[i] == '2')
		{
			num = CSprites::GetInstance()->Get(131);
		}
		else if (a[i] == '3')
		{
			num = CSprites::GetInstance()->Get(132);
		}
		else if (a[i] == '4')
		{
			num = CSprites::GetInstance()->Get(133);
		}
		else if (a[i] == '5')
		{
			num= CSprites::GetInstance()->Get(134);
		}
		else if (a[i] == '6')
		{
			num = CSprites::GetInstance()->Get(135);
		}
		else if (a[i] == '7')
		{
			num = CSprites::GetInstance()->Get(136);
		}
		else if (a[i] == '8')
		{
			num = CSprites::GetInstance()->Get(137);
		}
		else if (a[i] == '9')
		{
			num = CSprites::GetInstance()->Get(138);
		}
		num->Draw(-1, x + (i * 15), y);
	}
}


Number::~Number()
{
}

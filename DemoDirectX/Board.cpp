#include "Board.h"



Board::Board(int HealSimon,int HealBoss)
{
	//board = CAnimations::GetInstance()->Get(board_ani);
	board = CAnimationSets::GetInstance()->Get(board_ani_set);
	//board = CSprites::GetInstance()->Get(board_sprite);
	healsimon = new HealthBar(HealSimon);
	heallost = new HealthBar(max_heal);
	healboss = new HealthBar(HealBoss);

	subweapon.push_back(CSprites::GetInstance()->Get(82));
	subweapon.push_back(CSprites::GetInstance()->Get(83));

	
	time = 0;
}



void Board::Update(DWORD a,int currenhealsimon,int currenthealboss)
{
	//this->posx = x;
	//this->posy = y;
	healsimon->Update(currenhealsimon);
	heallost->Update(max_heal);
	healboss->Update(currenthealboss);

	time += a;
	timeremain = 300 - (time / CLOCKS_PER_SEC);
}

string Board::FillNumber(string s, UINT maxnumb)
{
	while (s.size() < maxnumb)
		s = "0" + s;
	return s;
}

void Board::Render(int idmap,int camx,int camy,Simon* simon)
{

	

	//this->posx = camx;
	//this->posy = camy;
	//board->Render(-1,posx,posy);
	board->at(board_ani)->Render(-1, camx, camy);
	heallost->Render(lose_heal,camx,camy);
	//board->Draw(-1, posx, posy);
	healsimon->Render(simon_heal, camx, camy);
	healboss->Render(boss_heal, camx, camy);
	

	if (simon->getcurrentweapon() !=-1)
	{
		subweapon[simon->getcurrentweapon()]->Draw(-1, camx + 310, camy + 38);
	}

	numb.Render(camx + 295, camy + 15, FillNumber(to_string(timeremain), max_num_time));
	numb.Render(camx + 100, camy + 15, FillNumber(to_string(simon->getscore()), max_num_score));
	numb.Render(camx + 393, camy + 33, FillNumber(to_string(simon->getmana()), max_num_mana));
	numb.Render(camx + 465, camy + 15, FillNumber(to_string(idmap), max_num_stage));
	numb.Render(camx + 393, camy + 51, FillNumber(to_string(simon->getlife()), max_num_life));
	
}

Board::~Board()
{
}

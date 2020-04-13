#include "Board.h"



Board::Board(int HealSimon,int HealBoss)
{
	//board = CAnimations::GetInstance()->Get(board_ani);
	board = CAnimationSets::GetInstance()->Get(board_ani_set);
	//board = CSprites::GetInstance()->Get(board_sprite);
	healsimon = new HealthBar(HealSimon);
	heallost = new HealthBar(max_heal);
	healboss = new HealthBar(HealBoss);
}

void Board::Update(int currenhealsimon,int currenthealboss)
{
	//this->posx = x;
	//this->posy = y;
	healsimon->Update(currenhealsimon);
	heallost->Update(max_heal);
	healboss->Update(currenthealboss);

}

void Board::Render(int idmap,int camx,int camy)
{
	//this->posx = camx;
	//this->posy = camy;
	//board->Render(-1,posx,posy);
	board->at(board_ani)->Render(-1, camx, camy);
	heallost->Render(lose_heal,camx,camy);
	//board->Draw(-1, posx, posy);
	healsimon->Render(simon_heal, camx, camy);
	healboss->Render(boss_heal, camx, camy);
	
}

Board::~Board()
{
}

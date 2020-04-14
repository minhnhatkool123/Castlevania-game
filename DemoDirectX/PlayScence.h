#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Whip.h"
#include "Ground.h"
#include "Items.h"
#include "Knife.h"
#include "Hit.h"
#include "TileMap.h"

#include"Board.h"

class CPlayScene : public CScene
{
protected:
		
	int idstage;
	TileMaps *tilemaps = TileMaps::GetInstance();
	Board *board;
	
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objectsstatic;
	vector<LPGAMEOBJECT> allobject;
	vector<LPGAMEOBJECT> listitems;
	//vector<LPHIT> listHit;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	Simon *simon;
	CPlayScene(/*int id, LPCWSTR filePath*/);

	virtual void Load();
	virtual void LoadObject();
	virtual void LoadBaseObject();
	virtual void SwitchScene(int id);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	Items* DropItem(float x, float y,int id);
	//Hit* CreateHit(float x, float y);
	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	void RunRight();
	void RunLeft();
	void Jump();
	void Idle();
	void Sit();
	void Hit();
	void Hit_SubWeapon();
	

	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};


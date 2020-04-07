#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"



using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_GROUND	1
#define OBJECT_TYPE_CANDLE	2


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

Items* CPlayScene::DropItem(float x, float y,int id)
{
	Items *a = new Items();

	a->SetPosition(x, y);
	a->idItems = id;
	a->SetState(id);
	
	//listitems.push_back(a);
	return a;
}


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;
	
	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
	{
		if (simon != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before! ");
			return;
		}
		//simon = new Simon();
		obj = new Simon();
		simon = (Simon*)obj;
		//simon->SetPosition(x, y);
		
		objects.push_back(simon);
		break;
	}
	case OBJECT_TYPE_GROUND: 
	{
		obj = new Ground();
		// General object setup
		//obj->SetPosition(x, y);

		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_CANDLE: 
	{
		int id = atof(tokens[4].c_str());
		obj = new Candle();
		//obj->SetPosition(x, y);
		/*LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);*/
		obj->idItems = id;
		allobject.push_back(obj);
		objectsstatic.push_back(obj);
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	

	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}



	for (UINT i = 0; i < allobject.size(); i++)
	{
		LPGAMEOBJECT obj = allobject[i];
		//float x, y;
		if (dynamic_cast<Candle*>(obj) && obj->GetState() == break_candle && !(obj->isDone))
		{
			obj->isDone = true;
			
			listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(),obj->idItems));
			

		}
	}

	simon->SimonColliWithItems(&listitems);

	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Update(dt, &coObjects);


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//for (int i = 0; i < coObjects.size(); i++)
	{
		if (simon->animation_set->at(simon_ani_stand_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_stand_hit||(simon->animation_set->at(simon_ani_sit_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_sit_hit))
		{
			if (simon->isHitSubWeapon)
			{				
				simon->GetKnife()->isDone = false;
			}
			else
				simon->GetWhip()->Update(dt, &objectsstatic);
			
		}
	}

	if(simon->currentWeapon!=-1&&!simon->GetKnife()->isDone) // khác -1 để ko bay ra phi tiêu // ko thể thêm đk đang đánh vũ khí phụ dc
		simon->GetKnife()->Update(dt, &objectsstatic);
		
	
	float cx, cy;
	simon->GetPosition(cx, cy);


	CGame *game = CGame::GetInstance();
	if (simon->GetPositionX() > (game->GetScreenWidth() / 2))
	{
		cx = simon->GetPositionX() - (game->GetScreenWidth() / 2);
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
	//cy -= game->GetScreenHeight() / 2;

	
}

void CPlayScene::Render()
{
	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Render();

	for (int i = 0; i < objectsstatic.size(); i++)
		objectsstatic[i]->Render();

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	//if(simon->isHitSubWeapon&&simon->currentWeapon!=-1)
		//simon->GetKnife()->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	simon = NULL;
}

void CPlayScenceKeyHandler::RunRight()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetNx(1);
	simon->SetState(simon_ani_run);
}

void CPlayScenceKeyHandler::RunLeft()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetNx(-1);
	simon->SetState(simon_ani_run);
	
}
// ,
void CPlayScenceKeyHandler::Jump()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->GetState() == simon_ani_stand_hit || simon->GetState() == simon_ani_sit_hit || simon->GetState() == simon_ani_sit || simon->GetState() == simon_ani_led)
		return;

	if (simon->isGrounded)
		simon->SetState(simon_ani_jump);
}

void CPlayScenceKeyHandler::Idle()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->isGrounded)
		simon->SetState(simon_ani_idle);
}

void CPlayScenceKeyHandler::Hit()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if ((simon->GetState() == simon_ani_idle || simon->GetState() == simon_ani_jump || simon->GetState() == simon_ani_run))
	{
		if (simon->isGrounded)
		{
			simon->SetState(simon_ani_stand_hit);
			simon->SetVx(0);
		}
		else
		{
			simon->SetState(simon_ani_stand_hit);
		}
	}
	else if (simon->GetState() == simon_ani_sit)
		simon->SetState(simon_ani_sit_hit);
}

void CPlayScenceKeyHandler::Sit()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetState(simon_ani_sit);
}

void CPlayScenceKeyHandler::Hit_SubWeapon()
{
	Simon *simon = ((CPlayScene*)scence)->simon;

	if (simon->currentWeapon == -1)
	{
		Hit();
		return;  //return để không bị đánh khi không có vũ khí phụ
	}

	if (simon->GetKnife()->isDone == false) //để cho vũ khí phụ ko thể đánh quá nhiều
		return;
	simon->isHitSubWeapon = true;
	if (simon->GetState() == simon_ani_sit) //ko để dc trong update simon
		simon->GetKnife()->SetPosSubWeapon(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), false);
	else
		simon->GetKnife()->SetPosSubWeapon(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), true);
	
	

	simon->GetKnife()->SetState(knife_ani);
	Hit();
}


void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->simon;
	switch (KeyCode)
	{
	case DIK_A:
		if (game->IsKeyDown(DIK_UP))
			Hit_SubWeapon();
		else
			Hit();
		break;
	case DIK_S:
		Jump();
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->simon;

	
	if (simon->GetState() == simon_ani_stand_hit && simon->animation_set->at(simon_ani_stand_hit)->RenderOver(300))//để cho ko bị đánh 2 lần
	{
		if (!(simon->isGrounded))
			simon->SetState(simon_ani_jump);
		else
			simon->SetState(simon_ani_idle);
	}

	if (!(simon->isGrounded))
		return;

	
	
	if (simon->GetState() == simon_ani_led && !(simon->animation_set->at(simon_ani_led)->RenderOver(600)))
		return;

	if ((simon->GetState() == simon_ani_stand_hit && !(simon->animation_set->at(simon_ani_stand_hit)->RenderOver(300))) || (simon->GetState() == simon_ani_sit_hit && !simon->animation_set->at(simon_ani_sit_hit)->RenderOver(300)))
	{	
		return;
	}
	else
		simon->isHitSubWeapon = false;



	if (game->IsKeyDown(DIK_DOWN))
	{
		Sit();
		if (game->IsKeyDown(DIK_RIGHT))
			simon->SetNx(1);
		else if (game->IsKeyDown(DIK_LEFT))
			simon->SetNx(-1);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		RunLeft();
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		RunRight();
	}
	else Idle();
}
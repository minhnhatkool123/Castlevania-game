/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include"Ground.h"
#include"Candle.h"
#include"Items.h"

#include"SceneManager.h";



#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevani"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120



CGame *game;
SceneManager *scenemanager;
//Simon *simon;
//
//vector<LPGAMEOBJECT> objects;
//vector<LPGAMEOBJECT> objectsstatic;
//vector<LPGAMEOBJECT> allobject;
//vector<LPGAMEOBJECT> listitems;
//
//class CSampleKeyHander : public CKeyEventHandler
//{
//	virtual void KeyState(BYTE *states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//
//	void RunRight()
//	{
//		simon->SetNx(1);
//		simon->SetState(simon_ani_run);
//	}
//	void RunLeft()
//	{
//		simon->SetNx(-1);
//		simon->SetState(simon_ani_run);
//	}
//	void Jump()
//	{
//
//		if (simon->GetState() == simon_ani_stand_hit || simon->GetState() == simon_ani_sit_hit || simon->GetState() == simon_ani_sit|| simon->GetState() == simon_ani_led)
//			return; 
//
//		if(simon->isGrounded)
//			simon->SetState(simon_ani_jump);	
//	}
//	void Idle()
//	{
//
//		if (simon->isGrounded)
//			simon->SetState(simon_ani_idle);
//	}
//	void Sit()
//	{
//		simon->SetState(simon_ani_sit);		
//	}
//	void Hit()
//	{		
//		if ((simon->GetState() == simon_ani_idle || simon->GetState() == simon_ani_jump ||simon->GetState()==simon_ani_run))
//		{
//			if (simon->isGrounded)
//			{
//				simon->SetState(simon_ani_stand_hit);
//				simon->SetVx(0);
//			}
//			else
//			{
//				simon->SetState(simon_ani_stand_hit);
//			}
//		}
//		else if (simon->GetState() == simon_ani_sit)//alo=)) nghe ko
//			simon->SetState(simon_ani_sit_hit);
//	}
//};
//
//CSampleKeyHander * keyHandler;
//
//void CSampleKeyHander::OnKeyDown(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//
//	switch (KeyCode)
//	{	
//	case DIK_A:
//		Hit();
//		break;
//	case DIK_SPACE:
//		Jump();
//		break;
//	}
//}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//}
//
//void CSampleKeyHander::KeyState(BYTE *states)
//{
//	if (simon->GetState()== simon_ani_stand_hit && simon->animations[simon_ani_stand_hit]->RenderOver(300))//để cho ko bị đánh 2 lần
//	{
//		if (!(simon->isGrounded))
//			simon->SetState(simon_ani_jump);
//		else
//			simon->SetState(simon_ani_idle);
//	}
//
//	if (!(simon->isGrounded)) 
//		return;
//
//
//	if (simon->GetState() == simon_ani_led && !(simon->animations[simon_ani_led]->RenderOver(600)))
//		return;
//
//	if ((simon->GetState() == simon_ani_stand_hit && !(simon->animations[simon_ani_stand_hit]->RenderOver(300))) || (simon->GetState() == simon_ani_sit_hit && !simon->animations[simon_ani_sit_hit]->RenderOver(300)))
//		return;
//
//	
//
//	if (game->IsKeyDown(DIK_DOWN))
//	{
//		Sit();
//		if (game->IsKeyDown(DIK_RIGHT))
//			simon->SetNx(1);
//		else if (game->IsKeyDown(DIK_LEFT))
//			simon->SetNx(-1);
//	}
//	else if (game->IsKeyDown(DIK_LEFT))
//	{
//			RunLeft();
//	}
//	else if (game->IsKeyDown(DIK_RIGHT))
//	{
//			RunRight();
//	}
//	else Idle();
//}


//Items* DropItem(float x, float y)
//{
//	Items *a = new Items();
//	a->AddAnimation(660);
//	a->SetPosition(x, y);
//	a->SetState(0);
//	
//	return a;
//}

/*Items* DropItem()
{
	float x, y;
	Items *a = new Items();
	for (UINT i = 0; i < allobject.size(); i++)
	{
		LPGAMEOBJECT obj = allobject[i];

		if (dynamic_cast<Candle*>(obj) && obj->GetState() == break_candle)
		{
			obj->GetPosition(x, y);
			a->AddAnimation(660);
			a->SetPosition(500, 130);
			a->SetState(0);

		}
	}
	return a;
}*/

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//void LoadResources()
//{
//	CTextures * textures = CTextures::GetInstance();
//
//	textures->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
//	textures->Add(ID_TEX_GROUND, L"textures\\Ground.png", D3DCOLOR_XRGB(255, 0, 255));
//	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_TEX_WHIP, L"textures\\WHIP.png", D3DCOLOR_XRGB(255, 0, 255));
//	textures->Add(ID_TEX_CANDLE, L"textures\\Candle.png", D3DCOLOR_XRGB(255, 0, 255));
//	textures->Add(ID_TEX_ITEMS, L"textures\\Items.png", D3DCOLOR_XRGB(255, 0, 255));
//
//	CSprites * sprites = CSprites::GetInstance();
//	CAnimations * animations = CAnimations::GetInstance();
//
//	LPDIRECT3DTEXTURE9 textSimon = textures->Get(ID_TEX_SIMON);
//	LPDIRECT3DTEXTURE9 textGround = textures->Get(ID_TEX_GROUND);
//	LPDIRECT3DTEXTURE9 textWhip = textures->Get(ID_TEX_WHIP);
//	LPDIRECT3DTEXTURE9 textCandle = textures->Get(ID_TEX_CANDLE);
//	LPDIRECT3DTEXTURE9 textItems = textures->Get(ID_TEX_ITEMS);
//	
//
//	sprites->Add(1000, 0, 0, 60, 64, textSimon);
//
//	sprites->Add(1005, 60, 0, 120, 64, textSimon);
//	sprites->Add(1006, 120, 0, 180, 64, textSimon);
//	sprites->Add(1007, 180, 0, 240, 64, textSimon);
//
//
//	sprites->Add(1008, 240, 0, 300, 64, textSimon);//jump
//
//
//	sprites->Add(1009, 302, 198, 360, 262, textSimon);//sitdown
//
//
//	sprites->Add(1010, 301, 0, 360, 64, textSimon);//đánh đứng
//	sprites->Add(1011, 361, 0, 420, 64, textSimon);//đánh đứng
//	sprites->Add(1012, 421, 0, 480, 64, textSimon);//đánh đứng
//
//	sprites->Add(1013, 420, 66, 480, 130, textSimon);//đánh ngồi
//	sprites->Add(1014, 0, 132, 60, 196, textSimon);
//	sprites->Add(1015, 60, 132, 120, 196, textSimon);
//
//	sprites->Add(1016, 120, 198, 180, 262, textSimon);//simon nhấp nháy khi ăn nâng cấp vũ khí
//	sprites->Add(1017, 60, 198, 120, 262, textSimon);
//	sprites->Add(1018, 0, 198, 60, 262, textSimon);
//
//
//	sprites->Add(1100, 0, 0, 32, 32, textGround);
//
//	sprites->Add(1200, 0, 0, 240, 66, textWhip);//whip lv1
//	sprites->Add(1201 ,240, 0, 480, 66, textWhip);
//	sprites->Add(1202, 480, 0, 720, 66, textWhip);
//
//	sprites->Add(1203, 0, 66, 240, 132, textWhip);//whip lv2
//	sprites->Add(1204, 240, 66, 480, 132, textWhip);
//	sprites->Add(1205, 480, 66, 720, 132, textWhip);
//
//	sprites->Add(1206, 0	,132,	240	,198, textWhip);//whip lv3
//	sprites->Add(1207, 240, 132, 480, 198, textWhip);
//	sprites->Add(1208, 480, 132, 720, 198, textWhip);
//	sprites->Add(1209, 0, 198, 240, 264, textWhip);
//	sprites->Add(1210, 240, 198, 480, 264, textWhip);
//	sprites->Add(1211, 480, 198, 720, 264, textWhip);
//	sprites->Add(1212, 0, 264, 240, 330, textWhip);
//	sprites->Add(1213, 240, 264, 480, 330, textWhip);
//	sprites->Add(1214, 480, 264, 720, 330, textWhip);
//	sprites->Add(1215, 0, 330, 240, 396, textWhip);
//	sprites->Add(1216, 240, 330, 480, 396, textWhip);
//	sprites->Add(1217, 480, 330, 720, 396, textWhip);
//
//
//
//	sprites->Add(1300, 0, 0, 32, 64, textCandle);//cây nến to
//	sprites->Add(1301, 32, 0, 64, 64, textCandle);
//
//	sprites->Add(1310, 130, 0, 162, 32, textItems);//Item tăng vũ khí chính
//
//	LPANIMATION ani;
//
//	ani = new CAnimation(100);
//	ani->Add(1000);
//	animations->Add(400, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1000);
//	ani->Add(1005);
//	ani->Add(1006);
//	ani->Add(1007);
//	animations->Add(401, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1008);
//	animations->Add(402, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1009);
//	animations->Add(403, ani);
//
//
//	ani = new CAnimation(100);
//	ani->Add(1010);
//	ani->Add(1011);
//	ani->Add(1012);
//	animations->Add(404, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1013);
//	ani->Add(1014);
//	ani->Add(1015);
//	animations->Add(405, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1016);
//	ani->Add(1017);
//	ani->Add(1018);
//	animations->Add(406, ani);
//
//	simon = new Simon();
//	simon->AddAnimation(400);
//	simon->AddAnimation(401);
//	simon->AddAnimation(402);
//	simon->AddAnimation(403);
//	simon->AddAnimation(404);
//	simon->AddAnimation(405);
//	simon->AddAnimation(406);
//
//
//	simon->SetPosition(400, 99);
//	objects.push_back(simon);
//
//	//Mặt đất
//	ani = new CAnimation(100);
//	ani->Add(1100);
//	animations->Add(500,ani);
//
//	//Whip
//	ani = new CAnimation(100);
//	ani->Add(1200);
//	ani->Add(1201);
//	ani->Add(1202);
//	animations->Add(600, ani);
//	
//	ani = new CAnimation(100);
//	ani->Add(1203);
//	ani->Add(1204);
//	ani->Add(1205);
//	animations->Add(601, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(1206);
//	//ani->Add(1207);
//	//ani->Add(1208);
//	//ani->Add(1209);
//	ani->Add(1210);
//	//ani->Add(1211);
//	//ani->Add(1212);
//	//ani->Add(1213);
//	ani->Add(1214);
//	//ani->Add(1215);
//	//ani->Add(1216);
//	//ani->Add(1217);
//	animations->Add(602, ani);
//	simon->GetWhip()->AddAnimation(600);
//	simon->GetWhip()->AddAnimation(601);
//	simon->GetWhip()->AddAnimation(602);
//
//	//whip = new Whip();
//	//whip->AddAnimation(600);
//
//	for (int i = 0; i < 30; i++)
//	{
//		Ground *ground = new Ground();
//		ground->SetPosition(0 + i* 32.0f, 162);
//		objects.push_back(ground);
//	}
//
//	Ground *ground = new Ground();
//	ground->SetPosition(100, 80);
//	objects.push_back(ground);
//
//
//	ani = new CAnimation(100);//cây nến to
//	ani->Add(1300);
//	ani->Add(1301);
//	animations->Add(650,ani);
//	
//	//candle->AddAnimation(650);
//	//candle->SetPosition(250,98);
//	
//
//	for (int i = 0; i < 3; i++)
//	{
//		Candle *candle = new Candle();
//		candle->SetPosition(200 + i * 200, 98);
//		objectsstatic.push_back(candle);
//		allobject.push_back(candle);
//	}
//
//
//	ani = new CAnimation(100);
//	ani->Add(1310);//Item tăng vũ khí chính
//	animations->Add(660, ani);
//	//Items *items = new Items();
//	//items->AddAnimation(660);
//	//items->SetPosition(500, 130);
//	//objects.push_back(items);
//	
//}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	//vector<LPGAMEOBJECT> coObjects;

	//for (int i = 1; i < objects.size(); i++)
	//{
	//		coObjects.push_back(objects[i]);
	//}



	//for (UINT i = 0; i < allobject.size(); i++)
	//{
	//	LPGAMEOBJECT obj = allobject[i];
	//	//float x, y;
	//	if (dynamic_cast<Candle*>(obj) && obj->GetState() == break_candle&&!(obj->isDone))
	//	{
	//		obj->isDone = true;
	//		//obj->GetPosition(x, y);
	//		listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY()));
	//		//objects.push_back(DropItem(obj->GetPositionX(),obj->GetPositionY())); //DropItem();

	//	}
	//}

	//simon->SimonColliWithItems(&listitems);

	//for (int i = 0; i < listitems.size(); i++)
	//	listitems[i]->Update(dt,&coObjects);
	//

	//for (int i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Update(dt, &coObjects);
	//}

	//for (int i = 0; i < coObjects.size(); i++)
	//{
	//	if (simon->animations[simon_ani_stand_hit]->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_stand_hit)
	//	{
	//		simon->GetWhip()->Update(dt, &objectsstatic);		
	//	}
	//}
	//



	//
	//
	//

	//float cx, cy;
	//simon->GetPosition(cx, cy);
	//cx -= SCREEN_WIDTH / 2; 
	//cy -= SCREEN_HEIGHT / 2;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*y*/);

	//CGame::GetInstance()->GetCurrentScene()->Update(dt);
	scenemanager->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		/*for (int i = 0; i < listitems.size(); i++)
			listitems[i]->Render();

		for (int i = 0; i < objectsstatic.size(); i++)
			objectsstatic[i]->Render();

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();*/

		
		//CGame::GetInstance()->GetCurrentScene()->Render();
		scenemanager->Render();
		


		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	scenemanager = SceneManager::GetInstance();
	game = CGame::GetInstance();
	game->Init(hWnd);
	game->InitKeyboard();

	//game->Load(L"Scenes\\Castlevania.txt");
	scenemanager->SetScene(new CPlayScene());
	


	/*LoadResources();*/

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
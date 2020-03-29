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

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include"Ground.h"
#include "Whip.h"



#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevani"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_SIMON 30
#define ID_TEX_GROUND 40
#define ID_TEX_WHIP 50

CGame *game;
Simon *simon;
Whip *whip;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	void RunRight()
	{
		simon->SetNx(1);
		simon->SetState(simon_ani_run);
	}
	void RunLeft()
	{
		simon->SetNx(-1);
		simon->SetState(simon_ani_run);
	}
	void Jump()
	{

		if (simon->GetState() == simon_ani_stand_hit || simon->GetState() == simon_ani_sit_hit || simon->GetState() == simon_ani_sit)
			return; 

		if(simon->isGrounded)
			simon->SetState(simon_ani_jump);	
	}
	void Idle()
	{

		if (simon->isGrounded)
			simon->SetState(simon_ani_idle);
	}
	void Sit()
	{
		simon->SetState(simon_ani_sit);		
	}
	void Hit()
	{		
		if ((simon->GetState() == simon_ani_idle || simon->GetState() == simon_ani_jump ||simon->GetState()==simon_ani_run))
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
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{	
	case DIK_A:
		Hit();
		break;
	case DIK_SPACE:
		Jump();
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (simon->GetState()== simon_ani_stand_hit && simon->animations[simon_ani_stand_hit]->RenderOver(300))//để cho ko bị đánh 2 lần
	{
		if (!(simon->isGrounded))
			simon->SetState(simon_ani_jump);
		else
			simon->SetState(simon_ani_idle);
	}

	if (!(simon->isGrounded)) 
		return;

	if ((simon->GetState() == simon_ani_stand_hit && !(simon->animations[simon_ani_stand_hit]->RenderOver(300))) || (simon->GetState() == simon_ani_sit_hit && !simon->animations[simon_ani_sit_hit]->RenderOver(300)))
		return;

	

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

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND, L"textures\\Ground.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP, L"textures\\WHIP.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 textGround = textures->Get(ID_TEX_GROUND);
	LPDIRECT3DTEXTURE9 textWhip = textures->Get(ID_TEX_WHIP);
	

	sprites->Add(1000, 0, 0, 60, 64, textSimon);

	sprites->Add(1005, 60, 0, 120, 64, textSimon);
	sprites->Add(1006, 120, 0, 180, 64, textSimon);
	sprites->Add(1007, 180, 0, 240, 64, textSimon);


	sprites->Add(1008, 240, 0, 300, 64, textSimon);//jump


	sprites->Add(1009, 302, 198, 360, 262, textSimon);//sitdown


	sprites->Add(1010, 301, 0, 360, 64, textSimon);//đánh đứng
	sprites->Add(1011, 361, 0, 420, 64, textSimon);//đánh đứng
	sprites->Add(1012, 421, 0, 480, 64, textSimon);//đánh đứng

	sprites->Add(1013, 420, 66, 480, 130, textSimon);//đánh ngồi
	sprites->Add(1014, 0, 132, 60, 196, textSimon);
	sprites->Add(1015, 60, 132, 120, 196, textSimon);


	sprites->Add(1100, 0, 0, 32, 32, textGround);

	sprites->Add(1200, 0, 0, 240, 66, textWhip);
	sprites->Add(1201 ,240, 0, 480, 66, textWhip);
	sprites->Add(1202, 480, 0, 720, 66, textWhip);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(1000);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(1000);
	ani->Add(1005);
	ani->Add(1006);
	ani->Add(1007);
	animations->Add(401, ani);

	ani = new CAnimation(100);
	ani->Add(1008);
	animations->Add(402, ani);

	ani = new CAnimation(100);
	ani->Add(1009);
	animations->Add(403, ani);


	ani = new CAnimation(100);
	ani->Add(1010);
	ani->Add(1011);
	ani->Add(1012);
	animations->Add(404, ani);

	ani = new CAnimation(100);
	ani->Add(1013);
	ani->Add(1014);
	ani->Add(1015);
	animations->Add(405, ani);

	simon = new Simon();
	simon->AddAnimation(400);
	simon->AddAnimation(401);
	simon->AddAnimation(402);
	simon->AddAnimation(403);
	simon->AddAnimation(404);
	simon->AddAnimation(405);

	simon->SetPosition(150, 99);
	objects.push_back(simon);

	//Mặt đất
	ani = new CAnimation(100);
	ani->Add(1100);
	animations->Add(500,ani);

	//Whip
	ani = new CAnimation(100);
	ani->Add(1200);
	ani->Add(1201);
	ani->Add(1202);
	animations->Add(600, ani);
	//whip = new Whip();
	//whip->AddAnimation(600);

	for (int i = 0; i < 20; i++)
	{
		Ground *ground = new Ground();
		ground->SetPosition(0 + i* 32.0f, 162);
		objects.push_back(ground);
	}

	Ground *ground = new Ground();
	ground->SetPosition(100, 130);
	objects.push_back(ground);

	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	//simon->Update(dt);

	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2; 
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*y*/);
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

		
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		//whip->Render(simon->animations[simon->GetState()]->GetcurrentFrame());
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

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2 , SCREEN_HEIGHT*2 , SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
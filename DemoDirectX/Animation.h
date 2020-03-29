#pragma once
#include"Sprites.h"

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD startFrameTime;

	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(int nx,float x, float y, int alpha = 255);
	void RenderWhip(int currentID, int nx, float x, float y, int alpha = 255); 
	
	void ResetcurrentFrame()
	{
		currentFrame = -1;
	}

	int GetcurrentFrame()
	{
		return currentFrame;
	}
	void StartAni()
	{
		startFrameTime = GetTickCount();
	}
	bool RenderOver(DWORD a)
	{
		if (GetTickCount() - startFrameTime >= a)
		{
			//startFrameTime = 0;
			return true;
		}
		else
			return false;
	}



};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};


#include "SceneManager.h"

SceneManager * SceneManager::__instance = NULL;


SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

SceneManager * SceneManager::GetInstance()
{
	if (__instance == NULL)
		__instance = new SceneManager();
	return __instance;
}

void SceneManager::Load()
{
	currentScene->Load();
}
void SceneManager::Unload()
{
	currentScene->Unload();
}
void SceneManager::Update(DWORD dt)
{
	currentScene->Update(dt);
}
void SceneManager::Render()
{
	currentScene->Render();
}
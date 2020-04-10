#include "SenceManager.h"


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


SceneManager * SceneManager::_instance = NULL;

SceneManager * SceneManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new SceneManager();
	return _instance;
}

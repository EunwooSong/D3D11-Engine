#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Render()
{

}

void SceneManager::Update(float dt)
{

}

void SceneManager::ChangeScene(Scene* iter)
{
	if (currentScene) SAFE_DELETE(currentScene);
	currentScene = iter;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}

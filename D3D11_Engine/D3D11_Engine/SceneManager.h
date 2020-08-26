#pragma once

class Scene;

class SceneManager
{
private:
	Scene* currentScene;

public:
	SceneManager();
	~SceneManager();

	void Render();
	void Update(float dt);

	void ChangeScene(Scene* iter);
	Scene* getCurrentScene();
};


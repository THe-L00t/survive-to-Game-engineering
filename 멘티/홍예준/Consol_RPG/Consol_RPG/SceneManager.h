#pragma once
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* Instance;

public:
	SceneManager() { if (Instance == nullptr) Instance = this; }
	~SceneManager() { Release(); }

	void Update(float deltaTime);
	void Render();
	void Release();

	//씬 교체 함수
	void ChangeScene(Scene* newScene);

private:
	Scene* currentScene = nullptr;
};


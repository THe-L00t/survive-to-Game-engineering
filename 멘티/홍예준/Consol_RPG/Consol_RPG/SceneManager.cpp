#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::Instance = nullptr;

void SceneManager::ChangeScene(Scene* newScene) {
	//기존 씬이 있다면 메모리 해제
	if (currentScene != nullptr) {
		currentScene->Release();
		delete currentScene;
	}

	//새로운 씬으로 교체 후 초기화
	currentScene = newScene;
	if (currentScene != nullptr) {
		currentScene->Init();
	}
}

void SceneManager::Update(float deltaTime) {
	if (currentScene) currentScene->Update(deltaTime);
}

void SceneManager::Render() {
	if (currentScene) currentScene->Render();
}

void SceneManager::Release() {
	if (currentScene) {
		currentScene->Release();
		delete currentScene;
		currentScene = nullptr;
	}
}
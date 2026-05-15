#pragma once
#include "Scene.h"

class TownScene : public Scene
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Release() override;

private:
	//bool isMenuOpen = false;	// 메뉴가 열려있는지 확인
	//int selectedIndex = 0;		// 현재 선택된 메뉴 번호
	//const int MAX_MENU = 2;		// 메뉴의 총 개수
};


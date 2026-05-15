#pragma once
#include "pch.h"
#include "Scene.h"

class MapScene : public Scene
{
public:
	MapScene(std::string name, int id);

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Release() override;

private:
	//맵의 아이디를 저장할 변수들
	std::string mapName;
	int mapID; //맵 자체의 id

	bool isMenuOpen = false;	// 메뉴가 열려있는지 확인
	int selectedIndex = 0;		// 현재 선택된 메뉴 번호
	const int MAX_MENU = 2;		// 메뉴의 총 개수
};


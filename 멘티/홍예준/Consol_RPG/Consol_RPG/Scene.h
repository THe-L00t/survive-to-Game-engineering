#pragma once
class Scene
{
protected:	//public 도 private도 아닌, 자식에게만 물려주는 공간
	bool isMapMenuOpen = false;	// 메뉴가 열려있는지 확인
	bool isMenuOpen = false;
	int selectedIndex = 0;		// 현재 선택된 메뉴 번호
	int selectedMenuIndex = 0;
	int maxMenu;		// 메뉴의 총 개수

public:
	virtual ~Scene() = default; // 가상 소멸자

	//순수 가상 함수 선언
	virtual void Init() = 0;					// 씬 진입시 1회 실행
	virtual void Update(float deltaTime) = 0;	// 매 프레임 로직 처리(이동, 입력)
	virtual void Render() = 0;					// 매 프레임 화면 출력
	virtual void Release() = 0;					// 씬 빠저나갈때 메모리 정리
};



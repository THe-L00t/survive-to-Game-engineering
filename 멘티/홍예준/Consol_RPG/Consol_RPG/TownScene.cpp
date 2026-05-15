#include "pch.h"
#include "TownScene.h"
#include "SceneManager.h"
#include "MapScene.h"

void TownScene::Init() {
	// 초기화
	system("cls");
	isMenuOpen = false;
	selectedIndex = 0;
}

void TownScene::Update(float deltaTime) {
	// 키 입려 받기
	if (_kbhit()) {
		int key = _getch();

		// ESC(27) 키를 입력 받았을때
		if (key == 27) {
			isMenuOpen = !isMenuOpen;	//true면 flase로 false면 true로
			system("cls");				//화면 겹치지 않게 초기화
		}
		// 메뉴가 열려있을때만 방향키 및 엔터 작동
		else if (isMenuOpen) {
			if (key == 224) {			//224 : 방향키 입력 감지
				key = _getch();			// 키 입력 한번 더 가져오기
				
				if (key == 72) {		// 위 화살표
					selectedIndex--;
					// 맨 위 메뉴에서 위로 한 칸 더 이동하면 맨 아래로 이동
					if (selectedIndex < 0) selectedIndex = MAX_MENU - 1;
				}
				else if (key == 80) {	// 아래 화살표
					selectedIndex++;
					// 맨 마지막 메뉴에서 아래로 한 칸 더 이동하면 맨 위로 이동
					if (selectedIndex >= MAX_MENU) selectedIndex = 0;
				}
			}
			else if (key == 13) {		// 엔터 입력
				if (selectedIndex == 0) {
					//맵 이동
					SceneManager::Instance->ChangeScene(new MapScene("울창한 숲", 1));
				}
				else if (selectedIndex == 1) {
					//맵 이동
					SceneManager::Instance->ChangeScene(new MapScene("어두운 동굴", 2));
				}

			}
		}
	}

}

void PrintBone() {
	std::cout << "=================================" << std::endl;
	std::cout << "         -시작의 마을-" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << std::endl << "당신은 시작의 마을에 도착합니다." << std::endl << "모든 것의 시작이라는 뜻으로 시작에 마을이라고 불리고 있지만" << std::endl;
	std::cout << "어쩐지 조금 한산하기도 한거 같습니다." << std::endl;
	std::cout << std::endl << "『뭐 부터 할까...』" << std::endl;
}

void TownScene::Render() {
	COORD cursorPosition = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	PrintBone();
	if (isMenuOpen) {
		std::cout << std::endl << "===== 맵 이동 메뉴 =====" << std::endl;

		//selectedIndex 값에 따라 커서의 위치가 바뀜
		if (selectedIndex == 0) {
			std::cout << " ▶ 1. 숲으로 이동" << std::endl;
		}
		else {
			std::cout << "    1. 숲으로 이동" << std::endl;
		}

		if (selectedIndex == 1) {
			std::cout << " ▶ 2. 어둠의 동굴 이동" << std::endl;
		}
		else {
			std::cout << "    2. 어둠의 동굴 이동" << std::endl;
		}
		std::cout << "========================";
	}
	else {
		//메뉴가 닫혔을때 잔상 지우기
		std::cout << "                                             " << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "                                             " << std::endl;
		std::cout << "                                             " << std::endl;
	}
}

void TownScene::Release() {

}
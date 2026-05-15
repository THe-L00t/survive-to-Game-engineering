#include "pch.h"
#include "MapScene.h"
#include "SceneManager.h"
#include "TownScene.h"


// 생성자로 넘어온 값을 변수에 저장
MapScene::MapScene(std::string name, int id) {
	mapName = name;
	mapID = id;
}

void MapScene::Init() {
	system("cls");
}

void MapScene::Update(float deltaTime) {
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
					if (selectedIndex < 0) selectedIndex = maxMenu - 1;
				}
				else if (key == 80) {	// 아래 화살표
					selectedIndex++;
					// 맨 마지막 메뉴에서 아래로 한 칸 더 이동하면 맨 위로 이동
					if (selectedIndex >= maxMenu) selectedIndex = 0;
				}
			}
			else if (key == 13) {		// 엔터 입력
				if (selectedIndex == 0) {
					//맵 이동
					SceneManager::Instance->ChangeScene(new TownScene);
				}
			}
		}
	}
}

void mapEx(int id) {
	if (id == 1) {
		std::cout << "울창한 숲에 도착했습니다." << std::endl;
		std::cout << "시원한 바람이 불고 가끔씩 들리는 새소리는 가만히 있어도 기분이 좋아지게 만듭니다." << std::endl;
		std::cout << "당신은 숲의 바람을 느끼며 앞으로 나아가기로 합니다." << std::endl;
	}
	else if (id == 2) {
		std::cout << "어두운 동굴에 도착했습니다." << std::endl;
		//아이템 유무에 따른 이동 방법
		//if (item != "torchlight") {
		//	std::cout << "동굴이 너무 어두워 들어갈 수 없을 것 같습니다." << std::endl;
		//	std::cout << "아이템 '횟불'이 필요합니다." << std::endl;
		//	SceneManager::Instance->ChangeScene(new TownScene);
		//}
		std::cout << "매우 어두운 동굴입니다. 횟불이 사라지면 아무것도 못할 거 같습니다." << std::endl;
		std::cout << "당신은 조금 긴장했지만 앞으로 나아가기로 합니다." << std::endl;
	}
}

void MapScene::Render() {
	COORD cursorPosition = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

	std::cout << "=================================" << std::endl;
	std::cout << "         - " << mapName << " - " << std::endl;
	std::cout << "=================================" << std::endl;
	mapEx(mapID);
	if (isMenuOpen) {
		std::cout << std::endl << "===== 맵 이동 메뉴 =====" << std::endl;

		//selectedIndex 값에 따라 커서의 위치가 바뀜
		if (selectedIndex == 0) {
			std::cout << " ▶ 1. 마을로 이동" << std::endl;
		}
		else {
			std::cout << "    1. 마을로 이동" << std::endl;
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

void MapScene::Release() {

}
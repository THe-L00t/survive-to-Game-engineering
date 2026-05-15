#include "pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "TownScene.h"
#include <iostream>

void TitleScene::Init() {
	// 타이틀 초기화 로직
}

void TitleScene::Update(float deltaTime) {
	//키 입력 처리
	//입력 ex) 엔터키 입력시
	if (_kbhit()) {					// _kbhit() : 키가 입력 될 경우 true 반환
		int key = _getche();		// _getche() : 눌린값 가져옴 지금은 int이기 때문에 아스키 코드가 가져와짐

		// 13은 'Enter'의 아스키 코드
		if (key == 13) {
			//씬 교체
			SceneManager::Instance->ChangeScene(new TownScene());
		}
	}
}

void TitleScene::Render() {
	// 콘솔 커서를 맨 왼쪽 위(0,0)로 이동
	COORD cursorPosition = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■         ■■■■     ■■■    ■■■■      ■■■■    ■■■    ■                    ■ " << std::endl;
	std::cout << "■       ■           ■      ■  ■      ■  ■          ■      ■  ■                    ■ " << std::endl;
	std::cout << "■       ■           ■      ■  ■      ■    ■■■■  ■      ■  ■                    ■ " << std::endl;
	std::cout << "■       ■           ■      ■  ■      ■          ■  ■      ■  ■                    ■ " << std::endl;
	std::cout << "■         ■■■■     ■■■    ■      ■  ■■■■      ■■■    ■■■                ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                  ■■■■■■■□        ■■■■■■□          ■■■■■■■□        ■ " << std::endl;
	std::cout << "■                ■■■■■■■■■□    ■■■■■■■■□      ■■■■■■■■■□      ■ " << std::endl;
	std::cout << "■                ■■□        ■■□    ■■□        ■■□  ■■■□                    ■ " << std::endl;
	std::cout << "■                ■■□        ■■□    ■■□        ■■□  ■■□                      ■ " << std::endl;
	std::cout << "■                ■■■■■■■■□      ■■■■■■■■□    ■■□                      ■ " << std::endl;
	std::cout << "■                ■■■■■□            ■■■■■■■□      ■■□        ■■■□      ■ " << std::endl;
	std::cout << "■                ■■■■■■□          ■■□                ■■□      ■■■■□      ■ " << std::endl;
	std::cout << "■                ■■□  ■■■□        ■■□                ■■■□        ■■□      ■ " << std::endl;
	std::cout << "■                ■■□    ■■■□      ■■□                  ■■■■■■■■□        ■ " << std::endl;
	std::cout << "■                ■■□      ■■□      ■■□                    ■■■■■■□          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                  ~그냥 대충 해보는 RPG 게임 스토리도 뭣도 아무것도 없다~                 ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                - Press Enter to Start -                                  ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■                                                                                          ■ " << std::endl;
	std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ " << std::endl;
}

void TitleScene::Release() {
		//데이터 정리
}
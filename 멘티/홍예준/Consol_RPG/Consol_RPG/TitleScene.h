#pragma once
#include "pch.h"
#include "Scene.h"
#include <iostream>

class TitleScene : public Scene
{
public:
	void Init() override {
		// 타이틀 초기화 로직
	}
	void Update(float deltaTime) override {
		//키 입력 처리
		//입력 ex) 엔터키 입력시
		// SceneManager::Instance->ChangeScene(new TownScene()); 실행
	}
	void Render() override {
		//콘솔 화면 지우기 (system("cls") 등) 후 타이틀 화면 출력
		// 콘솔 커서를 맨 왼쪽 위(0,0)로 이동
		COORD cursorPosition = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
		std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■         ■■■■     ■■■    ■■■■      ■■■■    ■■■    ■                    ■" << std::endl;
		std::cout << "■       ■           ■      ■  ■      ■  ■          ■      ■  ■                    ■" << std::endl;
		std::cout << "■       ■           ■      ■  ■      ■    ■■■■  ■      ■  ■                    ■" << std::endl;
		std::cout << "■       ■           ■      ■  ■      ■          ■  ■      ■  ■                    ■" << std::endl;
		std::cout << "■         ■■■■     ■■■    ■      ■  ■■■■      ■■■    ■■■                ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                  ■■■■■■■□        ■■■■■■□          ■■■■■■■□        ■" << std::endl;
		std::cout << "■                ■■■■■■■■■□    ■■■■■■■■□      ■■■■■■■■■□      ■" << std::endl;
		std::cout << "■                ■■□        ■■□    ■■□        ■■□  ■■■□                    ■" << std::endl;
		std::cout << "■                ■■□        ■■□    ■■□        ■■□  ■■□                      ■" << std::endl;
		std::cout << "■                ■■■■■■■■□      ■■■■■■■■□    ■■□                      ■" << std::endl;
		std::cout << "■                ■■■■■□            ■■■■■■■□      ■■□        ■■■□      ■" << std::endl;
		std::cout << "■                ■■■■■■□          ■■□                ■■□      ■■■■□      ■" << std::endl;
		std::cout << "■                ■■□  ■■■□        ■■□                ■■■□        ■■□      ■" << std::endl;
		std::cout << "■                ■■□    ■■■□      ■■□                  ■■■■■■■■□        ■" << std::endl;
		std::cout << "■                ■■□      ■■□      ■■□                    ■■■■■■□          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                  ~그냥 대충 해보는 RPG 게임 스토리도 뭣도 아무것도 없다~                 ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                - Press Enter to Start -                                  ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■                                                                                          ■" << std::endl;
		std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
	}
	void Release() override {
		//데이터 정리
	}
};


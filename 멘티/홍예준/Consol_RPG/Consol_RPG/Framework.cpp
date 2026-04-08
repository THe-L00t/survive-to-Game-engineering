#include "Framework.h"

TimeManager* TimeManager::Instance = nullptr; //Time의 실제 선언

Framework::Framework() {
	timer = std::make_unique<TimeManager>(); //Time을 동적으로 선언
}

Framework::~Framework() {

}

void Framework::Init() { //초기화

}

void Framework::Loop() { //반복
	startTime = timer.get()->timer;
	while (true) {
		//시간 업데이트
		timer->Update();


		//currentScene->Update(timer->deltaTime);

		// CPU 과부화 방지를 위한 짧은 sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
	}
}

void Framework::Destroy() { //종료

}
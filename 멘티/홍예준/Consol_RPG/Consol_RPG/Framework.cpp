#include "Framework.h"
#include "SceneManager.h"
#include "TitleScene.h"


TimeManager* TimeManager::Instance = nullptr; //Time의 실제 선언

Framework::Framework() {
	timer = std::make_unique<TimeManager>(); //Time을 동적으로 선언
}

Framework::~Framework() {
}

void Framework::Init() { //초기화
	// 씬 매니저 객체 생성 (싱글톤) <- 공부
	new SceneManager();

	// 첫 화면을 TitleScene으로 설정
	SceneManager::Instance->ChangeScene(new TitleScene());
}

void Framework::Loop() { //반복
	startTime = timer.get()->timer;
	while (true) {
		//시간 업데이트
		timer->Update();

		// 1. 데이터 및 로직 업데이트
		SceneManager::Instance->Update(timer->deltaTime);

		// 2. 화면 렌더링 (콘솔 출력)
		SceneManager::Instance->Render();
		
		// CPU 과부화 방지를 위한 짧은 sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
	}
}

void Framework::Destroy() { //종료

}
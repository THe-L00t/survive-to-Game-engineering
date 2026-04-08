#pragma once
#include <chrono>
#include <thread>
class TimeManager
{
public:
	static TimeManager* Instance; //어디서든 접근할 수 있는 정적 포인터

public:
	TimeManager() {
		if (Instance == nullptr) Instance = this; //Instance가 비어있다면 나의 주소를 (this) 집어넣겠다.
		startTime = std::chrono::high_resolution_clock::now(); //객체 생성 순간에 시각 찍기
		prevTime = startTime;
	}
	void Update() { //매 프레임 실행
		auto end = std::chrono::high_resolution_clock::now(); //현재 프레임의 시점을 end변수에 기록하겠다.
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - prevTime);
		// ㄴ 현재 시간(end)에서 이전 프레임의 시간을 빼겠다.
		deltaTime = static_cast<float>(duration.count()) / 1000; //걸린시간을 밀리초(ms, 1/1000초) 단위의 정수로 변환하여 duration에 저장한다.
		timer += deltaTime; //게임 시간 구하기
		prevTime = end; //현재 시점을 이전 시점에 찍고 마무리
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; //초기화된 그 시간을 startTime로 선언하겠다.
	std::chrono::time_point<std::chrono::high_resolution_clock> prevTime; //초기값은 초기화된 그 순간으로 선언.
public:
	float timer = 0;
	float deltaTime = 0;
};

/* Time의 기초
 Start Time = 시간 초기화(처음 값)
 Prev Tiem = 찍힌 시간의 전 값
 흐름
 ST로 초기화 시작
 update가 끝날때마다 end 찍힘
 deltaTime에는 st ~ end까지의 시간이 기록
 PT에는 찍혀있는 전값인 ST가 들어감
 이후 Update마다 end가 찍히며 위가 반복
 Timer에는 지속적으로 deltaTime이 들어감 <- 플레이 시간 기록
 
 startTime, prevTime [private]
 startTime : 프로그램이 처음 시작된 시각을 기록
 prevTime : Update() 함수가 마지막으로 실행됐던 '이전 플레임' 시각 기록
 
 timer, deltaTime [public]
 deltaTime : 마지막으로 기록된 시간부터 이번 프레임까지의 걸린 시간
 timer : 프로그램이 시작된 후 누적된 모든 시간 기록*/
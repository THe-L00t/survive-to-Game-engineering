#pragma once
#include <chrono>
class Time
{
public:
	static Time* Instance; //유일한 변수 선언

public:
	Time() {
		
	}
	void Update() {

	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; //초기화된 그 시간을 startTime로 선언하겠다.
	std::chrono::time_point<std::chrono::high_resolution_clock> prevTime; //초기값은 초기화된 그 순간으로 선언.
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
 Timer에는 지속적으로 deltaTime이 들어감 <- 플레이 시간 기록*/
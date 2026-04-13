#pragma once
#include <GLFW/glfw3.h>

class Time {
private:
    // 이전 프레임에서 현재 프레임까지 걸린 시간 (초 단위)
    inline static double deltaTime = 0.0f;

    // 게임 시작 후 흐른 총 시간
    inline static double time = 0.0f;

    // 시간 배율
    inline static double timeScale = 1.0f;

    // 프레임 카운트
    inline static unsigned long long frameCount = 0;

public:
    static void Init() {
        time = glfwGetTime();
    }

    // GameManager에서 매 프레임 호출하여 값을 갱신
    static void Update() {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - time;
        time = currentTime;

        deltaTime *= timeScale;
        frameCount++;
    }

    static const double GetDeltaTime() {
        return deltaTime;
    }

    static const double GetDeltaTimeF() {
        return (float)deltaTime;
    }
    
    static const double GetTime() {
        return time;
    }

    static const double GetTimeF() {
        return (float)time;
    }

    static const double GetTimeScale() {
        return timeScale;
    }

    static void SetTimeScale(double scale) {
        timeScale = scale;
    }

    static const unsigned long long GetFrameCount() {
        return frameCount;
    }
};
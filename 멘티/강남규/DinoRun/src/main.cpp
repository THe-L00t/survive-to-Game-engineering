#include "Input.hpp"
#include "DinoRun/DinoRunGame.hpp"

// stb_image 구현은 여기서 유지 (컴파일 유닛 관리용)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    // 게임 초기화
    DinoRunGame dinoGame;
    dinoGame.Init(1600, 800, "Dino Run");

    // 메인 루프
    while (!dinoGame.ShouldClose()) {
        dinoGame.Update();
        dinoGame.LateUpdate();
        dinoGame.Render();
        dinoGame.EndOfFrame();
    }

    dinoGame.Shutdown();
    
    return 0;
}
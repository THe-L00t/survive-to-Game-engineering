#include <iostream>
#include "Framework.h"

using namespace std;

struct CharacterStatus {
	int level;
	float atk;
	float def;
	float speed;
	int d;
};


int main() {
	// 1. 프레임워크 생성
	Framework game;

	// 2. 초기화 진행
	game.Init();

	// 3. 게임 무한 루프 실행
	game.Loop();

	// 4. 루프가 끝나면 종료 처리
	game.Destroy();

	return 0;
}
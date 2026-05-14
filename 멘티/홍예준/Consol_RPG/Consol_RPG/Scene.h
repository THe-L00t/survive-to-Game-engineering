#pragma once
class Scene
{
public:
	virtual ~Scene() = default; // 가상 소멸자

	//순수 가상 함수 선언
	virtual void Init() = 0;					// 씬 진입시 1회 실행
	virtual void Update(float deltaTime) = 0;	// 매 프레임 로직 처리(이동, 입력)
	virtual void Render() = 0;					// 매 프레임 화면 출력
	virtual void Release() = 0;					// 씬 빠저나갈때 메모리 정리
};



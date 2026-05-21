#pragma once

class UIManager
{
public:
	//플레이어 스텟 출력
	static void PrintPlayerStatus();

	// 프린트 화면 출력
	// text : 출력할 문장, delay : 글자당 타이핑 속도(밀리초, 기본값 30)
	static void PrintTyping(const std::string& text, int delay);
};


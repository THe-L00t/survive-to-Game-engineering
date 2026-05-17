#include "UIManager.h"

void UIManager::PrintPlayerStatus() {
	std::cout << std::endl << "============플레이어 스텟============" << std::endl;
	std::cout << "         직업 : " << Player::Instance->job << std::endl;
	std::cout << "         레벨 : " << Player::Instance->level << std::endl;
	std::cout << "         체력 : " << Player::Instance->currentHp << " / " << Player::Instance->maxHp << std::endl;
	std::cout << "         마나 : " << Player::Instance->currentMp << " / " << Player::Instance->maxMp << std::endl;
	std::cout << "  필요 경험치 : " << Player::Instance->currentExp << " / " << Player::Instance->maxExp << std::endl;
	std::cout << "=====================================" << std::endl;
}

void UIManager::PrintTyping(const std::string& text, int delay = 30) {
	for (size_t i = 0; i < text.length();) {
		int charLen = 1;	//영어, 숫자, 공백은 1바이트
		unsigned char c = text[i];

		// UTF-8 가변 길이 변독기
		if ((c & 0xF8) == 0xF) charLen = 4;
		else if ((c & 0xF0) == 0xE0) charLen = 3; //한국어 길이 판독
		else if ((c & 0xE0) == 0xC0) charLen = 2;

		// 글자 길이만큼 문자열을 잘라서 출력
		std::cout << text.substr(i, charLen);

		// std::flush : 출력 버퍼에 안쌓아두고 화면에 출력
		std::cout << std::flush;

		i += charLen;	//출력 바이트 수만큼 다음 위치로 이동

		// 공백일땐 그냥 바로 안쉬고 바로 넘어가기
		if (c != ' ') {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}
	std::cout << std::endl;
}
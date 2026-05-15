#include "UIManager.h"

void UIManager::PrintPlayerStatus() {
	std::cout << "============플레이어 스텟============" << std::endl;
	std::cout << "         직업 : " << Player::Instance->job << std::endl;
	std::cout << "         레벨 : " << Player::Instance->level << std::endl;
	std::cout << "         체력 : " << Player::Instance->currentHp << " / " << Player::Instance->maxHp << std::endl;
	std::cout << "         마나 : " << Player::Instance->currentMp << " / " << Player::Instance->maxMp << std::endl;
	std::cout << "  필요 경험치 : " << Player::Instance->currentExp << " / " << Player::Instance->maxExp << std::endl;
	std::cout << "=====================================" << std::endl;
}
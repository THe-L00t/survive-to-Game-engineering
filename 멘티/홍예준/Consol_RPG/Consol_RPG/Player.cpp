#include "pch.h"
#include "Player.h"

Player* Player::Instance = nullptr;

void Player::GainExp(int exp) {
	currentExp += exp;
	while (currentExp >= maxExp) {
		currentExp -= maxExp;
		level++;
		
		//레벨업 시 성장 스텟
		maxHp += 10;
		if (currentHp == maxHp) currentHp = maxHp;
		else {
			currentHp += 5;
			if (currentHp > maxHp) currentHp = maxHp;
		}
		atk += 2;
		def += 1;
		speed += 0.1f;
		maxExp = (int)(maxExp * 1.2f);	//다음 레벨업 시 필요한 경험치 증가

		std::cout << "레벨이 올랐습니다. 현재 레벨 : " << level << std::endl;;
	}
}

void Player::TakeDamage(float damage) {
	float actualDamage = damage - def;
	if (actualDamage < 1.0f) actualDamage = 1.0f;

	currentHp -= (int)actualDamage;

	if (currentHp <= 0) {
		currentHp = 0;
		std::cout << "플레이어가 쓰러졌습니다." << std::endl << "신의 힘으로 가까운 마을로 이동했습니다." << std::endl;
	}
}

void Player::Heal(int amount) {
	//아이템 코드에 따라 획득하는 회복량 amount에 넣기
	//회복 후 스킬이냐 아이템이냐에 따라서 스킬이면 mp빼기, 아이템이면 아이템 삭제
	//회복이 maxHp를 초과햇을 경우 maxHp까지만 회복
	currentHp += amount;

	if (currentHp > maxHp) {
		currentHp = maxHp;
	}
}

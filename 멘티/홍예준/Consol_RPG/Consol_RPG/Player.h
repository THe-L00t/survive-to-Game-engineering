#pragma once
#include "pch.h"

//장비 구조체
struct Equipment {
	std::string head;
	std::string top;
	std::string bottom;
	std::string gloves;
	std::string shoes;
};

class Player
{
public:
	static Player* Instance;
public:
	Player() { if (Instance == nullptr) Instance = this; }
	
	//플레이어 기본 정보
	std::string job = "전사";
	int level = 1;
	int gold = 100;
	int currentExp = 0;
	int maxExp = 100;

	//전투 스탯
	int maxHp = 100;
	int currentHp = 100;
	int maxMp = 100;
	int currentMp = 100;
	float atk = 10.0f;
	float def = 5.0f;
	float speed = 10.0f;

	//장비 시스템
	Equipment equipped;
	int inventoryCount = 0;

	//행동 함수
	void GainExp(int exp);			// 경험치 및 레벨업 로직
	void TakeDamage(float damage);	// 피해 로직
	void Heal(int amount);			// 체력 회복 로직
	void SpendMp(int amount);		// 스킬 사용시 소모 MP 로직
};


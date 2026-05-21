#pragma once
class Enemy
{
public:
	static Enemy* Instance;
public:
	Enemy() { if (Instance == nullptr) Instance = this; }

	//몬스터 기본 정보
	int level;
	int gold;

	//전투 스탯
	int maxHp;
	int currentHp;
	int maxMp;
	int currentMp;
	float atk;
	float def;
	float speed;

	//행동 로직
	void TakeDamage(float damage);	// 피해 로직
	void Heal(int amount);			// 체력 회복 로직
	void SpendMp(int amount);		// 스킬 사용시 소모 MP 로직

	void EnemyId()
};


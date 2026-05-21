#pragma once
#include "TimeManager.h"
#include <memory>

class Framework
{
public :
	Framework();
	~Framework();

	void Init();
	void Loop();
	void Destroy();
private:
	std::unique_ptr<TimeManager> timer;
	float startTime;

	
};


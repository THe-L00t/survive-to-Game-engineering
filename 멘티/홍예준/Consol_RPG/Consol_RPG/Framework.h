#pragma once
#include <memory>
#include "pch.h";
#include "TimeManager.h"

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


#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Release() override;
};
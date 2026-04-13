#pragma once
#include "GameManager.hpp"
#include "World.hpp"

class DinoRunGame : public GameManager
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnLateUpdate() override;
    void OnShutdown() override;

private:
    std::shared_ptr<Texture> spriteSheet;
    std::shared_ptr<GameObject> world;
};
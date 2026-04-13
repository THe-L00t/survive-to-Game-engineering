#pragma once
#include "Components/Render/SpriteRenderer.hpp"

class World : public Component
{
public:
    std::shared_ptr<Texture> atlas;

    float scrollSpeed = 5.0f;
    float groundWidth = 20.0f; // 바닥 하나의 가로 길이 (유닛 단위)

    World(std::shared_ptr<Texture> atlas) : atlas(atlas) {}

    void Awake() override;
    void Update() override;

private:
    std::vector<std::shared_ptr<GameObject>> grounds;

    float obstacleTimer = 0.0f;
    float spawnInterval = 2.0f;

    void SpawnObstacle();
    void ScrollGrounds();
};
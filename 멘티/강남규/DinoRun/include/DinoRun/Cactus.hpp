#pragma once
#include "Components/Render/SpriteRenderer.hpp"
#include "Components/Collider/BoxCollider2D.hpp"
#include "DinoRun/World.hpp"

class Cactus : public Component
{
public:
    std::shared_ptr<SpriteRenderer> renderer;
    std::shared_ptr<BoxCollider2D> collider;

    Cactus(std::shared_ptr<World> world) : world(world) {}

    void Awake() override;
    void Update() override;

private:
    std::shared_ptr<World> world;
};
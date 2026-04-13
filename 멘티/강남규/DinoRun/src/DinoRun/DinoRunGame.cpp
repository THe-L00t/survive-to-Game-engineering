#include "DinoRun/DinoRunGame.hpp"
#include "Components/Render/Camera.hpp"

void DinoRunGame::OnInit()
{
    spriteSheet = std::make_shared<Texture>("assets/dino_atlas.png", "assets/dino_atlas.json");

    // Camera 생성
    auto camObj = Instantiate<GameObject>("MainCamera");
    auto cam = camObj->AddComponent<Camera>(true);
    cam->size = 5.0f;

    world = Instantiate<GameObject>("World");
    world->AddComponent<World>(true, spriteSheet);
}

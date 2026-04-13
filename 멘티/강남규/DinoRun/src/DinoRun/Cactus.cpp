#include <algorithm>
#include "DinoRun/Cactus.hpp"
#include "GameManager.hpp"
#include "Time.hpp"

void Cactus::Awake() {
    
    renderer = AddComponent<SpriteRenderer>(true, world->atlas, "cactus_0", (int)Renderer::RenderLayer::StaticMob);
    collider = AddComponent<BoxCollider2D>(true);
    
    gameObject->transform->localPosition = glm::vec3(15.0f, -3.8f, 0.0f); // 화면 오른쪽 밖에서 생성
    float ratio = world->atlas->GetAspectRatio("cactus_0");
    gameObject->transform->localScale = glm::vec3(1.0f, 1.0f / ratio, 1.0f);
}

void Cactus::Update() {
    // 1. 왼쪽으로 이동 (World와 동기화)
    gameObject->transform->localPosition.x -= world->scrollSpeed * Time::GetDeltaTimeF();

    // 2. 화면 밖으로 완전히 나갔는지 체크
    if (gameObject->transform->localPosition.x < -15.0f) {
        Destroy(gameObject);
    }
}

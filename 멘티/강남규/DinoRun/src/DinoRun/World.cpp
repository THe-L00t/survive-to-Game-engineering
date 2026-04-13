#include "DinoRun/World.hpp"
#include "DinoRun/DinoRunGame.hpp"
#include "DinoRun/Cactus.hpp"
#include "Time.hpp"

void World::Awake()
{
    // 바닥(Ground) 세 개를 생성하여 무한 루프 배경 만들기
    for (int i = 0; i < 2; i++)
    {
        auto tag = "Ground_" + std::to_string(i);
        auto ground = Instantiate<GameObject>(tag, gameObject->transform);

        // SpriteRenderer 부착
        auto renderer = ground->AddComponent<SpriteRenderer>(true, atlas, tag, (int)Renderer::RenderLayer::Background);

        // 위치 설정
        ground->transform->localPosition = glm::vec3(i * groundWidth, -4.0f, 0.0f);
        float ratio = atlas->GetAspectRatio(tag);
        ground->transform->localScale = glm::vec3(groundWidth, groundWidth / ratio, 1.0f);

        grounds.push_back(ground);
    }
}

void World::Update()
{
    ScrollGrounds();

    // 장애물 스폰 타이머
    obstacleTimer += Time::GetDeltaTimeF();
    if (obstacleTimer >= spawnInterval)
    {
        SpawnObstacle();
        obstacleTimer = 0.0f;
        spawnInterval = 1.5f + (rand() % 100 * 0.01f);
    }

    scrollSpeed += Time::GetDeltaTimeF() * 0.1f;
}

void World::ScrollGrounds()
{
    for (auto &ground : grounds)
    {
        // 왼쪽으로 이동
        ground->transform->localPosition.x -= scrollSpeed * Time::GetDeltaTimeF();

        // 화면 왼쪽 끝으로 나가면 오른쪽 끝으로 재배치 (무한 루프)
        if (ground->transform->localPosition.x <= -groundWidth)
        {
            ground->transform->localPosition.x += groundWidth * 2.0f;
        }
    }
}

void World::SpawnObstacle()
{
    auto cactus = Instantiate<GameObject>("Cactus", gameObject->transform);
}
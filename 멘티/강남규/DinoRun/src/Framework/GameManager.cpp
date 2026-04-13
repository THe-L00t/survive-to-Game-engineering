#include "GameManager.hpp"
#include "Input.hpp"
#include "Time.hpp"

void GameManager::Init(int width, int height, const std::string &title)
{
    window = Renderer::CreateWindow(width, height, title.c_str());
    if (!window)
        throw std::runtime_error("Failed to initialize window");

    // 기본 셰이더 설정
    auto baseShader = std::make_shared<Shader>("shaders/base_shader.vs", "shaders/base_shader.fs");
    Renderer::SetMainShader(baseShader);

    Input::Init();
    Time::Init();
    OnInit();
}

void GameManager::Update()
{
    Time::Update();

    glfwPollEvents();
    Input::OnPreInput(window);

    if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (!pendingComponents.empty())
    {
        // 이번 프레임에 시작할 객체들을 복사 (루프 중 추가 방지)
        auto spawning = std::move(pendingComponents);
        pendingComponents.clear();

        for (auto &obj : spawning)
        {
            if (!obj->gameObject->isActive || !obj->isActive)
            {
                pendingComponents.push_back(obj); // 다음 프레임으로 대기
                continue;
            }

            if (obj->isAwaked && !obj->isStarted)
            {
                obj->Start();
            }

            activeComponents.push_back(obj); // 활성화 큐에 등록
        }
    }

    for (auto &obj : activeComponents)
    {
        obj->Update();
    }

    OnUpdate();
}

void GameManager::LateUpdate()
{
    for (auto &obj : activeComponents)
    {
        obj->LateUpdate();
    }

    OnLateUpdate();
}

void GameManager::Render()
{
    glfwMakeContextCurrent(window);

    // 크롬 디노 스타일의 배경색
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer::RenderAll(window);

    glfwSwapBuffers(window);
}

void GameManager::EndOfFrame()
{
    // 삭제 대기열 처리
    if (!destroyQueue.empty())
    {
        std::vector<std::shared_ptr<GameObject>> toDestroy = std::move(destroyQueue);
        destroyQueue.clear();

        for (auto &obj : toDestroy)
        {
            obj->isDestroyed = true;
            obj->Destroy();
        }

        std::erase_if(pendingComponents, [](const std::shared_ptr<Component> &obj)
                      { return obj->gameObject->isDestroyed; });
        std::erase_if(activeComponents, [](const std::shared_ptr<Component> &obj)
                      { return obj->gameObject->isDestroyed; });
        std::erase_if(sceneObjects, [](const std::shared_ptr<GameObject> &obj)
                      { return obj->isDestroyed; });
    }
}

bool GameManager::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void GameManager::Shutdown()
{
    OnShutdown();
    glfwTerminate();
}

#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Components/Render/Renderer.hpp"
#include "GameObject.hpp"

class GameManager
{
private:
    std::vector<std::shared_ptr<GameObject>> destroyQueue;     // 삭제 대기열 (다음 프레임에 정리)
    std::vector<std::shared_ptr<Component>> pendingComponents; // 생성 대기열 (다음 프레임에 활성화)
    std::vector<std::shared_ptr<Component>> activeComponents;  // 활성화 큐 (업데이트 및 렌더링 대상)
public:
    std::vector<std::shared_ptr<GameObject>> sceneObjects; // 모든 게임 오브젝트 관리

    void Init(int width, int height, const std::string &title);
    void Update();
    void LateUpdate();
    void Render();
    void EndOfFrame();

    bool ShouldClose();
    void Shutdown();

    void Register(std::shared_ptr<Component> com)
    {
        pendingComponents.push_back(com);
    }

    void Deactive(std::shared_ptr<Component> com)
    {
        if (!com)
            return;

        std::erase(activeComponents, com);
        if (std::find(pendingComponents.begin(), pendingComponents.end(), com) == pendingComponents.end())
            pendingComponents.push_back(com);
    }

    // 오브젝트 생성
    template <typename T>
    std::shared_ptr<T> Instantiate(std::string name = "New GameObject", std::shared_ptr<Transform> parent = nullptr, bool active = true)
    {
        static_assert(std::is_base_of_v<GameObject, T>, "T must derive from GameObject.");

        auto instance = std::make_shared<T>(this, name);
        instance->Init(parent); // 생성 직후 초기화
        instance->SetActive(active);
        sceneObjects.push_back(instance); // 관리 리스트에 추가

        return instance;
    }

    // 오브젝트 삭제 (다음 프레임에 정리)
    void Destroy(std::shared_ptr<GameObject> obj)
    {
        if (!obj)
            return;

        // 이미 삭제 대기열에 있다면 중복 추가 방지
        if (std::find(destroyQueue.begin(), destroyQueue.end(), obj) == destroyQueue.end())
        {
            destroyQueue.push_back(obj);
        }
    }

    GLFWwindow *GetWindow() { return window; }

protected:
    GLFWwindow *window = nullptr;

    virtual void OnInit() {};
    virtual void OnUpdate() {};
    virtual void OnLateUpdate() {}
    virtual void OnShutdown() {}
};
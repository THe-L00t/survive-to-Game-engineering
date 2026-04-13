#pragma once
#include <vector>
#include <memory>
#include <string>
#include <typeindex>
#include <ranges>
#include <unordered_map>
#include "Components/Transform/Transform.hpp"
#include "Components/Component.hpp"

#define LOCK_OR_RETURN(ptr, name) \
    auto name = ptr.lock();       \
    if (!name)                    \
        return;

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
    std::vector<std::shared_ptr<Component>> components;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> componentTypeMap;

public:
    bool isActive = true;
    bool isDestroyed = false;

    GameManager *manager;
    std::string name;
    std::shared_ptr<GameObject> gameObject;
    std::shared_ptr<Transform> transform; // 모든 객체는 Transform을 기본으로 가짐

    GameObject(GameManager *m, std::string n = "New GameObject") : manager(m), name(n) {}

    void SetActive(bool active)
    {
        isActive = active;
        for (auto &com : components)
        {
            com->SetActive(com->isActive);
        }
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> AddComponent(bool active, Args &&...args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component.");

        // 이미 해당 타입의 컴포넌트가 있다면 기존 것 반환
        auto it = componentTypeMap.find(typeid(T));
        if (it != componentTypeMap.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->gameObject = shared_from_this();

        component->SetActive(active);

        components.push_back(component);
        componentTypeMap[typeid(T)] = component;
        manager->Register(component);

        return component;
    }

    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        auto it = componentTypeMap.find(typeid(T));
        if (it != componentTypeMap.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template <typename T>
    bool HasComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        return componentTypeMap.find(typeid(T)) != componentTypeMap.end();
    }

    void Init(std::shared_ptr<Transform> parent = nullptr)
    {
        gameObject = shared_from_this();
        transform = AddComponent<Transform>(true); // 모든 객체는 Transform을 기본으로 가짐
        transform->SetParent(parent);
    }

    void Destroy()
    {
        componentTypeMap.clear();
        for (auto &comp : std::views::reverse(components))
        {
            comp->OnDestroy();
            comp->gameObject.reset();
        }
        components.clear();
        transform.reset();
        gameObject.reset();
    }
};
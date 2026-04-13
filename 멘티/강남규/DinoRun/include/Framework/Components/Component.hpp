#pragma once
#include <memory>
#include "GameObject.hpp"

class Component : public std::enable_shared_from_this<Component> {
public:
    bool isAwaked = false;
    bool isStarted = false;
    bool isActive = true;
    std::shared_ptr<GameObject> gameObject;
    virtual ~Component() {}
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void OnDestroy() {}

    template<typename T>
    T GetPtr(){
        return std::static_pointer_cast<T>(shared_from_this());
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> AddComponent(bool active, Args &&...args)
    {
        return gameObject->AddComponent<T>(active, std::forward<Args>(args)...);
    }

    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        return gameObject->GetComponent<T>();
    }
    
    template <typename T>
    bool HasComponent()
    {
        return gameObject->HasComponent<T>();
    }

    template <typename T>
    std::shared_ptr<T> Instantiate(std::string name = "New GameObject", std::shared_ptr<Transform> parent = nullptr, bool active = true)
    {
        return gameObject->manager->Instantiate<T>(name, parent, active);
    }

    void Destroy(std::shared_ptr<GameObject> obj)
    {
        gameObject->manager->Destroy(obj);
    }

    void SetActive(bool active){
        isActive = active;
        if(gameObject->isActive && isActive){
            if(!isAwaked){
                isAwaked = true;
                Awake();
            }
        }
        else{
            gameObject->manager->Deactive(shared_from_this());
        }
    }
};
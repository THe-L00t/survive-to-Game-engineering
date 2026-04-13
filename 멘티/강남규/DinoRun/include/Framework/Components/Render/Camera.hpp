#pragma once
#include "GameObject.hpp"
#include "Renderer.hpp" // Renderer::projectionMatrix 접근을 위해 필요
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Component
{
public:
    static inline Camera *main = nullptr;

    // size = 5.0f 일 때, 화면 세로는 -5.0 ~ 5.0 (총 10단위)
    float size = 5.0f;
    float nearPlane = -1.0f;
    float farPlane = 1.0f;

    void Awake() override
    {
        if (main == nullptr)
        {
            main = this;
        }
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::inverse(gameObject->transform->GetWorldModelMatrix());
    }

    glm::mat4 GetProjectionMatrix(float screenWidth, float screenHeight)
    {
        float aspect = screenWidth / screenHeight;

        // 가로 범위: -aspect * size ~ aspect * size
        // 세로 범위: -size ~ size
        return glm::ortho(-aspect * size, aspect * size, -size, size, nearPlane, farPlane);
    }
};
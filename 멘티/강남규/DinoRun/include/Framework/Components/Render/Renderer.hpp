#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include "Shader.hpp"
#include "Components/Component.hpp"

class Renderer : public Component
{
public:
    int order;
    enum class RenderLayer
    {
        Undefined = -1,
        Background = 0,
        StaticMob = 10,
        DynamicMob = 20,
        Effect = 30,
        UI = 999
    };

protected:
    // 기존 구조 유지
    inline static std::vector<std::weak_ptr<Renderer>> renderQueue;
    inline static bool isDirty = false;

    inline static std::shared_ptr<Shader> mainShader = nullptr;
    inline static glm::mat4 projectionMatrix = glm::mat4(1.0f);
    inline static glm::mat4 viewMatrix = glm::mat4(1.0f); // 뷰 행렬 추가

    // 자식 클래스(SpriteRenderer 등)에서 구현할 그리기 로직
    virtual void Draw() = 0;

public:
    Renderer(int renderOrder = (int)RenderLayer::Undefined) : order(renderOrder) { isDirty = true; }
    virtual ~Renderer() { isDirty = true; }

    void Awake() override;

    static GLFWwindow *CreateWindow(int width, int height, const char *title);
    static void SetMainShader(std::shared_ptr<Shader> shader);

    // 카메라에서 호출할 행렬 설정 함수들
    static void SetProjection(const glm::mat4 &proj);
    static void SetView(const glm::mat4 &view); // 새롭게 추가된 SetView

    static void SetDrawShader(std::shared_ptr<Shader> shader = nullptr);
    static void RenderAll(GLFWwindow *window);
    static std::vector<std::weak_ptr<Renderer>> &GetRenderQueue() { return renderQueue; }

    void SetOrder(int newOrder);
};
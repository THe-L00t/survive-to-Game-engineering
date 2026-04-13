#pragma once
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <glm/glm.hpp>
#include "Components/Render/Renderer.hpp"
#include "Components/Render/Camera.hpp"
#include "Components/Collider/Collider.hpp"
#include "GameObject.hpp"

class Input
{
private:
    struct KeyData
    {
        bool keyState = GLFW_RELEASE;
        bool prevKeyState = GLFW_RELEASE;
    };

    static inline std::map<int, KeyData> keyStates;

    static inline std::vector<int> usingKeys = {
        GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE,
        GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D,
        GLFW_KEY_Q, GLFW_KEY_E, GLFW_KEY_R, GLFW_KEY_F,
        GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN,
        GLFW_KEY_SPACE, GLFW_KEY_ENTER, GLFW_KEY_TAB,
        GLFW_KEY_LEFT_SHIFT, GLFW_KEY_RIGHT_SHIFT,
        GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_CONTROL,
        GLFW_KEY_LEFT_ALT, GLFW_KEY_RIGHT_ALT,
        GLFW_KEY_ESCAPE};

public:
    static void Init()
    {
        for (int key : usingKeys)
        {
            keyStates[key] = KeyData();
        }
    }

    static void OnPreInput(GLFWwindow *window)
    {
        for (auto key : usingKeys)
        {
            keyStates[key].prevKeyState = keyStates[key].keyState;
            // 마우스 버튼과 키보드 키 구분 (GLFW 상수 기준)
            keyStates[key].keyState = (key <= GLFW_MOUSE_BUTTON_LAST) ? glfwGetMouseButton(window, key) : glfwGetKey(window, key);
        }
    }

    static bool IsKeyDown(int button)
    {
        return keyStates[button].keyState == GLFW_PRESS && keyStates[button].prevKeyState == GLFW_RELEASE;
    }

    static bool IsKeyUp(int button)
    {
        return keyStates[button].keyState == GLFW_RELEASE && keyStates[button].prevKeyState == GLFW_PRESS;
    }

    static bool IsKey(int button)
    {
        return keyStates[button].keyState == GLFW_PRESS;
    }

    // 마우스의 스크린 좌표를 실제 게임 월드 좌표로 변환
    static glm::vec2 GetMouseWorldPos(GLFWwindow *window)
    {
        if (!Camera::main)
            return glm::vec2(0.0f);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);

        // 1. Screen Space -> NDC (-1.0 ~ 1.0)
        float nx = (2.0f * (float)xpos) / (float)w - 1.0f;
        float ny = 1.0f - (2.0f * (float)ypos) / (float)h;

        // 2. NDC -> World Space (Projection 및 View 역행렬 이용)
        glm::mat4 invProj = glm::inverse(Camera::main->GetProjectionMatrix((float)w, (float)h));
        glm::mat4 invView = glm::inverse(Camera::main->GetViewMatrix());

        glm::vec4 worldPos = invView * invProj * glm::vec4(nx, ny, 0.0f, 1.0f);

        return glm::vec2(worldPos.x, worldPos.y);
    }

    // 마우스가 클릭한 GameObject 반환
    static std::shared_ptr<GameObject> GetMousePick(GLFWwindow *window)
    {
        auto mousePos = GetMouseWorldPos(window);

        // RenderQueue를 역순(가장 앞에 그려진 것부터)으로 순회
        auto &queue = Renderer::GetRenderQueue();
        for (auto it = queue.rbegin(); it != queue.rend(); ++it)
        {
            if (auto ren = it->lock())
            {
                auto col = ren->gameObject->GetComponent<Collider>();
                if (col && col->IsPointInside(mousePos.x, mousePos.y))
                {
                    return ren->gameObject;
                }
            }
        }
        return nullptr;
    }
};
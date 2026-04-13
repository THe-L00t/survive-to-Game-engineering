#include "Components/Render/Renderer.hpp"
#include "Components/Render/Camera.hpp"

GLFWwindow *Renderer::CreateWindow(int width, int height, const char *title)
{
    static bool isGLFWLoaded = false;
    if (!isGLFWLoaded) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        isGLFWLoaded = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    static bool isGladLoaded = false;
    if (!isGladLoaded) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        isGladLoaded = true;
    }

    // 기본 뷰포트 및 알파 블렌딩 설정
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 창 크기 조절 콜백
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h)
                                   { glViewport(0, 0, w, h); });

    return window;
}

void Renderer::SetMainShader(std::shared_ptr<Shader> shader)
{
    mainShader = shader;
}

void Renderer::SetProjection(const glm::mat4 &proj)
{
    projectionMatrix = proj;
}

// 카메라 시스템에서 호출할 View 행렬 설정 함수
void Renderer::SetView(const glm::mat4 &view)
{
    viewMatrix = view;
}

void Renderer::SetDrawShader(std::shared_ptr<Shader> shader)
{
    std::shared_ptr<Shader> target = shader ? shader : mainShader;
    
    if (target)
    {
        target->use();
        target->setMat4("projection", projectionMatrix);
        target->setMat4("view", viewMatrix); // View 행렬 추가 전달
    }
}

void Renderer::Awake()
{
    renderQueue.push_back(std::static_pointer_cast<Renderer>(shared_from_this()));
}

void Renderer::SetOrder(int newOrder)
{
    if (order != newOrder)
    {
        order = newOrder;
        isDirty = true;
    }
}

void Renderer::RenderAll(GLFWwindow *window)
{
    if (!Camera::main)
        return;

    if (renderQueue.empty() || !mainShader)
        return;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);    
    SetProjection(Camera::main->GetProjectionMatrix((float)width, (float)height));
    SetView(Camera::main->GetViewMatrix());
    SetDrawShader();

    if (isDirty)
    {
        std::erase_if(renderQueue, [](std::weak_ptr<Renderer> w) { return w.expired(); });

        std::sort(renderQueue.begin(), renderQueue.end(),
                  [](std::weak_ptr<Renderer> a, std::weak_ptr<Renderer> b) {
                      auto sa = a.lock();
                      auto sb = b.lock();
                      if (sa && sb) return sa->order < sb->order;
                      return false;
                  });
        isDirty = false;
    }

    for (auto &wp : renderQueue)
    {
        if (auto obj = wp.lock())
        {
            obj->Draw();
        }
    }
}
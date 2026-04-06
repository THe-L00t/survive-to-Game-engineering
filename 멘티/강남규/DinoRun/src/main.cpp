#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 화면 설정
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// 콜백 함수 선언
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
    // 1. GLFW 초기화 및 설정
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. 창 생성 (Window Object)
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dino Run Clone", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. GLAD 초기화 (OpenGL 함수 포인터 로드)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // --- 여기에 Renderer, Dino 객체 등의 초기화 로직이 들어갑니다 ---

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // 4. 게임 루프 (Main Loop)
    while (!glfwWindowShouldClose(window)) {
        // Delta Time 계산
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 입력 처리
        processInput(window);

        // 렌더링 준비 (배경색 설정)
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f); // 크롬 디노 특유의 밝은 회색
        glClear(GL_COLOR_BUFFER_BIT);

        // --- 여기서 Update & Render 호출 ---
        // 예: dino.Update(deltaTime);
        // 예: renderer.Draw(dino);

        // 버퍼 교체 및 이벤트 확인
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 자원 해제
    glfwTerminate();
    return 0;
}

// 입력 처리 함수
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // 점프 입력 (Space)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // TODO: dino.Jump();
    }
}

// 창 크기 변경 대응
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
#pragma once
#include "Renderer.hpp"
#include "Texture.hpp"
#include <string>

class SpriteRenderer : public Renderer
{
public:
    std::shared_ptr<Texture> texture;
    std::string spriteName;
    glm::vec4 color = glm::vec4(1.0f); // 틴트 컬러 (RGBA)

    // 생성자: 텍스처와 스프라이트 이름을 받아 초기화
    SpriteRenderer(std::shared_ptr<Texture> tex, std::string name = "", int renderOrder = (int)RenderLayer::Undefined)
        : Renderer(renderOrder), texture(tex), spriteName(name) {}

    // Renderer의 순수 가상 함수 구현
    void Draw() override
    {
        if (!texture)
            return;

        // 1. 해당 스프라이트의 UV 좌표 가져오기
        UVRect uv = {0.0f, 0.0f, 1.0f, 1.0f}; // 기본값은 전체 텍스처
        if (!spriteName.empty())
        {
            uv = texture->GetUV(spriteName);
        }

        // 2. 셰이더 설정 및 월드 행렬 전달
        // RenderAll에서 이미 SetDrawShader가 호출되어 Projection/View는 세팅된 상태
        mainShader->setMat4("model", gameObject->transform->GetWorldModelMatrix());
        mainShader->setVec4("spriteColor", color);

        // 3. 텍스처 바인딩
        texture->Bind();

        // 4. 사각형 그리기
        RenderQuad(uv);
    }

    void OnDestroy() override
    {
        if (texture)
            texture.reset();
    }

private:
    void RenderQuad(const UVRect &uv)
    {
        static unsigned int quadVAO = 0;
        static unsigned int quadVBO;

        // 1x1 크기의 중심이 (0,0)인 사각형 정점 데이터
        // 위치(x, y)          // UV(u, v)
        float vertices[] = {
            -0.5f, 0.5f, uv.u, uv.vh,
            -0.5f, -0.5f, uv.u, uv.v,
            0.5f, -0.5f, uv.uw, uv.v,

            -0.5f, 0.5f, uv.u, uv.vh,
            0.5f, -0.5f, uv.uw, uv.v,
            0.5f, 0.5f, uv.uw, uv.vh};

        if (quadVAO == 0)
        {
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
        }
        else
        {
            // UV가 매 프레임 바뀔 수 있으므로(애니메이션) BufferSubData로 업데이트
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        }

        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};
#pragma once
#include "Collider.hpp"

class BoxCollider2D : public Collider
{
protected:
    float offsetX, offsetY; // 오브젝트 중심으로부터의 오프셋
    float width, height;    // 충돌체 본연의 크기

public:
    BoxCollider2D(float fx = 0, float fy = 0, float w = 1, float h = 1)
        : offsetX(fx), offsetY(fy), width(w), height(h) {}

    // 현재 transform의 위치와 스케일을 고려한 최종 영역 계산
    void GetBounds(float &minX, float &minY, float &maxX, float &maxY) const
    {
        // Transform의 월드 포지션 가져오기
        glm::vec3 worldPos = gameObject->transform->GetWorldPosition();
        glm::vec3 worldScale = gameObject->transform->GetWorldScale();

        // 스케일까지 고려하여 충돌 영역 계산
        float scaledHalfW = (width * worldScale.x) / 2.0f;
        float scaledHalfH = (height * worldScale.y) / 2.0f;

        minX = worldPos.x + (offsetX * worldScale.x) - scaledHalfW;
        minY = worldPos.y + (offsetY * worldScale.y) - scaledHalfH;
        maxX = minX + (width * worldScale.x);
        maxY = minY + (height * worldScale.y);
    }

    // 마우스 픽킹 및 점 충돌 확인
    bool IsPointInside(float RayX, float RayY) const override
    {
        float minX, minY, maxX, maxY;
        GetBounds(minX, minY, maxX, maxY);

        return (RayX >= minX && RayX <= maxX && RayY >= minY && RayY <= maxY);
    }

    // 다른 BoxCollider2D와의 AABB 충돌 확인
    bool IsCollidingWith(const BoxCollider2D &other) const
    {
        float minX1, minY1, maxX1, maxY1;
        this->GetBounds(minX1, minY1, maxX1, maxY1);

        float minX2, minY2, maxX2, maxY2;
        other.GetBounds(minX2, minY2, maxX2, maxY2);

        return (minX1 < maxX2 && maxX1 > minX2 &&
                minY1 < maxY2 && maxY1 > minY2);
    }

    // Getter / Setter
    void SetOffset(float x, float y)
    {
        offsetX = x;
        offsetY = y;
    }
    void SetSize(float w, float h)
    {
        width = w;
        height = h;
    }
};
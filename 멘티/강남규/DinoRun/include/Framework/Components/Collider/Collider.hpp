#pragma once
#include "GameObject.hpp"

class Collider : public Component
{
public:
    virtual ~Collider() {}

    // 충돌체의 바운딩 박스 정보를 가져오는 순수 가상 함수
    virtual bool IsPointInside(float x, float y) const = 0;
    
    // 다른 Collider와의 충돌 여부를 확인 (기본적인 인터페이스)
    // 필요에 따라 Circle vs Box 등을 위해 여러 오버로딩을 둘 수 있습니다.
};
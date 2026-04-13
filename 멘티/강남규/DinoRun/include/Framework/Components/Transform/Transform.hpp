#pragma once
#include <glm/gtx/matrix_decompose.hpp>
#include <vector>
#include <memory>
#include "Components/Component.hpp"
#include "Quaternion.hpp"

class Transform : public Component
{
public:
    // 상대적 변환 (Local)
    glm::vec3 localPosition = glm::vec3(0.0f);
    Quaternion localRotation;
    glm::vec3 localScale = glm::vec3(1.0f);

    // 계층 구조를 위한 포인터
    std::weak_ptr<Transform> parent;
    std::vector<std::weak_ptr<Transform>> children;

    glm::mat4 GetLocalModelMatrix() const
    {
        glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), localPosition);
        glm::mat4 rotationMat = glm::mat4_cast(localRotation.value);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), localScale);

        return translationMat * rotationMat * scaleMat;
    }

    glm::mat4 GetWorldModelMatrix() const
    {
        if (auto p = parent.lock())
        {
            // 부모의 월드 행렬 * 나의 로컬 행렬
            return p->GetWorldModelMatrix() * GetLocalModelMatrix();
        }
        return GetLocalModelMatrix();
    }

    glm::vec3 GetWorldPosition() const
    {
        return glm::vec3(GetWorldModelMatrix()[3]);
    }

    Quaternion GetWorldRotation() const
    {
        if (auto p = parent.lock())
        {
            // 쿼터니언 곱셈 순서: 부모(Parent) * 자식(Local)
            // .value를 통해 내부 glm::quat에 접근하여 연산합니다.
            return Quaternion(p->GetWorldRotation().value * localRotation.value);
        }
        return localRotation;
    }

    glm::vec3 GetWorldScale() const
    {
        if (auto p = parent.lock())
        {
            return p->GetWorldScale() * localScale;
        }
        return localScale;
    }

    void SetParent(std::shared_ptr<Transform> newParent)
    {
        if (!newParent || parent.lock() == newParent)
            return;

        auto self = std::static_pointer_cast<Transform>(shared_from_this());

        if (auto p = parent.lock())
            std::erase(p->children, self);

        auto tmpMatrix = GetWorldModelMatrix();
        tmpMatrix = glm::inverse(newParent->GetWorldModelMatrix()) * tmpMatrix;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(tmpMatrix, localScale, localRotation.value, localPosition, skew, perspective);
        localRotation = glm::conjugate(localRotation.value);
        parent = newParent;
        newParent->children.push_back(self);
    }

#ifdef DEBUG
    void _debug_print_hierarchy(int depth = 0, bool last = true, std::string prefix = "")
    {
        std::cout << prefix << (depth ? (last ? "└─ " : "├─ ") : "") << gameObject->name << "\n";

        for (size_t i = 0; i < children.size(); i++)
        {
            bool isLast = (i == children.size() - 1);
            auto pf = prefix + (depth ? (last ? "   " : "│  ") : "");
            children[i].lock()->_debug_print_hierarchy(depth + 1, isLast, pf);
        }
    }
#endif
};
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Quaternion
{
    glm::quat value;

    // 생성자: 기본값은 Identity (회전 없음)
    Quaternion() : value(glm::identity<glm::quat>()) {}
    Quaternion(const glm::quat &q) : value(q) {}

    // 1. 암시적 형변환: glm::quat이 필요한 곳에 바로 사용 가능
    operator glm::quat() { return value; }
    operator glm::quat() const { return value; }
    operator glm::quat &() { return value; }
    operator const glm::quat &() const { return value; }

    // 2. 오일러 각도 설정 (입력은 Degree 단위가 직관적이므로 변환 포함)
    void SetEuler(float x, float y, float z)
    {
        value = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
    }

    void SetEuler(const glm::vec3 &eulerDegrees)
    {
        SetEuler(eulerDegrees.x, eulerDegrees.y, eulerDegrees.z);
    }

    // 3. 오일러 각도 가져오기 (반환은 Degree 단위)
    glm::vec3 GetEuler() const
    {
        glm::vec3 eulerRadians = glm::eulerAngles(value);
        return glm::vec3(glm::degrees(eulerRadians.x),
                         glm::degrees(eulerRadians.y),
                         glm::degrees(eulerRadians.z));
    }

    // 4. 화살표(->) 연산자 지원을 위해 자기 자신을 가리키는 포인터 반환은 불가능하지만,
    // 필요 시 glm::quat의 멤버 함수에 접근하기 위한 오버로딩
    glm::quat *operator->() { return &value; }
    const glm::quat *operator->() const { return &value; }
    glm::quat* operator&() { return &value; }
    const glm::quat* operator&() const { return &value; }
};
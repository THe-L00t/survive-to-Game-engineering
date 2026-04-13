#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;      // 카메라의 변환 행렬
uniform mat4 model;     // 기물의 위치, 회전, 크기 행렬

void main() {
    // 좌표 변환: Local -> World -> View -> Clip
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
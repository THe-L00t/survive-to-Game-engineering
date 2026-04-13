#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 spriteColor;

void main() {
    // 텍스처 컬러와 틴트 컬러를 곱함
    vec4 texColor = texture(texture1, TexCoord);
    
    // 알파 테스팅 (완전 투명한 픽셀은 버림 - 성능 및 외곽선 깔끔함 유지)
    if(texColor.a < 0.01)
        discard;

    FragColor = texColor * spriteColor;
}
#version 430
layout(location = 0) out vec4 FragColor;

uniform vec4 color;

void main() {
    FragColor = vec4(color.r, color.g, color.b, color.w);
}

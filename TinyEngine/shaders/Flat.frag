#version 120

uniform vec4 color;

void main() {
    gl_FragColor = vec4(color.r, color.g, color.b, color.w);
}

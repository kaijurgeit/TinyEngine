#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}


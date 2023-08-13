#include "Program.h"

#include <iostream>

#include "Shader.h"
#include "glad/glad.h"
#include <glm/glm.hpp>

namespace TE
{
    Program::Program(std::vector<Shader> shaders)
    : id(0), shaders(std::move(shaders))
{
}

unsigned Program::Create()
{
    id = glCreateProgram();
    for (Shader& shader : shaders)
    {
        shader.Compile();
        glAttachShader(id, shader.id);        
    }

    glLinkProgram(id);

    LogDeleteIfCompilationFails();
    
    for (const Shader& shader : shaders)
    {
        glDeleteShader(shader.id);
    }
    
    return id;
}

void Program::Use()
{
    glUseProgram(id);
}

void Program::SetUniform(const std::string& name, bool value) const
{
    SetUniform(name, static_cast<int>(value));
}

void Program::SetUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Program::SetUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Program::LogDeleteIfCompilationFails()
{
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = static_cast<char*>(alloca(length * sizeof(char)));
        glGetProgramInfoLog(id, length, &length, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(id);
        id = 0;
    }
}

void Program::SetUniform(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y); 
}

void Program::SetUniform(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
}

void Program::SetUniform(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w); 
}

void Program::SetUniform(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::SetUniform(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::SetUniform(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

}


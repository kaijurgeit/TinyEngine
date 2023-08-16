#include "Program.h"

#include <iostream>

#include "Shader.h"
#include "glad/glad.h"
#include <glm/glm.hpp>

namespace TE
{
    Program::Program(std::vector<Shader> shaders)
    : Id(0), Shaders(std::move(shaders))
{
}

unsigned Program::Create()
{
    Id = glCreateProgram();
    for (Shader& shader : Shaders)
    {
        shader.Compile();
        glAttachShader(Id, shader.Id);        
    }

    glLinkProgram(Id);

    LogDeleteIfCompilationFails();
    
    for (const Shader& shader : Shaders)
    {
        glDeleteShader(shader.Id);
    }
    
    return Id;
}

void Program::Use()
{
    glUseProgram(Id);
}

void Program::SetUniform(const std::string& name, bool value) const
{
    SetUniform(name, static_cast<int>(value));
}

void Program::SetUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Program::SetUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Program::LogDeleteIfCompilationFails()
{
    int success;
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if(!success)
    {
        int length;
        glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = static_cast<char*>(alloca(length * sizeof(char)));
        glGetProgramInfoLog(Id, length, &length, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(Id);
        Id = 0;
    }
}

void Program::SetUniform(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(Id, name.c_str()), x, y); 
}

void Program::SetUniform(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z); 
}

void Program::SetUniform(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Program::SetUniform(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(Id, name.c_str()), x, y, z, w); 
}

void Program::SetUniform(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::SetUniform(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::SetUniform(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

}


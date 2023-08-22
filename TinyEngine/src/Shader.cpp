#include "Shader.h"

#include <iostream>

#include "glad/glad.h"
#include <glm/glm.hpp>

namespace TE
{
    Shader::Shader(std::vector<ShaderElement> shaders)
    : Id(0), Shaders(std::move(shaders))
{
}

    Shader::~Shader()
    {
        glDeleteProgram(Id);
    }

    unsigned Shader::Create()
{
    Id = glCreateProgram();
    for (ShaderElement& shader : Shaders)
    {
        shader.Compile();
        glAttachShader(Id, shader.Id);        
    }

    glLinkProgram(Id);

    LogDeleteIfCompilationFails();
    
    for (const ShaderElement& shader : Shaders)
    {
        glDeleteShader(shader.Id);
    }
    
    return Id;
}

void Shader::Bind() const
{
    glUseProgram(Id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, bool value) const
{
    SetUniform(name, static_cast<int>(value));
}

void Shader::SetUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::LogDeleteIfCompilationFails()
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

void Shader::SetUniform(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Shader::SetUniform(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(Id, name.c_str()), x, y); 
}

void Shader::SetUniform(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Shader::SetUniform(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z); 
}

void Shader::SetUniform(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]); 
}
void Shader::SetUniform(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(Id, name.c_str()), x, y, z, w); 
}

void Shader::SetUniform(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniform(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniform(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

}


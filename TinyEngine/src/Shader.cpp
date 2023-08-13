#include "Shader.h"

#include <iostream>
#include <glad/glad.h>

#include "FileSystem.h"

namespace TE
{
    Shader::Shader(unsigned int type, const char* path)
    : type(type), source(TE::FileSystem::ReadFile(path))
    {
    }

    unsigned int Shader::Compile()
    {
        id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        LogDeleteIfCompilationFails();

        return id;
    }

    void Shader::LogDeleteIfCompilationFails()
    {
        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* infoLog = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(id);
            id = 0;
        }
    }
}


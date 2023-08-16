#include "Shader.h"

#include <iostream>
#include <glad/glad.h>

#include "FileSystem.h"

namespace TE
{
    Shader::Shader(unsigned int type, const char* path)
    : Type(type), Source(TE::FileSystem::ReadFile(path))
    {
    }

    unsigned int Shader::Compile()
    {
        Id = glCreateShader(Type);
        const char* src = Source.c_str();
        glShaderSource(Id, 1, &src, nullptr);
        glCompileShader(Id);

        LogDeleteIfCompilationFails();

        return Id;
    }

    void Shader::LogDeleteIfCompilationFails()
    {
        int success;
        glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            int length;
            glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &length);
            char* infoLog = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(Id, length, &length, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(Id);
            Id = 0;
        }
    }
}


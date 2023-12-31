﻿#pragma once
#include <string>
#include <vector>
#include <glm/fwd.hpp>

#include "Core.h"
#include "ShaderElement.h"

namespace TE
{
    class ShaderElement;

    class TE_API Shader
    {
    public:

        Shader(std::vector<ShaderElement> shaders);
        Shader(const Shader& other) = default;
        Shader(Shader&& other) noexcept = default;
        Shader& operator=(const Shader& other) = default;
        Shader& operator=(Shader&& other) noexcept = default;
        ~Shader();
        
        unsigned int Create();
        void Bind() const;
        void Unbind() const;
        void SetUniform(const std::string &name, bool value) const;
        void SetUniform(const std::string &name, int value) const;
        void SetUniform(const std::string &name, float value) const;
        void SetUniform(const std::string &name, const glm::vec2 &value) const;
        void SetUniform(const std::string &name, float x, float y) const; 
        void SetUniform(const std::string &name, const glm::vec3 &value) const;
        void SetUniform(const std::string &name, float x, float y, float z) const;
        void SetUniform(const std::string &name, const glm::vec4 &value) const;
        void SetUniform(const std::string &name, float x, float y, float z, float w) const;
        void SetUniform(const std::string &name, const glm::mat2 &mat) const;
        void SetUniform(const std::string &name, const glm::mat3 &mat) const;
        void SetUniform(const std::string &name, const glm::mat4 &mat) const;
        
#define SETUNIFORM(var) SetUniform(#var, var)
    
    private:
        bool created = false;
        unsigned int Id;
        std::vector<ShaderElement> Shaders;
        
        void LogDeleteIfCompilationFails();
    };
}



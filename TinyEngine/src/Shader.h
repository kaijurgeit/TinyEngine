﻿#pragma once
#include <string>
#include <vector>
#include <glm/fwd.hpp>

namespace TE
{
    class ShaderElement;

    class Shader
    {
    public:
        Shader(std::vector<ShaderElement> shaders);
        unsigned int Create();
        void Use();
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
    
    private:
        unsigned int Id;
        std::vector<ShaderElement> Shaders;
        
        void LogDeleteIfCompilationFails();
    };
}



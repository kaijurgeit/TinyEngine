#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Texture.h"

namespace TE
{    
    struct Vertex
    {
        glm::vec3 Position;    
        glm::vec3 Normal;    
        glm::vec2 TexCoords; 
        glm::vec3 Tangent;
        glm::vec3 Bitangent;   
    };

    class Shader;

    class Mesh
    {
    public:
        // mesh data
        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indices;
        std::vector<Texture>        textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
    
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void SetupMesh();
    };
    
}




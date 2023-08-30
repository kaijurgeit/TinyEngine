#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Material.h"


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
    class VertexArray;

    class Mesh
    {
    public:
        Mesh(VertexArray* vertexArray, Material* material, glm::mat4 model = glm::mat4(1.0));
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        static Mesh CreateCube(VertexArray* vao, Material* material, glm::vec3 position, float scale = 1.0);
        
        void Draw();
        void Draw(Shader &shader);
        
        // mesh data
        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indices;
        std::vector<Texture>        textures;
    
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void SetupMesh();

    private:
        VertexArray* vertexArray;
        Material* material;
        glm::mat4 model;
    };    
}




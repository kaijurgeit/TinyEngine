#include "Mesh.h"

#include <glm/ext/matrix_transform.hpp>

#include "Application.h"
#include "Camera.h"
#include "glad/glad.h"
#include "Shader.h"
#include "VertexArray.h"

namespace TE
{
    Mesh::Mesh(VertexArray* vertexArray, Material* material, glm::mat4 model)
        : vertexArray(vertexArray), material(material), model(model)
    {
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
        : vertices(vertices), indices(indices), textures(textures)
    {
        SetupMesh();
    }

    Mesh Mesh::CreateCube(TE::VertexArray* vao, Material* material, glm::vec3 position, float scale)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        model = glm::scale(model, glm::vec3(scale)); // a smaller cube
        return Mesh(vao, material, model);
    }
    
    void Mesh::Draw()
    {
        vertexArray->Bind();
        glm::mat4 mvp = Application::Projection() * Application::GetCamera().GetViewMatrix() * model;
        material->Update(model);
        glDrawArrays(GL_TRIANGLES, 0, 36);        
    }

    void Mesh::Draw(Shader& program)
    {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (int i = 0; i < textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = textures[i].GetType();
            if(name == "texture_diffuse")
            {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNr++);
            }

            program.SetUniform(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].GetId());
        }
        
        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::SetupMesh()
    {
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

        glBindVertexArray(0);
    }
}

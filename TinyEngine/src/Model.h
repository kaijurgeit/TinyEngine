#pragma once

#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace TE
{

    class Model
    {
    public:
        Model(const char* path);
        void Draw(Shader& shader);

    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    };
}

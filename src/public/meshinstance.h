#ifndef MESHINSTANCE_H
#define MESHINSTANCE_H

#include <glm/glm.hpp>

class Mesh;
class Shader;
class Texture;

class MeshInstance
{
public:
    Mesh* mesh;

    glm::vec3 position;
    glm::vec3 rotation;

public:
    MeshInstance(Mesh& mesh, Shader& shader, Texture& texture,
        glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f));

    void Draw(Shader& shader);
    void SetMesh(Mesh &mesh);

    glm::mat4 GetModelMatrix() const;
};

#endif
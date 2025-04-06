#include "meshinstance.h"

#include "Shader/shader.h"
#include "mesh.h"

MeshInstance::MeshInstance(Mesh& mesh, Shader& shader, Texture& texture,
    glm::vec3 position, glm::vec3 rotation):
    mesh(&mesh), position(position), rotation(rotation)
{
    shader.SetVec4Parameter("modulate", glm::vec4(1.f));
    shader.SetIntParameter("colorTexture", 0);
    // glBindVertexArray(VAO);
}

void MeshInstance::Draw(Shader &shader)
{
    mesh->Draw();
    shader.SetMat4Parameter("model", GetModelMatrix());
}

void MeshInstance::SetMesh(Mesh &mesh)
{
    this->mesh = &mesh;
}

glm::mat4 MeshInstance::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.f, 0.f, 1.f));
    return model;
}
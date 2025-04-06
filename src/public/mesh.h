#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

class Mesh
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indicesToProcess;

public:
    Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);

    void Draw();
    void GenerateFromData(std::vector<float>& vertices, std::vector<unsigned int>& indices);
};

#endif
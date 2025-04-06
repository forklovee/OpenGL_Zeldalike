#include <cstdio>
#include <cmath>

#include "app.h"
#include "camera.h"
#include "mesh.h"
#include "meshinstance.h"

#include "texture.h"

#include "Shader/shader.h"

int main(int argc, char* argv[])
{
    App app = App();
    app.GetCamera()->Translate(glm::vec3(0.f, 0.5f, 0.f));

    // Set polygon mode
    bool bWireframeMode = false;
    glPolygonMode(GL_FRONT_AND_BACK, (bWireframeMode) ? GL_LINE : GL_FILL);

    std::vector<float> vertices = {
        // Base
        0.5f, 0.5f, 0.0f, // 0 top right
        0.75f, 0.75f, 0.75f, // color dark grey
        1.0f, 1.0f, // uv
        0.5f, -0.5f, 0.0f, // 1 bottom right
        0.75f, 0.75f, 0.75f, // color dark grey
        1.0f, 0.0f, // uv
        -0.5f, -0.5f, 0.0f, // 2 bottom left
        0.75f, 0.75f, 0.75f, // color dark grey
        0.0f, 0.0f, // uv
        -0.5f, 0.5f, 0.0f, // 3 top left
        0.75f, 0.75f, 0.75f, // color dark grey
        0.0f, 1.0f, // uv

        // Walls
        0.0f, 0.0f, 1.0f, // 4 tip
        1.0f, 1.0f, 1.0f, // color white
        0.5f, -1.0f, // uv

        0.5f, 0.5f, 0.0f, // 5 wall 1 (top right)
        0.5f, 0.5f, 0.5f, // color grey
        0.0f, 0.0f, // uv
        -0.5f, 0.5f, 0.0f, // 6 wall 1 (top left)
        0.5f, 0.5f, 0.5f, // color grey
        1.0f, 0.0f, // uv

        0.5f, 0.5f, 0.0f, // 7 wall 2 (top right)
        0.5f, 0.5f, 0.5f, // color grey
        0.0f, 0.0f, // uv
        0.5f, -0.5f, 0.0f, // 8 wall 2 (bottom right)
        0.5f, 0.5f, 0.5f, // color grey
        1.0f, 0.0f, // uv
        
        0.5f, -0.5f, 0.0f, // 9 wall 3 (bottom right)
        0.5f, 0.5f, 0.5f, // color grey
        0.0f, 0.0f, // uv
        -0.5f, -0.5f, 0.0f, // 10 wall 3 (bottom left)
        0.5f, 0.5f, 0.5f, // color grey
        1.0f, 0.0f, // uv
        
        -0.5f, -0.5f, 0.0f, // 11 wall 4 (bottom left)
        0.5f, 0.5f, 0.5f, // color grey
        0.0f, 0.0f, // uv
    };
    std::vector<unsigned int> indices = {
        // Base
        3, 0, 1, // first triangle
        1, 2, 3, // second triangle

        // Walls
        6, 4, 5,
        7, 4, 8,
        9, 4, 10,
        11, 4, 6
    };

    Texture containerTexture = Texture("../content/textures/catstanding.jpg", 0, GL_REPEAT);

    Shader shader = Shader("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl");
    Mesh catPyramidMesh = Mesh(vertices, indices);

    std::vector<MeshInstance> catPyramids = {
        MeshInstance(catPyramidMesh, shader, containerTexture, glm::vec3(0.f, 0.5f, -1.2), glm::vec3(-90.f, 45.f, 0.f)),
        MeshInstance(catPyramidMesh, shader, containerTexture, glm::vec3(-0.5f, 0.0f, -0.7), glm::vec3(-90.f, 0.f, 25.f)),
        MeshInstance(catPyramidMesh, shader, containerTexture, glm::vec3(0.5f, 0.0f, -1.2), glm::vec3(-90.f, 25.f, 25.f)),
    };

    // render loop
    while(app.IsRunning()){
        app.PreUpdate();

        float timeValue = app.GetRunTime();

        shader.UpdateProjectionView(*app.GetCamera());
        for (MeshInstance catPyramid: catPyramids)
        {
            catPyramid.rotation.y += 50.f*timeValue;
            catPyramid.Draw(shader);
        }

        app.Update();
    }

    // Unbind VAO
    glBindVertexArray(0);

    return 1;
}
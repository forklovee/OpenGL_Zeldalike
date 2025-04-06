#include <cstdio>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

#include "Shader/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Update viewport size
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char* argv[])
{
    printf("Hello GLFW!\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ZeldaLike [WIP]", NULL, NULL);
    if (window == NULL){
        printf("Failed to create GLFW window!\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD!\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    // bind window size chages to viewport size change
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glEnable(GL_DEPTH_TEST);

    // Set polygon mode
    bool bWireframeMode = false;
    glPolygonMode(GL_FRONT_AND_BACK, (bWireframeMode) ? GL_LINE : GL_FILL);

    float vertices[] = {
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
    unsigned int indices[] = {
        // Base
        3, 0, 1, // first triangle
        1, 2, 3, // second triangle

        // Walls
        6, 4, 5,
        7, 4, 8,
        9, 4, 10,
        11, 4, 6
    };

    glm::vec3 positions[] = {
        glm::vec3(-0.7f, 0.0f, 0.f),
        glm::vec3(0.7f, 0.0f, 0.f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };

    // Generate and bind Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind Vertex Buffer Object, and copy vertices to it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind Element Buffer Object, and copy indices to it
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
    glm::mat4 projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.001f, 100.f);

    Shader shader = Shader("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl");
    shader.SetMat4Parameter("view", view);
    shader.SetMat4Parameter("projection", projection);

    Texture containerTexture = Texture("../content/textures/catstanding.jpg", 0, GL_REPEAT);
    Texture wallTexture = Texture("../content/textures/wall.jpg", 1, GL_REPEAT);
    shader.SetVec4Parameter("modulate", glm::vec4(1.f));
    shader.SetIntParameter("colorTexture1", 0);
    shader.SetIntParameter("colorTexture2", 1);

    // Bind currently used VAO
    glBindVertexArray(VAO);

    // render loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.75f, 0.5f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeValue = glfwGetTime();

        glm::mat4 view = glm::mat4(1.f);
        view = glm::translate(view, glm::vec3(0.f, -1.f, -5.f));
        view = glm::rotate(view, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
        view = glm::rotate(view, timeValue*.5f, glm::vec3(0.f, 0.f, 1.f));
        shader.SetMat4Parameter("view", view);

        for(glm::vec3 position: positions)
        {
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.f));
            model = glm::rotate(model, timeValue, glm::vec3(0.0f, 0.0f, 1.f));

            shader.SetMat4Parameter("model", model);
            glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Unbind VAO
    glBindVertexArray(0);

    glfwTerminate();

    // delete shader;

    return 1;
}
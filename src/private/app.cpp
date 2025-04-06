#include "app.h"

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

App::App(std::string appName, glm::vec2 windowSize):
    appName(appName), windowSize(windowSize)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(this->windowSize.x, this->windowSize.y, appName.c_str(), NULL, NULL);
    if (window == NULL){
        printf("Failed to create GLFW window!\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD!\n");
        return;
    }

    glViewport(0, 0, windowSize.x, windowSize.y);
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mousePosition = windowSize*.5f;

    // Reroute glfw callbacks to this class
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    camera = new Camera(glm::vec3(0.f, 0.f, 3.f));
}

App::~App()
{
    delete camera;

    glfwTerminate();
}

void App::PreUpdate()
{
    ClearViewport();
    ProcessInput(window);
}

void App::Update()
{
    glfwSwapBuffers(window);
    glFinish();
    
    glfwPollEvents();

    // lastFrameTime = GetRunTime();
}

void App::ClearViewport()
{
    glClearColor(0.75f, 0.5f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool App::IsRunning() const
{
    return !glfwWindowShouldClose(window);
}

float App::GetRunTime() const
{
    return glfwGetTime();
}

float App::GetDeltaTime() const
{
    return GetRunTime() - lastFrameTime;
}

Camera* App::GetCamera()
{
    return camera;
}

void App::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // Get class instance
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    if(!app) return;

    app->windowSize = glm::vec2(width, height);
    // Update viewport size
    glViewport(0, 0, app->windowSize.x, app->windowSize.y);
}

void App::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    if(!app) return;


    // glm::vec3 cameraRotation = glm::vec3(
    //     app->mousePosition.x - xpos,
    //     app->mousePosition.y - ypos,
    //     0.f
    // );
    // app->GetCamera()->Rotate(0.f, cameraRotation.x, 0.f);

    app->mousePosition = glm::vec2(xpos, ypos);
}

void App::ProcessInput(GLFWwindow* window)
{
    // Quit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = 0.15;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->Translate(glm::vec3(0.f, 0.f, -1.f) * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->Translate(glm::vec3(0.f, 0.f, 1.f) * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->Translate(glm::vec3(-1.f, 0.f, 0.f) * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->Translate(glm::vec3(1.f, 0.f, 0.f) * cameraSpeed);
    }

}
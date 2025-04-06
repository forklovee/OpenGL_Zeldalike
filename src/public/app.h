#ifndef APP_H
#define APP_H

#include <glm/glm.hpp>
#include <string>

class GLFWwindow;
class Camera;

class App
{
private:
    std::string appName;
    glm::vec2 windowSize;
    
    GLFWwindow* window;
    Camera* camera;

    glm::vec2 mousePosition;

    float lastFrameTime = 0.f;
public:
    App(std::string appName = "App", glm::vec2 windowSize = glm::vec2(800, 600));
    ~App();
    
    void PreUpdate();
    void Update();

    bool IsRunning() const;
    float GetRunTime() const;
    float GetDeltaTime() const;

    Camera* GetCamera();

private:
    void ClearViewport();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

    void ProcessInput(GLFWwindow* window);
};

#endif
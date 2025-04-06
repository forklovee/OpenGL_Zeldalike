#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    glm::vec3 position;

private:
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 worldUp;


public:
    Camera(glm::vec3 position = glm::vec3(0.f),
        glm::vec3 forward = glm::vec3(0.f, 0.f, -1.f),
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f));

    void Translate(glm::vec3 positionOffset);
    void Rotate(glm::vec3 eulerRotation);
    void Rotate(float pitch, float yaw, float roll);
    void LookAt(glm::vec3 targetPosition);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    glm::vec3 GetForward();
    glm::vec3 GetRight();
    glm::vec3 GetUp();
};

#endif
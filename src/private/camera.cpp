#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) :
    position(position), forward(forward), up(up)
{
    worldUp = glm::vec3(0.f, 1.f, 0.f);
}

void Camera::Translate(glm::vec3 positionOffset)
{
    position += positionOffset;
}

void Camera::Rotate(glm::vec3 eulerRotation)
{
    Rotate(eulerRotation.x, eulerRotation.y, eulerRotation.z);
}

void Camera::Rotate(float pitch, float yaw, float roll)
{
    glm::vec3 newForward = GetForward();
    newForward.x += cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newForward.y += sin(glm::radians(pitch));
    newForward.x += sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(newForward);
    up = glm::normalize(glm::cross(GetRight(), forward));
}

void Camera::LookAt(glm::vec3 targetPosition)
{
    forward = glm::normalize(position - targetPosition);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + GetForward(), GetUp());
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(45.f), 800.f/600.f, 0.001f, 100.f);
}

glm::vec3 Camera::GetForward()
{
    return forward;
}

glm::vec3 Camera::GetRight()
{
    return glm::cross(GetForward(), worldUp);
}

glm::vec3 Camera::GetUp()
{
    return up;
}

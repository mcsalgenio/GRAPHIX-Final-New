#include "Camera.h"

Camera::Camera()
{
    camPos = glm::vec3(0, 0, 10.f);
    WorldUp = glm::vec3(0, 1.0f, 0);
    Center = glm::vec3(0, 0, 0);
    F = glm::normalize(glm::vec3(Center - camPos));
    R = glm::normalize(glm::cross(F, WorldUp));
    U = glm::normalize(glm::cross(R, F));

    viewMatrix = glm::lookAt(camPos, Center, U);
}

Camera::Camera(glm::vec3 pos)
{
    camPos = pos;

    WorldUp = glm::vec3(0, 1.0f, 0);
    Center = glm::vec3(0, 0, 0);
    F = glm::normalize(glm::vec3(Center - camPos));
    R = glm::normalize(glm::cross(F, WorldUp));
    U = glm::normalize(glm::cross(R, F));

    viewMatrix = glm::lookAt(camPos, Center, U);
}

void Camera::updateViewMatrix(double x_mod, double y_mod, double z_mod)
{
    camPos = glm::vec3(camPos.x + x_mod, camPos.y + y_mod, camPos.z + z_mod);
    Center = glm::vec3(Center.x + x_mod, Center.y + y_mod, Center.z + z_mod);

    F = glm::normalize(glm::vec3(Center - camPos));
    R = glm::normalize(glm::cross(F, WorldUp));
    U = glm::normalize(glm::cross(R, F));

    viewMatrix = glm::lookAt(camPos, Center, U);
}
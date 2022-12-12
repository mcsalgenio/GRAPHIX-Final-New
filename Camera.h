#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    glm::vec3 camPos;
    glm::vec3 WorldUp;
    glm::vec3 Center;
    glm::vec3 F;
    glm::vec3 R;
    glm::vec3 U;
    glm::mat4 viewMatrix;

    public:
        Camera();
        Camera(glm::vec3 pos);
        glm::vec3 getCamPos() { return camPos; };
        glm::mat4 getViewMatrix() { return viewMatrix; };
        void updateViewMatrix(double x_mod, double y_mod, double z_mod);
};


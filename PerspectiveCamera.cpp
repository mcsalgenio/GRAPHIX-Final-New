#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float FOV, float windowHeight, float windowWidth, float near, float far)
{
	projPerspective = glm::perspective(glm::radians(FOV), windowHeight / windowWidth, near, far);
	xPos = 0;
	yPos = 0;
}

void PerspectiveCamera::mouseControl(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	//Camera::updateViewMatrix(xPos, yPos, zPos);
}
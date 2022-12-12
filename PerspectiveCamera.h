#pragma once

#include "Camera.h"
class PerspectiveCamera: public Camera
{
	glm::mat4 projPerspective;
	double xPos, yPos;

	public:
		PerspectiveCamera(float FOV, float windowHeight, float windowWidth, float near, float far); //fov in degrees
		void mouseControl(GLFWwindow* window);
		glm::mat4 getProjPerspective() { return projPerspective; };
};


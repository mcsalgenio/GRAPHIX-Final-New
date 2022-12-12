#pragma once

#include "Camera.h"
class OrthoCamera: public Camera
{
	glm::mat4 projOrtho;

	public:
		OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar, glm::vec3 pos);
		glm::mat4 getProjOrtho() { return projOrtho; };
};


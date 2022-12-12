#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar, glm::vec3 pos) : Camera(pos)
{
	projOrtho = glm::ortho(left, right, bottom, top, zNear, zFar);
}
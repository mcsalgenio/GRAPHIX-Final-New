#include "Light.h"

Light::Light(glm::vec3 pos)
{
	lightPos = pos;
	lightColor = glm::vec3(0.0f, 0.0f, 2.0f);
	ambientStr = 0.1f;
	ambientColor = lightColor;
	specStr = 0.5f;
	specPhong = 16.0f;
}
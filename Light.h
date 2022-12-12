#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
	glm::vec3 lightPos;
	glm::vec3 lightColor;
	float ambientStr;
	glm::vec3 ambientColor;
	float specStr;
	float specPhong;

	public:
		Light(glm::vec3 pos);
		glm::vec3 getLightPos() { return lightPos; };
		glm::vec3 getLightColor() { return lightColor; };
		float getAmbientStr() { return ambientStr; };
		glm::vec3 getAmbientColor() { return ambientColor; };
		float getSpecStr() { return specStr; };
		float getSpecPhong() { return specPhong; };
};


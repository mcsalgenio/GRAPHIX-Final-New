#pragma once

#include <vector>

class Model
{
	glm::vec3 position;
	glm::vec3 scale;
	float theta;
	glm::vec3 rotation_x;
	glm::vec3 rotation_y;
	glm::vec3 rotation_z;
	std::vector<GLfloat> fullVertexData;
	GLuint VAO, VBO;

	public:
		Model(std::string obj_path, glm::vec3 pos, glm::vec3 scl, float rot);
		void draw(GLuint shaderProg, GLuint texture, GLuint norm_tex); //for enemy ships
		void draw(glm::vec3 pos, GLuint shaderProg, GLuint texture, GLuint norm_tex); //for main ship, needs pos for movement
		void deleteBuffers();
};


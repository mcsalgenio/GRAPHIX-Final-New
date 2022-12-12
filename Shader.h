#pragma once
class Shader
{
	GLuint shaderProg;

	public:
		Shader(std::string vert_path, std::string frag_path);
		GLuint getShader() { return shaderProg; };
		void useShaderProg();
};


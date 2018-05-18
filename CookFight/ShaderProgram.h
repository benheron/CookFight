#pragma once
#include <gl/glew.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


class ShaderProgram
{

public:
	ShaderProgram();
	~ShaderProgram();

	bool loadShader(std::string filePath, GLenum shaderType, GLuint &shader);

	bool loadProgram(std::string vertShaderPath, std::string fragShaderPath);

	void deleteProgram();

	bool bind();

	void unbind();

	GLuint getProgramID();

protected:
	void logProgram(GLuint program);


	void logShader(GLuint shader);

	GLuint programID;
	std::vector<GLuint> allShaders;
};
#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
	programID = 0;
}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
}

bool ShaderProgram::loadShader(std::string filePath, GLenum shaderType, GLuint &shader)
{

	//set shader type
	shader = glCreateShader(shaderType);

	//read shader file
	std::ifstream shaderData(filePath);

	std::string shaderCode;

	if (shaderData.is_open())
	{
		std::string line = "";

		while (std::getline(shaderData, line))
		{
			shaderCode += "\n" + line;
		}

		shaderData.close();

		//compile shader
		const GLchar* shaderSource = shaderCode.c_str();

		//set vertex source
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		//check vertex shader for errors
		GLint shaderCompiled = GL_FALSE;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

		if (shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile shader %d\n\nSource:\n%s\n", shader, shaderSource);
			logShader(shader);
			glDeleteShader(shader);
			shader = 0;
			return false;
		}
		else {
			allShaders.push_back(shader);
		}
	}
	else
	{
		printf("Can't open shader: %s", filePath);
		return false;
	}
	return true;
}

bool ShaderProgram::loadProgram(std::string vertShaderPath, std::string fragShaderPath)
{

	programID = glCreateProgram();

	GLuint vertexShader, fragmentShader;

	//load shaders
	loadShader(vertShaderPath, GL_VERTEX_SHADER, vertexShader);
	loadShader(fragShaderPath, GL_FRAGMENT_SHADER, fragmentShader);


	for (int i = 0; i < allShaders.size(); i++)
	{
		glAttachShader(programID, allShaders[i]);
	}

	glLinkProgram(programID);

	//check the program
	GLint programCheck = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &programCheck);

	if (programCheck != GL_TRUE)
	{
		printf("Error linking program %d!\n", programID);
		logProgram(programID);

		for (int i = 0; i < allShaders.size(); i++)
		{
			glDeleteShader(allShaders[i]);
		}
		glDeleteProgram(programID);
		programID = 0;
		return false;
	}

	for (int i = 0; i < allShaders.size(); i++)
	{
		glDetachShader(programID, allShaders[i]);
		glDeleteShader(allShaders[i]);
	}

	return true;
}

void ShaderProgram::deleteProgram()
{
	//delete program
	glDeleteProgram(programID);
}


bool ShaderProgram::bind()
{
	glUseProgram(programID);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("Error binding shader! %s\n", gluErrorString(err));
		logProgram(programID);
		return false;
	}

	return true;
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}


GLuint ShaderProgram::getProgramID()
{
	return programID;
}

void ShaderProgram::logProgram(GLuint program)
{

	if (glIsProgram(program))
	{

		int infoLogLen = 0;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
		char* infoLog = new char[infoLogLen];

		if (infoLogLen > 0)
		{
			glGetProgramInfoLog(programID, infoLogLen, NULL, infoLog);
			printf("%s\n", infoLog);
		}

		delete[] infoLog;
	}
	else {
		printf("Name %d is not a program\n", program);
	}
}

void ShaderProgram::logShader(GLuint shader)
{
	//make sure name is shader
	if (glIsShader(shader))
	{
		int infoLogLen = 0;

		//get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		char* infoLog = new char[infoLogLen];

		if (infoLogLen > 0)
		{
			//get info log
			glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
			printf("%s\n", infoLog);
		}

		//deallocate string
		delete[] infoLog;

	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}
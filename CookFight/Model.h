#pragma once
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

class Model {
public:
	Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs, std::vector<glm::vec3> vertNormals,
		std::vector<unsigned int> vertexIndices, glm::vec3 minPos, glm::vec3 maxPos, float width, float height, float depth, glm::vec3 medianPos);

	Model(std::vector<glm::vec2> vertices2D, std::vector<glm::vec2> UVs);
	Model(std::vector<glm::vec2> vertices2D);

	Model(std::vector < glm::vec3> vertices, std::vector<glm::vec2> UVs);

	Model(std::vector < glm::vec3> vertices);
	~Model();


	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getVertNormals();

	std::vector<unsigned int> getVertexIndices();


	std::vector<glm::vec2> getVertices2D();

	float getWidth();
	float getHeight();
	float getDepth();

	glm::vec3 getMinPos();

	glm::vec3 getMaxPos();

	glm::vec3 getMedian();


	GLuint getVertexBuffer();
	GLuint getUVBuffer();
	GLuint getNormalBuffer();

	GLuint getIndexBuffer();
	GLuint getVertexBuffer2D();

	void changeVertex2DBuffer(int startIndex, std::vector<glm::vec2> nVerts);

	void changeUVBUffer(int startIndex, std::vector<glm::vec2> nUVs);

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> vertNormals;
	std::vector<unsigned int> vertexIndices;

	std::vector<glm::vec2> vertices2D;
	std::vector<glm::vec2> UVs2D;
	GLuint UVsBuffer2D;


	GLuint vertexBuffer2D;

	glm::vec3 minPos;
	glm::vec3 maxPos;

	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;

	GLuint indexBuffer;

	glm::vec3 median;

	float width, height, depth;
};
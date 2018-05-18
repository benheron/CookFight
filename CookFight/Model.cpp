#include "Model.h"

Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs, std::vector<glm::vec3> vertNormals, 
	std::vector<unsigned int> vertexIndices, glm::vec3 minPos, glm::vec3 maxPos, float width, float height, float depth, glm::vec3 medianPos) :
	vertices(vertices), UVs(UVs), vertNormals(vertNormals), vertexIndices(vertexIndices), minPos(minPos), maxPos(maxPos), width(width), height(height), depth(depth), median(medianPos)
{

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertNormals.size() * sizeof(glm::vec3), &vertNormals[0], GL_STATIC_DRAW);


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);


	//Create IBO
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);




}


//3D vert + uv
Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs) :
	vertices(vertices), UVs(UVs)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_DYNAMIC_DRAW);
}

//3D just vert
Model::Model(std::vector<glm::vec3> vertices) :
	vertices(vertices)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

//2d vert + uv
Model::Model(std::vector<glm::vec2> vertices2D, std::vector<glm::vec2> UVs) :
	vertices2D(vertices2D), UVs(UVs)
{
	glGenBuffers(1, &vertexBuffer2D);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2D);
	glBufferData(GL_ARRAY_BUFFER, vertices2D.size() * sizeof(glm::vec2), &vertices2D[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_DYNAMIC_DRAW);
}

Model::Model(std::vector<glm::vec2> vertices2D) :
	vertices2D(vertices2D)
{
	glGenBuffers(1, &vertexBuffer2D);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2D);
	glBufferData(GL_ARRAY_BUFFER, vertices2D.size() * sizeof(glm::vec2), &vertices2D[0], GL_STATIC_DRAW);
}

Model::~Model()
{
	if (normalBuffer != NULL)
	{
		glDeleteBuffers(1, &normalBuffer);
	}
	
	if (indexBuffer)
	{
		glDeleteBuffers(1, &indexBuffer);
	}

	if (vertexBuffer)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	
	if (uvBuffer)
	{
		glDeleteBuffers(1, &uvBuffer);
	}

	if (vertexBuffer2D)
	{
		glDeleteBuffers(1, &vertexBuffer2D);
	}
	

}

std::vector<glm::vec3> Model::getVertices()
{
	return vertices;
}

std::vector<glm::vec2> Model::getUVs()
{
	return UVs;
}
std::vector<glm::vec3> Model::getVertNormals()
{
	return vertNormals;
}

std::vector<unsigned int> Model::getVertexIndices()
{
	return vertexIndices;
}

float Model::getWidth()
{
	return width;
}

float Model::getHeight()
{
	return height;
}


float Model::getDepth()
{
	return depth;
}


glm::vec3 Model::getMedian()
{
	return median;
}



GLuint Model::getVertexBuffer()
{
	return vertexBuffer;
}

GLuint Model::getUVBuffer()
{
	return uvBuffer;
}

GLuint Model::getNormalBuffer()
{
	return normalBuffer;
}

GLuint Model::getIndexBuffer()
{
	return indexBuffer;
}

std::vector<glm::vec2> Model::getVertices2D()
{
	return vertices2D;
}

GLuint Model::getVertexBuffer2D()
{
	return vertexBuffer2D;
}

void Model::changeVertex2DBuffer(int startIndex, std::vector<glm::vec2> nVerts)
{
	std::vector<glm::vec2> bufferContents;

	glNamedBufferSubData(vertexBuffer2D,
		startIndex * sizeof(glm::vec2),
		nVerts.size() * sizeof(glm::vec2),
		&nVerts[0]);
}

void Model::changeUVBUffer(int startIndex, std::vector<glm::vec2> nUVs)
{
	std::vector<glm::vec2> bufferContents;

	glNamedBufferSubData(uvBuffer,
		startIndex * sizeof(glm::vec2),
		nUVs.size() * sizeof(glm::vec2),
		&nUVs[0]);

}

glm::vec3 Model::getMinPos()
{
	return minPos;
}


glm::vec3 Model::getMaxPos()
{
	return maxPos;
}
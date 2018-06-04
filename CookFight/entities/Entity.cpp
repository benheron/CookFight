#include "Entity.h"


Entity::Entity(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens2, glm::vec2 uvSize2) : entTexture(entTexture), pos(pos), dimens(dimens2), uvSize(uvSize2)
{
	entTextures.push_back(entTexture);

	if (dimens == glm::vec3(0))
	{
		dimens = glm::vec3(entTexture->getOrigDimens(), 0);
	}

	if (uvSize == glm::vec2(0))
	{
		uvSize.x = (dimens.x)/entTexture->getOrigDimens().x;
		uvSize.y = (dimens.y)/entTexture->getOrigDimens().y;

		//uvPos = 0.5f / entTexture->getOrigDimens();
		uvPos = glm::vec2(0);
	}
	else if(uvSize == glm::vec2(1))
	{
		uvPos = glm::vec2(0);
	}
	else if (uvSize.x > 1.f || uvSize.y > 1.f) 
	{
		//given pixel size
	/*	uvSize.x /= entTexture->getOrigDimens().x;
		uvSize.y /= entTexture->getOrigDimens().y;*/

		uvSize = uvSize / entTexture->getOrigDimens();

		uvPos = glm::vec2(0.5f)/ entTexture->getOrigDimens();
		uvPos = glm::vec2(0);
	}

	container = false;

	offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);

	init();
}


Entity::Entity(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : pos(pos),  dimens(dimens), uvSize(uvSize), offsetPos(offPos), container(container)
{
	
	if (offPos == glm::vec3(0))
	{
		offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);

	}
	
	init();
}

Entity::~Entity()
{
	for (int i = 0; i < entModels.size(); i++)
	{
		delete entModels[i];
	}

	for (int i = children.size()-1; i > -1; i--)
	{
		delete children[i];
	}
}


void Entity::init()
{
	modelMatChanged = true;
	rotMatrix = glm::mat4(1.0);

	modelMatrix = glm::mat4(1.0);
	bbMatrix = glm::mat4(1.0);

	rotPitch = 0;
	rotYaw = 0;
	rotRoll = 0;

	modScale = glm::vec3(1.0);

	dimensScale = modScale * glm::vec3(dimens.x/2, dimens.y/2, 0);

	shouldRender = true;

	if (dimensScale == glm::vec3(0))
	{
		dimensScale = glm::vec3(1);
	}

	UVOffset = glm::vec2(0);


	hitboxDimensScale = dimensScale;

	hitboxPosRel = glm::vec3(0);

	speed = 150;

	blendColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	setQuadVertices(vertices);



	if (entTexture != NULL && uvSize != glm::vec2(0))
	{
		
		setQuadUVs(UVs);

		model = new Model(vertices, UVs);

		entModels.push_back(model);
	}
	else {
		if (!container)
		{
			model = new Model(vertices);
		}
		
	}
	secOffsetPos = glm::vec3(0);

	bb = new BoundingBox(glm::vec3(-1.f, -1.f, 0), glm::vec3(1.f, 1.f, 0));

	//bb = new BoundingBox(-offsetPos, -offsetPos+dimens, offsetPos);

	updateModelMatrix();
	updateBoundingBoxMatrix();

	//bb->transformByMat4(bbMatrix);


	acceleration = glm::vec3(0, 0.f, 0);

	velocity = glm::vec3(0);

	maxXVel = 0;


	


}

void Entity::update(float dt)
{
	/*velocity.x += acceleration.x *dt;
	velocity.y += acceleration.y *dt;




	
	
	pos += velocity * dt;*/


	if (!modelMatChanged)
	{
		//return;
	}


	



	updateModelMatrix();

	updateBoundingBoxMatrix();


	acceleration.x = 0;
}


void Entity::updateModelMatrix()
{
	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos + secOffsetPos;// +glm::vec3(0.001f, 0.001f, 0);

	//glm::vec3 roundPos = glm::vec3(round(jointPos.x), round(jointPos.y), 0);

	glm::vec3 roundPos =  jointPos;



	//glm::vec3 nPos = glm::vec3(round(jointPos.x), round(jointPos.y), round(jointPos.z));

	glm::vec3 nPos = roundPos + offsetPos;

	//printf("Real feet position y: %f \n", (pos.y + dimens.y));
	//printf("Jointpos position y: %f \n", jointPos.y);
	//printf("Render position y: %f \n", nPos.y);

	//translate to new position
	//use joint position as this is for rendering
	mm = glm::translate(mm, roundPos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	glm::vec3 joinScale = modScale * dimensScale;


	mm = glm::scale(mm, joinScale);

	
	modelMatrix = mm;

}


void Entity::updateBoundingBoxMatrix()
{
	glm::mat4 mm = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos + hitboxPosRel;

	mm = glm::translate(mm, jointPos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, hitboxDimensScale);


	bb->transformByMat4(mm);

	if (rotYaw >= 3.14/2)
	{
		bb->reverseDir();
	}
}


void Entity::setQuadVertices(std::vector<glm::vec2> &vertices)
{
	
	//make sure to have centred
	glm::vec3 startPos = pos - offsetPos;




	glm::vec2 topLeftVert = glm::vec2(-1.f, -1.f);
	glm::vec2 topRightVert = glm::vec2(1.f, -1.f);
	glm::vec2 bottomLeftVert = glm::vec2(-1.f, 1.f);
	glm::vec2 bottomRightVert = glm::vec2(1.f, 1.f);

	vertices.push_back(topLeftVert);
	vertices.push_back(bottomLeftVert);
	vertices.push_back(topRightVert);

	vertices.push_back(bottomRightVert);
	vertices.push_back(topRightVert);
	vertices.push_back(bottomLeftVert);





	/*glm::vec2 topLeftVert = glm::vec2(startPos.x, startPos.y);
	glm::vec2 topRightVert = glm::vec2(startPos.x + dimens.x, startPos.y);
	glm::vec2 bottomLeftVert = glm::vec2(startPos.x, startPos.y + dimens.y);
	glm::vec2 bottomRightVert = glm::vec2(startPos.x + dimens.x, startPos.y + dimens.y);

	vertices.push_back(topLeftVert);
	vertices.push_back(bottomLeftVert);
	vertices.push_back(topRightVert);

	vertices.push_back(bottomRightVert);
	vertices.push_back(topRightVert);
	vertices.push_back(bottomLeftVert);*/

}


void Entity::setQuadUVs(std::vector<glm::vec2> &UVs)
{


	glm::vec2 topLeftUV = glm::vec2(uvPos.x, uvPos.y);
	glm::vec2 botLeftUV = glm::vec2(uvPos.x, uvSize.y);
	glm::vec2 topRightUV = glm::vec2(uvSize.x, uvPos.y);
	glm::vec2 botRightUV = glm::vec2(uvSize.x, uvSize.y);


	UVs.push_back(topLeftUV);
	UVs.push_back(botLeftUV);
	UVs.push_back(topRightUV);

	UVs.push_back(botRightUV);
	UVs.push_back(topRightUV);
	UVs.push_back(botLeftUV);
}

GLuint Entity::getTextureUVBuffer()
{
	return model->getUVBuffer();
}

glm::vec2 Entity::getTextureUVOffset()
{
	return UVOffset;
}



void Entity::setModel(Model *m)
{
	model = m;

	bb = new BoundingBox(model->getMinPos(), model->getMaxPos());
}

glm::vec3 Entity::getPosition()
{
	return pos;
}

glm::vec3 Entity::getCentrePosition()
{
	return pos + (dimens / 2.f);
}

void Entity::setPosition(glm::vec3 p, bool add)
{
	glm::vec3 diff = p - pos;
	if (add)
	{
		pos += p;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->setPosition(p, true);
		}

	}
	else {
		pos = p;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->setPosition(diff, true);
		}

	}

	
	updateModelMatrix();
	updateBoundingBoxMatrix();

	modelMatChanged = true;


	
}

void Entity::setCentre(glm::vec3 p)
{


	setPosition(p - (dimens / 2.f));
	//updateModelMatrix();
	//updateBoundingBoxMatrix();
}

void Entity::setDimens(glm::vec3 nd, bool add)
{
	if (add)
	{
		dimens += nd;
	}
	else
	{
		dimens = nd;
	}
	
	offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);
	dimensScale = modScale * glm::vec3(dimens.x / 2, dimens.y / 2, 0);
}

void Entity::setYaw(float rot, bool add)
{
	if (add)
	{
		rotYaw += rot;
	}
	else {
		rotYaw = rot;
	}
	modelMatChanged = true;


	for (int i = 0; i < children.size(); i++)
	{
		children[i]->setYaw(rot, add);
	}
}

void Entity::setPitch(float rot, bool add)
{
	if (add)
	{
		rotPitch += rot;
	}
	else {
		rotPitch = rot;
	}
	modelMatChanged = true;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->setYaw(rot, add);
	}
}

void Entity::setRoll(float rot, bool add)
{
	if (add)
	{
		rotRoll += rot;
	}
	else {
		rotRoll = rot;
	}
	modelMatChanged = true;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->setYaw(rot, add);
	}
}



void Entity::setVelocity(glm::vec3 v, bool add)
{
	if (add)
	{
		velocity += v;
	}
	else {
		velocity = v;
	}
	modelMatChanged = true;
}

Model* Entity::getModel()
{
	return model;
}

void Entity::addTextrure(Texture* t)
{
	entTextures.push_back(t);
}

void Entity::setTexture(Texture *t)
{
	entTexture = t;
}

Texture *Entity::getTexture()
{
	return entTexture;
}


glm::mat4 Entity::getModelMatrix()
{
	return modelMatrix;
}


glm::mat4 Entity::getModelMatrix(int index)
{
	/*if (children.size() > 0)
	{
		return children[index]->getModelMatrix();
	}*/
	return modelMatrix;
}


void Entity::setScale(glm::vec3 s)
{
	modScale = s;
	updateModelMatrix();
	updateBoundingBoxMatrix();
}

glm::vec3 Entity::getDimensions()
{
	return dimens;
}

BoundingBox *Entity::getBoundingBox()
{
	return bb;
}


float Entity::getRoll()
{
	return rotRoll;
}


std::vector<glm::vec2> Entity::getEntityVertices()
{
	std::vector<glm::vec2> tmpVertices;

	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec4 v = glm::vec4(vertices[i], 0, 1);
		glm::vec4 newV = modelMatrix * v;

		tmpVertices.push_back(glm::vec2(newV));
	}

	return tmpVertices;


	return vertices;
}


void Entity::setShouldRender(bool r)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->setShouldRender(r);
	}

	shouldRender = r;
}
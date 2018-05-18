#pragma once
#include "../Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Texture.h"
#include "../BoundingBox.h"
#include <math.h> 

class Entity {
public:

	/**
	@brief Entity constructor with texture, position, dimensions and the uvsize of an individual element
	*/

	Entity(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	Entity(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);



	virtual ~Entity();


	/**
	@brief Initialise entity variables
	*/
	void init();

	/**
	@brief Update Entity positions
	@param dt Delta time - time in milliseconds from last frame
	*/
	virtual void update(float dt);

	/**
	@brief Update the model matrix to the current positions, rotations and scales
	*/
	void updateModelMatrix();

	/**
	@brief Update the bounding box matrix used for collision
	*/
	void updateBoundingBoxMatrix();


	/**
	@brief
	*/
	void setVelocity(glm::vec3 v, bool add = false);

	/**
	@brief
	*/
	glm::vec3 getVelocity() { return velocity; }

	/**
	@brief
	*/
	void setAcceleration(glm::vec3 a, bool add = false);

	/**
	@brief
	*/
	glm::vec3 getAcceleration() { return acceleration; }

	/**
	@brief
	*/
	void setModel(Model *m);

	/**
	@brief
	*/
	Model* getModel();

	/**
	@brief
	*/
	virtual std::vector<Model*> getModels() { return entModels; }

	/**
	@brief
	*/
	void setPosition(glm::vec3 p, bool add = false);

	/**
	@brief
	*/
	void setCentre(glm::vec3 p);

	/**
	@brief
	*/
	GLuint getTextureUVBuffer();

	/**
	@brief Set the uv offset for this entity
	*/
	void setTextureUVOffset(glm::vec2 uvo) { UVOffset = uvo; }

	/**
	@brief
	*/
	virtual glm::vec2 getTextureUVOffset();


	/**
	@brief Gets the Entity position
	@returns The Entity's position
	*/
	glm::vec3 getPosition();

	/**
	@brief Gets the position in the centre of 
	@returns The centre position of the Entity
	*/

	glm::vec3 getCentrePosition();

	glm::vec3 getDimensions();


	void setTexture(Texture* t);
	virtual Texture* getTexture();

	virtual Texture* getTexture(int index) { return entTextures[index]; }

	virtual std::vector<Texture*> getTextures() { return entTextures; }
	





	///rotate across x axis
	void setYaw(float rot, bool add);
	///rotate across y axis
	void setPitch(float rot, bool add);
	///rotate across z axis
	void setRoll(float rot, bool add);

	float getRoll();


	

	void setScale(glm::vec3 s);



	glm::mat4 getModelMatrix();

	virtual glm::mat4 getModelMatrix(int index);


	std::vector<glm::vec2> getEntityVertices();
	virtual std::vector<glm::vec2> getEntityUVs() { return UVs; }

	/**
	@brief Sets the blend colour to apply to the texture
	@param bc The blend Colour to apply to the texture
	*/
	void setBlendColour(glm::vec4 bc) { blendColour = bc; }


	/**
	@brief Get the blend colour to apply to the texture
	@returns A vec4 for RGBA of the blend colour
	*/
	glm::vec4 getBlendColour() { return blendColour; }

	/**
	@brief
	*/
	BoundingBox *getBoundingBox();

	/**
	@brief Sets value of should the entity render
	@param r True or false to render or not
	*/
	void setShouldRender(bool r) { shouldRender = r; }

	/**
	@brief Gets the value of if the entity should render
	@returns If the entity should render
	*/
	bool getShouldRender() { return shouldRender; }


	/**
	@brief Add a texture to the texture list
	*/
	void addTextrure(Texture* t);
	

	std::vector<Entity*> getChildren() { return children; }


protected:

	void setQuadVertices(std::vector<glm::vec2> &vertices);
	void setQuadUVs(std::vector<glm::vec2> &UVs);

	bool modelMatChanged;


	std::vector<Entity*> children;

	std::vector<Model*> entModels;
	std::vector<Texture*> entTextures;


	///The model for this entity
	Model *model;

	///The model matrix
	glm::mat4 modelMatrix;

	glm::mat4 bbMatrix;

	///The rotation matrix
	glm::mat4 rotMatrix;

	///The scale beyond sprite size
	glm::vec3 modScale;

	//scale for the sprite size
	glm::vec3 dimensScale;

	//scale for the hitbox size
	glm::vec3 hitboxDimensScale;

	//relative movement of the hitbox
	glm::vec3 hitboxPosRel;

	//rotation
	///x axis rotation
	float rotPitch;
	///y axis rotation
	float rotYaw;
	///z-axis rotation
	float rotRoll;

	///If entity is container or not
	bool container;

	///speed of the entity
	float speed;

	///position of the entity
	glm::vec3 pos;

	///The dimensions of the entity
	glm::vec3 dimens;

	///the offset of position - half width and height
	glm::vec3 offsetPos;


	glm::vec3 secOffsetPos;


	glm::vec2 UVOffset;


	Texture * entTexture;

	
	///The entity's bounding box - used for collision
	BoundingBox *bb;

	glm::vec2 uvPos;

	glm::vec2 uvSize;


	std::vector<glm::vec2> UVs;
	std::vector<glm::vec2> vertices;


	glm::vec4 blendColour;


	bool shouldRender;

	glm::vec3 velocity;
	glm::vec3 offsetVal;


	float maxXVel;

	glm::vec3 acceleration;
};
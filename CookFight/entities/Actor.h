#pragma once
#include "WorldObject.h"
#include "../Animation/SpriteSheet.h"
#include  "../Animation/Animation.h"

enum ActorState
{
	rightState,
	leftState,
	upState,
	downState
};

class Actor : public WorldObject
{
public:
	Actor(SpriteSheet* actorSpriteSheet, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	Actor(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);
	~Actor();


	virtual void update(float dt);

	void updateFloorHitBox();

	void updateHurtBox();


	void actorInit();


	
	void jump(float dt);


	void moveRight(float dt);
	void moveLeft(float dt);

	void moveDown(float dt);
	void moveUp(float dt);

	void moveActor(glm::vec2 axis, float mag, float dt);

	void hitTile(glm::vec3 colNorm, glm::vec3 tangent, glm::vec3 frictionVel, float dt);

	void hitTileFriction(glm::vec3 tangent, glm::vec3 frictionVel, float dt);

	glm::vec2 getTextureUVOffset();


	void setSpriteSheet(SpriteSheet* s) { actorSpriteSheet = s; }



	BoundingBox* getFloorHitBox() { return floorHitBox; }


	bool getMoving() { return moving; }
	void setMoving(bool m) { moving = m; }

	void setActorState(ActorState as) { aState = as; }
	ActorState getActorState() { return aState; }
	


	void hitStaticObject(glm::vec3 colNorm);


	BoundingBox* getHurtBox() { return hurtBox; }

	void setLockDir(bool lld) { lockLookDir = lld; }

	bool getLockLookDir() { return lockLookDir; }

private:

	void decelerate(glm::vec2 axis, float dt);

	void chooseState(glm::vec2 xyMag);


	bool alive;



	
	

	BoundingBox *floorHitBox;
	glm::vec3 fHBPos;
	glm::mat4 fHBMatrix;

	float maxVel;

	float velXLimit;
	float velYLimit;



	//if moving or not
	bool moving;

	
	float decelerationSpeed;
	float moveOppositeAcceleration;

	bool changeAnimation;
	float frameRateSpeed;




	SpriteSheet* actorSpriteSheet;
	Animation* currentAnimation;



	ActorState aState;
	ActorState prevState;




	BoundingBox* hurtBox;
	glm::vec3 hurtBoxScale;




	bool lockLookDir;







};


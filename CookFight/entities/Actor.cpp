#include "Actor.h"

Actor::Actor(SpriteSheet* actorSpriteSheet, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : WorldObject(actorSpriteSheet->getTexture(), pos, dimens, uvSize), actorSpriteSheet(actorSpriteSheet)
{
	actorInit();
}


Actor::Actor(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : WorldObject(pos, dimens, uvSize, offPos, container)
{
	actorInit();
}

Actor::~Actor()
{

}

void Actor::actorInit()
{

	fHBMatrix = glm::mat4(1);

	acceleration = glm::vec3(0, 0, 0);
	decelerationSpeed = 1800;

	moveOppositeAcceleration = 2400;

	float floorHBHalfHeight = 0.01;

	glm::vec3 ogFloorPos = glm::vec3(-offsetPos.x, -offsetPos.y - floorHBHalfHeight, 0);
	glm::vec3 ogFloorMaxPos = glm::vec3(-offsetPos.x, -offsetPos.y + floorHBHalfHeight, 0);


	floorHitBox = new BoundingBox(-ogFloorPos, ogFloorMaxPos);
	fHBPos = glm::vec3(pos.x, pos.y + dimens.y, 0);

	maxXVel = 300.f;
	velXLimit = maxXVel;
	velYLimit = maxXVel;

	staticFriction = 0.5;
	dynamicFriction = 0.2;

	moving = false;
	speed = 1500;
	

	changeAnimation = false;
	frameRateSpeed = 0;

	alive = true;

	aState = downState;

	lockLookDir = false;
	//set animation

	AnimationType* atype = actorSpriteSheet->getAnimationType("D");

	currentAnimation = new Animation();

	currentAnimation->setAnimationType(atype);
	currentAnimation->playAnimation();

	

	//hardcoded value
	hitboxDimensScale = glm::vec3(14, 8, 0);
	hitboxPosRel = glm::vec3(0, 12, 0);


	hurtBox = new BoundingBox(glm::vec3(-1.f, -1.f, 0), glm::vec3(1.f, 1.f, 0));
	hurtBoxScale = dimensScale;

	updateHurtBox();
	//if using large sprites
	//hitboxDimensScale *= 2;
	//hitboxPosRel *= 2;
	
}


void Actor::update(float dt)
{
	WorldObject::update(dt);
	updateHurtBox();
	velocity.x += acceleration.x *dt;
	velocity.y += acceleration.y *dt;






	



	//lower limit x
	if (velocity.x < 0.2 &&
		velocity.x > -0.2)
	{
		velocity.x = 0;
	}
	
	
	//lower limit y
	if (velocity.y < 0.2 &&
		velocity.y > -0.2)
	{
		velocity.y = 0;
	}
		

	if (velocity.x > velXLimit)
	{
		velocity.x -= decelerationSpeed * dt;
		if (velocity.x < 0)
		{
			velocity.x = 0;
		}
	}
	else if (velocity.x < -velXLimit)
	{
		velocity.x += decelerationSpeed * dt;
		if (velocity.x > 0)
		{
			velocity.x = 0;
		}
	}

	if (velocity.y > velYLimit)
	{
		velocity.y -= decelerationSpeed * dt;
		if (velocity.y < 0)
		{
			velocity.y = 0;
		}
	}
	else if (velocity.y < -velYLimit)
	{
		velocity.y += decelerationSpeed * dt;
		if (velocity.y > 0)
		{
			velocity.y = 0;
		}
	}


	pos += velocity *dt;



/*

	if (velocity.x > 0.01f)
	{
		if (abs(velocity.x) >= abs(velocity.y))
		{
			aState = rightState;
		}

	}

	if (velocity.x < -0.01f)
	{
		if (abs(velocity.x) >= abs(velocity.y))
		{
			aState = leftState;
		}
	}

	if (velocity.y > 0.01f)
	{
		if (abs(velocity.y) > abs(velocity.x))
		{
			aState = downState;
		}
	}

	if (velocity.y < -0.01f)
	{
		if (abs(velocity.y) > abs(velocity.x))
		{
			aState = upState;
		}
	}

	float relVel = abs(velocity.x) - abs(velocity.y);


	if (relVel < 20 && relVel > -20)
	{
		if (velocity.x > 0.01f)
		{
			aState = rightState;
		}
		else

			if (velocity.x < -0.01f)
			{
				aState = leftState;
			}
	}*/


	//animation
	if (aState != prevState)
	{
		switch (aState)
		{
		case rightState:
			currentAnimation->setAnimationType(actorSpriteSheet->getAnimationType("R"));
			break;
		case leftState:
			currentAnimation->setAnimationType(actorSpriteSheet->getAnimationType("L"));
			break;
		case downState:
			currentAnimation->setAnimationType(actorSpriteSheet->getAnimationType("D"));
			break;
		case upState:
			currentAnimation->setAnimationType(actorSpriteSheet->getAnimationType("U"));
			break;
		
		}

		
	}

	

	//float newAniFR = (abs(velocity.x) / 300) * 6 + 1;
	
	if (frameRateSpeed < 1.5)
	{
		frameRateSpeed = 1.5;
	}

	


	currentAnimation->setFrameRate(frameRateSpeed);

	

	if (currentAnimation->getFrameIndex() % 2 && (aState == downState || aState == upState))
	{
		secOffsetPos = glm::vec3(0, 0, 0);
	}
	else
	{		
		secOffsetPos = glm::vec3(0, -1, 0);
	}
	
	if (abs(velocity.x) > 0 || abs(velocity.y) > 0)
	{
		currentAnimation->update(dt);
	}
	else {
		currentAnimation->setFrameIndex(0);
	}
	

	//dimensScale = glm::vec3(currentAnimation->getCurrentFrame()->getFrameDimensPixels(), 0)/2.f;
	//printf("Dimens x: %f, y: %f \n", dimensScale.x, dimensScale.y);

	prevState = aState;
	
}

void Actor::updateFloorHitBox()
{

	glm::mat4 m = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos + fHBPos;



	


	//translate to new position
	//use joint position as this is for rendering
	m = glm::translate(m, jointPos);

	//rotate x
	m = glm::rotate(m, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	m = glm::rotate(m, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	m = glm::rotate(m, rotRoll, glm::vec3(0, 0, 1));

	//scale
	m = glm::scale(m, modScale);


	fHBMatrix = m;
}

void Actor::updateHurtBox()
{
	glm::mat4 mm = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos;

	mm = glm::translate(mm, jointPos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, hurtBoxScale);


	hurtBox->transformByMat4(mm);

}

void Actor::moveRight(float dt)
{
	
	velocity.x += speed  *dt;
	

	moving = true;

	modelMatChanged = true;
}

void Actor::moveLeft(float dt)
{
	
	velocity.x -= speed *dt;

	moving = true;
	modelMatChanged = true;
}

void Actor::moveDown(float dt)
{
	velocity.y += speed * dt;
	moving = true;
	modelMatChanged = true;
}

void Actor::moveUp(float dt)
{
	velocity.y -= speed * dt;
	moving = true;
	modelMatChanged = true;
}


void Actor::moveActor(glm::vec2 axis, float mag, float dt)
{
	//if (abs(axis.x))
	{
		velXLimit = abs(axis.x) * mag * maxXVel;
	}
	
	//if (abs(axis.y))
	{
		velYLimit = abs(axis.y) * mag * maxXVel;
	}
	


	frameRateSpeed = mag * 6;

	bool useDecelerateX = false;
	bool useDecelerateY = false;

	if (velocity.x > 0)
	{
		if (axis.x < 0)
		{
			useDecelerateX = true;
		}
		else {
			useDecelerateX = false;
		}
	}
	else 
	if (velocity.x < 0) {
		if (axis.x > 0)
		{
			useDecelerateX = true;
		}
		else {
			useDecelerateX = false;
		}
	}

	if (velocity.y > 0)
	{
		if (axis.y < 0)
		{
			useDecelerateY = true;
		}
		else {
			useDecelerateY = false;
		}
	}
	else
	if (velocity.y < 0)
	{
		if (axis.y > 0)
		{
			useDecelerateY = true;
		}
		else {
			useDecelerateY = false;
		}
	}






	



	
   
	if (velocity.x > -velXLimit &&
		velocity.x < velXLimit)
	{
		

		if (velocity.x > 0 && axis.x < 0)
		{
			//velocity.x += axis.x * moveOppositeAcceleration * dt;
			velocity.x = 0;
			velocity.x += axis.x * speed * dt;
		}
		else if (velocity.x > 0 && axis.x > 0)
		{
			velocity.x += axis.x * speed * dt;
		}
		else 
		if (velocity.x < 0 && axis.x > 0)
		{
			//velocity.x += axis.x * moveOppositeAcceleration * dt;
			velocity.x = 0;
			velocity.x += axis.x * speed * dt;
		}
		else if (velocity.x < 0 && axis.x < 0)
		{
			velocity.x += axis.x * speed * dt;
		} else {
			velocity.x += axis.x * speed * dt;
		}

		//velocity.x += axis.x * speed * dt;


	}

	if (velocity.y > -velYLimit &&
		velocity.y < velYLimit)
	{
		if (velocity.y > 0 && axis.y < 0)
		{
			//velocity.y += axis.y * moveOppositeAcceleration * dt;
			velocity.y = 0;
			velocity.y += axis.y * speed * dt;
		}
		else if (velocity.y > 0 && axis.y > 0)
		{
			velocity.y += axis.y * speed * dt;
			
		}
		else
			if (velocity.y < 0 && axis.y > 0)
			{
				//velocity.y += axis.y * moveOppositeAcceleration * dt;
				velocity.y = 0;
				velocity.y += axis.y * speed * dt;
				
			}
			else if (velocity.y < 0 && axis.y < 0)
			{
				velocity.y += axis.y * speed * dt;
				
			}
			else {
				velocity.y += axis.y * speed * dt;
			}

	}

	modelMatChanged = true;


	if (!lockLookDir)
	{
		float xMag = abs(axis.x) * mag;

		float yMag = abs(axis.y) * mag;

		glm::vec2 xyMag = axis * mag;

		chooseState(xyMag);
	}

	
	
	
}

void Actor::chooseState(glm::vec2 xyMag)
{
	if (xyMag.x > 0.01f)
	{
		if (abs(xyMag.x) >= abs(xyMag.y))
		{
			aState = rightState;
		}

	}

	if (xyMag.x < -0.01f)
	{
		if (abs(xyMag.x) >= abs(xyMag.y))
		{
			aState = leftState;
		}
	}

	if (xyMag.y > 0.01f)
	{
		if (abs(xyMag.y) > abs(xyMag.x))
		{
			aState = downState;
		}
	}

	if (xyMag.y < -0.01f)
	{
		if (abs(xyMag.y) > abs(xyMag.x))
		{
			aState = upState;
		}
	}
}

void Actor::decelerate(glm::vec2 axis, float dt)
{
	velocity += glm::vec3(axis - speed * dt, 0);
}

void Actor::jump(float dt)
{
	velocity.y -= 270.f;
	
}

void Actor::hitStaticObject(glm::vec3 colNorm)
{
	glm::vec3 normV = velocity * colNorm;

	if (colNorm.x > 0)
	{
		velocity.x -= normV.x;
	}
	else {
		velocity.x += normV.x;
	}

	if (colNorm.y > 0)
	{
		velocity.y -= normV.y;
	}
	else {
		velocity.y += normV.y;
	}
}

void Actor::hitTile(glm::vec3 colNorm, glm::vec3 tangent, glm::vec3 frictionVel, float dt)
{
	


	glm::vec3 normV = velocity * colNorm;

	glm::vec3 dtFriction = frictionVel *dt;



	//printf("Current velocity X: %f \n", velocity.x);
//	printf("Velocity X friction wants to take: %f \n", frictionVel.x);

	float tmpAccelX = 0;

	if (colNorm.x > 0)
	{
		velocity.x -= normV.x;
	}
	else {
		velocity.x += normV.x;
	}
	
	if (colNorm.y > 0)
	{
		velocity.y -= normV.y;
	}
	else {
		velocity.y += normV.y;
	}
}



void Actor::hitTileFriction(glm::vec3 tangent, glm::vec3 frictionVel, float dt)
{

	glm::vec3 dtFriction = frictionVel  *dt;


	float tmpAccelX = 0;
	if (!moving)
	{

		if (tangent.x > 0)
		{
			tmpAccelX -= dtFriction.x;
			velocity.x += tmpAccelX;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}

		}
		else {
			tmpAccelX -= dtFriction.x;
			velocity.x -= tmpAccelX;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
	}


}



glm::vec2 Actor::getTextureUVOffset()
{
	return currentAnimation->getCurrentFrame()->getFramePos();
}
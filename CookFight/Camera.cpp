#include "Camera.h"

Camera::Camera() : pos(glm::vec3(0)), baseMat(glm::mat4(1)), camMatrix(glm::mat4(1)), rotPitch(0), rotYaw(0), rotRoll(0), camScale(glm::vec3(1))
{
	pos.z = 0;
	origin = pos;
	newCamScale = camScale;
	updateCameraMatrix();
}

Camera::~Camera()
{

}

void Camera::update(float dt)
{
	


}

void Camera::updateCameraMatrix()
{
	glm::mat4 mm = glm::mat4(1.0);

	/*glm::vec3 newPos = pos;
	glm::vec3 f = glm::vec3(pos.x - origin.x/2, pos.y - origin.y/2, 0);
	glm::vec3  g = (1.f - newCamScale / camScale);

	newPos -= f*(1.f - newCamScale / camScale);

	camScale = newCamScale;

	newPos = glm::vec3(round(newPos.x), round(newPos.y), 0);
	pos = newPos;*/


	glm::vec3 newPos;
	
	/*if ((camScale.x > 1 &&
		camScale.y > 1)||
		(camScale.x < 1 &&
			camScale.y < 1))
	{
		newPos = pos;
	}
	else */
	{
		newPos = glm::vec3(round(pos.x), round(pos.y), 0);
	}


	glm::vec3 tmpTrans = glm::vec3(round(dimens.x / 2), round(dimens.y / 2), 0);
	
	mm = glm::translate(mm, tmpTrans);
	mm = glm::scale(mm, camScale);
	mm = glm::translate(mm, newPos - tmpTrans);
	//mm = glm::translate(mm, -pos);

	


	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	


	camMatrix = mm;



}

void Camera::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		pos.x += p.x;
		pos.y += p.y;
	}
	else {
		pos.x = p.x;
		pos.y = p.y;
	}



	updateCameraMatrix();
}

glm::vec3 Camera::getPosition()
{
	return pos;
}

void Camera::setYaw(float rot, bool add)
{
	if (add)
	{
		rotYaw += rot;
	}
	else {
		rotYaw = rot;
	}
	
}

void Camera::setPitch(float rot, bool add)
{
	if (add)
	{
		rotPitch += rot;
	}
	else {
		rotPitch = rot;
	}
	
}

void Camera::setRoll(float rot, bool add)
{
	if (add)
	{
		rotRoll += rot;
	}
	else {
		rotRoll = rot;
	}

}

void Camera::setCentrePosition(glm::vec3 p)
{
	/*pos = p - (dimens / 2.f);
	updateCameraMatrix();*/
}

glm::vec3 Camera::getCentrePosition()
{
	return pos;// +(dimens / 2.f);
}



void Camera::setScale(glm::vec3 s, bool add)
{
	if (add)
	{
		camScale += s;
	}
	else {
		camScale = s;
	}
	updateCameraMatrix();
}


void Camera::setDimensions(glm::vec2 d)
{
	dimens = d;
}

glm::vec2 Camera::getCurrentDimensions()
{
	glm::vec3 d = glm::vec3(dimens.x, dimens.y, 0) / (camScale*2.f);
	glm::vec2 d2 = glm::vec2(d.x, d.y);
	return d2;
}
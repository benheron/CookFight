#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>


class Camera
{
public:
	Camera();
	~Camera();

	void setPosition(glm::vec3 p, bool add = false);
	glm::vec3 getPosition();

	glm::mat4 getCamMatrix() { return camMatrix; }

	void update(float dt);


	void updateCameraMatrix();

	void setCentrePosition(glm::vec3 p);

	glm::vec3 getCentrePosition();

	///rotate across x axis
	void setYaw(float rot, bool add);
	///rotate across y axis
	void setPitch(float rot, bool add);
	///rotate across z axis
	void setRoll(float rot, bool add);

	void setScale(glm::vec3 s, bool add);


	void setOrigin(glm::vec3 o) { origin = o; }

	void setDimensions(glm::vec2 d);
	glm::vec2 getDimensions() { return dimens; }

	glm::vec2 getCurrentDimensions();


private:
	glm::vec3 pos;

	glm::vec2 dimens;

	glm::mat4 baseMat;
	glm::mat4 camMatrix;



	//rotation
	///x axis rotation
	float rotPitch;
	///y axis rotation
	float rotYaw;
	///z-axis rotation
	float rotRoll;


	glm::vec3 newCamScale;
	glm::vec3 camScale;

	glm::vec3 origin;
	


};
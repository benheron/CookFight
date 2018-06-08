#include "Gamepad.h"

Gamepad::Gamepad()
{
	buttons["a"] = false;
	buttons["b"] = false;
	buttons["x"] = false;
	buttons["y"] = false;

	buttons["lb"] = false;
	buttons["rb"] = false;
	buttons["lt"] = false;
	buttons["rt"] = false;

	buttons["leftThumb"] = false;
	buttons["rightThumb"] = false;

	buttons["dUp"] = false;
	buttons["dDown"] = false;
	buttons["dLeft"] = false;
	buttons["dRight"] = false;
	buttons["start"] = false;
	buttons["select"] = false;



	trigger["left"] = 0.0f;
	trigger["right"] = 0.0f;


	leftStick.x = 0;
	leftStick.y = 0;

	rightStick.x = 0;
	rightStick.y = 0;


	deadZone = 5800.f;





	buttonsPress["a"] = 0;
	buttonsPress["b"] = 0;
	buttonsPress["x"] = 0;
	buttonsPress["y"] = 0;

	buttonsPress["lb"] = 0;
	buttonsPress["rb"] = 0;
	buttonsPress["lt"] = 0;
	buttonsPress["rt"] = 0;

	buttonsPress["leftThumb"] = 0;
	buttonsPress["rightThumb"] = 0;

	buttonsPress["dUp"] = 0;
	buttonsPress["dDown"] = 0;
	buttonsPress["dLeft"] = 0;
	buttonsPress["dRight"] = 0;
	buttonsPress["start"] = 0;
	buttonsPress["select"] = 0;








}

Gamepad::~Gamepad()
{

}

void Gamepad::setThumb(float xval, float yval, int type) {
	if (type == 0)
	{
		leftStick.x = xval;
		leftStick.y = yval;
	}
	else if (type == 1)
	{
		rightStick.x = xval;
		rightStick.y = yval;
	}
}

StickVal Gamepad::getLeftStick(bool ignoreDeadZone)
{ 
	if (!ignoreDeadZone)
	{
		if (leftStick.x < deadZone &&
			leftStick.x > -deadZone)
		{
			leftStick.x = 0;
		}

		if (leftStick.y < deadZone &&
			leftStick.y > -deadZone)
		{
			leftStick.y = 0;
		}
	}
	




	return leftStick;
}

float Gamepad::getMagnitude()
{
	StickVal sv = getLeftStick();

	int maxMinDead = STICK_MAX_POSITIVE - deadZone;
	int minMinDead = STICK_MAX_NEGATIVE + deadZone;

	if (sv.x > 0)
	{
		sv.x -= deadZone;
		sv.x /= maxMinDead;
	}
	else if (sv.x < 0)
	{
		sv.x += deadZone;
		sv.x /= minMinDead;
	}


	if (sv.y > 0)
	{
		sv.y -= deadZone;
		sv.y /= maxMinDead;
	}
	else if (sv.y < 0)
	{
		sv.y += deadZone;
		sv.y /= minMinDead;
	}

	float m = sv.x + sv.y;

	if (m > 1)
	{
		m = 1;
	}
	else if (m < -1)
	{
		m = -1;
	}
	return m;
}

StickVal Gamepad::getRightStick()
{ 
	return rightStick; 
}

bool Gamepad::buttonPress(std::string k)
{
	if (buttonsPress[k] == 1)
	{
		return true;
	}

	return false;
}

void Gamepad::setButtonDown(std::string k, bool d) {
	buttons[k] = d; 
	
	if (d)
	{
		buttonsPress[k] += 1;
	}
	else {
		buttonsPress[k] = 0;
	}
}


float Gamepad::getTriggerNormalised(std::string k)
{
	float triggerNormal = trigger[k] / STICK_MAX_POSITIVE;

	return triggerNormal;
}
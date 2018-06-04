#pragma once
#include <unordered_map>
struct StickVal {
	float x;
	float y;
};
class Gamepad {
public:
	Gamepad();
	~Gamepad();

	void setButtonDown(std::string k, bool d);

	bool buttonDown(std::string k) { return buttons[k]; }

	bool buttonPress(std::string k);

	void setTriggerValue(std::string k, float val) { trigger[k] = val; }

	float getTriggerValue(std::string k) { return trigger[k]; }

	void setThumb(float xval, float yval, int type);

	StickVal getLeftStick(bool ignoreDeadZone = false);

	float getMagnitude();

	StickVal getRightStick();

	
private:
	std::unordered_map<std::string, bool> buttons;

	std::unordered_map<std::string, int> buttonsPress;

	std::unordered_map<std::string, float> trigger;

	StickVal leftStick;
	StickVal rightStick;

	int deadZone;
	const int STICK_MAX_POSITIVE = 32767;
	const int STICK_MAX_NEGATIVE = -32768;
};
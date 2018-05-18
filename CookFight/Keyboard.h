#pragma once
#include <unordered_map>

class KeyboardManager {
public:
	/**
	@brief Manages the keypresses
	*/
	KeyboardManager();
	~KeyboardManager();


	void update();

	/**
	@brief Returns whether is key is down or not
	@returns The value of if a key is down
	*/
	void setKeyDown(std::string k, bool d);
	/**
	@brief Returns whether is key is down or not
	@returns The value of if a key is down
	*/
	bool keyDown(std::string k) { return keys[k]; }

	/**
	@brief Returns whether is key has been pressed
	@returns The value of if a key was pressed this frame
	*/
	bool keyPressed(std::string k);

private:
	///The key values true/false
	std::unordered_map<std::string, bool> keys;

	std::unordered_map<std::string, bool> keyPress;


};
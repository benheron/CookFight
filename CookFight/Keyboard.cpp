#include "Keyboard.h"

KeyboardManager::KeyboardManager()
{
	keys["a"] = false;
	keys["b"] = false;
	keys["c"] = false;
	keys["d"] = false;
	keys["e"] = false;
	keys["f"] = false;
	keys["g"] = false;
	keys["h"] = false;
	keys["i"] = false;
	keys["j"] = false;
	keys["k"] = false;
	keys["l"] = false;
	keys["m"] = false;
	keys["n"] = false;
	keys["o"] = false;
	keys["p"] = false;
	keys["q"] = false;
	keys["r"] = false;
	keys["s"] = false;
	keys["t"] = false;
	keys["u"] = false;
	keys["v"] = false;
	keys["x"] = false;
	keys["y"] = false;
	keys["z"] = false;
	keys["shift"] = false;
	keys["ctrl"] = false; 
	keys["up"] = false;
	keys["down"] = false;
	keys["left"] = false;
	keys["right"] = false;
	keys["enter"] = false;
	keys["space"] = false;
	keys["esc"] = false;
	keys["0"] = false;
	keys["1"] = false;
	keys["2"] = false;
	keys["3"] = false;
	keys["4"] = false;
	keys["5"] = false;
	keys["6"] = false;
	keys["7"] = false;
	keys["8"] = false;
	keys["9"] = false;


	keyPress["a"] = false;
	keyPress["b"] = false;
	keyPress["c"] = false;
	keyPress["d"] = false;
	keyPress["e"] = false;
	keyPress["f"] = false;
	keyPress["g"] = false;
	keyPress["h"] = false;
	keyPress["i"] = false;
	keyPress["j"] = false;
	keyPress["k"] = false;
	keyPress["l"] = false;
	keyPress["m"] = false;
	keyPress["n"] = false;
	keyPress["o"] = false;
	keyPress["p"] = false;
	keyPress["q"] = false;
	keyPress["r"] = false;
	keyPress["s"] = false;
	keyPress["t"] = false;
	keyPress["u"] = false;
	keyPress["v"] = false;
	keyPress["x"] = false;
	keyPress["y"] = false;
	keyPress["z"] = false;
	keyPress["shift"] = false;
	keyPress["ctrl"] = false;
	keyPress["up"] = false;
	keyPress["down"] = false;
	keyPress["left"] = false;
	keyPress["right"] = false;
	keyPress["enter"] = false;
	keyPress["space"] = false;
	keyPress["esc"] = false;
	keyPress["0"] = false;
	keyPress["1"] = false;
	keyPress["2"] = false;
	keyPress["3"] = false;
	keyPress["4"] = false;
	keyPress["5"] = false;
	keyPress["6"] = false;
	keyPress["7"] = false;
	keyPress["8"] = false;
	keyPress["9"] = false;
}

KeyboardManager::~KeyboardManager()
{

}


void KeyboardManager::setKeyDown(std::string k, bool d) {
	if (d)
	{
		if (!keys[k])
		{
			keyPress[k] = true;
		//	printf("Keypress down %s \n", k.c_str());
		}
		else {
			keyPress[k] = false;
			//printf("Keypress up %s \n", k.c_str());
		}
	}
	else {
		keyPress[k] = false;
		//printf("Keypress up %s \n", k.c_str());
	}

	
	keys[k] = d;
	if (keyPress[k])
	{
		//printf("Keypress down %s \n", k.c_str());
	}
}


bool KeyboardManager::keyPressed(std::string k)
{ 
	return keyPress[k]; 
}
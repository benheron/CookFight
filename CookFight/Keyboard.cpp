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


	keyPress["a"] = 0;
	keyPress["b"] = 0;
	keyPress["c"] = 0;
	keyPress["d"] = 0;
	keyPress["e"] = 0;
	keyPress["f"] = 0;
	keyPress["g"] = 0;
	keyPress["h"] = 0;
	keyPress["i"] = 0;
	keyPress["j"] = 0;
	keyPress["k"] = 0;
	keyPress["l"] = 0;
	keyPress["m"] = 0;
	keyPress["n"] = 0;
	keyPress["o"] = 0;
	keyPress["p"] = 0;
	keyPress["q"] = 0;
	keyPress["r"] = 0;
	keyPress["s"] = 0;
	keyPress["t"] = 0;
	keyPress["u"] = 0;
	keyPress["v"] = 0;
	keyPress["x"] = 0;
	keyPress["y"] = 0;
	keyPress["z"] = 0;
	keyPress["shift"] = 0;
	keyPress["ctrl"] = 0;
	keyPress["up"] = 0;
	keyPress["down"] = 0;
	keyPress["left"] = 0;
	keyPress["right"] = 0;
	keyPress["enter"] = 0;
	keyPress["space"] = 0;
	keyPress["esc"] = 0;
	keyPress["0"] = 0;
	keyPress["1"] = 0;
	keyPress["2"] = 0;
	keyPress["3"] = 0;
	keyPress["4"] = 0;
	keyPress["5"] = 0;
	keyPress["6"] = 0;
	keyPress["7"] = 0;
	keyPress["8"] = 0;
	keyPress["9"] = 0;
}

KeyboardManager::~KeyboardManager()
{

}


void KeyboardManager::setKeyDown(std::string k, bool d) 
{
	keys[k] = d;

	if (d)
	{
		//keyPress[k] += 1;
	}
	else {
		keyPress[k] = 0;
	}
}


bool KeyboardManager::keyPressed(std::string k)
{ 
	if (keyPress[k] == 1)
	{
		return true;
	}

	return false;
}

void KeyboardManager::update()
{
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		if (it->second)
		{
			keyPress[it->first]++;
		}
	}
}
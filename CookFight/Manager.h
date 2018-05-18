#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

class Manager {
public:
	Manager();
	~Manager();

	virtual void loadData(std::string filePath) = 0;

protected:


};
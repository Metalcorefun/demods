#pragma once

#include "Class.h"
#include <string>
#include <vector>

using namespace std;

class DSClass
{
public:
	static int classCount;
	DSClass() {};
	//DSClass(string name);
	DSClass(string name, string description);
	DSClass(string id, string name, string description);
	~DSClass();
	string getID();
	string getName();
	string getDescription();
	void setName(string name);
	void setDescription(string description);
private:
	string id_, name_, description_;
};
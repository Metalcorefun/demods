#pragma once

#include <string>
#include <vector>

using namespace std;

class DSAttribute
{
public:
	static int attribCount;
	DSAttribute() {};
	DSAttribute(string name, string type, string description);
	DSAttribute(string id, string name, string type, string description);
	~DSAttribute();
	string getID();
	string getName();
	string getType();
	string getDescription();
	void setName(string name);
	void setType(string type);
	void setDescription(string description);
private:
	string id_, name_, type_, description_;
};
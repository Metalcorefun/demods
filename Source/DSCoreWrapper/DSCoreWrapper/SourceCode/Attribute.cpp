#pragma once
#include "Attribute.h"
#include <iostream>
#include <vector>

using namespace std;

DSAttribute::DSAttribute(string name, string type, string description)
{
	attribCount++;
	id_ = "attr" + to_string(attribCount);
	name_ = name;
	type_ = type;
	description_ = description;
};
DSAttribute::DSAttribute(string id, string name, string type, string description)
{
	if (id.length() == 5)
		attribCount = stoi(id.substr(id.length() - 1, 1));
	else if (id.length() == 6)
		attribCount = stoi(id.substr(id.length() - 2, 2));
	id_ = id;
	name_ = name;
	type_ = type;
	description_ = description;
};
DSAttribute::~DSAttribute()
{
	id_.clear();
	name_.clear();
	type_.clear();
};

string DSAttribute::getID()
{
	return id_;
}
string DSAttribute::getName()
{
	return name_;
}
string DSAttribute::getType()
{
	return type_;
}
string DSAttribute::getDescription()
{
	return description_;
}
void DSAttribute::setName(string name)
{
	name_ = name;
}
void DSAttribute::setType(string type)
{
	type_ = type;
}
void DSAttribute::setDescription(string description)
{
	description_ = description;
}

#pragma once
#include "Class.h"
#include <iostream>
#include <vector>

using namespace std;
DSClass::DSClass(string name, string description)
{
	classCount++;
	id_ = "c" + to_string(classCount);
	name_ = name;
	description_ = description_;
};
DSClass::DSClass(string id, string name, string description)
{
	if (id.length() == 2)
		classCount = stoi(id.substr(id.length() - 1, 1));
	else if (id.length() == 3)
		classCount = stoi(id.substr(id.length() - 2, 2));
	id_ = id;
	name_ = name;
	description_ = description;
}
DSClass::~DSClass()
{
	id_.clear();
	name_.clear();
};
string DSClass::getID()
{
	return id_;
}
string DSClass::getName()
{
	return name_;
}
string DSClass::getDescription()
{
	return description_;
}
void DSClass::setName(string name)
{
	name_ = name;
}
void DSClass::setDescription(string description)
{
	description_ = description;
}
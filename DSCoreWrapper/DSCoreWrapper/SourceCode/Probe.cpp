#pragma once
#include "Attribute.h"
#include "Class.h"
#include "Probe.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

DSProbe::DSProbe(vector<AttribValue> attribValues, vector<ClassMemFunc> classMemFuncs)
{
	attribValues_ = attribValues;
	classMemFuncs_ = classMemFuncs;
}
DSProbe::DSProbe(vector <reference_wrapper<DSAttribute>> attributes, vector<reference_wrapper<DSClass>> classes, string* values_a, double* values_c)
{

	AttribValue a;
	ClassMemFunc c;
	for (int i = 0; i < attributes.size(); i++)
	{
		a.attribPtr = &(attributes[i].get());
		a.value = values_a[i];
		attribValues_.push_back(a);
	}

	for (int i = 0; i < classes.size(); i++)
	{
		c.classPtr = &(classes[i].get());
		c.mem_func = values_c[i];
		classMemFuncs_.push_back(c);
	}
}
DSProbe::~DSProbe()
{
	attribValues_.clear();
	classMemFuncs_.clear();
}
void DSProbe::removeAttribute(DSAttribute& attribute)
{
	for (int i = 0; i < attribValues_.size(); i++)
	{
		if (attribValues_[i].attribPtr == &attribute)
		{
			attribValues_.erase(attribValues_.begin() + i);
		}
	}
}
void DSProbe::removeClass(DSClass& Class)
{
	for (int i = 0; i < classMemFuncs_.size(); i++)
	{
		if (classMemFuncs_[i].classPtr == &Class)
		{
			classMemFuncs_.erase(classMemFuncs_.begin() + i);
		}
	}
}
void DSProbe::addAttribute(DSAttribute& attribute)
{
	AttribValue a;
	a.attribPtr = &attribute;
	a.value = " ";
	attribValues_.emplace_back(a);
}
void DSProbe::addClass(DSClass& Class)
{
	ClassMemFunc c;
	c.classPtr = &Class;
	c.mem_func = 0.0;
	classMemFuncs_.emplace_back(c);
}
vector <AttribValue>& DSProbe::getAttribValues()
{
	return attribValues_;
}
vector <ClassMemFunc>& DSProbe::getClassMemFuncs()
{
	return classMemFuncs_;
}
void DSProbe::setAttribValues(vector <AttribValue> values)
{
	attribValues_ = values;
}
void DSProbe::setClassMemFuncs(vector <ClassMemFunc> mem_funcs)
{
	classMemFuncs_ = mem_funcs;
}
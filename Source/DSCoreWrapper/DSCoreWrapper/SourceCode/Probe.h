#pragma once

#include "Attribute.h"
#include "Class.h"
#include "Probe.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct AttribValue
{
	DSAttribute* attribPtr;
	string value;
};

struct ClassMemFunc
{
	DSClass* classPtr;
	double mem_func;
};

class DSProbe //один опыт из обучающей выборки
{
public:
	DSProbe() {};
	DSProbe(vector<AttribValue> attribValues, vector<ClassMemFunc> classMemFuncs);
	DSProbe(vector<reference_wrapper<DSAttribute>> attributes, vector<reference_wrapper<DSClass>> classes, string* attribValues, double* classValues);
	~DSProbe();
	void removeAttribute(DSAttribute& attribute);
	void removeClass(DSClass& Class);
	void addAttribute(DSAttribute& attribute);
	void addClass(DSClass& Class);
	vector <AttribValue>& getAttribValues();
	vector <ClassMemFunc>& getClassMemFuncs();
	void setAttribValues(vector <AttribValue> values);
	void setClassMemFuncs(vector <ClassMemFunc> mem_funcs);
private:
	vector <AttribValue> attribValues_;
	vector <ClassMemFunc> classMemFuncs_;
};
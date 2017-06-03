#pragma once

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "Attribute.h"
#include "Class.h"
#include "Probe.h"
#include "Classifier.h"
#include "COMExecutor.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class DSHierarchy
{
public:
	//singleton
	static DSHierarchy& Instance();
	//
	void clear();
	//save/load
	bool load(string fileName);
	bool save(string fileName);
	//add
	void addAttribute(DSAttribute attribute);
	void addClass(DSClass Class);
	void addClassifier(DSClassifier classifier);
	//get
	vector <DSAttribute>& getAttributes();
	vector <DSClass>& getClasses();
	vector <DSClassifier>& getClassifiers();
	//remove
	void removeAttribute(string id);
	void removeClass(string id);
	void removeClassifier(string id);
	//find
	DSAttribute& findAttribute(string id);
	DSClass& findClass(string id);
	DSClassifier& findClassifier(string id);
	//apex(entry) point
	bool apexPointExists();
	int getApexPoint();
	void setApexPoint(string id, bool value);
	//classify
	void sortClassifiers();
	void classify();
	//COM
	void com_sendData();
	bool com_learn();
	void com_saveFOV(string filePath);
	void com_saveFSC(string filePath);
private:
	DSHierarchy();
	~DSHierarchy();
	DSHierarchy(DSHierarchy const&) = delete;
	DSHierarchy& operator = (DSHierarchy const&) = delete;

	vector <DSAttribute> attributes_;
	vector <DSClass> classes_;
	vector <DSClassifier> classifiers_;
	COMExecutor *connector;
};

#endif
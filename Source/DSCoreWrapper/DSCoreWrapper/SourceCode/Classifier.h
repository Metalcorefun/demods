#pragma once

#include "Attribute.h"
#include "Class.h"
#include "Probe.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class DSClassifier
{
public:
	static int classifierCount;
	DSClassifier();
	DSClassifier(string name);
	DSClassifier(string id, string name);
	~DSClassifier();
	//add
	void addAttribute(DSAttribute& attribute);
	void addClass(DSClass& Class);
	void addChild(DSClassifier& classifier);
	void setBaseObject(string* values_a);
	void setBaseObject(vector <AttribValue> base_object);
	void toTrainingSet(string* values_a, double* values_c);
	void toTrainingSet(DSProbe probe);
	//remove
	void removeAttribute(string id);
	void removeClass(string id);
	void removeChild(string id);
	void removeTrainingSet();
	//get
	int getLevel();
	string getID();
	string getName();
	string getType();
	vector <reference_wrapper<DSAttribute>> getAttributes();
	vector <reference_wrapper<DSClass>> getClasses();
	vector <reference_wrapper<DSClassifier>> getChilds();
	vector <DSProbe>& getTrainingSet();
	vector <AttribValue>& getBaseObject();
	//set
	void setName(string name);
	void setType(string type);
	void setLevel(int level);
	//update references
	void updateAttributesReferences(vector <DSAttribute> &attributes, int index);
	void updateClassesReferences(vector <DSClass> &classes, int index);
	void updateClassifiersReferences(vector <DSClassifier> &classifiers, int index);
	void classify();
	bool operator<(const DSClassifier& cl) const { return level_ < cl.level_; }
	bool isSent();
	void send();
private:
	string id_, name_, type_;
	int level_;
	bool is_sent_;
	vector <reference_wrapper<DSAttribute>> attributes_;
	vector <reference_wrapper<DSClass>> classes_;
	vector <reference_wrapper<DSClassifier>> childs_;
	vector <DSProbe> trainingSet_;
	vector <AttribValue> baseObject_;
};
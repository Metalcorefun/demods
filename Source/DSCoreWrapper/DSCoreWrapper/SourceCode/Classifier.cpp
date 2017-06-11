#pragma once 

#include "Classifier.h"
#include "Attribute.h"
#include "Class.h"
#include "Probe.h"

#include <vector>
#include <iostream>

using namespace std;

//init
DSClassifier::DSClassifier()
{
	level_ = 1;
	is_sent_ = false;
}
DSClassifier::DSClassifier(string name)
{
	classifierCount++;
	id_ = "cl" + to_string(classifierCount);
	name_ = name;
	level_ = 1;
	is_sent_ = false;
}
DSClassifier::DSClassifier(string id, string name)
{
	id_ = id;
	if (id.length() == 3)
		classifierCount = stoi(id.substr(id.length() - 1, 1));
	else if (id.length() == 4)
		classifierCount = stoi(id.substr(id.length() - 2, 2));
	name_ = name;
	level_ = 1;
	is_sent_ = false;
}
DSClassifier::~DSClassifier()
{
	id_.clear(); name_.clear();
	attributes_.clear();
	classes_.clear();
	trainingSet_.clear();
	baseObject_.clear();
}
//get
int DSClassifier::getLevel()
{
	return level_;
}
string DSClassifier::getID()
{
	return id_;
}
string DSClassifier::getName()
{
	return name_;
}
vector <reference_wrapper<DSAttribute>> DSClassifier::getAttributes()
{
	return attributes_;
}
vector <reference_wrapper<DSClass>> DSClassifier::getClasses()
{
	return classes_;
}
vector <reference_wrapper<DSClassifier>> DSClassifier::getChilds()
{
	return childs_;
}
vector <DSProbe>& DSClassifier::getTrainingSet()
{
	return trainingSet_;
}
vector <AttribValue>& DSClassifier::getBaseObject()
{
	return baseObject_;
}
string DSClassifier::getType()
{
	return type_;
}
//set
void DSClassifier::setName(string name)
{
	name_ = name;
}
void DSClassifier::setType(string type)
{
	type_ = type;
}
void DSClassifier::setLevel(int level)
{
	level_ = level;
}

//add
void DSClassifier::addAttribute(DSAttribute& attribute)
{
	attributes_.push_back(attribute);
	for (int i = 0; i < trainingSet_.size(); i++)
	{
		trainingSet_[i].addAttribute(attribute);
	}
	AttribValue av;
	av.attribPtr = &attribute;
	av.value = " ";
	baseObject_.emplace_back(av);
}
void DSClassifier::addClass(DSClass& Class)
{
	classes_.push_back(Class);
	for (int i = 0; i < trainingSet_.size(); i++)
	{
		trainingSet_[i].addClass(Class);
	}
}
void DSClassifier::addChild(DSClassifier& classifier)
{
	childs_.push_back(classifier);
}
void DSClassifier::toTrainingSet(string* values_a, double* values_c)
{
	DSProbe probe(attributes_, classes_, values_a, values_c);
	trainingSet_.push_back(probe);
}
void DSClassifier::toTrainingSet(DSProbe probe)
{
	trainingSet_.push_back(probe);
}
void DSClassifier::setBaseObject(string* values_a)
{
	for (int i = 0; i < baseObject_.size(); i++) //формирование значений признаков для базового объекта
	{
		baseObject_[i].value = values_a[i];
	}
}
void DSClassifier::setBaseObject(vector <AttribValue> base_object)
{
	baseObject_ = base_object;
}
//remove
void DSClassifier::removeAttribute(string id)
{
	for (int i = 0; i < attributes_.size(); i++)
	{
		if (attributes_[i].get().getID() == id)
		{
			for (int j = 0; j < trainingSet_.size(); j++)
			{
				trainingSet_[j].removeAttribute(attributes_[i]);
			}
			for (int j = 0; j < baseObject_.size(); j++)
			{
				if (baseObject_[j].attribPtr->getID() == id)
				{
					baseObject_.erase(baseObject_.begin() + j);
				}
			}
			attributes_.erase(attributes_.begin() + i);
		}
	}
}
void DSClassifier::removeClass(string id)
{
	for (int i = 0; i < classes_.size(); i++)
	{
		if (classes_[i].get().getID() == id)
		{
			for (int j = 0; j < trainingSet_.size(); j++)
			{
				trainingSet_[j].removeClass(classes_[i]);
			}
			classes_.erase(classes_.begin() + i);
		}
	}
}
void DSClassifier::removeChild(string id)
{
	for (int i = 0; i < childs_.size(); i++)
	{
		if (childs_[i].get().getID() == id)
		{
			childs_.erase(childs_.begin() + i);
		}
	}
}
void DSClassifier::removeTrainingSet()
{
	trainingSet_.clear();
}
//update references
void DSClassifier::updateAttributesReferences(vector <DSAttribute> &attributes, int index)
{
	for (int i = index + 1; i < attributes.size(); i++)
	{
		for (int j = 0; j < attributes_.size(); j++)
		{
			if (attributes[i].getID() == attributes_[j].get().getID())
			{
				attributes_[j] = attributes[i - 1];
				for (int k = 0; k < trainingSet_.size(); k++)
				{
					getTrainingSet()[k].getAttribValues()[j].attribPtr = &(attributes[i - 1]);
				}
				baseObject_[j].attribPtr = &(attributes_[j].get());
			}
		}
	}
}
void DSClassifier::updateClassesReferences(vector <DSClass> &classes, int index)
{
	for (int i = index + 1; i < classes.size(); i++)
	{
		for (int j = 0; j < classes_.size(); j++)
		{
			if (classes[i].getID() == classes_[j].get().getID())
			{
				classes_[j] = classes[i - 1];
				for (int k = 0; k < trainingSet_.size(); k++)
				{
					getTrainingSet()[k].getClassMemFuncs()[j].classPtr = &(classes[i - 1]);
				}
			}
		}
	}
}
void DSClassifier::updateClassifiersReferences(vector <DSClassifier> &classifiers, int index)
{
	for (int i = index + 1; i < classifiers.size(); i++)
	{
		for (int j = 0; j < childs_.size(); j++)
		{
			if (classifiers[i].getID() == childs_[j].get().getID())
				childs_[j] = classifiers[i - 1];
		}
	}
}
//classifier
void DSClassifier::classify()
{
	if (!childs_.empty())
	{
		for (int i = 0; i < childs_.size(); i++)
			childs_[i].get().classify();
	}
	cout << id_ << " , classified." << endl;
	//DSModules& modules = DSModules::Instance(); //выуживаем ссылку на фасад и вызываем сам классификатор
	//modules.AC_ClassifyCall();
}
bool DSClassifier::isSent()
{
	return is_sent_;
}
void DSClassifier::send()
{
	is_sent_ = true;
}
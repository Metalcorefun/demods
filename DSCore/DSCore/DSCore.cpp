#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "DSCore.h"
#include "Resources/TinyXML2/tinyxml2.h"

using namespace std;


//---------------DSMODULES(FACADE)-------------------//
DSModules& DSModules::Instance()
{
	static DSModules instance;
	return instance;
};

//---------------DSATTRIBUTE-------------------//
//DSAttribute::DSAttribute(string name, string type)
//{
//	attribCount++;
//	id_ = "attr" + to_string(attribCount);
//	name_ = name;
//	type_ = type;
//};
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

//---------------DSCLASS-------------------//
//DSClass::DSClass(string name)
//{
//	classCount++;
//	id_ = "c" + to_string(classCount);
//	name_ = name;
//};
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
//---------------DSPROBE-------------------//
DSProbe::DSProbe(vector <reference_wrapper<DSAttribute>> attributes, vector<reference_wrapper<DSClass>> classes, int* values_a, int* values_c)
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
vector <AttribValue>& DSProbe::getAttribValues()
{
	return attribValues_;
}
vector <ClassMemFunc>& DSProbe::getClassMemFuncs()
{
	return classMemFuncs_;
}

//---------------DSCLASSIFIER-------------------//
//init
DSClassifier::DSClassifier()
{
	level_ = 1;
}
DSClassifier::DSClassifier(string name)
{
	classifierCount++;
	id_ = "cl" + to_string(classifierCount);
	name_ = name;	
	level_ = 1;
}
DSClassifier::DSClassifier(string id, string name)
{
	id_ = id;
	if(id.length() == 3)
		classifierCount = stoi(id.substr(id.length() - 1, 1));
	else if(id.length() == 4)
		classifierCount = stoi(id.substr(id.length() - 2, 2));
	name_ = name;
	level_ = 1;
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
bool DSClassifier::isApexPoint()
{
	return(apex_ ? true : false);
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
void DSClassifier::setApex(bool value)
{
	apex_ = value;
}

//add
void DSClassifier::addAttribute(DSAttribute& attribute)
{
	attributes_.push_back(attribute);
}
void DSClassifier::addClass(DSClass& Class)
{
	classes_.push_back(Class);
}
void DSClassifier::addChild(DSClassifier& classifier)
{
	childs_.push_back(classifier);
}
void DSClassifier::toTrainingSet(int* values_a, int* values_c)
{
	DSProbe p(attributes_, classes_, values_a, values_c);
	trainingSet_.push_back(p);
}
void DSClassifier::setBaseObject(int* values_a)
{
	AttribValue a;
	for (int i = 0; i < attributes_.size(); i++) //формирование значений признаков для базового объекта
	{
		a.attribPtr = &(attributes_[i].get());
		a.value = values_a[i];
		baseObject_.push_back(a);
	}
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
				if(baseObject_[j].attribPtr->getID() == id)
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

//---------------DSHIERARCHY-------------------//
//singleton
DSHierarchy& DSHierarchy::Instance()
{
	static DSHierarchy instance;
	return instance;
}
//init
DSHierarchy::DSHierarchy()
{
	attributes_.reserve(100);
	classes_.reserve(100);
	classifiers_.reserve(100);
}
DSHierarchy::~DSHierarchy()
{
	attributes_.clear();
	classes_.clear();
	classifiers_.clear();

}
//clear
void DSHierarchy::clear()
{
	classifiers_.clear();
	classes_.clear();
	attributes_.clear();
	resultsTable_.clear();
	DSAttribute::attribCount = 0;
	DSClass::classCount = 0;
	DSClassifier::classifierCount = 0;
}
//save/load
bool DSHierarchy::load(string fileName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName.c_str());
	try
	{
		if (!doc.Error())
		{
			tinyxml2::XMLElement *levelElement = doc.FirstChildElement("hierarchy")->FirstChildElement("attributes");//LEAK HERE!
			for (tinyxml2::XMLElement* child = levelElement->FirstChildElement("attribute"); child != NULL; child = child->NextSiblingElement())
			{
				DSAttribute a(child->Attribute("id"), child->FirstChildElement("attr_name")->GetText(), child->FirstChildElement("attr_type")->GetText(), child->FirstChildElement("description")->GetText());
				addAttribute(a);
			}
			levelElement = levelElement->NextSiblingElement();
			for (tinyxml2::XMLElement* child = levelElement->FirstChildElement("class"); child != NULL; child = child->NextSiblingElement())
			{
				DSClass c(child->Attribute("id"), child->FirstChildElement("class_title")->GetText(), child->FirstChildElement("description")->GetText());
				addClass(c);
			}
			levelElement = levelElement->NextSiblingElement();
			for (tinyxml2::XMLElement* child = levelElement->FirstChildElement("classifier"); child != NULL; child = child->NextSiblingElement())
			{
				DSClassifier cl(child->Attribute("id"), child->FirstChildElement("classifier_title")->GetText());
				cl.setType(child->Attribute("type"));
				cl.setLevel(stoi(child->Attribute("level")));
				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("classifier_attr_list")->FirstChildElement("attr_id"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					cl.addAttribute(findAttribute(child1->GetText()));
				}
				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("classifier_class_list")->FirstChildElement("class_id"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					cl.addClass(findClass(child1->GetText()));
				}
				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("training_set")->FirstChildElement("probe"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					int i = 0;
					int* values_a = new int[cl.getAttributes().size()], *values_c = new int[cl.getClasses().size()];
					for (tinyxml2::XMLElement* child2 = child1->FirstChildElement("attr_val"); child2 != NULL; child2 = child2->NextSiblingElement("attr_val"))
					{
						if (cl.getAttributes()[i].get().getID() == child2->FirstChildElement("attr_id")->GetText())
						{
							values_a[i] = stoi(child2->FirstChildElement("attr_value")->GetText());
						}
						i++;
					}
					i = 0;
					for (tinyxml2::XMLElement* child2 = child1->FirstChildElement("cls_pr"); child2 != NULL; child2 = child2->NextSiblingElement("cls_pr"))
					{
						if (cl.getClasses()[i].get().getID() == child2->FirstChildElement("class_id")->GetText())
						{
							values_c[i] = stoi(child2->FirstChildElement("class_mem")->GetText());
						}
						i++;
					}
					cl.toTrainingSet(values_a, values_c);
					delete[] values_a, values_c;
				}

				int i = 0;
				int* values_a = new int[cl.getAttributes().size()];
				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("base_object")->FirstChildElement("attr_val"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					if (cl.getAttributes()[i].get().getID() == child1->FirstChildElement("attr_id")->GetText())
					{
						values_a[i] = stoi(child1->FirstChildElement("attr_value")->GetText());
					}
					i++;
				}
				cl.setBaseObject(values_a);
				delete[] values_a;

				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("childs")->FirstChildElement("clsfr_id"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					cl.addChild(findClassifier(child1->GetText()));
				}
				addClassifier(cl);
			}
			doc.DeleteNode(levelElement);
			return true;
		}
		else return false;
	}
	catch (...)
	{
		return false;
	}
}
bool DSHierarchy::save(string fileName)
{
	try
	{
		sortClassifiers();
		tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
		doc->Parse("<?xml version=\"1.0\" encoding = \"UTF-8\"?>");
		tinyxml2::XMLNode *root = doc->InsertEndChild(doc->NewElement("hierarchy"));
		doc->FirstChildElement("hierarchy")->InsertEndChild(doc->NewElement("attributes"));
		tinyxml2::XMLElement* insert;
		for (int i = 0; i < attributes_.size(); i++)
		{
			insert = doc->NewElement("attribute");
			insert->SetAttribute("id", (attributes_[i].getID()).c_str());
			insert->InsertEndChild(doc->NewElement("attr_name"));
			insert->InsertEndChild(doc->NewElement("attr_type"));
			insert->InsertEndChild(doc->NewElement("description"));
			insert->FirstChildElement("attr_name")->SetText((attributes_[i].getName()).c_str());
			insert->FirstChildElement("attr_type")->SetText((attributes_[i].getType()).c_str());
			insert->FirstChildElement("description")->SetText((attributes_[i].getDescription()).c_str());
			doc->FirstChildElement("hierarchy")->FirstChildElement("attributes")->InsertEndChild(insert);
		}
		doc->FirstChildElement("hierarchy")->InsertEndChild(doc->NewElement("classes"));
		for (int i = 0; i < classes_.size(); i++)
		{
			insert = doc->NewElement("class");
			insert->SetAttribute("id", (classes_[i].getID()).c_str());
			insert->InsertEndChild(doc->NewElement("class_title"));
			insert->InsertEndChild(doc->NewElement("description"));
			insert->FirstChildElement("class_title")->SetText((classes_[i].getName()).c_str());
			insert->FirstChildElement("description")->SetText((classes_[i].getDescription()).c_str());
			doc->FirstChildElement("hierarchy")->FirstChildElement("classes")->InsertEndChild(insert);
		}
		doc->FirstChildElement("hierarchy")->InsertEndChild(doc->NewElement("classifiers"));
		for (int i = 0; i < classifiers_.size(); i++)
		{
			insert = doc->NewElement("classifier");
			insert->SetAttribute("id", (classifiers_[i].getID()).c_str());
			insert->SetAttribute("type", (classifiers_[i].getType()).c_str());
			insert->SetAttribute("level", (classifiers_[i].getLevel()));
			insert->InsertEndChild(doc->NewElement("classifier_title"));
			insert->InsertEndChild(doc->NewElement("classifier_attr_list"));
			insert->InsertEndChild(doc->NewElement("classifier_class_list"));
			insert->InsertEndChild(doc->NewElement("training_set"));
			insert->InsertEndChild(doc->NewElement("base_object"));
			insert->InsertEndChild(doc->NewElement("childs"));
			insert->FirstChildElement("classifier_title")->SetText((classifiers_[i].getName()).c_str());
			for (int j = 0; j < classifiers_[i].getAttributes().size(); j++)
			{
				insert->FirstChildElement("classifier_attr_list")->InsertEndChild(doc->NewElement("attr_id"));
				insert->FirstChildElement("classifier_attr_list")->LastChildElement("attr_id")->SetText(classifiers_[i].getAttributes()[j].get().getID().c_str());
			}
			for (int j = 0; j < classifiers_[i].getClasses().size(); j++)
			{
				insert->FirstChildElement("classifier_class_list")->InsertEndChild(doc->NewElement("class_id"));
				insert->FirstChildElement("classifier_class_list")->LastChildElement("class_id")->SetText(classifiers_[i].getClasses()[j].get().getID().c_str());
			}
			for (int j = 0; j < classifiers_[i].getTrainingSet().size(); j++)
			{
				insert->FirstChildElement("training_set")->InsertEndChild(doc->NewElement("probe"));
				for (int k = 0; k < classifiers_[i].getTrainingSet()[j].getAttribValues().size(); k++)
				{
					insert->FirstChildElement("training_set")->LastChildElement("probe")->InsertEndChild(doc->NewElement("attr_val"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("attr_val")->InsertEndChild(doc->NewElement("attr_id"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("attr_val")->FirstChildElement("attr_id")->SetText(classifiers_[i].getTrainingSet()[j].getAttribValues()[k].attribPtr->getID().c_str());
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("attr_val")->InsertEndChild(doc->NewElement("attr_value"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("attr_val")->FirstChildElement("attr_value")->SetText(classifiers_[i].getTrainingSet()[j].getAttribValues()[k].value);
				}
				for (int k = 0; k < classifiers_[i].getTrainingSet()[j].getClassMemFuncs().size(); k++)
				{
					insert->FirstChildElement("training_set")->LastChildElement("probe")->InsertEndChild(doc->NewElement("cls_pr"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("cls_pr")->InsertEndChild(doc->NewElement("class_id"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("cls_pr")->FirstChildElement("class_id")->SetText(classifiers_[i].getTrainingSet()[j].getClassMemFuncs()[k].classPtr->getID().c_str());
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("cls_pr")->InsertEndChild(doc->NewElement("class_mem"));
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("cls_pr")->FirstChildElement("class_mem")->SetText(classifiers_[i].getTrainingSet()[j].getClassMemFuncs()[k].mem_func);
				}
			}
			for (int j = 0; j < classifiers_[i].getBaseObject().size(); j++)
			{
				insert->FirstChildElement("base_object")->InsertEndChild(doc->NewElement("attr_val"));
				insert->FirstChildElement("base_object")->LastChildElement("attr_val")->InsertEndChild(doc->NewElement("attr_id"));
				insert->FirstChildElement("base_object")->LastChildElement("attr_val")->InsertEndChild(doc->NewElement("attr_value"));
				insert->FirstChildElement("base_object")->LastChildElement("attr_val")->FirstChildElement("attr_id")->SetText(classifiers_[i].getBaseObject()[j].attribPtr->getID().c_str());
				insert->FirstChildElement("base_object")->LastChildElement("attr_val")->FirstChildElement("attr_value")->SetText(classifiers_[i].getBaseObject()[j].value);
			}
			for (int j = 0; j < classifiers_[i].getChilds().size(); j++)
			{
				insert->FirstChildElement("childs")->InsertEndChild(doc->NewElement("clsfr_id"));
				insert->FirstChildElement("childs")->LastChildElement("clsfr_id")->SetText(classifiers_[i].getChilds()[j].get().getID().c_str());
			}
			doc->FirstChildElement("hierarchy")->FirstChildElement("classifiers")->InsertEndChild(insert);
		}
		doc->SaveFile(fileName.c_str());
		delete doc;
		return true;
	}
	catch (...)
	{
		return false;
	}
}
//add
void DSHierarchy::addAttribute(DSAttribute attribute)
{
	attributes_.push_back(attribute);
}
void DSHierarchy::addClass(DSClass Class)
{
	classes_.push_back(Class);
}
void DSHierarchy::addClassifier(DSClassifier classifier)
{
	classifiers_.emplace_back(classifier);
	initResultsTable(findClassifier(classifier.getID()));
}
void DSHierarchy::initResultsTable(DSClassifier& classifier)
{
	DSResults result_temp;
	result_temp.classifier = &classifier;
	for (int i = 0; i < classifier.getClasses().size(); i++)
	{
		ClassMemFunc class_temp;
		class_temp.classPtr = &(classifier.getClasses()[i].get());
		class_temp.mem_func = 0;
		result_temp.result.push_back(class_temp);
	}
	resultsTable_.emplace_back(result_temp);
}
//get
vector <DSAttribute>& DSHierarchy::getAttributes()
{
	return attributes_;
}
vector <DSClass>& DSHierarchy::getClasses()
{
	return classes_;
}
vector <DSClassifier>& DSHierarchy::getClassifiers()
{
	return classifiers_;
}
//remove
void DSHierarchy::removeAttribute(string id)
{
	for (int i = 0; i < attributes_.size(); i++)
	{
		if (attributes_[i].getID() == id)
		{
			for (int j = 0; j < classifiers_.size(); j++)
			{
				classifiers_[j].removeAttribute(id);
				classifiers_[j].updateAttributesReferences(attributes_,i);
			}
			attributes_.erase(attributes_.begin() + i);
		}
	}
}
void DSHierarchy::removeClass(string id)
{
	for (int i = 0; i < classes_.size(); i++)
	{
		if (classes_[i].getID() == id)
		{
			for (int j = 0; j < classifiers_.size(); j++)
			{
				classifiers_[j].removeClass(id);
				classifiers_[j].updateClassesReferences(classes_, i);
			}
			classes_.erase(classes_.begin() + i);
		}
	}
}
void DSHierarchy::removeClassifier(string id)
{
	for (int i = 0; i < classifiers_.size(); i++)
	{
		if (classifiers_[i].getID() == id)
		{
			for (int j = 0; j < classifiers_.size(); j++)
			{
				classifiers_[j].removeChild(id);
				classifiers_[j].updateClassifiersReferences(classifiers_, i);
			}
			classifiers_.erase(classifiers_.begin() + i);
		}
	}
}
//find
DSAttribute& DSHierarchy::findAttribute(string id)
{
	DSAttribute A;
	for (int i = 0; i < attributes_.size(); i++)
	{
		if (attributes_[i].getID() == id)
			return attributes_[i];
	}
	return A;
}
DSClass& DSHierarchy::findClass(string id)
{
	DSClass C;
	for (int i = 0; i < classes_.size(); i++)
	{
		if (classes_[i].getID() == id)
			return classes_[i];
	}
	return C;
}
DSClassifier& DSHierarchy::findClassifier(string id)
{
	DSClassifier C;
	for (int i = 0; i < classifiers_.size(); i++)
	{
		if (classifiers_[i].getID() == id)
			return classifiers_[i];
	}
	return C;
}
bool DSHierarchy::apexPointExists()
{
	for (int i = 0; i < classifiers_.size(); i++)
		if (classifiers_[i].isApexPoint())
			return true;
	return false;
}
int DSHierarchy::getApexPoint()
{
	for (int i = 0; i < classifiers_.size(); i++)
		if (classifiers_[i].isApexPoint())
			return i;
	return -1;
}
void DSHierarchy::setApexPoint(string id, bool value)
{
	DSClassifier& classifier = findClassifier(id);
	if ((apexPointExists() && !value) || (!apexPointExists() && value))
		classifier.setApex(value);
}
//classify
void DSHierarchy::sortClassifiers()
{
	sort(classifiers_.begin(), classifiers_.end());
}
void DSHierarchy::classify()
{
	if (getApexPoint() != -1)
	{
		classifiers_[getApexPoint()].classify();
	}
}


//--------------counters---------------//
int DSAttribute::attribCount = 0;
int DSClass::classCount = 0;
int DSClassifier::classifierCount = 0;
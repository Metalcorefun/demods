#include <iostream>
#include <string>
#include <vector>
#include "DSCore.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//---------------DSMODULES(FACADE)-------------------//
DSModules& DSModules::Instance()
{
	static DSModules instance;
	return instance;
};

//---------------DSATTRIBUTE-------------------//

DSAttribute::DSAttribute(string name, string type)
{
	attribCount++;
	id_ = "attr" + to_string(attribCount);
	name_ = name;
	type_ = type;
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

//---------------DSCLASS-------------------//

DSClass::DSClass(string name)
{
	classCount++;
	id_ = "c" + to_string(classCount);
	name_ = name;
};

DSClass::~DSClass()
{
	id_.clear();
	name_.clear();
};

string DSClass::getID()
{
	return id_;
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
		attribValues.push_back(a);
	}

	for (int i = 0; i < classes.size(); i++)
	{
		c.classPtr = &(classes[i].get());
		c.mem_func = values_c[i];
		classMemFuncs.push_back(c);
	}
}
DSProbe::~DSProbe()
{
	attribValues.clear();
	classMemFuncs.clear();
}

//---------------DSCLASSIFIER-------------------//

DSClassifier::DSClassifier(string name)
{
	classifierCount++;
	id_ = "cl" + to_string(classifierCount);
	name_ = name;	
}
int DSClassifier::getLevel()
{
	return level_;
}

string DSClassifier::getID()
{
	return id_;
}

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

vector <reference_wrapper<DSAttribute>> DSClassifier::getAttributes()
{
	return attributes_;
}

vector <reference_wrapper<DSClass>> DSClassifier::getClasses()
{
	return classes_;
}
void DSClassifier::classify()
{
	DSModules& modules = DSModules::Instance(); //выуживаем ссылку на фасад и вызываем сам классификатор
	modules.AC_ClassifyCall();
}
DSClassifier::~DSClassifier()
{
	id_.clear(); name_.clear();
	attributes_.clear();
	classes_.clear();
	trainingSet_.clear();
	baseObject_.clear();
}

//---------------DSHIERARCHY-------------------//
DSHierarchy& DSHierarchy::Instance()
{
	static DSHierarchy instance;
	return instance;
}

void DSHierarchy::load(char* fileName)
{
	XMLDocument doc;
	doc.LoadFile(fileName);
	if (!doc.Error())
	{	
		XMLElement *levelElement = doc.FirstChildElement("hierarchy")->FirstChildElement("attributes");
		for (XMLElement* child = levelElement->FirstChildElement("attribute"); child != NULL; child = child->NextSiblingElement())
		{
			DSAttribute a(child->FirstChildElement("attr_name")->GetText(), child->FirstChildElement("attr_type")->GetText());
			addAttribute(a);
		}
		levelElement = levelElement->NextSiblingElement();
		for (XMLElement* child = levelElement->FirstChildElement("class"); child != NULL; child = child->NextSiblingElement())
		{
			DSClass c(child->FirstChildElement("class_title")->GetText());
			addClass(c);
		}
		levelElement = levelElement->NextSiblingElement();
		for (XMLElement* child = levelElement->FirstChildElement("classifier"); child != NULL; child = child->NextSiblingElement())
		{
			DSClassifier cl(child->FirstChildElement("classifier_title")->GetText());
			for (XMLElement* child1 = child->FirstChildElement("classifier_attr_list")->FirstChildElement("attr_id"); child1 != NULL; child1 = child1->NextSiblingElement())
			{
				cl.addAttribute(findAttribute(child1->GetText()));
			}
			for (XMLElement* child1 = child->FirstChildElement("classifier_class_list")->FirstChildElement("class_id"); child1 != NULL; child1 = child1->NextSiblingElement())
			{
				cl.addClass(findClass(child1->GetText()));
			}
			for (XMLElement* child1 = child->FirstChildElement("training_set")->FirstChildElement("probe"); child1 != NULL; child1 = child1->NextSiblingElement())
			{
				int i = 0;
				int* values_a = new int[cl.getAttributes().size()], *values_c = new int[cl.getClasses().size()];
				for (XMLElement* child2 = child1->FirstChildElement("attr_val"); child2 != NULL; child2 = child2->NextSiblingElement("attr_val"))
				{
					if (cl.getAttributes()[i].get().getID() == child2->FirstChildElement("attr_id")->GetText())
					{
						values_a[i] = stoi(child2->FirstChildElement("attr_value")->GetText());
					}
					i++;
				}
				i = 0;
				for (XMLElement* child2 = child1->FirstChildElement("cls_pr"); child2 != NULL; child2 = child2->NextSiblingElement("cls_pr"))
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
			for (XMLElement* child1 = child->FirstChildElement("base_object")->FirstChildElement("attr_val"); child1 != NULL; child1 = child1->NextSiblingElement())
			{
				if (cl.getAttributes()[i].get().getID() == child1->FirstChildElement("attr_id")->GetText())
				{
					values_a[i] = stoi(child1->FirstChildElement("attr_value")->GetText());
				}
				i++;
			}
			cl.setBaseObject(values_a);
			delete[] values_a;

			for (XMLElement* child1 = child->FirstChildElement("childs")->FirstChildElement("clsfr_id"); child1 != NULL; child1 = child1->NextSiblingElement())
			{
				cl.addChild(findClassifier(child1->GetText()));
			}
			addClassifier(cl);
		}
	}
	else
	{
		throw "ERROR_READING_XML_FILE()";
	}
}

void DSHierarchy::save(char* fileName)
{
	XMLDocument doc;
	char* xml = "<?xml version=\"1.0\" encoding = \"UTF-8\"?>";
	doc.NewDeclaration(xml);
	doc.SaveFile(fileName);
}

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
	classifiers_.push_back(classifier);
}

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

void DSHierarchy::initResultsTable(DSClassifier classifier)
{
	DSResults result_temp;
	result_temp.classifier = &classifier;
	vector<reference_wrapper<DSClass>> classes_temp = classifier.getClasses();

	for (int i = 0; i < classes_temp.size(); i++)
	{
		ClassMemFunc class_temp;
		class_temp.classPtr = &(classes_temp[i].get());
		class_temp.mem_func = 0;
		result_temp.result.push_back(class_temp);
	}
	classes_temp.clear();
}

int DSAttribute::attribCount = 0;
int DSClass::classCount = 0;
int DSClassifier::classifierCount = 0;
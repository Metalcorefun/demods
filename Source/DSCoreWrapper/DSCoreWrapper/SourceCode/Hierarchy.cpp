#pragma once

#include "Attribute.h"
#include "Class.h"
#include "Probe.h"
#include "Classifier.h"
#include "Hierarchy.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Resources/TinyXML2/tinyxml2.h"

using namespace std;

DSHierarchy& DSHierarchy::Instance()
{
	static DSHierarchy instance;
	return instance;
}
//init
DSHierarchy::DSHierarchy()
{
	connector = new COMExecutor(*this);
	attributes_.reserve(100);
	classes_.reserve(100);
	classifiers_.reserve(100);
}
DSHierarchy::~DSHierarchy()
{
	delete connector;
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
				if (child->FirstChildElement("description")->GetText() != nullptr)
				{
					DSAttribute a(child->Attribute("id"), child->FirstChildElement("attr_name")->GetText(), child->FirstChildElement("attr_type")->GetText(), child->FirstChildElement("description")->GetText());
					addAttribute(a);
				}
				else
				{
					DSAttribute a(child->Attribute("id"), child->FirstChildElement("attr_name")->GetText(), child->FirstChildElement("attr_type")->GetText(), " ");
					addAttribute(a);
				}			
			}
			levelElement = levelElement->NextSiblingElement();
			for (tinyxml2::XMLElement* child = levelElement->FirstChildElement("class"); child != NULL; child = child->NextSiblingElement())
			{   
				if (child->FirstChildElement("description")->GetText() != nullptr)
				{
					DSClass c(child->Attribute("id"), child->FirstChildElement("class_title")->GetText(), child->FirstChildElement("description")->GetText());
					addClass(c);
				}
				else 
				{ 
					DSClass c(child->Attribute("id"), child->FirstChildElement("class_title")->GetText(), " ");
					addClass(c);
				}				
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
					string* values_a = new string[cl.getAttributes().size()]; double *values_c = new double[cl.getClasses().size()];
					for (tinyxml2::XMLElement* child2 = child1->FirstChildElement("attr_val"); child2 != NULL; child2 = child2->NextSiblingElement("attr_val"))
					{
						if (cl.getAttributes()[i].get().getID() == child2->FirstChildElement("attr_id")->GetText())
						{
							if (child2->FirstChildElement("attr_value")->GetText() != nullptr)
							{
								values_a[i] = child2->FirstChildElement("attr_value")->GetText();
							}
							else
							{
								values_a[i] = "  ";
							}
						}
						i++;
					}
					i = 0;
					for (tinyxml2::XMLElement* child2 = child1->FirstChildElement("cls_pr"); child2 != NULL; child2 = child2->NextSiblingElement("cls_pr"))
					{
						if (cl.getClasses()[i].get().getID() == child2->FirstChildElement("class_id")->GetText())
						{
							if (child2->FirstChildElement("class_mem")->GetText() != nullptr)
								values_c[i] = stod(child2->FirstChildElement("class_mem")->GetText());
							else
								values_c[i] = 0;
						}
						i++;
					}
					cl.toTrainingSet(values_a, values_c);
					delete[] values_a, values_c;
				}

				int i = 0;
				string* values_a = new string[cl.getAttributes().size()];
				for (tinyxml2::XMLElement* child1 = child->FirstChildElement("base_object")->FirstChildElement("attr_val"); child1 != NULL; child1 = child1->NextSiblingElement())
				{
					if (cl.getAttributes()[i].get().getID() == child1->FirstChildElement("attr_id")->GetText())
					{
						if (child1->FirstChildElement("attr_value")->GetText() != nullptr)
							values_a[i] = child1->FirstChildElement("attr_value")->GetText();
						else
							values_a[i] = "  ";
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
					insert->FirstChildElement("training_set")->LastChildElement("probe")->LastChildElement("attr_val")->FirstChildElement("attr_value")->SetText(classifiers_[i].getTrainingSet()[j].getAttribValues()[k].value.c_str());
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
				insert->FirstChildElement("base_object")->LastChildElement("attr_val")->FirstChildElement("attr_value")->SetText(classifiers_[i].getBaseObject()[j].value.c_str());
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
				classifiers_[j].updateAttributesReferences(attributes_, i);
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
//classify
void DSHierarchy::sortClassifiers()
{
	sort(classifiers_.begin(), classifiers_.end());
}
void DSHierarchy::sendAll()
{
	for (int i = 0; i < classifiers_.size(); i++)
		classifiers_[i].send();
}

//COM
void DSHierarchy::com_sendData()
{
	connector->sendDataToPressure();
}
bool DSHierarchy::com_learn()
{
	if(connector->learnPressure()) return true;
	else return false;
}
void DSHierarchy::com_saveFOV(string filePath)
{
	connector->savePressureFOV(filePath);
}
void DSHierarchy::com_saveFSC(string filePath)
{
	connector->savePressureFSC(filePath);
}
bool DSHierarchy::com_isreliable(DSClassifier classifier)
{
	return connector->ISReliable(classifier);
}
float DSHierarchy::com_tcriterion(DSClassifier classifier)
{
	return connector->TCriterion(classifier);
}
float DSHierarchy::com_tcriteriontable(DSClassifier classifier)
{
	return connector->TCriterionTable(classifier);
}

//--------------counters---------------//
int DSAttribute::attribCount = 0;
int DSClass::classCount = 0;
int DSClassifier::classifierCount = 0;
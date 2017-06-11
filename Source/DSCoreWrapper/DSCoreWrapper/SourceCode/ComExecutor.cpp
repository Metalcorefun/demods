#pragma once 


#include <iostream>
#include <vector> 
#include <string>
#include "Switch.h"
#include "Hierarchy.h"
#include "COMExecutor.h"

using namespace std; 

#import "Resources\\COM\\Pressure.exe"
//#import "C:\Users\Антон\Documents\Visual Studio 2017\Projects\DSCoreUpdated\DSCoreUpdated\Resources\COM\Pressure.exe"

COMExecutor::COMExecutor(DSHierarchy& hierarchy)
{
	hierarchy_ = &hierarchy;
	::CoInitialize(NULL);
	Pressure::IALON_TeacherPtr neo(__uuidof(Pressure::ALON_Teacher));
	Pressure::IALON_StudentPtr kkk(__uuidof(Pressure::ALON_Student));
	teacher = neo;
	teacher->All_Init();
}

COMExecutor::~COMExecutor()
{
	try
	{
		teacher->All_Destroy();
	}
	catch (...) {}
	::CoUninitialize();
}

bool COMExecutor::ISReliable(DSClassifier classifier)
{
	if (teacher->c_Rs_Reliable[(classifier.getID() + " " + classifier.getName()).c_str()])
		return true;
	else return false;
}
float COMExecutor::TCriterion(DSClassifier classifier)
{
	return teacher->c_Rs_TCriterion[(classifier.getID() + " " + classifier.getName()).c_str()];
}
float COMExecutor::TCriterionTable(DSClassifier classifier)
{
	return teacher->c_Rs_TCriterionTable[(classifier.getID() + " " + classifier.getName()).c_str()];
}
bool COMExecutor::learnPressure()
{
	string comment(teacher->All_Execute());
	if (comment == "") return true;
	else return false;
}
void COMExecutor::savePressureFOV(string filePath)
{
	teacher->All_Store(filePath.c_str());
}
void COMExecutor::savePressureFSC(string filePath)
{
	teacher->All_Store(filePath.c_str());
}

void COMExecutor::sendDataToPressure()
{
	vector<DSAttribute> attributes = hierarchy_->getAttributes();
	vector<DSClass> classes = hierarchy_->getClasses();
	vector<DSClassifier> classifiers = hierarchy_->getClassifiers();
	for each(DSAttribute attribute in attributes)
	{

		SWITCH(attribute.getType())
		{
			CASE("Numeric") :
				teacher->Dictionary_SetElement((attribute.getID() + " " + attribute.getName()).c_str(), Pressure::tPr, Pressure::stNumber);
				break;
			CASE("NumArrayT") :
				teacher->Dictionary_SetElement((attribute.getID() + " " + attribute.getName()).c_str(), Pressure::tPr, Pressure::stListOfNumber_Yak);
				break;
			CASE("NumArrayS") :
				teacher->Dictionary_SetElement((attribute.getID() + " " + attribute.getName()).c_str(), Pressure::tPr, Pressure::stListOfNumber_Bag);
				break;
			CASE("FuzSetsO") :
			CASE("FuzSetsSC") :
			CASE("FuzzDistr") :
				teacher->Dictionary_SetElement((attribute.getID() + " " + attribute.getName()).c_str(), Pressure::tPr, Pressure::stFuzzyDistr);
				break;
			CASE("StatDistr") :
			CASE("WeightStr") :
			CASE("LogicUnit") :
			CASE("FuzzyUnit") :
			DEFAULT:
				teacher->Dictionary_SetElement((attribute.getID() + " " + attribute.getName()).c_str(), Pressure::tPr, Pressure::stNoType);
				break;
		}
	}
	for each(DSClass Class in classes)
	{
		teacher->Dictionary_SetElement((Class.getID() + " " + Class.getName()).c_str(), Pressure::tCl, Pressure::stNumber);
	}
	for each(DSClassifier classifier in classifiers)
	{
		vector <reference_wrapper<DSAttribute>> classifier_attributes = classifier.getAttributes();
		vector <reference_wrapper<DSClass>> classifier_classes = classifier.getClasses();
		vector <DSProbe> classifier_training_set = classifier.getTrainingSet();
		vector <AttribValue> classifier_base_object = classifier.getBaseObject();
		vector <reference_wrapper<DSClassifier>> classifier_childs = classifier.getChilds();
		teacher->Hierar_CreateComponent((classifier.getID() + " " + classifier.getName()).c_str(), Pressure::ctClr);
		switch (classifier.getLevel())
		{
		case 1:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_1;
			break;
		case 2:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_2;
			break;
		case 3:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_3;
			break;
		case 4:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_4;
			break;
		case 5:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_5;
			break;
		case 6:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_6;
			break;
		case 7:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_7;
			break;
		default:
			teacher->c_Level[(classifier.getID() + " " + classifier.getName()).c_str()] = Pressure::Level_1;
			break;
		}
		teacher->c_Npr[(classifier.getID() + " " + classifier.getName()).c_str()] = classifier_attributes.size() + classifier_childs.size();
		teacher->c_Ncl[(classifier.getID() + " " + classifier.getName()).c_str()] = classifier_classes.size();
		teacher->c_Nob[(classifier.getID() + " " + classifier.getName()).c_str()] = classifier_training_set.size(); 
		for (int i = 0; i < classifier_attributes.size(); i++)
		{
			teacher->c_Pr_DispositionByNumber_inOV[(classifier.getID() + " " + classifier.getName()).c_str()][i + 1] = (classifier_attributes[i].get().getID() + " " + classifier_attributes[i].get().getName()).c_str();
		}
		for (int i = 0; i < classifier_classes.size(); i++)
		{
			teacher->c_Cl_DispositionByNumber_inOV[(classifier.getID() + " " + classifier.getName()).c_str()][i + 1] = (classifier_classes[i].get().getID() + " " + classifier_classes[i].get().getName()).c_str();
		}
		for (int i = classifier_attributes.size(); i < classifier_attributes.size() + classifier_childs.size(); i++)
		{
			teacher->c_Pr_DispositionByNumber_inOV[(classifier.getID() + " " + classifier.getName()).c_str()][i + 1] = ((classifier_childs[i - classifier_attributes.size()].get().getID() + " " + classifier_childs[i - classifier_attributes.size()].get().getName()).c_str());
		}
		for (int i = 0; i < classifier_training_set.size(); i++)
		{
			vector <AttribValue> probe_av = classifier_training_set[i].getAttribValues();
			vector <ClassMemFunc> probe_cm = classifier_training_set[i].getClassMemFuncs();
			for each(AttribValue av in probe_av)
			{
				teacher->c_PrCl_Value_By_Name[(classifier.getID() + " " + classifier.getName()).c_str()][i + 1][(av.attribPtr->getID() + " " + av.attribPtr->getName()).c_str()] = av.value.c_str();
			}
			for each(ClassMemFunc cm in probe_cm)
			{
				teacher->c_PrCl_Value_By_Name[(classifier.getID() + " " + classifier.getName()).c_str()][i + 1][(cm.classPtr->getID() + " " + cm.classPtr->getName()).c_str()] = to_string(cm.mem_func).c_str();
			}
			probe_av.clear();
			probe_cm.clear();
		}
		classifier_attributes.clear();
		classifier_classes.clear();
		classifier_base_object.clear();
		classifier_training_set.clear();
	}
	hierarchy_->sendAll();
}
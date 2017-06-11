// Главный DLL-файл.

#include "stdafx.h"
#include "DSCoreWrapper.h"
#include <msclr/marshal_cppstd.h>

#include "SourceCode\Attribute.h"
#include "SourceCode\Attribute.cpp"
#include "SourceCode\Class.h"
#include "SourceCode\Class.cpp"
#include "SourceCode\Probe.h"
#include "SourceCode\Probe.cpp"
#include "SourceCode\Classifier.h"
#include "SourceCode\Classifier.cpp"
#include "SourceCode\Hierarchy.h"
#include "SourceCode\Hierarchy.cpp"
#include "SourceCode\COMExecutor.h"
#include "SourceCode\COMExecutor.cpp"
#include "SourceCode\Resources\TinyXML2\tinyxml2.h"
#include "SourceCode\Resources\TinyXML2\tinyxml2.cpp"
#include "SourceCode\Switch.h"

//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"
//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.h"
//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.cpp"

DSCoreWrapper::DSAttributeWrapper::DSAttributeWrapper()
{
	attribute_ = new DSAttribute();
}
DSCoreWrapper::DSAttributeWrapper::DSAttributeWrapper(System::String^ name, System::String^ type, System::String^ description)
{
	attribute_ = new DSAttribute(msclr::interop::marshal_as<std::string>(name), msclr::interop::marshal_as<std::string>(type), msclr::interop::marshal_as<std::string>(description));
}
DSCoreWrapper::DSAttributeWrapper::~DSAttributeWrapper()
{
	delete attribute_;
}
System::String^ DSCoreWrapper::DSAttributeWrapper::getID()
{
	return msclr::interop::marshal_as<System::String^>(attribute_->getID());
}
System::String^ DSCoreWrapper::DSAttributeWrapper::getName()
{
	return msclr::interop::marshal_as<System::String^>(attribute_->getName());
}
System::String^ DSCoreWrapper::DSAttributeWrapper::getType()
{
	return msclr::interop::marshal_as<System::String^>(attribute_->getType());
}
System::String^ DSCoreWrapper::DSAttributeWrapper::getDescription()
{
	return msclr::interop::marshal_as<System::String^>(attribute_->getDescription());
}
void DSCoreWrapper::DSAttributeWrapper::setName(System::String^ name)
{
	attribute_->setName(msclr::interop::marshal_as<std::string>(name));
}
void DSCoreWrapper::DSAttributeWrapper::setType(System::String^ type)
{
	attribute_->setType(msclr::interop::marshal_as<std::string>(type));
}
void DSCoreWrapper::DSAttributeWrapper::setDescription(System::String^ description)
{
	attribute_->setDescription(msclr::interop::marshal_as<std::string>(description));
}
DSAttribute* DSCoreWrapper::DSAttributeWrapper::getInstance()
{
	return attribute_;
}
void DSCoreWrapper::DSAttributeWrapper::setInstance(DSAttribute* attribute)
{
	attribute_ = attribute;
}
void DSCoreWrapper::DSAttributeWrapper::setInstance(reference_wrapper<DSAttribute> attribute)
{
	attribute_ = &attribute.get();
}

DSCoreWrapper::DSClassWrapper::DSClassWrapper(System::String^ name, System::String^ description)
{
	class_ = new DSClass(msclr::interop::marshal_as<std::string>(name), msclr::interop::marshal_as<std::string>(description));
}
DSCoreWrapper::DSClassWrapper::~DSClassWrapper()
{
	delete class_;
}
System::String^ DSCoreWrapper::DSClassWrapper::getID()
{
	return msclr::interop::marshal_as<System::String^>(class_->getID());
}
System::String^ DSCoreWrapper::DSClassWrapper::getName()
{
	return msclr::interop::marshal_as<System::String^>(class_->getName());
}
System::String^ DSCoreWrapper::DSClassWrapper::getDescription()
{
	return msclr::interop::marshal_as<System::String^>(class_->getDescription());
}
void DSCoreWrapper::DSClassWrapper::setName(System::String^ name)
{
	class_->setName(msclr::interop::marshal_as<std::string>(name));
}
void DSCoreWrapper::DSClassWrapper::setDescription(System::String^ description)
{
	class_->setDescription(msclr::interop::marshal_as<std::string>(description));
}
DSClass* DSCoreWrapper::DSClassWrapper::getInstance()
{
	return class_;
}
void DSCoreWrapper::DSClassWrapper::setInstance(DSClass* Class)
{
	class_ = Class;
}
void DSCoreWrapper::DSClassWrapper::setInstance(reference_wrapper<DSClass> Class)
{
	class_ = &Class.get();
}

DSCoreWrapper::AttribValueWrapper::AttribValueWrapper()
{
	attribValue_ = new AttribValue;
}
DSCoreWrapper::AttribValueWrapper::AttribValueWrapper(DSAttributeWrapper^ attribute, System::String^ value)
{
	attribValue_ = new AttribValue;
	attribValue_->attribPtr = attribute->getInstance();
	attribValue_->value = msclr::interop::marshal_as<std::string>(value);
}
DSCoreWrapper::AttribValueWrapper::AttribValueWrapper(DSAttribute* attribute, string value)
{
	attribValue_ = new AttribValue;
	attribValue_->attribPtr = attribute;
	attribValue_->value = value;
}
DSCoreWrapper::AttribValueWrapper::~AttribValueWrapper()
{
	delete attribValue_;
}
void DSCoreWrapper::AttribValueWrapper::setAttributeReference(DSAttributeWrapper^ attribute)
{
	attribValue_->attribPtr = attribute->getInstance();
}
void DSCoreWrapper::AttribValueWrapper::setValue(System::String^ value)
{
	attribValue_->value = msclr::interop::marshal_as <std::string> (value);
}
DSCoreWrapper::DSAttributeWrapper^ DSCoreWrapper::AttribValueWrapper::getAttributeReference()
{
	DSAttributeWrapper^ a = gcnew DSAttributeWrapper();
	a->setInstance(attribValue_->attribPtr);
	return a;
}
System::String^ DSCoreWrapper::AttribValueWrapper::getValue()
{
	return msclr::interop::marshal_as <System::String^>(attribValue_->value);
}
AttribValue* DSCoreWrapper::AttribValueWrapper::getInstance()
{
	return attribValue_;
}
void DSCoreWrapper::AttribValueWrapper::setInstance(AttribValue* av)
{
	attribValue_ = av;
}

DSCoreWrapper::ClassMemFuncWrapper::ClassMemFuncWrapper()
{
	classMemFunc_ = new ClassMemFunc;
}
DSCoreWrapper::ClassMemFuncWrapper::ClassMemFuncWrapper(DSClassWrapper^ Class, double value)
{
	classMemFunc_ = new ClassMemFunc;
	classMemFunc_->classPtr = Class->getInstance();
	classMemFunc_->mem_func = value;
}
DSCoreWrapper::ClassMemFuncWrapper::ClassMemFuncWrapper(DSClass* Class, double value)
{
	classMemFunc_ = new ClassMemFunc;
	classMemFunc_->classPtr = Class;
	classMemFunc_->mem_func = value;
}
DSCoreWrapper::ClassMemFuncWrapper::~ClassMemFuncWrapper()
{
	delete classMemFunc_;
}
void DSCoreWrapper::ClassMemFuncWrapper::setClassReference(DSClassWrapper^ Class)
{
	classMemFunc_->classPtr = Class->getInstance();
}
void DSCoreWrapper::ClassMemFuncWrapper::setMembershipFunction(double value)
{
	classMemFunc_->mem_func = value;
}
DSCoreWrapper::DSClassWrapper^ DSCoreWrapper::ClassMemFuncWrapper::getClassReference()
{
	DSClassWrapper^ c = gcnew DSClassWrapper();
	c->setInstance(classMemFunc_->classPtr);
	return c;
}
double DSCoreWrapper::ClassMemFuncWrapper::getMembershipFunction()
{
	return classMemFunc_->mem_func;
}

DSCoreWrapper::DSProbeWrapper::DSProbeWrapper()
{
	probe_ = new DSProbe();
}
DSCoreWrapper::DSProbeWrapper::DSProbeWrapper(List<AttribValueWrapper^>^ attributes, List <ClassMemFuncWrapper^>^ classes)
{
	vector<AttribValue> attribValues;
	vector<ClassMemFunc> classMemFuncs;
	for each (AttribValueWrapper^ av in attributes)
	{
		AttribValue a;
		a.attribPtr = av->getAttributeReference()->getInstance();
		a.value = msclr::interop::marshal_as<std::string>(av->getValue());
		attribValues.emplace_back(a);
	}
	for each(ClassMemFuncWrapper^ cm in classes)
	{
		ClassMemFunc c;
		c.classPtr = cm->getClassReference()->getInstance();
		c.mem_func = cm->getMembershipFunction();
		classMemFuncs.emplace_back(c);
	}
	probe_ = new DSProbe(attribValues, classMemFuncs);
}
DSCoreWrapper::DSProbeWrapper::~DSProbeWrapper()
{
	delete probe_;
}
List <DSCoreWrapper::AttribValueWrapper^>^ DSCoreWrapper::DSProbeWrapper::getAttribValues()
{
	vector <AttribValue>& av = probe_->getAttribValues();
	List <AttribValueWrapper^>^ al = gcnew List <AttribValueWrapper^>;
	for (int i = 0; i < av.size(); i++)
	{
		AttribValueWrapper^ a = gcnew AttribValueWrapper(av[i].attribPtr, av[i].value);
		al->Add(a);
	}
	return al;
}
List <DSCoreWrapper::ClassMemFuncWrapper^>^ DSCoreWrapper::DSProbeWrapper::getClassMemFuncs()
{
	vector <ClassMemFunc>& cv = probe_->getClassMemFuncs();
	List <ClassMemFuncWrapper^>^ cl = gcnew List <ClassMemFuncWrapper^>;
	for (int i = 0; i < cv.size(); i++)
	{
		ClassMemFuncWrapper^ c = gcnew ClassMemFuncWrapper(cv[i].classPtr, cv[i].mem_func);
		cl->Add(c);
	}
	return cl;
}
void DSCoreWrapper::DSProbeWrapper::setAttribValues(List <DSCoreWrapper::AttribValueWrapper^>^ attributes)
{
	vector<AttribValue> attribValues;
	for each (AttribValueWrapper^ av in attributes)
	{
		AttribValue a;
		a.attribPtr = av->getAttributeReference()->getInstance();
		a.value = msclr::interop::marshal_as<std::string>(av->getValue());
		attribValues.emplace_back(a);
	}
	probe_->setAttribValues(attribValues);
}
void DSCoreWrapper::DSProbeWrapper::setClassMemFuncs(List <DSCoreWrapper::ClassMemFuncWrapper^>^ classes)
{
	vector<ClassMemFunc> classMemFuncs;
	for each(ClassMemFuncWrapper^ cm in classes)
	{
		ClassMemFunc c;
		c.classPtr = cm->getClassReference()->getInstance();
		c.mem_func = cm->getMembershipFunction();
		classMemFuncs.emplace_back(c);
	}
	probe_->setClassMemFuncs(classMemFuncs);
}
DSProbe* DSCoreWrapper::DSProbeWrapper::getInstance()
{
	return probe_;
}
void DSCoreWrapper::DSProbeWrapper::setInstance(DSProbe* probe)
{
	probe_ = probe;
}

DSCoreWrapper::DSClassifierWrapper::DSClassifierWrapper()
{
	classifier_ = new DSClassifier;
}
DSCoreWrapper::DSClassifierWrapper::DSClassifierWrapper(System::String^ name)
{
	classifier_ = new DSClassifier(msclr::interop::marshal_as<std::string>(name));
}
DSCoreWrapper::DSClassifierWrapper::~DSClassifierWrapper()
{
	delete classifier_;
}
System::String^ DSCoreWrapper::DSClassifierWrapper::getID()
{
	return msclr::interop::marshal_as<System::String^>(classifier_->getID());
}
System::String^ DSCoreWrapper::DSClassifierWrapper::getName()
{
	return msclr::interop::marshal_as<System::String^>(classifier_->getName());
}
System::String^ DSCoreWrapper::DSClassifierWrapper::getType()
{
	return msclr::interop::marshal_as<System::String^>(classifier_->getType());
}
int DSCoreWrapper::DSClassifierWrapper::getLevel()
{
	return classifier_->getLevel();
}
List <DSCoreWrapper::DSAttributeWrapper^>^ DSCoreWrapper::DSClassifierWrapper::getAttributes()
{
	List <DSAttributeWrapper^>^ attributes = gcnew List<DSAttributeWrapper^>;
	vector <reference_wrapper<DSAttribute>> attr_ = classifier_->getAttributes();

	for (int i = 0; i < attr_.size(); i++)
	{
		DSAttributeWrapper^ a = gcnew DSAttributeWrapper();
		a->setInstance(attr_[i]);
		attributes->Add(a);
	}
	return attributes;
}
List <DSCoreWrapper::DSClassWrapper^>^ DSCoreWrapper::DSClassifierWrapper::getClasses()
{
	List <DSClassWrapper^>^ classes = gcnew List<DSClassWrapper^>;
	vector <reference_wrapper<DSClass>> classes_ = classifier_->getClasses();

	for (int i = 0; i < classes_.size(); i++)
	{
		DSClassWrapper^ c = gcnew DSClassWrapper();
		c->setInstance(classes_[i]);
		classes->Add(c);
	}
	return classes;
}
List <DSCoreWrapper::DSClassifierWrapper^>^ DSCoreWrapper::DSClassifierWrapper::getChilds()
{
	List <DSClassifierWrapper^>^ childs = gcnew List<DSClassifierWrapper^>;
	vector <reference_wrapper<DSClassifier>> childs_ = classifier_->getChilds();

	for (int i = 0; i < childs_.size(); i++)
	{
		DSClassifierWrapper^ c = gcnew DSClassifierWrapper();
		c->setInstance(childs_[i]);
		childs->Add(c);
	}
	return childs;
}
void DSCoreWrapper::DSClassifierWrapper::setName(System::String^ name)
{
	classifier_->setName(msclr::interop::marshal_as <std::string>(name));
}
void DSCoreWrapper::DSClassifierWrapper::setType(System::String^ type)
{
	classifier_->setType(msclr::interop::marshal_as <std::string>(type));
}
void DSCoreWrapper::DSClassifierWrapper::setLevel(int level)
{
	classifier_->setLevel(level);
}
void DSCoreWrapper::DSClassifierWrapper::addAttribute(DSAttributeWrapper^ attribute)
{
	classifier_->addAttribute(*attribute->getInstance());
}
void DSCoreWrapper::DSClassifierWrapper::addClass(DSClassWrapper^ Class)
{
	classifier_->addClass(*Class->getInstance());
}
void DSCoreWrapper::DSClassifierWrapper::addChild(DSClassifierWrapper^ classifier)
{
	classifier_->addChild(*classifier->getInstance());
}
void DSCoreWrapper::DSClassifierWrapper::removeAttribute(System::String^ id)
{
	classifier_->removeAttribute(msclr::interop::marshal_as <std::string>(id));
}
void DSCoreWrapper::DSClassifierWrapper::removeClass(System::String^ id)
{
	classifier_->removeClass(msclr::interop::marshal_as <std::string>(id));
}
void DSCoreWrapper::DSClassifierWrapper::removeChild(System::String^ id)
{
	classifier_->removeChild(msclr::interop::marshal_as <std::string>(id));
}
void DSCoreWrapper::DSClassifierWrapper::removeTrainingSet()
{
	classifier_->removeTrainingSet();
}
List <DSCoreWrapper::DSProbeWrapper^>^ DSCoreWrapper::DSClassifierWrapper::getTrainingSet()
{
	vector<DSProbe>& training_set = classifier_->getTrainingSet();
	List<DSProbeWrapper^>^ ts = gcnew List<DSProbeWrapper^>;
	for (int i = 0; i < training_set.size(); i++)
	{
		DSProbeWrapper^ probe = gcnew DSProbeWrapper();
		probe->setInstance(&training_set[i]);
		ts->Add(probe);
	}
	return ts;
}
List <DSCoreWrapper::AttribValueWrapper^>^ DSCoreWrapper::DSClassifierWrapper::getBaseObject()
{
	vector <AttribValue>& base_object = classifier_->getBaseObject();
	List <AttribValueWrapper^>^ bo = gcnew List<AttribValueWrapper^>;
	for (int i = 0; i < base_object.size(); i++)
	{
		AttribValueWrapper^ av = gcnew AttribValueWrapper();
		av->setInstance(&base_object[i]);
		bo->Add(av);
	}
	return bo;
}
void DSCoreWrapper::DSClassifierWrapper::toTrainingSet(DSProbeWrapper^ probe)
{
	classifier_->toTrainingSet(*(probe->getInstance()));
}
void DSCoreWrapper::DSClassifierWrapper::setBaseObject(List <AttribValueWrapper^>^ base_object)
{
	vector <AttribValue> baseObject_;
	for each(AttribValueWrapper^ av in base_object)
	{
		AttribValue a;
		a.attribPtr = av->getAttributeReference()->getInstance();
		a.value = msclr::interop::marshal_as<std::string>(av->getValue());
		baseObject_.emplace_back(a);
	}
	classifier_->setBaseObject(baseObject_);
}
DSClassifier* DSCoreWrapper::DSClassifierWrapper::getInstance()
{
	return classifier_;
}
void DSCoreWrapper::DSClassifierWrapper::setInstance(DSClassifier* classifier)
{
	classifier_ = classifier;
}
void DSCoreWrapper::DSClassifierWrapper::setInstance(reference_wrapper<DSClassifier> classifier)
{
	classifier_ = &classifier.get();
}
bool DSCoreWrapper::DSClassifierWrapper::isSent()
{
	return classifier_->isSent();
}


bool DSCoreWrapper::DSHierarchyWrapper::load(System::String^ fileName)
{
	if (hierarchy_.load(msclr::interop::marshal_as <std::string>(fileName))) return true;
	else return false;
}
bool DSCoreWrapper::DSHierarchyWrapper::save(System::String^ fileName)
{
	if (hierarchy_.save(msclr::interop::marshal_as <std::string>(fileName))) return true;
	else return false;
}
void DSCoreWrapper::DSHierarchyWrapper::clear()
{
	hierarchy_.clear();
}
void DSCoreWrapper::DSHierarchyWrapper::addAttribute(DSAttributeWrapper^ attribute)
{
	hierarchy_.addAttribute(*attribute->getInstance());
}
void DSCoreWrapper::DSHierarchyWrapper::addClass(DSClassWrapper^ Class)
{
	hierarchy_.addClass(*Class->getInstance());
}
void DSCoreWrapper::DSHierarchyWrapper::addClassifier(DSClassifierWrapper^ classifier)
{
	hierarchy_.addClassifier(*classifier->getInstance());
}
void DSCoreWrapper::DSHierarchyWrapper::removeAttribute(System::String^ id)
{
	hierarchy_.removeAttribute(msclr::interop::marshal_as<std::string>(id));
}
void DSCoreWrapper::DSHierarchyWrapper::removeClass(System::String^ id)
{
	hierarchy_.removeClass(msclr::interop::marshal_as<std::string>(id));
}
void DSCoreWrapper::DSHierarchyWrapper::removeClassifier(System::String^ id)
{
	hierarchy_.removeClassifier(msclr::interop::marshal_as<std::string>(id));
}
List <DSCoreWrapper::DSAttributeWrapper^>^ DSCoreWrapper::DSHierarchyWrapper::getAttributes()
{
	List <DSAttributeWrapper^>^ attributes = gcnew List<DSAttributeWrapper^>;
	vector <DSAttribute>& attr_ = hierarchy_.getAttributes();

	for (int i = 0; i < attr_.size(); i++)
	{
		DSAttributeWrapper^ a = gcnew DSAttributeWrapper();
		a->setInstance(&attr_[i]);
		attributes->Add(a);
	}
	return attributes;
}
List <DSCoreWrapper::DSClassWrapper^>^ DSCoreWrapper::DSHierarchyWrapper::getClasses()
{
	List <DSClassWrapper^>^ classes = gcnew List<DSClassWrapper^>;
	vector <DSClass>& classes_ = hierarchy_.getClasses();

	for (int i = 0; i < classes_.size(); i++)
	{
		DSClassWrapper^ c = gcnew DSClassWrapper();
		c->setInstance(&classes_[i]);
		classes->Add(c);
	}
	return classes;
}
List <DSCoreWrapper::DSClassifierWrapper^>^ DSCoreWrapper::DSHierarchyWrapper::getClassifiers()
{
	List <DSClassifierWrapper^>^ classifiers = gcnew List<DSClassifierWrapper^>;
	vector <DSClassifier>& classifiers_ = hierarchy_.getClassifiers();

	for (int i = 0; i < classifiers_.size(); i++)
	{
		DSClassifierWrapper^ c = gcnew DSClassifierWrapper();
		c->setInstance(&classifiers_[i]);
		classifiers->Add(c);
	}
	return classifiers;
}
void DSCoreWrapper::DSHierarchyWrapper::COM_sendData()
{
	hierarchy_.com_sendData();
}
bool DSCoreWrapper::DSHierarchyWrapper::COM_learn()
{
	if (hierarchy_.com_learn()) return true;
	else return false;
}
void DSCoreWrapper::DSHierarchyWrapper::COM_saveFOV(System::String^ filePath)
{
	hierarchy_.com_saveFOV(msclr::interop::marshal_as <std::string>(filePath));
}
void DSCoreWrapper::DSHierarchyWrapper::COM_saveFSC(System::String^ filePath)
{
	hierarchy_.com_saveFSC(msclr::interop::marshal_as <std::string>(filePath));
}
bool DSCoreWrapper::DSHierarchyWrapper::COM_IsReliable(DSClassifierWrapper^ classifier)
{
	return hierarchy_.com_isreliable(*classifier->getInstance());
}
float DSCoreWrapper::DSHierarchyWrapper::COM_TCriterion(DSClassifierWrapper^ classifier)
{
	return hierarchy_.com_tcriterion(*classifier->getInstance());
}
float DSCoreWrapper::DSHierarchyWrapper::COM_TCriterionTable(DSClassifierWrapper^ classifier)
{
	return hierarchy_.com_tcriteriontable(*classifier->getInstance());
}
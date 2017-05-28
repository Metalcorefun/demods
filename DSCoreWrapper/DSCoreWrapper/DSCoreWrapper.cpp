// Главный DLL-файл.

#include "stdafx.h"
#include "DSCoreWrapper.h"
#include <msclr/marshal_cppstd.h>
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.cpp"

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
DSCoreWrapper::AttribValueWrapper::AttribValueWrapper(DSAttributeWrapper^ attribute, int value)
{
	attribValue_ = new AttribValue;
	attribValue_->attribPtr = attribute->getInstance();
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
void DSCoreWrapper::AttribValueWrapper::setValue(int value)
{
	attribValue_->value = value;
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
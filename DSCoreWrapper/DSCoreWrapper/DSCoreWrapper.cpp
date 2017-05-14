// Главный DLL-файл.

#include "stdafx.h"
#include "DSCoreWrapper.h"
#include <msclr/marshal_cppstd.h>
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\Resources\TinyXML2\tinyxml2.cpp"

DSCoreWrapper::DSAttributeWrapper::DSAttributeWrapper(System::String^ name, System::String^ type)
{
	attribute_ = new DSAttribute(msclr::interop::marshal_as<std::string>(name), msclr::interop::marshal_as<std::string>(type));
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
DSAttribute* DSCoreWrapper::DSAttributeWrapper::getInstance()
{
	return attribute_;
}
void DSCoreWrapper::DSAttributeWrapper::setInstance(DSAttribute& attribute)
{
	attribute_ = &attribute;
}

DSCoreWrapper::DSClassWrapper::DSClassWrapper(System::String^ name)
{
	class_ = new DSClass(msclr::interop::marshal_as<std::string>(name));
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
DSClass* DSCoreWrapper::DSClassWrapper::getInstance()
{
	return class_;
}
void DSCoreWrapper::DSClassWrapper::setInstance(DSClass& Class)
{
	class_ = &Class;
}


//DSCoreWrapper::DSClassifierWrapper::DSClassifierWrapper(string name)
//{
//	classifier_ = new DSClassifier(name);
//}
//DSCoreWrapper::DSClassifierWrapper::~DSClassifierWrapper()
//{
//	delete classifier_;
//}
//DSClassifier* DSCoreWrapper::DSClassifierWrapper::getInstance()
//{
//	return classifier_;
//}
//void DSCoreWrapper::DSClassifierWrapper::addAttribute(DSAttributeWrapper attribute)
//{
//	classifier_->addAttribute(*attribute.getInstance());
//}
//void DSCoreWrapper::DSClassifierWrapper::addClass(DSClassWrapper Class)
//{
//	classifier_->addClass(*Class.getInstance());
//}
//void DSCoreWrapper::DSClassifierWrapper::addChild(DSClassifierWrapper classifier)
//{
//	classifier_->addChild(*classifier.getInstance());
//}



//void DSCoreWrapper::DSHierarchyWrapper::addAttribute(DSAttributeWrapper attribute)
//{
//	hierarchy_.addAttribute(*attribute.getInstance());
//}
//void DSCoreWrapper::DSHierarchyWrapper::addClass(DSClassWrapper Class)
//{
//	hierarchy_.addClass(*Class.getInstance());
//}
//void DSCoreWrapper::DSHierarchyWrapper::addClassifier(DSClassifierWrapper classifier)
//{
//	hierarchy_.addClassifier(*classifier.getInstance());
//}
//vector <DSCoreWrapper::DSAttributeWrapper> DSCoreWrapper::DSHierarchyWrapper::getAttributes()
//{
//	
//	vector <DSCoreWrapper::DSAttributeWrapper> attr;
//	for (int i = 0; i < hierarchy_.getAttributes().size(); i++)
//	{
//		attr[i].setInstance(hierarchy_.getAttributes()[i]);
//	}
//}
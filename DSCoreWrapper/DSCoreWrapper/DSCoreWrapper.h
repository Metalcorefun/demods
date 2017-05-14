// DSCoreWrapper.h

#pragma once
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"

#include <msclr/marshal.h>
using namespace System;
using namespace System::Configuration;


namespace DSCoreWrapper {

	public ref class DSAttributeWrapper
	{
	public:
		// TODO: здесь следует добавить свои методы для этого класса.
		DSAttributeWrapper(System::String^ name, System::String^ type);
		~DSAttributeWrapper();
		System::String^ getID();
		System::String^ getName();
		System::String^ getType();
	private:
		DSAttribute* getInstance();
		void setInstance(DSAttribute& attribute);
		DSAttribute* attribute_;
	};

	public ref class DSClassWrapper
	{
	public:
		DSClassWrapper() {};
		DSClassWrapper(System::String^ name);
		~DSClassWrapper();
		System::String^ getID();
		System::String^ getName();
	private:
		DSClass* getInstance();
		void setInstance(DSClass& Class);
		DSClass* class_;
	};

	//public ref struct AttribValueWrapper
	//{
	//	AttribValue* attribValue_;
	//};

	//public ref struct ClassMemFuncWrapper
	//{
	//	ClassMemFunc* classMemFunc_;
	//};

	//public ref class DSProbeWrapper
	//{
	//public:
	//	DSProbeWrapper() {};
	//	~DSProbeWrapper() {};
	//private:
	//	DSProbe *probe_;
	//};

	//public ref class DSClassifierWrapper
	//{
	//public:
	//	DSClassifierWrapper(string name);
	//	~DSClassifierWrapper();
	//	DSClassifier* getInstance();
	//	void addAttribute(DSAttributeWrapper attribute);
	//	void addClass(DSClassWrapper Class);
	//	void addChild(DSClassifierWrapper classifier);
	//private:
	//	DSClassifier* classifier_;
	//};

	//public ref class DSHierarchyWrapper
	//{
	//public:
	//	DSHierarchyWrapper() {};
	//	~DSHierarchyWrapper() {};
	//	void addAttribute(DSAttributeWrapper attribute);
	//	void addClass(DSClassWrapper Class);
	//	void addClassifier(DSClassifierWrapper classifier);
	//	vector <DSAttributeWrapper> getAttributes();
	//private:
	//	DSHierarchy& hierarchy_ = DSHierarchy::Instance();
	//};
}

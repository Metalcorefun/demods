// DSCoreWrapper.h

#pragma once
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"

#include <msclr/marshal.h>
using namespace System;
using namespace System::Configuration;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;


namespace DSCoreWrapper {

	public ref class DSAttributeWrapper
	{
	public:
		// TODO: здесь следует добавить свои методы для этого класса.
		DSAttributeWrapper();
		DSAttributeWrapper(System::String^ name, System::String^ type, System::String^ description);
		~DSAttributeWrapper();
		System::String^ getID();
		System::String^ getName();
		System::String^ getType();
		System::String^ getDescription();
		void setName(System::String^ name);
		void setType(System::String^ type);
		void setDescription(System::String^ description);
		DSAttribute* getInstance();
		void setInstance(DSAttribute* attribute);
	private:
		DSAttribute* attribute_;
	};

	public ref class DSClassWrapper
	{
	public:
		DSClassWrapper() {};
		DSClassWrapper(System::String^ name, System::String^ description);
		~DSClassWrapper();
		System::String^ getID();
		System::String^ getName();
		System::String^ getDescription();
		void setName(System::String^ name);
		void setDescription(System::String^ description);
		DSClass* getInstance();
		void setInstance(DSClass* Class);
	private:
		DSClass* class_;
	};

	public ref class AttribValueWrapper
	{
	public:
		AttribValueWrapper();
		AttribValueWrapper(DSAttributeWrapper^ attribute, int value);
		void setAttributeReference(DSAttributeWrapper^ attribute);
		void setValue(int value);
		void getAttributeReference() {};
		void getValue() {};
		~AttribValueWrapper();
		
	private:
		AttribValue* attribValue_;
	};

	public ref class ClassMemFuncWrapper
	{
	public:
		ClassMemFuncWrapper();
		ClassMemFuncWrapper(DSClassWrapper^ Class, double value);
		~ClassMemFuncWrapper();
		void setClassReference(DSClassWrapper^ Class);
		void setMembershipFunction(double value);
		void getAttributeReference() {};
		void getValue() {};
	private:
		ClassMemFunc* classMemFunc_;
	};

	public ref class DSProbeWrapper
	{
	public:
		DSProbeWrapper() {};
		~DSProbeWrapper() {};
	private:
		DSProbe *probe_;
	};

	public ref class DSClassifierWrapper
	{
	public:
		DSClassifierWrapper();
		DSClassifierWrapper(string name);
		~DSClassifierWrapper();
		System::String^ getID();
		System::String^ getName();
		DSClassifier* getInstance();
		void setInstance(DSClassifier* classifier);
		void addAttribute(DSAttributeWrapper^ attribute);
		void addClass(DSClassWrapper^ Class);
		void addChild(DSClassifierWrapper^ classifier);
	private:
		DSClassifier* classifier_;
	};

	public ref class DSHierarchyWrapper
	{
	public:
		DSHierarchyWrapper() {};
		~DSHierarchyWrapper() {};	
		void load(System::String^ fileName);
		void save(System::String^ fileName);
		void clear();
		void addAttribute(DSAttributeWrapper^ attribute);
		void addClass(DSClassWrapper^ Class);
		void addClassifier(DSClassifierWrapper^ classifier);
		void removeAttribute(System::String^ id);
		void removeClass(System::String^ id);
		void removeClassifier(System::String^ id);
		List <DSAttributeWrapper^>^ getAttributes();
		List <DSClassWrapper^>^ getClasses();
		List <DSClassifierWrapper^>^ getClassifiers();
	private:
		DSHierarchy& hierarchy_ = DSHierarchy::Instance();
	};
}

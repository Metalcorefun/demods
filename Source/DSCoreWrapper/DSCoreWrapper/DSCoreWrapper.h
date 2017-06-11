// DSCoreWrapper.h

#pragma once

#include "SourceCode\Attribute.h"
#include "SourceCode\Class.h"
#include "SourceCode\Probe.h"
#include "SourceCode\Classifier.h"
#include "SourceCode\Hierarchy.h"
#include "SourceCode\COMExecutor.h"
//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.h"
//#include "C:\Users\Антон\Documents\Visual Studio 2017\Projects\AquariusDS\DSCore\DSCore\DSCore.cpp"

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
		void setInstance(reference_wrapper<DSAttribute> attribute);
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
		void setInstance(reference_wrapper<DSClass> Class);
	private:
		DSClass* class_;
	};

	public ref class AttribValueWrapper
	{
	public:
		AttribValueWrapper();
		AttribValueWrapper(DSAttributeWrapper^ attribute, System::String^ value);
		AttribValueWrapper(DSAttribute* attribute, string value);
		void setAttributeReference(DSAttributeWrapper^ attribute);
		void setValue(System::String^ value);
		DSAttributeWrapper^ getAttributeReference();
		System::String^ getValue();
		AttribValue* getInstance();
		void setInstance(AttribValue* av);
		~AttribValueWrapper();
		
	private:
		AttribValue* attribValue_;
	};

	public ref class ClassMemFuncWrapper
	{
	public:
		ClassMemFuncWrapper();
		ClassMemFuncWrapper(DSClassWrapper^ Class, double value);
		ClassMemFuncWrapper(DSClass* Class, double value);
		~ClassMemFuncWrapper();
		void setClassReference(DSClassWrapper^ Class);
		void setMembershipFunction(double value);
		DSClassWrapper^ getClassReference();
		double getMembershipFunction();
	private:
		ClassMemFunc* classMemFunc_;
	};

	public ref class DSProbeWrapper
	{
	public:
		DSProbeWrapper();
		DSProbeWrapper(List<AttribValueWrapper^>^ attributes, List<ClassMemFuncWrapper^>^ classes);
		~DSProbeWrapper();
		List<AttribValueWrapper^>^ getAttribValues();
		List<ClassMemFuncWrapper^>^ getClassMemFuncs();
		void setAttribValues(List <AttribValueWrapper^>^ attributes);
		void setClassMemFuncs(List<ClassMemFuncWrapper^>^ classes);
		DSProbe* getInstance();
		void setInstance(DSProbe* probe);
	private:
		DSProbe* probe_;
	};

	public ref class DSClassifierWrapper
	{
	public:
		DSClassifierWrapper();
		DSClassifierWrapper(System::String^ name);
		~DSClassifierWrapper();
		System::String^ getID();
		System::String^ getName();
		System::String^ getType();
		int getLevel();
		List<DSAttributeWrapper^>^ getAttributes();
		List<DSClassWrapper^>^ getClasses();
		List<DSClassifierWrapper^>^ getChilds();
		void setName(System::String^ name);
		void setType(System::String^ type);
		void setLevel(int level);
		void addAttribute(DSAttributeWrapper^ attribute);
		void addClass(DSClassWrapper^ Class);
		void addChild(DSClassifierWrapper^ classifier);
		void removeAttribute(System::String^ id);
		void removeClass(System::String^ id);
		void removeChild(System::String^ id);
		void removeTrainingSet();
		List <DSProbeWrapper^>^ getTrainingSet();
		List <AttribValueWrapper^>^ getBaseObject();
		void toTrainingSet(DSProbeWrapper^ probe);
		void setBaseObject(List <AttribValueWrapper^>^ base_object);
		DSClassifier* getInstance();
		void setInstance(DSClassifier* classifier);
		void setInstance(reference_wrapper<DSClassifier> classifier);
		bool isSent();
	private:
		DSClassifier* classifier_;
	};

	public ref class DSHierarchyWrapper
	{
	public:
		DSHierarchyWrapper() {};
		~DSHierarchyWrapper() {};	
		bool load(System::String^ fileName);
		bool save(System::String^ fileName);
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
		//COM
		void COM_sendData();
		bool COM_learn();
		void COM_saveFOV(System::String^ filePath);
		void COM_saveFSC(System::String^ filePath);
		bool COM_IsReliable(DSClassifierWrapper^ classifier);
		float COM_TCriterion(DSClassifierWrapper^ classifier);
		float COM_TCriterionTable(DSClassifierWrapper^ classifier);
		
	private:
		DSHierarchy& hierarchy_ = DSHierarchy::Instance();
	};
}

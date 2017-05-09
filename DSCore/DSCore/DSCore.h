#pragma once

#include <string>
#include <vector>

using namespace std;


class DSModules
{
public:
	static DSModules& Instance();
	void AC_LearnCall() {};
	void AC_ClassifyCall() {};
private:
	DSModules() {};
	~DSModules() {};
	DSModules(DSModules const&) = delete;
	DSModules& operator = (DSModules const&) = delete;
};

class DSAttribute
{
public:
	static int attribCount;
	DSAttribute() {};
	DSAttribute(string name, string type);
	~DSAttribute();
	string getID();
	string getName();
	string getType();
private:
	string id_, name_, type_;
};

class DSClass
{
public:
	static int classCount;
	DSClass() {};
	DSClass(string name);
	~DSClass();
	string getID();
	string getName();
private:
	string id_, name_;
};

struct AttribValue
{
	DSAttribute* attribPtr;
	int value;
};


struct ClassMemFunc
{
	DSClass* classPtr;
	int mem_func;
};


class DSProbe //один опыт из обучающей выборки
{
public:
	DSProbe(vector<reference_wrapper<DSAttribute>> attributes, vector<reference_wrapper<DSClass>> classes, int* attribValues, int* classValues);
	~DSProbe();
	vector <AttribValue> getAttribValues();
	vector <ClassMemFunc> getClassMemFuncs();
private:
	vector <AttribValue> attribValues_;
	vector <ClassMemFunc> classMemFuncs_;
};

class DSClassifier
{
public:
	static int classifierCount;
	DSClassifier() {};
	DSClassifier(string name);
	~DSClassifier();
	void addAttribute(DSAttribute& attribute);
	void addClass(DSClass& Class);
	void addChild(DSClassifier& classifier);
	int getLevel();
	string getID();
	string getName();
	vector <reference_wrapper<DSAttribute>> getAttributes();
	vector <reference_wrapper<DSClass>> getClasses();
	vector <reference_wrapper<DSClassifier>> getChilds();
	vector <DSProbe> getTrainingSet();
	vector <AttribValue> getBaseObject();
	void setBaseObject(int* values_a);
	void toTrainingSet(int* values_a, int* values_c);
	void classify();
private:
	string id_, name_;
	int level_;
	vector <reference_wrapper<DSAttribute>> attributes_;
	vector <reference_wrapper<DSClass>> classes_;
	vector <reference_wrapper<DSClassifier>> childs_;
	vector <DSProbe> trainingSet_;
	vector <AttribValue> baseObject_;
	
};

struct DSResults
{
	DSClassifier* classifier;
	vector <ClassMemFunc> result;
};


class DSHierarchy
{
public:
	static DSHierarchy& Instance();
	void load(char* fileName);
	void save(char* fileName);
	void addAttribute(DSAttribute attribute);
	void addClass(DSClass Class);
	void addClassifier(DSClassifier classifier);
	DSAttribute& findAttribute(string id);
	DSClass& findClass(string id);
	DSClassifier& findClassifier(string id);
	void initResultsTable(DSClassifier classifier);
private:
	DSHierarchy();
	~DSHierarchy();
	DSHierarchy(DSHierarchy const&) = delete;
	DSHierarchy& operator = (DSHierarchy const&) = delete;

	vector <DSAttribute> attributes_;
	vector <DSClass> classes_;
	vector <DSClassifier> classifiers_;
	vector <vector <DSResults>> resultsTable_;
};
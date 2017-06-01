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
	//DSAttribute(string name, string type);
	DSAttribute(string name, string type, string description);
	DSAttribute(string id, string name, string type, string description);
	~DSAttribute();
	string getID();
	string getName();
	string getType();
	string getDescription();
	void setName(string name);
	void setType(string type);
	void setDescription(string description);
private:
	string id_, name_, type_, description_;
};

class DSClass
{
public:
	static int classCount;
	DSClass() {};
	//DSClass(string name);
	DSClass(string name, string description);
	DSClass(string id, string name, string description);
	~DSClass();
	string getID();
	string getName();
	string getDescription();
	void setName(string name);
	void setDescription(string description);
private:
	string id_, name_, description_;
};

struct AttribValue
{
	DSAttribute* attribPtr;
	string value;
};

struct ClassMemFunc
{
	DSClass* classPtr;
	double mem_func;
};

class DSProbe //один опыт из обучающей выборки
{
public:
	DSProbe() {};
	DSProbe(vector<AttribValue> attribValues, vector<ClassMemFunc> classMemFuncs);
	DSProbe(vector<reference_wrapper<DSAttribute>> attributes, vector<reference_wrapper<DSClass>> classes, string* attribValues, double* classValues);
	~DSProbe();
	void removeAttribute(DSAttribute& attribute);
	void removeClass(DSClass& Class);
	void addAttribute(DSAttribute& attribute);
	void addClass(DSClass& Class);
	vector <AttribValue>& getAttribValues();
	vector <ClassMemFunc>& getClassMemFuncs();
	void setAttribValues(vector <AttribValue> values);
	void setClassMemFuncs(vector <ClassMemFunc> mem_funcs);
private:
	vector <AttribValue> attribValues_;
	vector <ClassMemFunc> classMemFuncs_;
};

class DSClassifier
{
public:
	static int classifierCount;
	DSClassifier();
	DSClassifier(string name);
	DSClassifier(string id, string name);
	~DSClassifier();
	//add
	void addAttribute(DSAttribute& attribute);
	void addClass(DSClass& Class);
	void addChild(DSClassifier& classifier);
	void setBaseObject(string* values_a);
	void setBaseObject(vector <AttribValue> base_object);
	void toTrainingSet(string* values_a, double* values_c);
	void toTrainingSet(DSProbe probe);
	//remove
	void removeAttribute(string id);
	void removeClass(string id);
	void removeChild(string id);
	void removeTrainingSet();
	//get
	int getLevel();
	string getID();
	string getName();
	string getType();
	vector <reference_wrapper<DSAttribute>> getAttributes();
	vector <reference_wrapper<DSClass>> getClasses();
	vector <reference_wrapper<DSClassifier>> getChilds();
	vector <DSProbe>& getTrainingSet();
	vector <AttribValue>& getBaseObject();
	bool isApexPoint();
	//set
	void setName(string name);
	void setType(string type);
	void setLevel(int level);
	void setApex(bool value);
	//update addresses
	void updateAttributesReferences(vector <DSAttribute> &attributes, int index);
	void updateClassesReferences(vector <DSClass> &classes, int index);
	void updateClassifiersReferences(vector <DSClassifier> &classifiers, int index);
	void classify();
	bool operator<(const DSClassifier& cl) const { return level_ < cl.level_; }
private:
	string id_, name_, type_;
	int level_;
	bool apex_ = false;
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
	~DSResults()
	{
		result.clear();
	}
};

class DSHierarchy
{
public:
	//singleton
	static DSHierarchy& Instance();
	//
	void clear();
	//save/load
	bool load(string fileName);
	bool save(string fileName);
	//add
	void addAttribute(DSAttribute attribute);
	void addClass(DSClass Class);
	void addClassifier(DSClassifier classifier);
	void initResultsTable(DSClassifier& classifier);
	//get
	vector <DSAttribute>& getAttributes();
	vector <DSClass>& getClasses();
	vector <DSClassifier>& getClassifiers();
	//remove
	void removeAttribute(string id);
	void removeClass(string id);
	void removeClassifier(string id);
	
	//find
	DSAttribute& findAttribute(string id);
	DSClass& findClass(string id);
	DSClassifier& findClassifier(string id);
	//apex(entry) point
	bool apexPointExists();
	int getApexPoint();
	void setApexPoint(string id, bool value);
	//classify
	void sortClassifiers();
	void classify();
private:
	DSHierarchy();
	~DSHierarchy();
	DSHierarchy(DSHierarchy const&) = delete;
	DSHierarchy& operator = (DSHierarchy const&) = delete;

	vector <DSAttribute> attributes_;
	vector <DSClass> classes_;
	vector <DSClassifier> classifiers_;
	vector  <DSResults> resultsTable_;
};
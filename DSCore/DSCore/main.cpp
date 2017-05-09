//все описанные здесь классы планируется собрать в библиотеку классов и использовать в пользовательском интерфейсе
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int AttrCnt = 0, ClsCnt = 0, ClsfCnt = 0; //используются для генерации ID-шников

class ModuleAccess  //фасад
{	//пока оставлю так
public:
	static ModuleAccess& Instance()
	{
		static ModuleAccess access;
		return access;
	}
	void FuzzyAC_Call() {};
private:
	ModuleAccess() {};
	~ModuleAccess() {};
	ModuleAccess(ModuleAccess const&) = delete;
	ModuleAccess& operator = (ModuleAccess const&) = delete;
};

//компоненты иерархии

class DSAttribute  //признак
{
public:
	DSAttribute(string iname, string itype) //насчет формы представления типов данных(шкал), мне нужно будет переговорить с Вами отдельно
	{
		AttrCnt++;
		id = "attr_" + to_string(AttrCnt);
		name = iname;
		type = itype;
	}
	~DSAttribute()
	{
		id.clear();
		name.clear();
		type.clear();
	}
private:
	string id, name, type;
};

class DSClass  //класс
{
public:
	DSClass(string iname)
	{
		ClsCnt++;
		id = "cls_" + to_string(ClsCnt);
		name = iname;
	}
	~DSClass()
	{
		id.clear();
		name.clear();
	}
private:
	string id, name;
};

struct AttrVal //структура для хранения ссылки на признак и его значения в текущем опыте
{
	DSAttribute *Attr;
	int value;
};

struct ClsPr //структура для хранения ссылки на класс и степени принадлежности к нему
{
	DSClass *Cls;
	int probability;
};

class DSProbe //один опыт из обучающей выборки
{
public:
	DSProbe(vector<DSAttribute>& At, vector<DSClass>& Cl, int *values)
	{
		int i;
		AttrVal atemp;
		ClsPr ctemp;
		for (i = 0; i < At.size(); i++)  //формирование векторов признаков с их значениями и классов со степенями принадлежности
		{
			atemp.Attr = &At[i];
			atemp.value = values[i];
			AttrVector.push_back(atemp);
		}

		for (int j = 0; j < Cl.size(); j++)
		{
			ctemp.Cls = &Cl[j];
			ctemp.probability = values[j+i];
			ClsVector.push_back(ctemp);
		}
	}
	~DSProbe()
	{
		AttrVector.clear();
		ClsVector.clear();
	}
private:
	vector <AttrVal> AttrVector;
	vector <ClsPr> ClsVector;
};

class DSClassifier
{
public:
	DSClassifier(string iname)
	{
		ClsfCnt++;
		id = "clsf_" + to_string(ClsfCnt);
		name = iname;
	}
	int get_level()
	{
		return level;
	}
	
	void add_attrib(DSAttribute iAt)
	{
		Attributes.push_back(iAt);
	}
	
	void add_class(DSClass iCl)
	{
		Classes.push_back(iCl);
	}
	void init_training_set(int *vals)
	{
		DSProbe temp(Attributes,Classes,vals);
		TrainingSet.push_back(temp);
	}
	void init_base_object(int *vals)
	{
		AttrVal temp;
		for (int i = 0; i < Attributes.size(); i++) //формирование значений признаков для базового объекта
		{
			temp.Attr = &Attributes[i];
			temp.value = vals[i];
			BaseObject.push_back(temp);
		}
	}
	vector <DSClass> get_classes()
	{
		return Classes;
	}
	void classify()
	{
		ModuleAccess& access = ModuleAccess::Instance(); //выуживаем ссылку на фасад и вызываем сам классификатор
		access.FuzzyAC_Call();
	}
	vector <DSClassifier*> ptr_prev;
	~DSClassifier()
	{
		id.clear(); name.clear();
		Attributes.clear();
		Classes.clear();
		TrainingSet.clear();
		BaseObject.clear();
	}
private:
	string id, name;
	int level;
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
	vector <DSProbe> TrainingSet;
	vector <AttrVal> BaseObject;
};

class DSHierarchy //реализация посредством паттерна "Одиночка", так как в проекте может быть лишь одна иерархия
{
public:
	static DSHierarchy& Instance()
	{
		static DSHierarchy h;
		return h;
	}
	struct DSResults
	{
		DSClassifier* current;
		vector <ClsPr> result;
	};
	void add_attribute(DSAttribute iAt)
	{
		Attributes.push_back(iAt);
	}
	void add_class(DSClass iCl)
	{
		Classes.push_back(iCl);
	}
	void init_results_table(DSClassifier iClsf)
	{
		DSResults Rtemp;
		Rtemp.current = &iClsf;
		vector<DSClass> Ctemp = iClsf.get_classes();

		for (int i = 0; i < Ctemp.size(); i++)
		{
			ClsPr temp;
			temp.Cls = &Ctemp[i];
			temp.probability = 0;
			Rtemp.result.push_back(temp);
		}
		Ctemp.clear();
		
	}
	void load() //функции импорта/экспорта я не трогаю, пока не будет готовы все классы, включая иерархию
	{

	}
	void save()
	{
		
	}
private:
	DSHierarchy() {};
	~DSHierarchy() {};
	DSHierarchy(DSHierarchy const&) = delete;
	DSHierarchy& operator = (DSHierarchy const&) = delete;

	vector <vector <DSResults>> ResultsTable;
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
};



int main() 
{	
	DSHierarchy& hierarchy = DSHierarchy::Instance();
	hierarchy.load();
	system("pause");
	return 0;
}
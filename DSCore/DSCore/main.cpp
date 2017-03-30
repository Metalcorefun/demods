//все описанные здесь классы планируется собрать в библиотеку классов и использовать в пользовательском интерфейсе
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int AttrCnt = 0, ClsCnt = 0, ClsfCnt = 0; //используются для генерации ID-шников



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
	DSClassifier *next; //указатель на следующий классификатор иерархии(уровнем выше)
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
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
	vector <DSProbe> TrainingSet;
	vector <AttrVal> BaseObject;
};

class DSHierarchy //над реализацией еще надо подумать
{
public:
	DSHierarchy();
	void load() //функции импорта/экспорта я не трогаю, пока не будет готовы все классы, включая иерархию
	{

	}
	void save()
	{

	}
private:
	vector<DSClassifier> Classifiers;
};

int main() 
{	
	system("pause");
	return 0;
}
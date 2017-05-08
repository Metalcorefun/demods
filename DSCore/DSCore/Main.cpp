//все описанные здесь классы планируется собрать в библиотеку классов и использовать в пользовательском интерфейсе
#include <iostream>
#include <string>
#include <vector>
#include "DSCore.h"
using namespace std;




int main()
{
	DSHierarchy& hierarchy = DSHierarchy::Instance();
	hierarchy.load("codebeautify.xml");
	hierarchy.save("savior.xml");
	system("pause");
	return 0;
}
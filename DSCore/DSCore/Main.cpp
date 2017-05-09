//все описанные здесь классы планируется собрать в библиотеку классов и использовать в пользовательском интерфейсе
#include <iostream>
#include <string>
#include <vector>

#include "DSCore.h"

using namespace std;




int main()
{
	DSHierarchy& hierarchy = DSHierarchy::Instance();
	hierarchy.load("XMLFiles\\codebeautify.xml");
	hierarchy.save("XMLFiles\\savior.xml");

	return 0;
}
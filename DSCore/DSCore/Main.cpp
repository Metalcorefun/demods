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
	/*hierarchy.findClassifier("cl1").removeAttribute("attr1");
	hierarchy.findClassifier("cl2").removeClass("c2");
	hierarchy.findClassifier("cl2").removeChild("cl1");
	hierarchy.removeAttribute("attr2");
	hierarchy.removeClass("c3");
	hierarchy.removeClassifier("cl1");*/
	hierarchy.save("XMLFiles\\savior.xml");

	return 0;
}
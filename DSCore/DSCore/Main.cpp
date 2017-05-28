//все описанные здесь классы планируется собрать в библиотеку классов и использовать в пользовательском интерфейсе
#include <iostream>
#include <string>
#include <vector>

#include "DSCore.h"

using namespace std;

int main()
{
	DSHierarchy& hierarchy = DSHierarchy::Instance();
	hierarchy.load("XMLFiles\\codebeautify3.xml");
	hierarchy.addAttribute(DSAttribute("Attrib05", "Numeric", "a5"));
	hierarchy.setApexPoint("cl2", true);
	hierarchy.classify();
	hierarchy.save("XMLFiles\\savior.xml");
	hierarchy.clear();

	return 0;
}
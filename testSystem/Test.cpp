#include "menuFunc.h"
#include "Test.h"


void Test::TestMenu(User& Person) {

	Frame();
	

	Menu menu;

	std::vector<std::string> objMenu{
		"> ÍÀ×ÀÒÜ ÒÅÑÒ",
		"> ÏĞÎÄÎËÆÈÒÜ ÒÅÑÒ",
		"> ÑÒÀÒÈÑÒÈÊÀ",
		"> ÂÛÉÒÈ"
	};


	int test_select = menu.select_vertical(objMenu, Center, 8);

	switch (test_select)
	{
	case 0:
		StartTest(Person);


	case 4:
		exit(0);
		break;
	}

}

void Test::StartTest(User& Person) {
}

void Test::ContinueTest(User& Person) {
}

void Test::TestStat(User& Person) {
}

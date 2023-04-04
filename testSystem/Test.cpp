#include "Test.h"


void Test::TestMenu(User& Person) {

	Frame();
	

	Menu menu;

	std::vector<std::string> objTest{
		"> ÍÀ×ÀÒÜ ÒÅÑÒ",
		"> ÏĞÎÄÎËÆÈÒÜ ÒÅÑÒ",
		"> ÑÒÀÒÈÑÒÈÊÀ",
		"> ÂÛÉÒÈ"
	};


	int test_select = menu.select_vertical(objTest, Center, 8);

	switch (test_select)
	{
	case 0:
		StartTest(Person);
		break;
	default:
		break;

	
	}

}

void Test::StartTest(User& Person) {
}

void Test::ContinueTest(User& Person) {
}

void Test::TestStat(User& Person) {
}

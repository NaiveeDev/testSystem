#include "Test.h"


void Test::ChooseTest(User& Person) {

	Frame();

	Menu menu;
	std::string CategoriesItem;

	
	

	int select = menu.select_vertical(Categories, Center, 8);

	switch (select)
	{
	case 0:
		StartTest(Person, Categories.front());



	}
	
}

void Test::TestMenu(User& Person) {

	Frame();
	Menu menu;

	std::vector<std::string> objTest{
		"> Õ¿◊¿“‹ “≈—“",
		"> œ–ŒƒŒÀ∆»“‹ “≈—“",
		"> —“¿“»—“» ¿",
		"> ¬€…“»"
	};


	int test_select = menu.select_vertical(objTest, Center, 8);

	switch (test_select)
	{
	case 0:
		ChooseTest(Person);


	
	}

}


void Test::ContinueTest(User& Person) {
}

void Test::TestStat(User& Person) {
}

void Test::StartTest(User& Person, std::string categoryName) {

	Question quest;
	Menu testMenu;

	std::ifstream category("QuestionsDB//" + categoryName + "//");

	if (category.is_open()) {

		std::vector <std::string> tests;

		const std::string path = "QuestionsDB//" + categoryName;

		for (const auto& entry : fs::directory_iterator(path)) {
			if (entry.is_regular_file()) {
				tests.push_back(entry.path().string());
			}
		}
		for (const auto& filename : tests) {
			std::cout << filename << std::endl;
		}

		int select_test = testMenu.select_vertical(tests, Center, 8);

	}
	if (!category)
	{
		std::cerr << "FAIL";
	}


}

#pragma once
#include "imports.h"
#include "menuFunc.h"
#include "Question.h"
#include "User.h"

namespace fs = std::filesystem;


class Test {

	std::vector<std::string> Categories {
		"МАТЕМАТИКА",
		"ГЕОГРАФИЯ",
		"> НАЗАД",
	};


public:

	//Меню
	void TestMenu(User& Person);
	
	//Функции меню
	void ChooseTest(User& Person);
	void ContinueTest(User& Person);
	void TestStat(User& Person);
	
	//Функции тестирования
	void StartTest(User& Person, std::string categoryName);

};


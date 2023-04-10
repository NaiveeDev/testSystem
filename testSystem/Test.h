#pragma once
#include "imports.h"
#include "menuFunc.h"
#include "Question.h"
#include "User.h"

namespace fs = std::filesystem;


class Test {

	std::vector<std::string> Categories {
		"����������",
		"���������",
		"> �����",
	};


public:

	//����
	void TestMenu(User& Person);
	
	//������� ����
	void ChooseTest(User& Person);
	void ContinueTest(User& Person);
	void TestStat(User& Person);
	
	//������� ������������
	void StartTest(User& Person, std::string categoryName);

};


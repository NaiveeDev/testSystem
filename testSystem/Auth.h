#pragma once
#include "imports.h"
#include "User.h"


class Auth {

public:

	void Register(User& Person);
	void Login(User& Person);
	void AuthMenu(User& Person);
	void AdminMenu(User& Person);
	void AddAdmin(User& Person);

};

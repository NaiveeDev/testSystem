#pragma once
#include "imports.h"




class User {

	std::string login, password, phone_number;

public:

	User() : login(login), password(password), phone_number(phone_number) { }
	~User() {}

	void setLogin(const std::string& u_Login) ;
	void setPassword(const std::string& u_Password);
	void setPhoneNumber(const std::string& u_PhoneNumber);

	std::string getLogin();
	std::string getPassword();
	std::string getPhoneNumber();
	

};


#include "User//User.h"


//ÃÅÒÒÅÐÛ, ÑÅÒÒÅÐÛ
void User::setLogin (const std::string& u_Login) {
	this->login = u_Login;
}
void User::setPassword(const std::string& u_Password) {
	this->password = u_Password;
}
void User::setPhoneNumber(const std::string& u_PhoneNumber) {
	this->phone_number = u_PhoneNumber;
}

std::string User::getLogin() {
	return this->login;
}
std::string User::getPassword() {
	return this->password;
}
std::string User::getPhoneNumber() {
	return this->phone_number;
}




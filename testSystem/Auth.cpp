#include "Auth.h"
#include "menuFunc.h"




//LOGIN VALIDATION
void AlreadyLogin(User Person) {

	ifstream File("UsersDB//" + Person.getLogin() + ".txt");

	if (File) {

		int x, y;
		x = 2;
		y = 1;

		SetColor(LightRed, Black);
		Frame();
		gotoxy(x, y);

		std::cout << "Пользователь уже зарегистрирован!" << std::endl;

		Sleep(1200);
		exit(0);
	}	
}

//PASSWORD VALIDATION
bool withSpace(const std::string& str) {
	for (const auto& ch : str) {
		if (ch == ' ') 
			return true;
	}
	return false;
}
void PasswordValid(User Person) {

	if (withSpace(Person.getPassword()))
	{
		int x, y;
		x = 2;
		y = 1;

		SetColor(LightRed, Black);
		Frame();
		gotoxy(x, y);

		std::cout << "В пароле не может быть пробелов!" << std::endl;

		Sleep(1200);
		exit(0);
	}

}

//PHONE VALIDATION
bool isValidNumber(const std::string& str) {
	for (char c: str) {
		if (!isdigit(c) && c != '+') 
			return false;
	}

	return true;
}
void PhoneNumberValid(User Person) {

	

	if (!isValidNumber(Person.getPhoneNumber())) {
		int x, y;
		x = 2;
		y = 1;

		SetColor(LightRed, Black);
		Frame();
		gotoxy(x, y);

		std::cout << "В номере телефона не может быть букв!" << std::endl;

		Sleep(1200);
		exit(NULL);
	}

}


void Auth::Register(User& Person) {

	std::string temp_Login, temp_Password, temp_PhoneNumber;
	int x = 3, y = 3;

	Frame();
	gotoxy(34, 1);
	SetColor(LightGreen, Black);
	std::cout << "РЕГИСТРАЦИЯ";


	//LOGIN
	SetColor(White, Black);
	gotoxy(x, y);
	std::cout << "Логин: ";
	std::getline(cin, temp_Login);
	Person.setLogin(temp_Login);
	AlreadyLogin(Person);

	//PASSWORD
	gotoxy(x, ++y);
	std::cout << "Пароль: ";
	std::getline(cin, temp_Password);
	Person.setPassword(temp_Password);
	PasswordValid(Person);

	//PHONE NUMBER
	gotoxy(x, ++y);
	std::cout << "Номер телефона: ";
	std::getline(cin, temp_PhoneNumber);
	Person.setPhoneNumber(temp_PhoneNumber);
	PhoneNumberValid(Person);

	//FILE READER
	ofstream File("UsersDB//" + Person.getLogin() + ".txt", ios::app);
	if (File.is_open()) {
		File << Person.getLogin() << "\n";
		File << Person.getPassword() << "\n";
		File << Person.getPhoneNumber();
		File.close();
	}
	else {
		std::cerr << "Ошибка, файл не открыт!\n";
	}

}

void Auth::Login(User& Person) {

	std::string temp_Login, temp_Password, filePassword;

	Frame();

	gotoxy(34, 1);
	SetColor(LightGreen, Black);
	cout << "АВТОРИЗАЦИЯ";

	int x = 3, y = 3;

	SetColor(White, Black);
	gotoxy(x, y);
	
	std::cout << "Логин: ";
	std::getline(cin, temp_Login);
	
	ifstream regFile("UsersDB//" + temp_Login + ".txt");
	if (!regFile) {

		system("cls");
		Frame();
		gotoxy(28, 9);
		SetColor(LightRed, Black);
		cout << "Пользователь не найден!" << endl;

		exit(0);
	}
	std::getline(regFile, temp_Login);
	
	gotoxy(x, ++y);
	std::cout << "Пароль: ";
	std::getline(cin, temp_Password);
	//Person.setPassword(temp_Password);

	

	if (regFile.is_open()) {
		
		system("cls");
		Frame();

		std::getline(regFile, filePassword);
		if (filePassword == temp_Password) {
			gotoxy(29, 9);
			SetColor(LightGreen, Black);
			cout << "Авторизация успешна!" << endl;
			regFile.close();
			Sleep(1500);
			
		}
		else {
			gotoxy(26, 9);
			SetColor(LightRed, Black);
			cout << "Неверный логин или пароль" << endl;
			regFile.close();
			Sleep(1500);
		}
	} 
	

	
	
	


}

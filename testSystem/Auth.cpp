#pragma comment(lib,"shell32")
#include "Auth.h"
#include "Test.h"
#include "menuFunc.h"
#include "md5.h"
#include <filesystem>



using std::cout; using std::endl;


namespace fs = std::filesystem;


//LOGIN VALIDATION
void AlreadyLogin(User Person, bool adminFlag = false) {

	if (!adminFlag) {
		std::ifstream File("UsersDB//" + Person.getLogin() + ".txt");

		if (File) {

			int x, y;
			x = 2;
			y = 1;

			SetColor(LightRed, Black);
			Frame();
			gotoxy(24, 9);

			std::cout << "Пользователь уже зарегистрирован!" << std::endl;
			Sleep(1200);
			system("cls");
			SetColor(White, Black);
			Auth* instance = new Auth();
			instance->AuthMenu(Person);
		}
		if (Person.getLogin().empty()) {

			int x, y;
			x = 2;
			y = 1;

			SetColor(LightRed, Black);
			Frame();
			gotoxy(32, 9);

			std::cout << "Вы не ввели логин!" << std::endl;
			Sleep(1200);
			system("cls");
			SetColor(White, Black);
			Auth* instance = new Auth();
			instance->AuthMenu(Person);

		}
	}
	else {
		std::ifstream AdminFile("AdminsDB//" + Person.getLogin() + ".txt");

		if (AdminFile) {

			int x, y;
			x = 2;
			y = 1;

			SetColor(LightRed, Black);
			Frame();
			gotoxy(24, 9);

			std::cout << "Пользователь уже зарегистрирован!" << std::endl;
			Sleep(1200);
			system("cls");
			SetColor(White, Black);
			Auth* instance = new Auth();
			instance->AdminMenu(Person);
		}
		/*if (Person.getLogin().empty()) {

			int x, y;
			x = 2;
			y = 1;

			SetColor(LightRed, Black);
			Frame();
			gotoxy(32, 9);

			std::cout << "Вы не ввели логин!" << std::endl;
			Sleep(1200);
			system("cls");
			SetColor(White, Black);
			Auth* instance = new Auth();
			instance->AdminMenu(Person);

		}*/
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
void PasswordValid(User Person, std::string TempPassword) {

	if (withSpace(TempPassword) || TempPassword.empty())
	{
		int x, y;
		x = 2;
		y = 1;

		SetColor(LightRed, Black);
		Frame();
		gotoxy(22, 9);

		std::cout << "В пароле не должно быть пробелов!" << std::endl;
		Sleep(1200);
		system("cls");
		SetColor(White, Black);
		Auth* instance = new Auth();
		instance->AuthMenu(Person);
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
		gotoxy(24, 9);

		std::cout << "Проверьте правильность номера!" << std::endl;
		Sleep(1200);
		system("cls");
		SetColor(White, Black);
		Auth* instance = new Auth();
		instance->AuthMenu(Person);
	}

}


void Auth::Register(User& Person) {

	std::string temp_Login, temp_Password, temp_PhoneNumber;
	int x = 3, y = 3;

	Frame();
	gotoxy(34, 1);
	SetColor(LightGreen, Black);
	cout << "РЕГИСТРАЦИЯ";


	//LOGIN
	SetColor(White, Black);
	gotoxy(x, y);
	cout << "Логин: ";
	std::getline(std::cin, temp_Login);
	Person.setLogin(temp_Login);
	AlreadyLogin(Person);

	//PASSWORD
	gotoxy(x, ++y);
	cout << "Пароль: ";
	std::getline(std::cin, temp_Password);
	PasswordValid(Person, temp_Password);
	Person.setPassword(md5(temp_Password));
	

	//PHONE NUMBER
	gotoxy(x, ++y);
	cout << "Номер телефона: ";
	std::getline(std::cin, temp_PhoneNumber);
	Person.setPhoneNumber(temp_PhoneNumber);
	PhoneNumberValid(Person);

	//FILE READER
	std::ofstream File("UsersDB//" + Person.getLogin() + ".txt", std::ios::app);
	if (File.is_open()) {
		File << Person.getLogin() << "\n";
		File << Person.getPassword() << "\n";
		File << Person.getPhoneNumber();
		File.close();
		AuthMenu(Person);
	}
	else {
		std::cerr << "Ошибка, файл не открыт!\n";
	}

}

void Auth::Login(User& Person) {

	std::string temp_Login, temp_Password, filePassword;
	bool isUser, isAdmin;

	Frame();
	gotoxy(34, 1);
	SetColor(LightGreen, Black);
	cout << "АВТОРИЗАЦИЯ";
	int x = 3, y = 3;
	SetColor(White, Black);
	
	gotoxy(x, y);
	cout << "Логин: ";
	std::getline(std::cin, temp_Login);
	Person.setLogin(temp_Login);
	
	isUser = fs::exists("UsersDB//" + temp_Login + ".txt");
	isAdmin = fs::exists("AdminsDB//" + temp_Login + ".txt");

	if (isUser) {

		std::ifstream regFile("UsersDB//" + temp_Login + ".txt");

		if (!regFile) {

			system("cls");
			Frame();
			gotoxy(28, 9);
			SetColor(LightRed, Black);
			cout << "Пользователь не найден!" << endl;
			Sleep(1200);
			system("cls");
			SetColor(White, Black);
			Auth* instance = new Auth();
			instance->AuthMenu(Person);
		}

		std::getline(regFile, temp_Login);

		gotoxy(x, ++y);
		std::cout << "Пароль: ";
		std::getline(std::cin, temp_Password);

		std::getline(regFile, filePassword);

		if (regFile.is_open()) {

			system("cls");
			Frame();


			if (filePassword == md5(temp_Password)) {
				gotoxy(29, 9);
				SetColor(LightGreen, Black);
				cout << "Авторизация успешна!" << endl;
				regFile.close();
				Sleep(1500);
				system("cls");
				SetColor(White, Black);

			}
			else {
				gotoxy(26, 9);
				SetColor(LightRed, Black);
				cout << "Неверный логин или пароль" << endl;
				regFile.close();
				Sleep(1500);
				system("cls");
				SetColor(White, Black);

				Auth* instance = new Auth();
				instance->AuthMenu(Person);

			}
		}
	}

	if (isAdmin) {
		
		std::ifstream AdminFile("AdminsDB//" + temp_Login + ".txt");

		std::getline(AdminFile, temp_Login);

		gotoxy(x, ++y);
		std::cout << "Пароль: ";
		std::getline(std::cin, temp_Password);

		std::getline(AdminFile, filePassword);

		if (AdminFile.is_open()) {

			system("cls");
			Frame();


			if (filePassword == md5(temp_Password)) {
				gotoxy(29, 9);
				SetColor(LightGreen, Black);
				cout << "Авторизация успешна!" << endl;
				AdminFile.close();
				Sleep(1500);
				system("cls");
				SetColor(White, Black);
				AdminMenu(Person);
			}
			else {
				gotoxy(26, 9);
				SetColor(LightRed, Black);
				cout << "Неверный логин или пароль" << endl;
				AdminFile.close();
				Sleep(1500);
				system("cls");
				SetColor(White, Black);

				Auth* instance = new Auth();
				instance->AuthMenu(Person);
			}
		}

		
	}

	
	

	
	
	


}

void Auth::AuthMenu(User& Person) {
	
	Frame();
	ConsoleCursor(false);

	Test test;
	Menu menu;

	std::vector<std::string> objMenu { 
		"> ЗАРЕГИСТРИРОВАТЬСЯ", 
		"> ВОЙТИ", 
		"> GITHUB",
		"> ВЫЙТИ" 
	};


	int select = menu.select_vertical(objMenu, Center, 8);

	switch (select)
	{
	case 0:
		Register(Person);
		break;
	case 1:
		Login(Person);
		test.TestMenu(Person);
		break;
	case 2:
		ShellExecute(0, L"open", L"https://github.com/NaiveeDev/testSystem", NULL, NULL, SW_SHOWDEFAULT);
		AuthMenu(Person);
		break;
	default:
		break;
	}
	

}

void Auth::AdminMenu(User& Person) {

	Frame();
	ConsoleCursor(false);

	int x = 57, y = 2;
	gotoxy(x, y);

	cout << "Вы вошли как: ";
	SetColor(LightRed, Black);
	cout << Person.getLogin();

	SetColor(White, Black);


	Menu menu;

	std::vector<std::string> objAMenu {
		"> УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ",
		"> РЕДАКТИРОВАНИЕ",
		"> УПРАВЛЕНИЕ ТЕСТАМИ",
		"> ВЫЙТИ"
	};


	int select = menu.select_vertical(objAMenu, Center, 8);

	switch (select)
	{

	case 0:
		AddAdmin(Person);

	default:
		break;
	}

}

void Auth::AddAdmin(User& Person) {

	Frame();
	int x, y;
	std::string Login, Password, PhoneNumber;
	SetColor(LightGreen, Black);
	gotoxy(x = 10, y = 2);
	
	cout << "Чтобы добавить Админа, заполните поля ниже.";
	gotoxy(x = 13, y = 3);
	cout << "Если пользователь уже существует, он получит права Админа";

	SetColor(White, Black);
	gotoxy(x = 3, y = 6);
	cout << "Логин: ";
	std::getline(std::cin, Login);
	Person.setLogin(Login);
	AlreadyLogin(Person, true);

	gotoxy(x = 3, y = 7);
	cout << "Пароль: ";
	std::getline(std::cin, Password);
	Person.setPassword(Password);
	PasswordValid(Person, Password);

	gotoxy(x = 3, y = 8);
	cout << "Телефон: ";
	std::getline(std::cin, PhoneNumber);
	Person.setPhoneNumber(PhoneNumber);
	PhoneNumberValid(Person);

	std::ofstream File("AdminsDB//" + Person.getLogin() + ".txt", std::ios::app);
	if (File.is_open()) {
		File << Person.getLogin() << "\n";
		File << md5(Person.getPassword()) << "\n";
		File << Person.getPhoneNumber();
		File.close();
		AdminMenu(Person);
	}
	else {
		SetColor(LightRed, Black);
		std::cerr << "Ошибка, файл не открыт!\n";
	}

}

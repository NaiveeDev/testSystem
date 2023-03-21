#include "Auth.h"
#include "menuFunc.h"
#include "md5.h"
#pragma comment(lib,"shell32")


using std::cout; using std::endl;


//LOGIN VALIDATION
void AlreadyLogin(User Person) {

	std::ifstream File("UsersDB//" + Person.getLogin() + ".txt");

	if (File) {

		int x, y;
		x = 2;
		y = 1;

		SetColor(LightRed, Black);
		Frame();
		gotoxy(x, y);

		std::cout << "Пользователь уже зарегистрирован!" << std::endl;
		Sleep(1200);
		system("cls");
		SetColor(White, Black);
		Auth* instance = new Auth();
		instance->AuthMenu(Person);
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

	if (withSpace(TempPassword))
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

	Frame();

	gotoxy(34, 1);
	SetColor(LightGreen, Black);
	cout << "АВТОРИЗАЦИЯ";

	int x = 3, y = 3;

	SetColor(White, Black);
	gotoxy(x, y);
	
	cout << "Логин: ";
	std::getline(std::cin, temp_Login);
	
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
	//Person.setPassword(temp_Password);

	

	if (regFile.is_open()) {
		
		system("cls");
		Frame();

		std::getline(regFile, filePassword);
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

void Auth::AuthMenu(User& Person) {
	
	Frame();
	ConsoleCursor(false);

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
	case 1:
		Login(Person);
	case 2:

		ShellExecute(0, L"open", L"https://github.com/NaiveeDev/testSystem", NULL, NULL, SW_SHOWDEFAULT);
		AuthMenu(Person);
	default:
		break;
	}
	

}

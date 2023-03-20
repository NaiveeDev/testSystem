#pragma once
#include "imports.h"


using namespace std;


enum DIRECTION
{
	UP_DIR = 72, DOWN_DIR = 80, LEFT_DIR = 75, RIGHT_DIR = 77, ESC = 27, ENTER = 13
};

enum class HORIZONTAL_POSITION
{
	LEFT, CENTER, RIGHT
};

enum class VERTICAL_POSITION
{
	TOP, CENTER, BOTTOM
};

enum class ALLIGNMENT
{
	LEFT, CENTER, RIGHT
};

enum Color
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

inline void SetColor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

inline void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline int CenterText() {

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(wHnd, &consoleInfo);
	int width = consoleInfo.dwSize.X;
	int height = consoleInfo.dwSize.Y;

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(wHnd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	int maxLength = 0;

	int x;
	x = (width - maxLength) / 2;
	return x;
}

inline void Frame()
{
	gotoxy(0, 0);
	setlocale(LC_ALL, "C");
	cout << static_cast <char> (201);
	for (int i = 0; i < 78; i++)
		cout << static_cast <char> (205);
	cout << static_cast <char> (187);

	for (int j = 0; j < 18; j++)
	{
		cout << static_cast <char> (186);
		for (int i = 0; i < 78; i++)
			cout << " ";
		cout << static_cast <char> (186);
	}

	cout << static_cast <char> (200);
	for (int i = 0; i < 78; i++)
		cout << static_cast <char> (205);
	cout << static_cast <char> (188);
	setlocale(LC_ALL, "Russian");
}

inline int vertical_menu(char** menuItem, HORIZONTAL_POSITION hp, VERTICAL_POSITION vp, ALLIGNMENT allignment)
{

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(wHnd, &consoleInfo);
	int width = consoleInfo.dwSize.X;
	int height = consoleInfo.dwSize.Y;

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(wHnd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);



	int size = _msize(menuItem) / sizeof(char*);
	int maxLength = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (strlen(menuItem[i]) > maxLength)
			maxLength = strlen(menuItem[i]);
	}

	int x, y;

	switch (hp)
	{
	case HORIZONTAL_POSITION::LEFT:     x = 1;                       break;
	case HORIZONTAL_POSITION::CENTER:   x = (width - maxLength) / 2; break;
	case HORIZONTAL_POSITION::RIGHT:    x = width - maxLength - 1;   break;
	}

	switch (vp)
	{
	case VERTICAL_POSITION::TOP:      y = 1;                   break;
	case VERTICAL_POSITION::CENTER:   y = (height - size) / 2; break;
	case VERTICAL_POSITION::BOTTOM:   y = height - size - 1;   break;
	}

	char** menuItemChanged = new char* [size];
	char space[] = "                              ";
	for (size_t i = 0; i < size; i++)
	{
		menuItemChanged[i] = new char[maxLength + 1];
		menuItemChanged[i][0] = '\0';
		switch (allignment)
		{
		case ALLIGNMENT::LEFT:
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			break;
		case ALLIGNMENT::CENTER:
			strncat(menuItemChanged[i], space, (maxLength - strlen(menuItem[i])) / 2);
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]) - (maxLength - strlen(menuItem[i])) / 2);
			break;
		case ALLIGNMENT::RIGHT:
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			strcat(menuItemChanged[i], menuItem[i]);
			break;
		}

	}

	int position = 0;

	char choise;

	do
	{
		for (size_t i = 0; i < size; i++)
		{
			if (i == position)
			{
				SetColor(Black, White);
			}
			else
			{
				SetColor(White, Black);
			}
			gotoxy(x, y + i);
			cout << setw(maxLength) << menuItemChanged[i];
		}

		//click
		choise = _getch();

		switch (choise)
		{
		case UP_DIR:
			if (position > 0)
				position--;
			break;
		case DOWN_DIR:
			if (position < size - 1)
				position++;
			break;
		case ESC:
			return -1;

		default: break;
		}
	} while (choise != ENTER);

	for (size_t i = 0; i < 2; i++)
	{

		SetColor(White, Black);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);

		SetColor(Black, White);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);
	}
	SetColor(White, Black);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	///// Alt CLS
	char* voidItem = new char[maxLength + 1];
	for (size_t i = 0; i < maxLength; i++) voidItem[i] = ' ';
	voidItem[maxLength] = '\0';
	for (size_t i = 0; i < size; i++)
	{
		gotoxy(x, y + i);
		cout << voidItem;
	}

	//system("cls");
	return position;
}

inline void ClearMemory(char** arr)
{
	int size = _msize(arr) / sizeof(char*);
	for (size_t i = 0; i < size; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

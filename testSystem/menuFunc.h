#pragma once
#include "imports.h"

using std::cout; using std::endl;


enum DIRECTION
{
	UP_DIR = 72, DOWN_DIR = 80, LEFT_DIR = 75, RIGHT_DIR = 77, ESC = 27, ENTER = 13
};

enum HorizontalAlignment
{
	Center, Left, Right
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
	std::cout << static_cast <char> (201);
	for (int i = 0; i < 78; i++)
		std::cout << static_cast <char> (205);
	std::cout << static_cast <char> (187);

	for (int j = 0; j < 18; j++)
	{
		std::cout << static_cast <char> (186);
		for (int i = 0; i < 78; i++)
			std::cout << " ";
		std::cout << static_cast <char> (186);
	}

	std::cout << static_cast <char> (200);
	for (int i = 0; i < 78; i++)
		std::cout << static_cast <char> (205);
	std::cout << static_cast <char> (188);
	setlocale(LC_ALL, "Russian");
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

class Menu {
public:
	static int select_vertical(std::vector <std::string> menu, HorizontalAlignment ha, int y = 12)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO start_attribute;
		GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
		int backColor = start_attribute.wAttributes & 15;
		int textColor = (start_attribute.wAttributes >>= 4) & 15;
		int maxLen = 0;
		for (size_t i = 0; i < menu.size(); i++)
		{
			menu[i] = " " + menu[i] + " ";
			if (menu[i].length() > maxLen)
				maxLen = menu[i].length();
		}
		int x = 0;
		switch (ha)
		{
		case Center: x = 40 - maxLen / 2; break;
		case Left:   x = 0;	              break;
		case Right:  x = 80 - maxLen;     break;
		}
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(textColor, backColor);
					gotoxy(x, y + i);
					cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					cout << menu[i] << endl;
					SetColor(backColor, textColor);
				}
				else
				{
					SetColor(backColor, textColor);
					gotoxy(x, y + i);
					cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					cout << menu[i] << endl;
					SetColor(textColor, backColor);
				}
			}
			c = _getch();
			switch (c)
			{
			case 72: if (pos > 0)               pos--; break; // up
			case 80: if (pos < menu.size() - 1) pos++; break; // down
			case 13: break;
			}
		} while (c != 13);

		for (size_t i = 0; i < 2; i++)
		{
			SetColor(backColor, textColor);
			gotoxy(x, y + pos);
			cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			cout << menu[pos] << endl;
			Sleep(200);
			SetColor(textColor, backColor);
			gotoxy(x, y + pos);
			cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			cout << menu[pos] << endl;
			SetColor(backColor, textColor);
			Sleep(200);
		}
		SetColor(backColor, textColor);
		system("cls");
		return pos;
	}

};

//void ConsoleCursor(bool isVisible = true) {
//
//	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_CURSOR_INFO cursorInfo;
//
//	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
//	cursorInfo.bVisible = isVisible;
//	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
//
//}
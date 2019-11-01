#ifndef _CONSOLE_
#define _CONSOLE_
#include <Windows.h>

class Console
{
public:
	static int WindowHeight;
	static int WindowWidth;

	static HANDLE hConsole;


	static void GotoXY(int column, int line)
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		SetConsoleCursorPosition(hConsole, coord);
	}


	static void TextColor(int color)
	{
		SetConsoleTextAttribute(hConsole, color);
	}


	static void ClearScreen()
	{
		CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
		COORD	Home = { 0, 0 };
		DWORD	dummy;

		GetConsoleScreenBufferInfo(hConsole, &csbiInfo);

		FillConsoleOutputCharacter(hConsole, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
		csbiInfo.dwCursorPosition.X = 0;
		csbiInfo.dwCursorPosition.Y = 0;
		SetConsoleCursorPosition(hConsole, csbiInfo.dwCursorPosition);
	}

	static void Nocursortype()
	{
		CONSOLE_CURSOR_INFO Info;
		Info.bVisible = FALSE;
		Info.dwSize = 20;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
	}
};
#endif





#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <malloc.h>
#include <time.h>
#include "Conlib.h"
#ifdef __GNUC__

#include <windows.h>

#include <mingw32/conio.h>

#else	// default: MSVC

#include <wtypes.h>
#include <wincon.h>
#include <conio.h>

#endif // __GNUC__


int GotoXY(int x, int y) {
	COORD pos = { x, y };

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleCursorPosition(hStdOut, pos);
}

int MaxXY(int *px, int *py) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		*px = csbi.srWindow.Right - csbi.srWindow.Left;
		*py = csbi.srWindow.Bottom - csbi.srWindow.Top;
		return 1;
	}
	return 0; // error
}

int ClearConsole() {
	int mx, my;

	if (MaxXY(&mx, &my)) {
		COORD szBuf = { mx + 1, my + 1 };
		COORD BufferCoord = { 0, 0 };
		SMALL_RECT srWriteRegion = { 0, 0, mx, my };

		CHAR_INFO *lpBuffer = (CHAR_INFO *)calloc(szBuf.X * szBuf.Y, sizeof(CHAR_INFO));

		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int result = WriteConsoleOutput(hStdOut, lpBuffer, szBuf, BufferCoord, &srWriteRegion);
		free(lpBuffer);
		return result;
	}
	return 0; // error
}

int SetColor(short color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hStdOut, (short)color);
}

int ConShowCursor(int bVisible) {
	CONSOLE_CURSOR_INFO ci;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &ci)) {
		ci.bVisible = bVisible;
		return SetConsoleCursorInfo(hStdOut, &ci);
	}

	return 0; // error
}
////////////////////////////////////////////////////////
// Input functions

int KeyPressed() {
	return _kbhit();
}

int GetKey() {
	int ch = _getch();

	if (ch == 0 || ch == 224) // extended code
		return -_getch();

	return ch;
}

void frame(int maxX, int maxY, int foregroung) {
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			if (((i == 0) || (j == 0)) || ((i == maxX - 1) || (j == maxY - 1))) {
				GotoXY(i, j);
				SetColor(foregroung);
				wprintf(L" ");
			}
		}
	}
	ConShowCursor(0);
}

#include "GameMenu.h"
#include "Conlib.h"
#include "Menu.h"
#include <stdio.h>
#include <malloc.h>
#include <io.h>
#include <fcntl.h>

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	int flag, exit = 0;
	int maxX = 0, maxY = 0;
	char Name[25] = "Player";
	while (!exit) {
		ClearConsole();
		flag = 0;
		flag = Menu(*&maxX, *&maxY);
		switch (flag) {
		case 1: {
			exit = ExitGame(*&maxX, *&maxY);
			flag = 2;
			break;
		}
		case 2: {
			int Score=0 ;
			double Time =0;
			GameMenu(*&maxX, *&maxY, &Score, Name, &Time);
			//WriteRecord(Score, Time);
			//
			break;
		}
		case 3: {
			ClearConsole();
			GotoXY(maxX / 2 - maxX / 8, maxY / 4);
			wprintf(L"Records");
			getchar();
			break;
		}
		case 4: {
			ClearConsole();
			GotoXY(maxX / 2 - maxX / 8, maxY / 4);
			wprintf(L"Map Editor");
			getchar();
			break;
		}
		case 5: {
			ClearConsole();
			GotoXY(maxX / 2 - maxX / 8, maxY / 4);
			wprintf(L"Developers");
			getchar();
			break;
		}
		default:
			break;
		}
	}
	return 0;
	//init_game(1, 0);
	
	return 0;
}
#include "Conlib.h"
#include "Menu.h"
#include "Checkers.h"
#include "GameMenu.h"

void GameMenu(int maxX, int maxY, int* Score, char* Name, double* Time) {
	ClearConsole();
	int flag = 0;
	int key;
	int maxXS, maxYS; // reference
	int X_Pos = 1, Y_Pos = 1;
	int firstPColor = 0x0010, secondPColor = 0x0040;
	//1 - player vs player; 2 - player vs pc;  3 - pc vs pc
	int GameMode = 1;
	MaxXY(&maxX, &maxY);
	maxXS = maxX;
	maxYS = maxY;
	Y_Pos = maxY / 4;
	frame(maxX, maxY, FOREGROUND_RED);
	SetColor(FOREGROUND_BLUE);
	GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
	wprintf(L"->");
	while (!flag) {
		MaxXY(&maxX, &maxY);
		if (maxXS != maxX || maxYS != maxY) {
			maxXS = maxX;
			maxYS = maxY;
			ClearConsole();
			Y_Pos = maxY / 4;
			GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
			wprintf(L"->");
			ConShowCursor(0);
		}
		frame(maxX, maxY, FOREGROUND_RED);

		SetColor(FOREGROUND_BLUE);
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 - 1);
		wprintf(L"Game Settings");
		SetColor(FOREGROUND_RED);
		GotoXY(maxX / 2 - maxX / 20, maxY / 4);
		wprintf(L"Play");
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 2);
		wprintf(L"GameMode:");
		GotoXY(maxX / 2 - maxX / 20 + 16, maxY / 4 + 2);
		SetColor(FOREGROUND_BLUE);
		wprintf(L" %d ", GameMode);
		SetColor(FOREGROUND_RED);
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 4);
		wprintf(L"Color of checkers FP:");
		GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 4);
		SetColor(firstPColor);
		wprintf(L"&&");
		SetColor(FOREGROUND_RED);
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 6);
		wprintf(L"Color of checkers SP:");
		GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 6);
		SetColor(secondPColor);
		wprintf(L" S");
		SetColor(FOREGROUND_RED);
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 8);
		wprintf(L"Back to Main Menu");
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 10);
		SetColor(FOREGROUND_BLUE);
		wprintf(L"!!!WARNING!!!");
		GotoXY(maxX / 2 - maxX / 5, maxY / 4 + 11);
		wprintf(L"Only in game settings you can change frame size for game!");

		key = GetKey();

		SetColor(0x0000 | 0x0000);
		if (key == KEY_ESC)
			flag = 1;
		if ((key == KEY_UP) && (Y_Pos == maxY / 4)) {
			GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
			wprintf(L"  ");
			Y_Pos = maxY / 4 + 8;
		}
		else if (key == KEY_UP) {
			GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
			wprintf(L"  ");
			Y_Pos = Y_Pos - 2;
		}
		if ((key == KEY_DOWN) && (Y_Pos == maxY / 4 + 8)) {
			GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
			wprintf(L"  ");
			Y_Pos = maxY / 4;
		}
		else if (key == KEY_DOWN) {
			GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
			wprintf(L"  ");
			Y_Pos = Y_Pos + 2;
		}
		if ((key == KEY_LEFT) && (Y_Pos == maxY / 4 + 6)) {
			if (secondPColor > 0) {
				secondPColor -= 20;
				GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 4);
				SetColor(firstPColor);
				wprintf(L"  ");
				SetColor(FOREGROUND_RED);
			}
		}
		else if ((key == KEY_LEFT) && (Y_Pos == maxY / 4 + 4)) {
			if (firstPColor > 0) {
				firstPColor -= 20;
				GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 4);
				SetColor(firstPColor);
				wprintf(L"  ");
				SetColor(FOREGROUND_RED);
			}
		}
		else if ((key == KEY_LEFT) && (Y_Pos == maxY / 4 + 2)) {
			GotoXY(maxX / 2 - maxX / 20 + 16, maxY / 4 + 2);
			if (GameMode > 1) {
				GameMode--;
			}
			SetColor(FOREGROUND_BLUE);
			wprintf(L" %d", GameMode);
			SetColor(FOREGROUND_RED);
		}
		if ((key == KEY_RIGHT) && (Y_Pos == maxY / 4 + 6)) {
			if (secondPColor < 257) {
				secondPColor += 20;
				GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 6);
				SetColor(secondPColor);
				wprintf(L"  ");
				SetColor(FOREGROUND_RED);
			}
		}
		else if ((key == KEY_RIGHT) && (Y_Pos == maxY / 4 + 4)) {
			if (firstPColor < 257) {
				firstPColor += 1;
				GotoXY(maxX / 2 - maxX / 20 + 21, maxY / 4 + 4);
				SetColor(firstPColor);
				wprintf(L"  ");
				SetColor(FOREGROUND_RED);
			}
		}
		else if ((key == KEY_RIGHT) && (Y_Pos == maxY / 4 + 2)) {
			GotoXY(maxX / 2 - maxX / 20 + 16, maxY / 4 + 2);
			if (GameMode < 3) {
				GameMode++;
			}
			SetColor(FOREGROUND_BLUE);
			wprintf(L" %d", GameMode);
			SetColor(FOREGROUND_RED);
		}
		if ((key == KEY_ENTER) && (Y_Pos == maxY / 4)) {
			/*Game*/
			flag = 3;
			SetColor(0);
			SetColor(3);
			system("cls");
			GotoXY(0, 0); //field start place
			//for (int wtf = 0; wtf < 1000; wtf++) 
			init_game(GameMode, 0, firstPColor, secondPColor);
			system("cls");
			Score = 0/*ReturnScore()*/;
			Time = 0/*ReturnTime()*/;
			SetColor(FOREGROUND_BLUE);
			GotoXY(maxX / 2 - maxX / 20, maxY / 4 - 1);
			wprintf(L"Game Over");
			GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 1);
			//wprintf(L"Your score:%d", Score);
			GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 3);
			//wprintf(L"Your time:%lf", Time);
			//getchar();
			if (Y_Pos == maxY / 4 + 2) /*Records*/ {
				flag = 3;
			}
			else if (Y_Pos == maxY / 4 + 4) /*Map Editor*/ {
				flag = 4;
			}
			else if (Y_Pos == maxY / 4 + 6) /*Developers*/ {
				flag = 5;
			}
			else if (Y_Pos == maxY / 4 + 8) /*Exit*/ {
				flag = 1;
			}
		}
		else if ((key == KEY_ENTER) && (Y_Pos == maxY / 4 + 4)) {
			int k = 2;
			for (int i = 0; i < 256;) {
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 4);
				k++;
				SetColor(i);
				wprintf(L".");
				i += 16;
				if (k == 17) {
					break;
				}
			}
			key = 0;
			k = 2;
			int i = 0;
			int temporary_BG = i;
			int temporary_FG = i % 0x0010;
			while (key != KEY_ENTER) {
				//
				SetColor(1);
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 3);
				wprintf(L"↓");
				key = GetKey();
				if (key == KEY_RIGHT && k < 17) {
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 3);
					wprintf(L" ");
					k++;
					i += 16;
					temporary_BG = i;
				}
				else if (key == KEY_LEFT && k > 2) {
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 3);
					SetColor(0);
					wprintf(L" ");
					k--;
					i -= 16;
					temporary_BG = i;
				}
				else if (key == KEY_DOWN && i % 16 < 15) {
					i++;
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 4);
					SetColor(i);
					wprintf(L".");
					temporary_FG = i % 0x0010;
				}
				else if (key == KEY_UP && i % 16 > 0) {
					i--;
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 4);
					SetColor(i);
					wprintf(L".");
					temporary_BG = i % 0x0010;
				}
			}
			GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 3);
			SetColor(0);
			wprintf(L" ");
			k = 2;
			for (int i = 0; i < 256;) {
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 4);
				k++;
				SetColor(0);
				wprintf(L" ");
				i += 16;
				if (k == 17) {
					break;
				}
			}
			firstPColor = (temporary_BG | temporary_FG);
		}
		else if ((key == KEY_ENTER) && (Y_Pos == maxY / 4 + 6)) {
			int k = 2;
			for (int i = 0; i < 256;) {
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 6);
				k++;
				SetColor(i);
				wprintf(L".");
				i += 16;
				if (k == 17) {
					break;
				}
			}
			key = 0;
			k = 2;
			int i = 0;
			int temporary_BG = i;
			int temporary_FG = i % 0x0010;
			while (key != KEY_ENTER) {
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 5);
				SetColor(1);
				wprintf(L"↓");
				key = GetKey();
				if (key == KEY_RIGHT && k < 17) {
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 5);
					wprintf(L" ");
					k++;
					i += 16;
					temporary_BG = i;
				}
				else if (key == KEY_LEFT && k > 2) {
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 5);
					SetColor(0);
					wprintf(L" ");
					k--;
					i -= 16;
					temporary_BG = i;
				}
				else if (key == KEY_DOWN && i % 16 < 15) {
					i++;
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 6);
					SetColor(i);
					wprintf(L".");
					temporary_FG = i % 0x0010;

				}
				else if (key == KEY_UP && i % 16 > 0) {
					i--;
					GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 6);
					SetColor(i);
					wprintf(L".");
					temporary_BG = i % 0x0010;
				}
			}
			GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 5);
			SetColor(0);
			wprintf(L" ");
			for (int i = 0; i < 256;) {
				GotoXY(maxX / 2 - maxX / 20 + 21 + k, maxY / 4 + 6);
				k++;
				SetColor(0);
				wprintf(L" ");
				i += 16;
				if (k == 17) {
					break;
				}
			}
			secondPColor = (temporary_BG | temporary_FG);
		}
		else if ((key == KEY_ENTER) && (Y_Pos == maxY / 4 + 8)) {
			flag = 1;
		}
		SetColor(FOREGROUND_BLUE);
		GotoXY(maxX / 2 - maxX / 20 - 2, Y_Pos);
		wprintf(L"->");
		GotoXY(X_Pos, Y_Pos);
	}
}

#include "Checkers.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>

static checker checker_init(char* field[], checker unit, int i, int j, bool color)
{
	unit.alive = 1;
	unit.color = color;
	unit.queen = 0;
	unit.pos[0] = i;
	unit.pos[1] = j;
	if (color) {
		field[i][j] = 'B';
	}
	else {
		field[i][j] = 'W';
	}
	return unit;
}

static char** field_init()
{
	char** field = malloc(8 * sizeof(char*));
	if (field == NULL) {
		return NULL;
	}
	for (char i = 0; i < 8; i++) {
		field[i] = malloc(8 * sizeof(int));
		if (field[i] == NULL) {
			return NULL;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			field[i][j] = ' ';
			if ((i + j) % 2 == 0) {
				field[i][j] = '#';
			}
		}
	}
	return field;
}

static void player_init(char* field[], playerinf* Player1, playerinf* Player2, bool Player1Color)
{
	Player1->color = Player1Color;
	Player2->color = !(Player1->color);
	int k = 0;
	int c = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {
				if (Player1->color == 0 && i > 4) {
					Player1->checkers[k] = checker_init(field, Player1->checkers[k], i, j, Player1->color);
					k++;
				}
				else if (Player1->color == 1 && i < 3) {
					Player1->checkers[k] = checker_init(field, Player1->checkers[k], i, j, Player1->color);
					k++;
				}
				if (Player2->color == 0 && i > 4) {
					Player2->checkers[c] = checker_init(field, Player2->checkers[c], i, j, Player2->color);
					c++;
				}
				else if (Player2->color == 1 && i < 3) {
					Player2->checkers[c] = checker_init(field, Player2->checkers[c], i, j, Player2->color);
					c++;
				}
			}
		}
	}
}

char** init_game(int GameMode, bool Player1Color, int p1ChClr, int p2ChClr)
{
	srand(time(NULL));
	char (*game)(char* field[], playerinf * Player1, playerinf * Player2, int p1ChClr, int p2ChClr, int numb_of_move, int* ai_turns, int* ai_turns_2);
	int* ai_turns = (int*)malloc(50 * sizeof(int));
	if (ai_turns == NULL) {
		exit(13123);//RENAME
	}
	int* ai_turns_2 = (int*)malloc(50 * sizeof(int));
	if (ai_turns_2 == NULL) {
		exit(13123);//RENAME
	}
	for (int i = 0; i < 50; i++) {
		ai_turns[i] = 0;
		ai_turns_2[i] = 0;
	}
	char** field = NULL;
	playerinf* Player1;
	playerinf* Player2;
	Player1 = (playerinf*)malloc(sizeof(playerinf));
	Player2 = (playerinf*)malloc(sizeof(playerinf));
	if ((field=field_init()) == NULL && Player1 == NULL && Player2 == NULL) {
		return NULL;
	}
	switch (GameMode) {
	case 0:
		game = NULL;
		break;
	case 1:
		game = player_vs_player;
		break;
	case 2:
		game = player_vs_ai;
		break;
	case 3:
		game = ai_vs_ai;
		break;
	default:
		return NULL;
	}
	player_init(field, Player1, Player2, Player1Color);
	int numb_of_move = 0;
	while (true) {
		if (numb_of_move == 50) {
			break;
		}
		if (game == NULL) {
			break;
		}
		if (game(field, Player1, Player2, p1ChClr, p2ChClr, numb_of_move, ai_turns, ai_turns_2, -1)!=NULL) {
			break;
		}
		numb_of_move += 1;
	}
	free(Player1);
	free(Player2);
	for (int i = 0; i < 8; i++) {
		free(field[i]);
	}
	free(field);
	free(ai_turns);
	free(ai_turns_2);
	//assert(!_CrtDumpMemoryLeaks());//just for tests
	return field;
}

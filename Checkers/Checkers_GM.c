#include "Checkers_GM.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>

static bool gs_movement_posibility(char* field[], playerinf* Player, int i, bool smbd_can_move)
{
	int** pos = (int**)malloc(2 * sizeof(int*));
	if (pos == NULL) {
		exit(1488); //RENAME
	}
	for (int j = 0; j < 2; j++) {
		pos[j] = (int*)malloc(2 * sizeof(int));
		if (pos[j] == NULL) {
			exit(1488); //RENAME
		}
	}
	int** pot_mov = NULL;
	if (Player->checkers[i].queen) {
		if (!smbd_can_move) {
			pos[0][0] = Player->checkers[i].pos[0];
			pos[0][1] = Player->checkers[i].pos[1];
			pot_mov = potential_queen_movement(field, Player, pos);
			for (int j = 0; j < 28; j++) {
				if (pot_mov[j][0] != -1) {
					for (int j = 0; j < 2; j++) {
						free(pos[j]);
					}
					free(pos);
					for (int i = 0; i < 28; i++) {
						free(pot_mov[i]);
					}
					free(pot_mov);
					return true;
				}
			}
		}
		for (int i = 0; i < 28; i++) {
			free(pot_mov[i]);
		}
		free(pot_mov);
	}
	if (!Player->checkers[i].queen) {
		if (!smbd_can_move) {
			pos[0][0] = Player->checkers[i].pos[0];
			pos[0][1] = Player->checkers[i].pos[1];
			pot_mov = potential_checker_movement(field, Player, pos);
			for (int j = 0; j < 8; j++) {
				if (pot_mov[j][0] != -1) {
					for (int j = 0; j < 2; j++) {
						free(pos[j]);
					}
					free(pos);
					for (int i = 0; i < 8; i++) {
						free(pot_mov[i]);
					}
					free(pot_mov);
					return true;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			free(pot_mov[i]);
		}
		free(pot_mov);
	}
	for (int j = 0; j < 2; j++) {
		free(pos[j]);
	}
	free(pos);
	return false;
}
/*
Returns:
0 - game in progress
1 - Player 1 win
2 - Player 2 win
3 - draw
*/
static int game_situation(char* field[], playerinf* Player1, playerinf* Player2, int turn)//0 - white turn, 1 - black turn
{
	int count_alive_1 = 0;
	int count_alive_2 = 0;
	/*---------------------------------*/
	/*"Do we have alive checkers?" test*/
	for (int i = 0; i < 12; i++) {
		if (Player1->checkers[i].alive) {
			count_alive_1++;
		}
		if (Player2->checkers[i].alive) {
			count_alive_2++;
		}
		if (count_alive_1 > 0 && count_alive_2 > 0) {
			break;
		}
	}
	if (count_alive_2 == 0) {
		return 1;
	}
	else if (count_alive_1 == 0) {
		return 2;
	}
	/*---------------------------------*/
	/*"Can even one checker make a move?" test*/
	bool smbd_can_move_1 = false;
	bool smbd_can_move_2 = false;
	for (int i = 0; i < 12; i++) {
		if (!smbd_can_move_1) {
			smbd_can_move_1 = gs_movement_posibility(field, Player1, i, smbd_can_move_1);
		}
		if (!smbd_can_move_2) {
			smbd_can_move_2 = gs_movement_posibility(field, Player2, i, smbd_can_move_2);
		}
		if (smbd_can_move_1 && smbd_can_move_2) {
			break;
		}
	}
	if (!smbd_can_move_1 && turn) {
		return 3;
	}
	else if (!smbd_can_move_2 && !turn) {
		return 3;
	}
	/*---------------------------------*/
	return 0;
}
int print_who_win(char* win, char* lose, bool mode)
{
	int maxX, maxY;
	system("cls");
	MaxXY(&maxX, &maxY);
	GotoXY(maxX / 2 - maxX / 20, maxY / 4 - 1);
	wprintf(L"Game Over");
	if (mode) {
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 1);
		wprintf(L"Player 1 win", win);//DIDN'T work 
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 3);
		wprintf(L"Player 2 lose", lose);//DIDN'T work 
	}
	else {
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 1);
		wprintf(L"Draw");
		GotoXY(maxX / 2 - maxX / 20, maxY / 4 + 3);
		wprintf(L"piew piew");
	}

}
char** player_vs_player(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker)
{
	int** turn;
	turn = malloc(2 * sizeof(int*));
	if (turn == NULL) {
		exit(-3);
	}
	for (int i = 0; i < 2; i++) {
		turn[i] = malloc(2 * sizeof(int));
		if (turn[i] == NULL) {
			exit(-4);
		}
	}
	int gameState = game_situation(field, Player1, Player2, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		player_turn(field, Player1, Player2, turn, p1ChClr, p2ChClr, numb_of_turn, turn, secondTurnChecker);
	}
	if (gameState == 1) {
		print_who_win("Player 1", "Player 2", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		return "end";
	}
	else if (gameState == 2) {
		print_who_win("Player 2", "Player 1", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		return "end";
	}
	else if (gameState == 3) {
		print_who_win("Nobody", "Nobody", 0);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		return "end";
	}
	gameState = game_situation(field, Player1, Player2, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		player_turn(field, Player2, Player1, turn, p1ChClr, p2ChClr, numb_of_turn, turn, secondTurnChecker);
	}
	if (gameState == 1) {
		print_who_win("Player 2", "Player 1", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 2) {
		print_who_win("Player 1", "Player 2", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 3) {
		print_who_win("Nobody", "Nobody", 0);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	for (int i = 0; i < 2; i++) {
		free(turn[i]);
	}
	free(turn);
}

char** player_vs_ai(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker)
{
	if (ai_turns == NULL) {
		exit(13123);//RENAME
	}
	int** turn;
	turn = malloc(2 * sizeof(int*));
	if (turn == NULL) {
		exit(54342);
	}
	for (int i = 0; i < 2; i++) {
		turn[i] = malloc(2 * sizeof(int));
		if (turn[i] == NULL) {
			exit(42342);
		}
	}
	int turns_ai_1[50][2];
	int gameState = game_situation(field, Player1, Player2, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		player_turn(field, Player1, Player2, turn, p1ChClr, p2ChClr, numb_of_turn, turn, secondTurnChecker);

	}
	if (gameState == 1) {
		ai_rebalancing(ai_turns, Player2, 0);
		print_who_win("Player", "AI", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 2) {
		ai_rebalancing(ai_turns, Player2, 1);
		print_who_win("AI", "Player", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 3) {
		print_who_win("Nobody", "Nobody", 0);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	gameState = game_situation(field, Player2, Player1, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		ai_turn(field, Player2, Player1, numb_of_turn, p1ChClr, p2ChClr, 0, ai_turns, secondTurnChecker);
		numb_of_turn++;
	}
	if (gameState == 1) {
		ai_rebalancing(ai_turns, Player2, 1);
		print_who_win("AI", "Player", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 2) {
		ai_rebalancing(ai_turns, Player2, 0);
		print_who_win("Player", "AI", 1);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	else if (gameState == 3) {
		print_who_win("Nobody", "Nobody", 0);
		for (int i = 0; i < 2; i++) {
			free(turn[i]);
		}
		free(turn);
		getch();
		return "end";
	}
	for (int i = 0; i < 2; i++) {
		free(turn[i]);
	}
	free(turn);
}

char** ai_vs_ai(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker)
{
	print_field(field, p1ChClr, p2ChClr);
	int gameState = game_situation(field, Player1, Player2, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		ai_turn(field, Player1, Player2, numb_of_turn, p1ChClr, p2ChClr, 0, ai_turns, secondTurnChecker);
	}
	if (gameState == 1) {
		ai_rebalancing(ai_turns, Player1, 1);
		ai_rebalancing(ai_turns_2, Player2, 0);
		return "end";
	}
	else if (gameState == 2) {
		ai_rebalancing(ai_turns_2, Player2, 1);
		ai_rebalancing(ai_turns, Player1, 0);
		return "end";
	}
	else if (gameState == 3) {
		return "end";
	}
	print_field(field, p1ChClr, p2ChClr);
	gameState = game_situation(field, Player2, Player1, ((Player1->color) ? 1 : 0));
	if (gameState == 0) {
		ai_turn(field, Player2, Player1, numb_of_turn, p1ChClr, p2ChClr, 0, ai_turns_2, secondTurnChecker);
	}
	if (gameState == 1) {
		ai_rebalancing(ai_turns_2, Player2, 1);
		ai_rebalancing(ai_turns, Player1, 0);
		return "end";
	}
	else if (gameState == 2) {
		ai_rebalancing(ai_turns_2, Player2, 0);
		ai_rebalancing(ai_turns, Player1, 1);
		return "end";
	}
	else if (gameState == 3) {
		return "end";
	}
	return NULL;
}
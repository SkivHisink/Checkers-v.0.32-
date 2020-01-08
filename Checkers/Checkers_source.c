#include "Checkers_source.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
//no Leaks
void print_field(char* field[], int p1ChClr, int p2ChClr)
{
	int maxX, maxY;
	MaxXY(&maxX, &maxY);
	for (int i = 0; i < 16; i++) {
		GotoXY(maxX / 2 - 7, maxY / 5 + i);
		SetColor(FIELD_COLOR);
		wprintf("|");
		for (int j = 0; j < 8; j++) {
			if (field[(i + 1) / 2][j] == 'W') {
				SetColor(p1ChClr);
			}
			else if (field[(i + 1) / 2][j] == 'B') {
				SetColor(p2ChClr);
			}

			wprintf(L"%c", field[(i + 1) / 2][j]);
			SetColor(FIELD_COLOR);
			wprintf("|");
		}
		wprintf(L"\n");
		i++;
		GotoXY(maxX / 2 - 7, maxY / 5 + i);
		for (int j = 0; j < 17; j++) {
			if (j % 2 == 0) {
				SetColor(FIELD_COLOR);
				wprintf(L"+");
			}
			else {
				SetColor(FIELD_COLOR);
				wprintf(L"―");
			}
		}
	}
	SetColor(BlackBack | WhiteFore);
}
//no Leaks
static bool move_to(int* pos[], int* pot_mov[], int a)
{
	return pos[1][0] == pot_mov[a][0] && pos[1][1] == pot_mov[a][1];
}
//no Leaks
bool on_board(int* pot_mov[], int a)
{
	return ((pot_mov[a][0] > -1 && pot_mov[a][0] < 8) && (pot_mov[a][1] > -1 && pot_mov[a][1] < 8));
}

//func which find potential place which you can go

int** potential_checker_movement(char* field[], playerinf* Player, int* pos[])
{
	/*
	77##FF##66
	##33##22##
	FF##CC##FF
	##11##00##
	55##FF##44
	*/
	int** pot_mov = (int**)malloc(8 * sizeof(int*));
	if (pot_mov == NULL) {
		exit(443);//RENAME
	}
	for (int i = 0; i < 8; i++) {
		pot_mov[i] = (int*)malloc(2 * sizeof(int));
		if (pot_mov[i] == NULL) {
			exit(444);//RENAME
		}
	}
	int k = 1;
	for (int i = 0; i < 7;) {
		pot_mov[i][0] = pos[0][0] + k;
		pot_mov[i][1] = pos[0][1] + k;
		pot_mov[i + 1][0] = pos[0][0] + k;
		pot_mov[i + 1][1] = pos[0][1] - k;
		pot_mov[i + 2][0] = pos[0][0] - k;
		pot_mov[i + 2][1] = pos[0][1] + k;
		pot_mov[i + 3][0] = pos[0][0] - k;
		pot_mov[i + 3][1] = pos[0][1] - k;
		k++;
		i += 4;
	}
	for (int i = 0; i < 8; i++) {
		if (!(on_board(pot_mov, i))) {
			pot_mov[i][0] = -100;
			pot_mov[i][1] = -100;
		}
		else if (field[pot_mov[i][0]][pot_mov[i][1]] == 'W') {
			pot_mov[i][0] = 8;
			pot_mov[i][1] = 8;
		}
		else if (field[pot_mov[i][0]][pot_mov[i][1]] == 'B') {
			pot_mov[i][0] = 9;
			pot_mov[i][1] = 9;
		}
	}
	if ((on_board(pot_mov, 0) && !Player->color)) {
		pot_mov[0][0] = -100;
		pot_mov[0][1] = -100;
		pot_mov[4][0] = -100;
		pot_mov[4][1] = -100;
	}
	if ((on_board(pot_mov, 1) && !Player->color)) {
		pot_mov[1][0] = -100;
		pot_mov[1][1] = -100;
		pot_mov[5][0] = -100;
		pot_mov[5][1] = -100;
	}
	if ((on_board(pot_mov, 2) && Player->color)) {
		pot_mov[2][0] = -100;
		pot_mov[2][1] = -100;
		pot_mov[6][0] = -100;
		pot_mov[6][1] = -100;
	}
	if ((on_board(pot_mov, 3) && Player->color)) {
		pot_mov[3][0] = -100;
		pot_mov[3][1] = -100;
		pot_mov[7][0] = -100;
		pot_mov[7][1] = -100;
	}

	for (int i = 0; i < 4; i++) {
		if (on_board(pot_mov, i)) {
			pot_mov[i + 4][0] = -100;
			pot_mov[i + 4][1] = -100;
		}
		if ((pot_mov[i][0] == 9 && Player->color) || (pot_mov[i][0] == 8 && !Player->color) || (on_board(pot_mov, i) && on_board(pot_mov, i + 4))) {
			pot_mov[i + 4][0] = -100;
			pot_mov[i + 4][1] = -100;
		}
		if (on_board(pot_mov, i) && on_board(pot_mov, i + 4) || pot_mov[i][0] == -1 && on_board(pot_mov, i + 4))
		{
			pot_mov[i + 4][0] = -100;
			pot_mov[i + 4][1] = -100;
		}
	}
	return pot_mov;
}

int** potential_queen_movement(char* field[], playerinf* Player, int* pos[])
{
	int** pot_qmov = (int**)malloc(28 * sizeof(int*));
	if (pot_qmov == NULL) {
		exit(4243);//RENAME
	}
	for (int i = 0; i < 28; i++) {
		pot_qmov[i] = (int*)malloc(2 * sizeof(int));
		if (pot_qmov[i] == NULL) {
			exit(4244);//RENAME
		}
	}
	int k = 1;
	int f = 0;
	for (int i = 0; i < 28; i += 4) {
		pot_qmov[i][0] = pos[0][0] + k;
		pot_qmov[i][1] = pos[0][1] + k;
		pot_qmov[i + 1][0] = pos[0][0] + k;
		pot_qmov[i + 1][1] = pos[0][1] - k;
		pot_qmov[i + 2][0] = pos[0][0] - k;
		pot_qmov[i + 2][1] = pos[0][1] + k;
		pot_qmov[i + 3][0] = pos[0][0] - k;
		pot_qmov[i + 3][1] = pos[0][1] - k;
		k++;
	}
	for (int i = 0; i < 28; i++) {
		if (pot_qmov[i][0] != -100) {
			if (!on_board(pot_qmov, i)) {
				pot_qmov[i][0] = -100;
				pot_qmov[i][1] = -100;
				k = i;
				while (k + 4 < 28) {
					pot_qmov[k][0] = -100;
					pot_qmov[k][1] = -100;
					k += 4;
				}
			}
			else if (field[pot_qmov[i][0]][pot_qmov[i][1]] == 'W') {
				pot_qmov[i][0] = 8;
				pot_qmov[i][1] = 8;
				if (Player->color) {
					for (int l = 8; l < 24; l += 4) {
						if (i + l < 28 && on_board(pot_qmov, i + l)) {
							if (field[pot_qmov[i + l][0]][pot_qmov[i + l][1]] == 'W') {
								while (f + i + l < 28) {
									pot_qmov[f + i + l][0] = -100;
									pot_qmov[f + i + l][1] = -100;
									f += 4;
								}
								f = 0;
							}
						}
					}
				}
			}
			else if (field[pot_qmov[i][0]][pot_qmov[i][1]] == 'B') {
				pot_qmov[i][0] = 9;
				pot_qmov[i][1] = 9;
				if (!Player->color) {
					for (int l = 8; l < 24; l += 4) {
						if (i + l < 28 && on_board(pot_qmov, i + l)) {
							if (field[pot_qmov[i + l][0]][pot_qmov[i + l][1]] == 'B') {
								while (f + i + l < 28) {
									pot_qmov[f + i + l][0] = -100;
									pot_qmov[f + i + l][1] = -100;
									f += 4;
								}
								f = 0;
							}
						}
					}
				}
			}
		}
	}
	for (int j = 0; j < 24; j += 4) {
		for (int i = 0; i < 4; i++) {
			if (((pot_qmov[i + j][0] == 9 && Player->color) || (pot_qmov[i + j][0] == 8 && !Player->color)) && on_board(pot_qmov, i + j + 4)) {
				k = i + j + 4;
				while (k < 28) {
					pot_qmov[k][0] = -100;
					pot_qmov[k][1] = -100;
					k += 4;
				}
			}
		}
	}
	return pot_qmov;
}

static bool additional_queen_attack(char* field[], playerinf* Player, int* pos[], int i)
{
	bool can_attack = false;
	int who_can_attack = -1;
	int** new_pos = (int**)malloc(sizeof(int*));
	for (int i = 0; i < 1; i++) {
		new_pos[i] = (int*)malloc(2 * sizeof(int));
		if (new_pos[i] == NULL) {
			exit(1337); //RENAME!!!
		}
	}
	new_pos[0][0] = Player->checkers[i].pos[0];
	new_pos[0][1] = Player->checkers[i].pos[1];
	if (new_pos == NULL) {
		exit(1337); //RENAME!!!
	}
	int** pot_mov;
	int color = 8;
	if (!Player->color) {
		color = 9;
	}
	pot_mov = potential_queen_movement(field, Player, new_pos);
	int enemyChecker = (Player->color) ? (8) : (9);
	for (int line = 0; line < 4; line++) {
		if (pot_mov[line][0] == enemyChecker && on_board(pot_mov, line + 4)) {
			can_attack = true;
		}
		else if (pot_mov[line + 4][0] == enemyChecker &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line))) {
			can_attack = true;
		}
		else if (pot_mov[line + 8][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 12))) {
			can_attack = true;
		}
		else if (pot_mov[line + 12][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 16))) {
			can_attack = true;
		}
		else if (pot_mov[line + 16][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
			(on_board(pot_mov, line + 20))) {
			can_attack = true;
		}
		else if (pot_mov[line + 20][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
			(on_board(pot_mov, line + 16)) && (on_board(pot_mov, line + 24))) {
			can_attack = true;
		}
	}
	for (int i = 0; i < 28; i++) {
		free(pot_mov[i]);
	}
	for (int i = 0; i < 1; i++) {
		free(new_pos[i]);
	}
	free(new_pos);
	free(pot_mov);
	if (can_attack)
	{
		return true;
	}
	return false;
}

static bool check_attack(char* field[], playerinf* Player, int* pos[])
{
	bool can_attack = false;
	int who_can_attack = -1;
	bool do_attack = false;
	int** new_pos = (int**)malloc(sizeof(int*));
	if (new_pos == NULL) {
		exit(1337); //RENAME!!!
	}
	for (int i = 0; i < 1; i++) {
		new_pos[i] = (int*)malloc(2 * sizeof(int));
		if (new_pos[i] == NULL) {
			exit(1337); //RENAME!!!
		}
	}
	int** pot_mov;
	int color = 8;
	if (!Player->color) {
		color = 9;
	}
	for (int i = 0; i < 12; i++) {
		if (do_attack) {
			break;
		}
		new_pos[0][0] = Player->checkers[i].pos[0];
		new_pos[0][1] = Player->checkers[i].pos[1];
		if (!Player->checkers[i].queen && Player->checkers[i].alive) {
			pot_mov = potential_checker_movement(field, Player, new_pos);
			if ((pot_mov[3][1] == color && on_board(pot_mov, 7)) ||
				(pot_mov[2][1] == color && on_board(pot_mov, 6)) ||
				(pot_mov[1][1] == color && on_board(pot_mov, 5)) ||
				(pot_mov[0][1] == color && on_board(pot_mov, 4))) {
				if (pot_mov[3][1] == color && on_board(pot_mov, 7)) {
					who_can_attack = i;
					can_attack = true;
					if (pot_mov[7][0] == pos[1][0] && pot_mov[7][1] == pos[1][1]) {
						do_attack = true;
						for (int i = 0; i < 8; i++) {
							free(pot_mov[i]);
						}
						free(pot_mov);
						break;
					}
				}
				if (pot_mov[2][1] == color && on_board(pot_mov, 6)) {
					who_can_attack = i;
					can_attack = true;
					if (pot_mov[6][0] == pos[1][0] && pot_mov[6][1] == pos[1][1]) {
						do_attack = true;
						for (int i = 0; i < 8; i++) {
							free(pot_mov[i]);
						}
						free(pot_mov);
						break;
					}
				}
				if (pot_mov[1][1] == color && on_board(pot_mov, 5)) {
					who_can_attack = i;
					can_attack = true;
					if (pot_mov[5][0] == pos[1][0] && pot_mov[5][1] == pos[1][1]) {
						do_attack = true;
						for (int i = 0; i < 8; i++) {
							free(pot_mov[i]);
						}
						free(pot_mov);
						break;
					}
				}
				if (pot_mov[0][1] == color && on_board(pot_mov, 4)) {
					who_can_attack = i;
					can_attack = true;
					if (pot_mov[4][0] == pos[1][0] && pot_mov[4][1] == pos[1][1]) {
						do_attack = true;
						for (int i = 0; i < 8; i++) {
							free(pot_mov[i]);
						}
						free(pot_mov);
						break;
					}
				}
			}
			for (int i = 0; i < 8; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
		}
		else if (Player->checkers[i].queen && Player->checkers[i].alive) {
			pot_mov = potential_queen_movement(field, Player, new_pos);
			int enemyChecker = (Player->color) ? (8) : (9);
			for (int line = 0; line < 4; line++) {
				if (pot_mov[line][0] == enemyChecker && on_board(pot_mov, line + 4)) {
					who_can_attack = i;
					can_attack = true;
					if (move_to(pos, pot_mov, line + 4) ||
						on_board(pot_mov, line + 8) && (move_to(pos, pot_mov, line + 8) ||
							on_board(pot_mov, line + 12) && (move_to(pos, pot_mov, line + 12) ||
								on_board(pot_mov, line + 16) && (move_to(pos, pot_mov, line + 16) ||
									on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
										on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)))))) {
						do_attack = true;
						break;
					}
				}
				else if (pot_mov[line + 4][0] == enemyChecker &&
					(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line))) {
					who_can_attack = i;
					can_attack = true;
					if (move_to(pos, pot_mov, line + 8) ||
						on_board(pot_mov, line + 12) && (move_to(pos, pot_mov, line + 12) ||
							on_board(pot_mov, line + 16) && (move_to(pos, pot_mov, line + 16) ||
								on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
									on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24))))) {
						do_attack = true;
						break;
					}
				}
				else if (pot_mov[line + 8][0] == enemyChecker &&
					(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
					(on_board(pot_mov, line + 12))) {
					who_can_attack = i;
					can_attack = true;
					if (move_to(pos, pot_mov, line + 12) || on_board(pot_mov, line + 16) &&
						(move_to(pos, pot_mov, line + 16) || on_board(pot_mov, line + 20) &&
						(move_to(pos, pot_mov, line + 20) || on_board(pot_mov, line + 24) &&
							move_to(pos, pot_mov, line + 24)))) {
						do_attack = true;
						break;
					}
				}
				else if (pot_mov[line + 12][0] == enemyChecker &&
					(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
					(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 16))) {
					who_can_attack = i;
					can_attack = true;
					if (move_to(pos, pot_mov, line + 16) ||
						on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
							on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24))) {
						do_attack = true;
						break;
					}
				}
				else if (pot_mov[line + 16][0] == enemyChecker &&
					(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
					(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
					(on_board(pot_mov, line + 20))) {
					who_can_attack = i;
					can_attack = true;
					if (move_to(pos, pot_mov, line + 20) ||
						on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)) {
						do_attack = true;
						break;
					}
				}
				else if (pot_mov[line + 20][0] == enemyChecker &&
					(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
					(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
					(on_board(pot_mov, line + 16)) && (on_board(pot_mov, line + 24))) {
					can_attack = true;
					if (on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)) {
						do_attack = true;
						break;
					}
				}
				if (do_attack == true) {
					break;
				}
			}
			for (int i = 0; i < 28; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
		}
	}

	for (int i = 0; i < 1; i++) {
		free(new_pos[i]);
	}
	free(new_pos);
	if (can_attack && !do_attack) {
		if (Player->checkers[who_can_attack].alive) {
			Player->checkers[who_can_attack].alive = false;
			field[Player->checkers[who_can_attack].pos[0]][Player->checkers[who_can_attack].pos[1]] = '#';
			return false;
		}
		else {
			return true;
		}
	}
	//assert(!_CrtDumpMemoryLeaks());
	return true;
}

//trying to find killed checker place
static int** death_pos(int line, int* pos[])
{
	int counter = 1;
	int add = 1;
	int** new_pos = (int**)malloc(1 * sizeof(int*));
	if (new_pos == NULL) {
		exit(55123);//RENAME
	}
	for (int i = 0; i < 1; i++) {
		new_pos[i] = (int*)malloc(2 * sizeof(int));
		if (new_pos[i] == NULL) {
			exit(23123);//RENAME
		}
	}
	for (int i = 0; i < 4; i++) {

		if (line == counter - 1) {
			new_pos[0][0] = pos[0][0] + add;
			new_pos[0][1] = pos[0][1] + add;
		}
		else if (line == counter) {
			new_pos[0][0] = pos[0][0] + add;
			new_pos[0][1] = pos[0][1] - add;
		}
		else if (line == counter + 1) {
			new_pos[0][0] = pos[0][0] - add;
			new_pos[0][1] = pos[0][1] + add;
		}
		else if (line == counter + 2) {
			new_pos[0][0] = pos[0][0] - add;
			new_pos[0][1] = pos[0][1] - add;
		}
		counter += 4;
		add++;
	}
	return new_pos;
}

bool make_turn(char* field[], playerinf* Player, int* pos[], playerinf* Enemy, int p1ChClr, int p2ChClr, int gameTurn, int* memory[], bool bot_or_player, int numbaddturn)
{
	if (pos == NULL) {
		exit(-5);//
	}
	if (pos[0][0] > 7 || pos[1][0] > 7 || pos[0][1] > 7 || pos[1][1] > 7) {
		return false;
	}
	if ((pos[0][0] == pos[1][0]) && (pos[0][1] == pos[1][1])) {
		return false;
	}
	checker unit;
	checker enemy;
	int numbOfChecker = -1;
	enemy.pos[0] = -1;
	enemy.pos[1] = -1;
	unit.pos[0] = -1;
	unit.pos[1] = -1;
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 12; k++) { // we try to find checker which we want to move and find what placed on the another cell
			if (Player->checkers[k].pos[0] == pos[0][0] && Player->checkers[k].pos[1] == pos[0][1]) {
				if (Player->checkers[k].alive) {
					unit = Player->checkers[k];
					numbOfChecker = k;
				}
			}
			if (Enemy->checkers[k].pos[0] == pos[0][0] && Enemy->checkers[k].pos[1] == pos[0][1]) {
				if (Enemy->checkers[k].alive) {
					enemy = Enemy->checkers[k];
				}
			}
		}
		if ((pos[i][0] > 8 && pos[i][1] < 0)) {
			return false;
		}
		if ((pos[i][0] + pos[i][1]) % 2 != 0) {
			return false;
		}
	}
	if ((unit.pos[0] == -1 && unit.pos[1] == -1) ||
		(enemy.pos[0] != -1 || enemy.pos[1] != -1)) { // we didn't find checker on this position
		return false;
	}

	if (!unit.queen) {
		int** pot_mov = potential_checker_movement(field, Player, pos);
		bool kill = false;
		bool can_move = false;
		int mov;
		for (int i = 0; i < 8; i++) { // check for real moves
			if (pot_mov[i][0] == pos[1][0] && pot_mov[i][1] == pos[1][1]) {
				can_move = true;
				mov = i;
				break;
			}
		}
		if (!can_move) {
			for (int i = 0; i < 8; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
			return false;
		}
		if (abs(pos[1][0] - pos[0][0]) == 2 && pos[1][1] == pos[0][1]) {
			for (int i = 0; i < 8; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
			return false;
		}
		int firstCoord = pos[1][0] - pos[0][0];
		firstCoord = (firstCoord > 0) ? (firstCoord - 1) : (firstCoord + 1);
		int secondCoord = pos[1][1] - pos[0][1];
		secondCoord = (secondCoord > 0) ? (secondCoord - 1) : (secondCoord + 1);
		for (int k = 0; k < 12; k++) {
			if ((Enemy->checkers[k].pos[0] == pos[1][0] - firstCoord) &&
				(Enemy->checkers[k].pos[1] == pos[1][1] - secondCoord)) {
				if (Enemy->checkers[k].alive) {
					field[Enemy->checkers[k].pos[0]][Enemy->checkers[k].pos[1]] = '#';
					Enemy->checkers[k].alive = false;
					Enemy->checkers[k].pos[0] = -10;
					Enemy->checkers[k].pos[1] = -10;
					kill = true;
					break;
				}
			}
		}
		if (numbOfChecker != numbaddturn && numbaddturn != -1) {
			if (!bot_or_player) {
				int maxX, maxY;
				MaxXY(&maxX, &maxY);
				GotoXY(maxX / 2 - 7, maxY / 5 + 17);
				wprintf(L"You didn't attack secondly");
				getch();
				GotoXY(maxX / 2 - 7, maxY / 5 + 17);
				wprintf(L"                          ");
			}
			Player->checkers[numbaddturn].alive = false;
			field[Player->checkers[numbaddturn].pos[0]][Player->checkers[numbaddturn].pos[1]] = '#';
			Player->checkers[numbaddturn].pos[0] = -100;
			Player->checkers[numbaddturn].pos[1] = -100;
		}
		if (!kill) {
			if (!check_attack(field, Player, pos)) {
				if (!bot_or_player) {
					int maxX, maxY;
					MaxXY(&maxX, &maxY);
					GotoXY(maxX / 2 - 7, maxY / 5 + 17);
					wprintf(L"You did't attack and your checker dead");
					//Sleep(1000);
					getch();
					GotoXY(maxX / 2 - 7, maxY / 5 + 17);
					wprintf(L"                                      ");
				}
				if (!Player->checkers[numbOfChecker].alive) {
					for (int i = 0; i < 8; i++) {
						free(pot_mov[i]);
					}
					free(pot_mov);
					return true;
				}
			}
		}
		field[pos[0][0]][pos[0][1]] = '#';
		if (unit.color) {
			field[pos[1][0]][pos[1][1]] = 'B';
		}
		else {
			field[pos[1][0]][pos[1][1]] = 'W';
		}
		Player->checkers[numbOfChecker].pos[0] = pos[1][0];
		Player->checkers[numbOfChecker].pos[1] = pos[1][1];
		//make checker queen!!!
		if (unit.color && pos[1][0] == 7) {
			Player->checkers[numbOfChecker].queen = true;
		}
		else if (!unit.color && pos[1][0] == 0) {
			Player->checkers[numbOfChecker].queen = true;
		}
		for (int i = 0; i < 8; i++) {
			free(pot_mov[i]);
		}
		free(pot_mov);
		pot_mov = NULL;
		if (kill == true && !Player->checkers[numbOfChecker].queen) {
			int del = 8;
			pos[0][0] = pos[1][0];
			pos[0][1] = pos[1][1];
			pot_mov = potential_checker_movement(field, Player, pos);
			int color = 8;
			if (!unit.color) {
				color = 9;
			}
			if ((pot_mov[3][1] == color && on_board(pot_mov, 7)) ||
				(pot_mov[2][1] == color && on_board(pot_mov, 6)) ||
				(pot_mov[1][1] == color && on_board(pot_mov, 5)) ||
				(pot_mov[0][1] == color && on_board(pot_mov, 4))) {
				if (!bot_or_player) {
					player_turn(field, Player, Enemy, pos, p1ChClr, p2ChClr, gameTurn, memory, numbOfChecker);
				}
				else {
					ai_turn(field, Player, Enemy, gameTurn, p1ChClr, p2ChClr, gameTurn, memory, numbOfChecker);
				}
			}
			for (int i = 0; i < 8; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
		}
		return true;
	}
	else if (unit.queen) {
		/*
		27##FF##FF##FF##FF##FF##FF##26
		##23##FF##FF##FF##FF##FF##22##
		FF##19##FF##FF##FF##FF##18##FF
		##FF##15##FF##FF##FF##14##FF##
		FF##FF##11##FF##FF##10##FF##FF
		##FF##FF##77##FF##66##FF##FF##
		FF##FF##FF##33##22##FF##FF##FF
		##FF##FF##FF##CC##FF##FF##FF##
		FF######FF##11##00##FF##FF##FF
		##FF##FF##55##FF##44##FF##FF##
		FF##FF##99##FF##FF##88##FF##FF
		##FF##13##FF##FF##FF##12##FF##
		FF##17##FF##FF##FF##FF##16##FF
		##21##FF##FF##FF##FF##FF##20##
		25##FF##FF##FF##FF##FF##FF##24
		*/
		int** pot_mov = potential_queen_movement(field, Player, pos);
		bool kill = false;
		bool can_move = false;
		int place_of_murder = -1; // inited
		int line = 0;
		for (int i = 0; i < 28; i++) { // check for real moves
			if (pot_mov[i][0] == pos[1][0] && pot_mov[i][1] == pos[1][1]) {
				can_move = true;
				line = i;
				break;
			}
		}
		line = line % 4;
		if (!can_move) {
			for (int i = 0; i < 28; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
			return false;
		}
		int enemyChecker = (Player->color) ? (8) : (9);
		if (pot_mov[line][0] == enemyChecker && on_board(pot_mov, line + 4)) {
			if (move_to(pos, pot_mov, line + 4) ||
				on_board(pot_mov, line + 8) && (move_to(pos, pot_mov, line + 8) ||
					on_board(pot_mov, line + 12) && (move_to(pos, pot_mov, line + 12) ||
						on_board(pot_mov, line + 16) && (move_to(pos, pot_mov, line + 16) ||
							on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
								on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)))))) {
				place_of_murder = line;
			}
		}
		else if (pot_mov[line + 4][0] == enemyChecker &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line))) {
			if (move_to(pos, pot_mov, line + 8) ||
				on_board(pot_mov, line + 12) && (move_to(pos, pot_mov, line + 12) ||
					on_board(pot_mov, line + 16) && (move_to(pos, pot_mov, line + 16) ||
						on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
							on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24))))) {
				place_of_murder = line + 4;
			}
		}
		else if (pot_mov[line + 8][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 12))) {
			if (move_to(pos, pot_mov, line + 12) || on_board(pot_mov, line + 16) &&
				(move_to(pos, pot_mov, line + 16) || on_board(pot_mov, line + 20) &&
				(move_to(pos, pot_mov, line + 20) || on_board(pot_mov, line + 24) &&
					move_to(pos, pot_mov, line + 24)))) {
				place_of_murder = line + 8;
			}
		}
		else if (pot_mov[line + 12][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 16))) {
			if (move_to(pos, pot_mov, line + 16) ||
				on_board(pot_mov, line + 20) && (move_to(pos, pot_mov, line + 20) ||
					on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24))) {
				place_of_murder = line + 12;
			}
		}
		else if (pot_mov[line + 16][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
			(on_board(pot_mov, line + 20))) {
			if (move_to(pos, pot_mov, line + 20) ||
				on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)) {
				place_of_murder = line + 16;
			}
		}
		else if (pot_mov[line + 20][0] == enemyChecker &&
			(on_board(pot_mov, line)) && (on_board(pot_mov, line + 4)) &&
			(on_board(pot_mov, line + 8)) && (on_board(pot_mov, line + 12)) &&
			(on_board(pot_mov, line + 16)) && (on_board(pot_mov, line + 24))) {
			if (on_board(pot_mov, line + 24) && move_to(pos, pot_mov, line + 24)) {
				place_of_murder = line + 20;
			}
		}
		if (abs(pos[1][0] - pos[0][0]) == 2 && pos[1][1] == pos[0][1]) {
			for (int i = 0; i < 28; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
			return false;
		}
		if (place_of_murder != -1) {
			int** death_pos_coords = death_pos(place_of_murder, pos);
			for (int k = 0; k < 12; k++) {
				if ((Enemy->checkers[k].pos[0] == death_pos_coords[0][0]) &&
					(Enemy->checkers[k].pos[1] == death_pos_coords[0][1])) {
					if (Enemy->checkers[k].alive) {
						field[Enemy->checkers[k].pos[0]][Enemy->checkers[k].pos[1]] = '#';
						Enemy->checkers[k].alive = false;
						Enemy->checkers[k].pos[0] = -10;
						Enemy->checkers[k].pos[1] = -10;
						kill = true;
						break;
					}
				}
			}
			for (int k = 0; k < 1; k++) {
				free(death_pos_coords[k]);
			}
			free(death_pos_coords);
		}
		if (numbOfChecker != numbaddturn && numbaddturn != -1) {
			if (!bot_or_player) {
				int maxX, maxY;
				MaxXY(&maxX, &maxY);
				GotoXY(maxX / 2 - 7, maxY / 5 + 17);
				wprintf(L"You didn't attack secondly");
				getch();
				GotoXY(maxX / 2 - 7, maxY / 5 + 17);
				wprintf(L"                          ");
			}
			Player->checkers[numbaddturn].alive = false;
			field[Player->checkers[numbaddturn].pos[0]][Player->checkers[numbaddturn].pos[1]] = '#';
			Player->checkers[numbaddturn].pos[0] = -100;
			Player->checkers[numbaddturn].pos[1] = -100;
		}
		if (!kill) {
			if (!check_attack(field, Player, pos)) {
				if (!bot_or_player) {
					int maxX, maxY;
					MaxXY(&maxX, &maxY);
					GotoXY(maxX / 2 - 7, maxY / 5 + 17);
					wprintf(L"You did't attack and your checker dead");
					//Sleep(1000);
					//getch();//BUG
					GotoXY(maxX / 2 - 7, maxY / 5 + 17);
					wprintf(L"                                      ");
				}
				if (!Player->checkers[numbOfChecker].alive) {
					for (int i = 0; i < 28; i++) {
						free(pot_mov[i]);
					}
					free(pot_mov);
					return true;
				}
			}
		}
		field[pos[0][0]][pos[0][1]] = '#';
		if (unit.color) {
			field[pos[1][0]][pos[1][1]] = 'B';
		}
		else {
			field[pos[1][0]][pos[1][1]] = 'W';
		}
		Player->checkers[numbOfChecker].pos[0] = pos[1][0];
		Player->checkers[numbOfChecker].pos[1] = pos[1][1];

		for (int i = 0; i < 28; i++) {
			free(pot_mov[i]);
		}
		free(pot_mov);
		pot_mov = NULL;
		if (kill == true) {
			pos[0][0] = pos[1][0];
			pos[0][1] = pos[1][1];
			pot_mov = potential_queen_movement(field, Player, pos);
			int color = 8;
			if (!unit.color) {
				color = 9;
			}
			if (additional_queen_attack(field, Player, pos, numbOfChecker)) {
				if (!bot_or_player) {
					player_turn(field, Player, Enemy, pos, p1ChClr, p2ChClr, gameTurn, memory, numbOfChecker);
				}
				else {
					ai_turn(field, Player, Enemy, gameTurn, p1ChClr, p2ChClr, gameTurn, memory, numbOfChecker);
				}
			}
			for (int i = 0; i < 28; i++) {
				free(pot_mov[i]);
			}
			free(pot_mov);
		}
		return true;
	}
}
static int** make_coords(char* field[], int** turn, int p1ChClr, int p2ChClr) {
	int maxX, maxY;
	MaxXY(&maxX, &maxY);
	int key = 0;
	int cX = 0;//coord X
	int cY = 0;//coord Y
	int timer = 0;
	int color;
	while (true) {
		if (KeyPressed() == 1) {
			key = GetKey();
			if (field[cY / 2][cX / 2] == 'W') {
				color = p1ChClr;
			}
			else if (field[cY / 2][cX / 2] == 'B') {
				color = p2ChClr;
			}
			else {
				color = BlackBack | WhiteFore;
			}
			GotoXY(maxX / 2 - 7 + 1 + cX, maxY / 5 + cY);
			SetColor(color);
			wprintf(L"%c", field[cY / 2][cX / 2]);
			switch (key) {
			case KEY_UP:
				if (cY > 0) {
					cY -= 2;
				}
				break;
			case KEY_DOWN:
				if (cY < 14) {
					cY += 2;
				}
				break;
			case KEY_LEFT:
				if (cX > 0) {
					cX -= 2;
				}
				break;
			case KEY_RIGHT:
				if (cX < 14) {
					cX += 2;
				}
				break;
			case KEY_SPACE:
				if (timer == 0) {
					turn[0][0] = cY / 2;
					turn[0][1] = cX / 2;
					timer++;
				}
				else if (timer == 1) {
					turn[1][0] = cY / 2;
					turn[1][1] = cX / 2;
					return turn;
				}
			}
		}
		GotoXY(maxX / 2 - 7 + 1 + cX, maxY / 5 + cY);
		SetColor(WhiteBack);
		wprintf(L"%c", field[cY / 2][cX / 2]);
		Sleep(100);
		GotoXY(maxX / 2 - 7 + 1 + cX, maxY / 5 + cY);
		SetColor(BlackBack | WhiteFore);
		wprintf(L"%c", field[cY / 2][cX / 2]);
		Sleep(100);
	}
	exit(505);//RENAME
}

void player_turn(char* field[], playerinf* Player, playerinf* Enemy, int** turn, int p1ChClr, int p2ChClr, int numb_of_turn, int* memory[], int secondTurnChecker)
{
	/*--------------------*/
	int maxX, maxY;
	MaxXY(&maxX, &maxY);
	print_field(field, p1ChClr, p2ChClr);
	/*-------------------*/
	while (true) {
		if (Player->color) {
			GotoXY(maxX / 2 - 7, maxY / 5 + 16);
			wprintf(L"Make your turn black:\n");
		}
		else {
			GotoXY(maxX / 2 - 7, maxY / 5 + 16);
			wprintf(L"Make your turn white:\n");
		}
		turn = make_coords(field, turn, p1ChClr, p2ChClr);
		if (make_turn(field, Player, turn, Enemy, p1ChClr, p2ChClr, 1, memory, false, secondTurnChecker)) {
			int numb_of_pos = numb_of_turn;
			if (numb_of_turn > 9) {
				numb_of_pos %= 10;
			}
			if (Player->color) {
				GotoXY(maxX / 2 + 15, maxY / 5);
				wprintf(L"%d)(%d;%d) to (%d;%d) ", numb_of_turn, turn[0][0], turn[0][1], turn[1][0], turn[1][1]);
				wprintf(L"black\n");
			}
			else {
				GotoXY(maxX / 2 + 15, maxY / 5 + 1);
				wprintf(L"%d)(%d;%d) to (%d;%d) ", numb_of_turn, turn[0][0], turn[0][1], turn[1][0], turn[1][1]);
				wprintf(L"white\n");
			}
			break;
		}
		else {
			SetColor(BlackBack | WhiteFore);
			GotoXY(maxX / 2 - 7, maxY / 5 + 16);
			wprintf(L"You can't do it turn!\nPress Any Key to continue . . .");
			getch();
			print_field(field, p1ChClr, p2ChClr);
			GotoXY(maxX / 2 - 7, maxY / 5 + 16);
			wprintf(L"                     \n                               ");
		}
	}
}

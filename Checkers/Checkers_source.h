#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include "Conlib.h"
//
#define FIELD_COLOR BlackBack| WhiteFore
//
typedef struct _checker {
	bool color; //0 - white ; 1 - black
	bool alive; //0 - no ; 1 - yes
	bool queen; //0 - no ; 1 - yes
	int pos[2];
}checker;

typedef struct _playerinf {
	checker checkers[12];
	bool color;
} playerinf;

void player_turn(char* field[], playerinf* Player, playerinf* Enemy, int** turn, int p1ChClr, int p2ChClr, int numb_of_turn, int* memory[], int secondTurnChecker);

void print_field(char* field[], int p1ChClr, int p2ChClr);

int** potential_checker_movement(char* field[], playerinf* Player, int* pos[]);

int** potential_queen_movement(char* field[], playerinf* Player, int* pos[]);

bool on_board(int* pot_mov[], int a);

bool make_turn(char* field[], playerinf* Player, int* pos[], playerinf* Enemy, int p1ChClr, int p2ChClr, int gameTurn, int* memory[], bool bot_or_player, int numbaddturn);

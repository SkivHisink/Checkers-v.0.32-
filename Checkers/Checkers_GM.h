#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Checkers_source.h"

char** player_vs_player(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker);

char** player_vs_ai(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker);

char** ai_vs_ai(char* field[], playerinf* Player1, playerinf* Player2, int p1ChClr, int p2ChClr, int numb_of_turn, int* ai_turns, int* ai_turns_2, int secondTurnChecker);
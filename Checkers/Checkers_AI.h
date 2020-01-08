#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Checkers_source.h"

void ai_turn(char* field[], playerinf* Player, playerinf* Enemy, int turn, int p1ChClr, int p2ChClr, int gameTurn, int* memory, int secondTurnChecker);

void ai_rebalancing(int* ai_turns, playerinf* Player, bool correction);

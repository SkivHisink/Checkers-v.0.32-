#ifndef _CHECKERS_GAME
#define _CHECKERS_GAME
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Checkers_source.h"
#include "Conlib.h"
#include "Checkers_GM.h"


/*GameMode values:
0 - develop mode | 1 - player vs player | 2 - player vs pc | 3 - pc vs pc
Player1 color:
0 - white | 1 - black
Return:
[1][0] - game score | [2][0] - names who win\opponent | [3][0] - time | [4][0] - number of turns
*/
char** init_game(int GameMode, bool Player1Color, int p1ChClr, int p2ChClr);

#endif // !1

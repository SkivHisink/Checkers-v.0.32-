#include "Checkers_AI.h"
#include <errno.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
#define MAX_PROBABILITY 10000000

static FILE * file_opening(FILE * brain, playerinf * Player) {
	errno = 0;
	errno_t error_num = errno;
	if (Player->color) {
		if ((brain = fopen("brain.txt", "r+")) == NULL) {
			char* errorbuf = strerror(error_num);
			fprintf(stderr, "Error message : %s", errorbuf);
			exit(333);//RENAME
		}
	}
	else {
		if ((brain = fopen("brain2.txt", "r+")) == NULL) {
			char* errorbuf = strerror(error_num);
			fprintf(stderr, "Error message : %s", errorbuf);
			exit(333);//RENAME
		}
	}
	return brain;
}

static int find_pos_to_write(FILE* brain, int read_char, int number_of_turn, playerinf* Player)
{
	fclose(brain);
	brain = file_opening(brain, Player);
	int temp = 0;
	while (number_of_turn != temp) {
		while ((((char)(read_char)) != '#') && (read_char != EOF)) {
			fscanf(brain, "%c", &read_char);
		}
		if (read_char == EOF) {
			exit(302);//RENAME
		}
		read_char = 0;
		fscanf(brain, "%d", &temp);
	}
	fscanf(brain, "%c", &read_char);
	return ftell(brain);
}

static bool cant_move(int* table_probability, int counter_of_turns) {
	for (int i = 0; i < counter_of_turns; i++) {
		if (table_probability[i] != 0) {
			return true;
		}
	}
	return false;
}
void ai_turn(char* field[], playerinf* Player, playerinf* Enemy, int turn, int p1ChClr, int p2ChClr, int gameTurn, int* memory, int secondTurnChecker)
{
	FILE* brain = NULL;
	brain = file_opening(brain, Player);//file with coefficients
	int** new_pos = (int**)malloc(2 * sizeof(int*));
	if (new_pos == NULL) {
		exit(5244);//RENAME!!!
	}
	for (int i = 0; i < 2; i++) {
		new_pos[i] = (int*)malloc(2 * sizeof(int));
		if (new_pos[i] == NULL) {
			exit(568);//RENAME!!
		}
	}
	int** pot_mov;
	int move_mem_size = 100;//??
	int** move = (int**)malloc(move_mem_size * sizeof(int*));
	if (move == NULL) {
		exit(506);//RENAME
	}
	for (int i = 0; i < move_mem_size; i++) {
		move[i] = (int*)malloc(4 * sizeof(int));
		if (move[i] == NULL) {
			exit(343);//RENAME!!
		}
	}
	int counter = 0;
	/*
	1) ищем возможные ходы на этот ход и записываем
	2) смотрим есть ли такие ходы в нашей таблице
	3) добааляем отсутствующие, переставляем вероятности
	4) выбираем один рандомом, запоминаем его положение
	5) делаем ход
	6) повторяем операции*/
	for (int i = 0; i < 12; i++) {
		new_pos[0][0] = Player->checkers[i].pos[0];
		new_pos[0][1] = Player->checkers[i].pos[1];
		if (Player->checkers[i].queen) {
			pot_mov = potential_queen_movement(field, Player, new_pos);
			for (int j = 0; j < 28; j++) {
				if (on_board(pot_mov, j)) {
					move[counter][0] = new_pos[0][0];
					move[counter][1] = new_pos[0][1];
					move[counter][2] = pot_mov[j][0];
					move[counter][3] = pot_mov[j][1];
					counter++;
					if (counter + 1 == move_mem_size) {
						int old_memory = move_mem_size;
						move_mem_size *= 2;
						move = realloc(move, move_mem_size);
						if (move == NULL) {
							exit(4124); //RENAME
						}
						for (int k = old_memory; k < move_mem_size; k++) {
							move[k] = (int*)malloc(4 * sizeof(int));
							if (move[k] == NULL) {
								exit(4553);//RENAME
							}
						}
					}
				}
			}
			for (int i = 0; i < 28; i++) {
				free(pot_mov[i]);
			}
		}
		else {
			pot_mov = potential_checker_movement(field, Player, new_pos);
			for (int j = 0; j < 8; j++) {
				if (on_board(pot_mov, j)) {
					move[counter][0] = new_pos[0][0];
					move[counter][1] = new_pos[0][1];
					move[counter][2] = pot_mov[j][0];
					move[counter][3] = pot_mov[j][1];
					counter++;
					if (counter + 1 == move_mem_size) {
						int old_memory = move_mem_size;
						move_mem_size *= 2;
						move = realloc(move, move_mem_size);
						if (move == NULL) {
							exit(2323);//RENAME
						}
						for (int k = old_memory; k < move_mem_size; k++) {
							move[k] = (int*)malloc(4 * sizeof(int));
							if (move[k] == NULL) {
								exit(4553); //RENAME
							}
						}
					}
				}
			}
			for (int i = 0; i < 8; i++) {
				free(pot_mov[i]);
			}
		}
		free(pot_mov);
	}
	int number_of_turn = 0;
	int have_turns = 0;
	int counter_of_turns = 0;
	int read_char = 0;
	fscanf(brain, "#%d %d %d", &number_of_turn, &have_turns, &counter_of_turns);
	if (number_of_turn != turn + 1) {
		while (number_of_turn != turn + 1) {
			while ((read_char != '#') && (read_char != EOF)) {
				fscanf(brain, "%c", &read_char);
			}
			if (read_char == EOF) {
				exit(302);//RENAME
			}
			fscanf(brain, "%d %d %d", &number_of_turn, &have_turns, &counter_of_turns);
			read_char = 0;
			if (number_of_turn > turn + 1 && turn + 1 < 50) {
				break;
			}
		}
	}
	if (have_turns) {
		int** table_turns = (int**)malloc(counter_of_turns * sizeof(int*));
		if (table_turns == NULL) {
			exit(505);
		}
		int* table_probability = (int*)malloc(counter_of_turns * sizeof(int));
		if (table_probability == NULL) {
			exit(505);
		}
		for (int i = 0; i < counter_of_turns; i++) {
			table_turns[i] = (int*)malloc(4 * sizeof(int));
			if (table_turns[i] == NULL) {
				exit(505);
			}
			fscanf(brain, "%d", &read_char);
			table_turns[i][0] = read_char / 1000;
			table_turns[i][1] = (read_char / 100) % 10;
			table_turns[i][2] = (read_char / 10) % 10;
			table_turns[i][3] = read_char % 10;
			fscanf(brain, "%c", &read_char);
			fscanf(brain, "%d", &read_char);
			table_probability[i] = read_char;
		}
		if (counter_of_turns >= counter) {
			int coincidence = 0;
			int* coincidences = (int*)malloc(counter_of_turns * sizeof(int));
			if (coincidences == NULL) {
				exit(505);
			}
			for (int j = 0; j < counter; j++) {
				for (int i = 0; i < counter_of_turns; i++) {
					if ((table_turns[i][0] == move[j][0]) && (table_turns[i][1] == move[j][1]) &&
						(table_turns[i][2] == move[j][2]) && (table_turns[i][3] == move[j][3])) {
						coincidence++;
						coincidences[i] = 1;
						break;
					}
				}
			}
			if (coincidence == counter) {
				bool turn_ability;
				do {
					bool probability = true;
					int place = 0;
					int var = (int)((double)rand() / RAND_MAX * MAX_PROBABILITY);
					while (probability) {
						for (int i = 0; i < counter_of_turns; i++) {
							if (table_probability[i] > var) {
								probability = false;
								var = i;
								place = i;
								break;
							}
							var = (int)((double)rand() / RAND_MAX * MAX_PROBABILITY);
						}
					}
					new_pos[0][0] = table_turns[var][0];
					new_pos[0][1] = table_turns[var][1];
					new_pos[1][0] = table_turns[var][2];
					new_pos[1][1] = table_turns[var][3];
					turn_ability = make_turn(field, Player, new_pos, Enemy, p1ChClr, p2ChClr, turn, memory, true, secondTurnChecker);
					if (!turn_ability) {
						table_probability[place] = 0;
					}
					if (!cant_move(table_probability, counter_of_turns)) {
						free(coincidences);
						for (int i = 0; i < move_mem_size; i++) {
							free(move[i]);
						}
						free(move);
						for (int f = 0; f < counter_of_turns; f++) {
							free(table_turns[f]);
						}
						free(table_probability);
						free(table_turns);
						memory[turn] = -100;
						for (int i = 0; i < 2; i++) {
							free(new_pos[i]);
						}
						free(new_pos);
						return;
					}
				} while (!turn_ability);
				free(coincidences);
				for (int i = 0; i < move_mem_size; i++) {
					free(move[i]);
				}
				free(move);
				for (int f = 0; f < counter_of_turns; f++) {
					free(table_turns[f]);
				}
				free(table_probability);
				free(table_turns);
				memory[turn] = new_pos[0][0] * 1000 + new_pos[0][1] * 100 + new_pos[1][0] * 10 + new_pos[1][1];
				for (int i = 0; i < 2; i++) {
					free(new_pos[i]);
				}
				free(new_pos);
			}
			else {
				//add elems change probability
				int pos_in_file = find_pos_to_write(brain, read_char, number_of_turn, Player);
				fclose(brain);
				brain = file_opening(brain, Player);
				fseek(brain, pos_in_file - 1, SEEK_SET);
				fprintf(brain, " 1");
				fprintf(brain, " %d", counter_of_turns - coincidence + counter);
				for (int i = 0; i < counter; i++) {
					read_char = move[i][0] * 1000 + move[i][1] * 100 + move[i][2] * 10 + move[i][3];
					fprintf(brain, " ");
					if (read_char < 1000) {
						if (read_char < 100)
						{
							if (read_char < 10) {
								fprintf(brain, "0");
							}
							fprintf(brain, "0");
						}
						fprintf(brain, "0");
					}
					fprintf(brain, "%d_%d", read_char, MAX_PROBABILITY / (counter_of_turns - coincidence + counter));
				}
				for (int i = 0; i < counter_of_turns; i++) {
					if (coincidences[i] != 1) {
						read_char = table_turns[i][0] * 1000 + table_turns[i][1] * 100 + table_turns[i][2] * 10 + table_turns[i][3];
						fprintf(brain, " ");
						if (read_char < 1000) {
							if (read_char < 100)
							{
								if (read_char < 10) {
									fprintf(brain, "0");
								}
								fprintf(brain, "0");
							}
							fprintf(brain, "0");
						}
						fprintf(brain, "%d_%d", read_char, MAX_PROBABILITY / (counter_of_turns - coincidence + counter));
					}
				}
				counter = 0;
				while (counter < 100) {
					fprintf(brain, " ");
					counter++;
				}
				fclose(brain);
				free(coincidences);
				for (int i = 0; i < move_mem_size; i++) {
					free(move[i]);
				}
				free(move);
				free(table_probability);
				for (int f = 0; f < counter_of_turns; f++) {
					free(table_turns[f]);
				}
				free(table_turns);
				for (int i = 0; i < 2; i++) {
					free(new_pos[i]);
				}
				free(new_pos);
				ai_turn(field, Player, Enemy, turn, p1ChClr, p2ChClr, gameTurn, memory, secondTurnChecker);
			}
		}
		else {
			int coincidence = 0;
			int* coincidences = (int*)malloc(counter * sizeof(int));
			if (coincidences == NULL) {
				exit(505);
			}
			for (int j = 0; j < counter; j++) {
				for (int i = 0; i < counter_of_turns; i++) {
					if ((table_turns[i][0] == move[j][0]) && (table_turns[i][1] == move[j][1]) &&
						(table_turns[i][2] == move[j][2]) && (table_turns[i][3] == move[j][3])) {
						coincidence++;
						coincidences[i] = 1;
					}
				}
			}
			int pos_in_file = find_pos_to_write(brain, read_char, number_of_turn, Player);
			fclose(brain);
			brain = file_opening(brain, Player);
			fseek(brain, pos_in_file, SEEK_SET);
			fprintf(brain, "1");
			fprintf(brain, " %d", counter_of_turns - coincidence + counter);
			for (int i = 0; i < counter_of_turns - coincidence; i++) {
				if (coincidences[i] != 1) {
					read_char = table_turns[i][0] * 1000 + table_turns[i][1] * 100 + table_turns[i][2] * 10 + table_turns[i][3];
					fprintf(brain, " ");
					if (read_char < 1000) {
						if (read_char < 100)
						{
							if (read_char < 10) {
								fprintf(brain, "0");
							}
							fprintf(brain, "0");
						}
						fprintf(brain, "0");
					}
					fprintf(brain, "%d_%d", read_char, MAX_PROBABILITY / (counter_of_turns - coincidence + counter));
				}
			}
			for (int i = 0; i < counter; i++) {
				read_char = move[i][0] * 1000 + move[i][1] * 100 + move[i][2] * 10 + move[i][3];
				fprintf(brain, " ");
				if (read_char < 1000) {
					if (read_char < 100)
					{
						if (read_char < 10) {
							fprintf(brain, "0");
						}
						fprintf(brain, "0");
					}
					fprintf(brain, "0");
				}
				fprintf(brain, "%d_%d", read_char, MAX_PROBABILITY / (counter_of_turns - coincidence + counter));
			}
			counter = 0;
			while (counter < 100) {
				fprintf(brain, " ");
				counter++;
			}
			fclose(brain);
			free(coincidences);
			for (int i = 0; i < move_mem_size; i++) {
				free(move[i]);
			}
			free(move);
			for (int f = 0; f < counter_of_turns; f++) {
				free(table_turns[f]);
			}
			free(table_probability);
			free(table_turns);
			for (int i = 0; i < 2; i++) {
				free(new_pos[i]);
			}
			free(new_pos);
			ai_turn(field, Player, Enemy, turn, p1ChClr, p2ChClr, 0, memory, secondTurnChecker);
		}
	}
	else {
		fclose(brain);
		brain = file_opening(brain, Player);
		fscanf(brain, "#%d", &number_of_turn);
		if (number_of_turn != turn + 1) {
			while (number_of_turn != turn + 1) {
				while ((read_char != '#') && (read_char != EOF)) {
					fscanf(brain, "%c", &read_char);
				}
				if (read_char == EOF) {
					exit(302);//
				}
				read_char = 0;
				fscanf(brain, "%d ", &number_of_turn);
			}
		}
		int pos_in_file = ftell(brain);
		fclose(brain);
		brain = file_opening(brain, Player);
		fseek(brain, pos_in_file, SEEK_SET);
		have_turns = 1;
		counter_of_turns = counter;
		fprintf(brain, "%d %d", have_turns, counter_of_turns);
		for (int i = 0; i < counter_of_turns; i++)
		{
			read_char = move[i][0] * 1000 + move[i][1] * 100 + move[i][2] * 10 + move[i][3];
			fprintf(brain, " ");
			if (read_char < 1000) {
				if (read_char < 100)
				{
					if (read_char < 10) {
						fprintf(brain, "0");
					}
					fprintf(brain, "0");
				}
				fprintf(brain, "0");
			}
			fprintf(brain, "%d_%d", read_char, MAX_PROBABILITY / counter_of_turns);
		}
		read_char = 0;
		counter = 0;
		while (counter < 100) {
			fprintf(brain, " ");
			counter++;
		}
		fclose(brain);
		for (int i = 0; i < move_mem_size; i++) {
			free(move[i]);
		}
		free(move);
		for (int i = 0; i < 2; i++) {
			free(new_pos[i]);
		}
		free(new_pos);
		ai_turn(field, Player, Enemy, turn, p1ChClr, p2ChClr, 0, memory, secondTurnChecker);
	}
}
/*ai_turns - turns which AI do at game
Player - player info for find file of AI
correction - up or down probability*/
void ai_rebalancing(int* ai_turns, playerinf* Player, bool correction)
{
	if (ai_turns == NULL) {
		exit(5823);
	}
	FILE* brain = NULL;
	int turn[4];

	for (int i = 0; ai_turns[i] != 0; i++) {
		if (ai_turns >= 0) {
		brain = file_opening(brain, Player);
		int number_of_turn = 0;
		int change_prob = 0;
		int counter_of_turns = 0;
		int read_char = 0;
			turn[0] = ai_turns[i] / 1000;
			turn[1] = (ai_turns[i] / 100) % 10;
			turn[2] = (ai_turns[i] / 10) % 10;
			turn[3] = ai_turns[i] % 10;
			fscanf(brain, "#%d %d %d", &number_of_turn, &change_prob, &counter_of_turns);
			if (number_of_turn != i + 1) {
				while (number_of_turn != i + 1) {
					while ((((char)(read_char)) != '#') && (read_char != EOF)) {
						fscanf(brain, "%c", &read_char);
					}
					if (read_char == EOF) {
						exit(302);//RENAME 
					}
					fscanf(brain, "%d %d %d", &number_of_turn, &change_prob, &counter_of_turns);
					read_char = 0;
					if (number_of_turn > i + 1 && i + 1 < 50) {
						break;
					}
				}
			}
			int** table_turns = (int**)malloc(counter_of_turns * sizeof(int*));
			if (table_turns == NULL) {
				exit(505);//REnAME
			}
			int* table_probability = (int*)malloc(counter_of_turns * sizeof(int));
			if (table_probability == NULL) {
				exit(505);//REnAME
			}
			for (int k = 0; k < counter_of_turns; k++) {
				table_turns[k] = (int*)malloc(4 * sizeof(int));
				if (table_turns[k] == NULL) {
					exit(505);
				}
				fscanf(brain, "%d", &read_char);
				table_turns[k][0] = read_char / 1000;
				table_turns[k][1] = (read_char / 100) % 10;
				table_turns[k][2] = (read_char / 10) % 10;
				table_turns[k][3] = read_char % 10;
				fscanf(brain, "%c", &read_char);
				fscanf(brain, "%d", &read_char);
				table_probability[k] = read_char;
				if ((table_turns[k][0] == turn[0]) && (table_turns[k][1] == turn[1]) &&
					(table_turns[k][2] == turn[2]) && (table_turns[k][3] == turn[3])) {
					change_prob = k;
				}
			}
			for (int i = 0; i < counter_of_turns; i++) {
				if (i != change_prob) {
					if (correction) {
						table_probability[i] -= (table_probability[change_prob] / 100) / (counter_of_turns - 1);
						if (table_probability[i] < 0) {
							table_probability[i] = 100;
						}
					}
					else {
						table_probability[i] += (table_probability[change_prob] / 100) / (counter_of_turns - 1);
						if (table_probability[i] < 0) {
							table_probability[i] = 100;
						}
					}
				}
			}
			if (correction) {
				table_probability[change_prob] += table_probability[change_prob] / 100;
			}
			else {
				table_probability[change_prob] -= table_probability[change_prob] / 100;
			}
			fclose(brain);
			brain = file_opening(brain, Player);
			fscanf(brain, "#%d ", &number_of_turn);
			if (number_of_turn != i + 1) {
				while (number_of_turn != i + 1) {
					while ((((char)(read_char)) != '#') && (read_char != EOF)) {
						fscanf(brain, "%c", &read_char);
					}
					if (read_char == EOF) {
						exit(302);//
					}
					read_char = 0;
					if (number_of_turn > i + 1 && i + 1 < 50) {
						fclose(brain);
						free(table_probability);
						for (int i = 0; i < counter_of_turns; i++) {
							free(table_turns[i]);
						}
						free(table_turns);
						return;
					}
					fscanf(brain, "%d ", &number_of_turn);
				}
			}
			int pos_in_file = ftell(brain);
			fclose(brain);
			brain = file_opening(brain, Player);
			fseek(brain, pos_in_file, SEEK_SET);
			change_prob = 1;
			fprintf(brain, "%d %d", change_prob, counter_of_turns);
			for (int i = 0; i < counter_of_turns; i++)
			{
				read_char = table_turns[i][0] * 1000 + table_turns[i][1] * 100 + table_turns[i][2] * 10 + table_turns[i][3];
				fprintf(brain, " ");
				if (read_char < 1000) {
					if (read_char < 100)
					{
						if (read_char < 10) {
							fprintf(brain, "0");
						}
						fprintf(brain, "0");
					}
					fprintf(brain, "0");
				}
				fprintf(brain, "%d_%d", read_char, table_probability[i]);
			}
			read_char = 0;
			int counter = 0;
			while (counter < 100 && i != 0) {
				fprintf(brain, " ");
				counter++;
			}
			fclose(brain);
			free(table_probability);
			for (int i = 0; i < counter_of_turns; i++) {
				free(table_turns[i]);
			}
			free(table_turns);
		}
	}
	fcloseall();
}
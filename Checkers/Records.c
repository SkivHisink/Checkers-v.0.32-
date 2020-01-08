//#include "Records.h"
//#include "List.h"
//#include <stdbool.h>
//typedef struct PersonData {
//	char *Name;
//	int *Score;
//	double *Time;
//} PersonData;
////Func to create info of contact 
//void add_in_record(List *list) {
//		PersonData *Stats;
//		Stats = (PersonData*)malloc(sizeof(PersonData));
//		scanf("%s", Stats->Name);
//		scanf("%s", Stats->Score);
//		scanf("%s", Stats->Time);
//		list_add_tail(list, Stats);
//}
////Func to print list 
//void print_tel_list(List *list) {
//	PersonData *pd;
//	pd = (PersonData*)malloc(sizeof(PersonData));
//	printf("Contact list:\n");
//	int i = 0;
//	while (i < list->size) {
//		pd = (PersonData*)list_get_data(list, i);
//		printf(" Name: %s ", pd->Name);
//		printf("%s\n", pd->Score);
//		printf(" Number %s\n", pd->Time);
//		printf("\n-----------------------\n");
//		i++;
//	}
//}
////Func to find lenght of char[] 
//int string_lenght(char a, char *c) {
//	int b = 0;
//	while (a != '\0') {
//		a = c[b];
//		b++;
//	}
//	return b;
//};
//
//void save_list_in_txt(List *list) {
//	FILE *text;
//	PersonData *pd;
//	text = fopen("D:/text13.txt", "w");
//	if (text = fopen("D:/text13.txt", "w")) {
//		printf("The file was open!\n");
//	}
//	else {
//		printf("The file was not open!");
//		getchar();
//	}
//
//	fprintf(text, "Contact list:\n");
//	int i = 0;
//	while (i < list->size) {
//		pd = (PersonData*)malloc(sizeof(PersonData));
//		pd = (PersonData*)list_get_data(list, i);
//		fprintf(text, "\n-----------------------\n");
//		fprintf(text, " Name: %s ", pd->FirstN);
//		fprintf(text, "%s\n", pd->SecondN);
//		fprintf(text, " Number %s\n", pd->Number);
//		fprintf(text, " Birthday: %s\n", pd->Birthday);
//		i++;
//	}
//	fprintf(text, "\n-----------------------\n");
//	printf("Saved!");
//	fclose(text);
//}
////Func to get list in .txt file
//void get_list_from_txt(List *list) {
//	FILE *text;
//	PersonData *Stats;
//	char *a = (char*)malloc(sizeof(char));
//	text = fopen("D:/text13.txt", "r");
//
//	if (text = fopen("D:/text13.txt", "r")) {
//		printf("The file was open!");
//	}
//	else {
//		printf("The file was not open!");
//		getchar();
//	}
//	int b;
//	fscanf(text, "%d", &b);
//	for (int i = 0; i < b; i++) {
//		Stats = (PersonData*)malloc(sizeof(PersonData));
//		fscanf(text, "%s", Stats->Name);
//		fscanf(text, "%s", Stats->Score);
//		fscanf(text, "%s", Stats->Time);
//		list_add_tail(list, Stats);
//	}
//	fclose(text);
//}
////Func to activate menu
//void Menu(List *list) {
//	bool check = 1;
//	int flag = 1;
//	
//}
//

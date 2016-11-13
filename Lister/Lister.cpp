// Lister.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"
#include "time.h"
#include "conio.h"

#define error _error()
#define say(text) _say(text);
#define pause _pause();

void _pause() {
	system("pause");
}

void _error() {
	printf_s("Îøèáêà ââîäà!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}

void _cls() {
	system("cls");
}

typedef struct {
	int number;
	int *previus;
} Item;

typedef struct {
	Item *first; /*Ïåğâûé åëåìåíò*/
	int count; /*Ğàçìåğ*/
} Descr;

int menu_mode;
Descr* createitem(int, Descr*);
int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251); // Ââîä ñ êîíñîëè â êîäèğîâêå 1251
	SetConsoleOutputCP(1251);
	int *de, *ke;
	char* string;
	//Point p;
	//Point p1;
	menu_mode = 0;
	//char i;
	int nums;

	int i = 0;
	int j = 1488;

	int num;
	Descr *des;
	des = (Descr*)malloc(sizeof(Descr));
	des->count = 0;
	while (1) {
		say("Ââåäèòå ÷èñëî: ");
		if (scanf_s("%d", &num)) {
			des = createitem(num, des);
		}
		else {
			error;
		}
		printf_s("Â ñòåêå %d åëåìåíòîâ\n", des->count);
	}
	_getch();
	return 0;
}

Descr* createitem(int number, Descr *des) {
	Item* item = (Item*)malloc(sizeof(Item));
	item->previus = des->first;
	item->number = number;

	des->first = item;
	des->count++;
	return des;
}
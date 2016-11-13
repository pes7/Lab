// CMenu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"
#include "time.h"
#include<conio.h>

#define error _error()
//#define cls _cls()
#define say(text) _say(text);
#define pause _pause();

void _pause() {
	system("pause");
}

void _error() {
	printf_s("Ошибка ввода!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}

void _cls() {
	system("cls");
}

typedef struct {
	char *str;
	int lengh;
} Word;

typedef struct {
	char *binds;
	int count;
} Binds;

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	int width;
	int height;
} Size;

typedef struct {
	Point coords;
	Size size;
	Binds dbreak;
	int height;
	int prioritet;
	char *header;
} Properties;

typedef struct {
	Word *text;
	Binds *binds;
	Properties properties;
	int *pointers;
	int slots;
} Menu;

/*Кастомная очистка екрана*/
void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten)) {
		return;
	}
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten)) {
		return;
	}
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void MassageBox(char*, int, Point*);
void CrateBorder(Point*, Point*);
void Say(char*, Point*);
void SmartChoose(Menu*);
Menu *CMenu(Menu*, int);
void sap();
void stek_menu();
void stek_glavn();
void stek_dop();
void MenuFree(Menu*);

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);

	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 2);

	menu->text[menu->slots].str = "D)Стек";
	menu->binds[menu->slots].binds = "DВ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_menu;
	menu->slots++;

	menu->text[menu->slots].str = "F)Дек";
	menu->binds[menu->slots].binds = "FА";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&sap;

	menu->properties.header = "Меню программы:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 19;
	menu->properties.size.width = 30;
	menu->properties.dbreak.binds = "PЗ";
	menu->properties.dbreak.count = 2;
	menu->properties.prioritet = 0;

	SmartChoose(menu);

	_getch();

    return 0;
}

/*Выделение памяти на Menu*/
Menu *CMenu(Menu *menu, int slots) {
	menu = (Menu*)malloc(sizeof(Menu));
	menu->binds = (Binds*)malloc(sizeof(Binds) * slots);
	menu->properties.dbreak = *(Binds*)malloc(sizeof(Binds) * slots);
	menu->text = (Word*)malloc(sizeof(Word) * slots);
	menu->pointers = (int*)malloc(sizeof(int) * slots);
	menu->properties.dbreak.binds = NULL;
	menu->slots = 0;
	return menu;
}

/*Инициализация меню*/
void SmartChoose(Menu *menu) {
	char i;
	int d = 0, j, g;
	Point p, p1;
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	do {
		cls(hStdout);
		/*Выщетка позиций окантовки*/
		p.x = menu->properties.size.width;
		p.y = menu->properties.size.height;
		p1.x = menu->properties.coords.x - 2;
		p1.y = menu->properties.coords.y - 2;
		CrateBorder(&p, &p1);
		/*Выщетка позиции заголовка*/
		p.x = p.x / 2 - strlen(menu->properties.header) / 2 + menu->properties.coords.x - 2;
		p.y = menu->properties.coords.y - 1;
		Say(menu->properties.header, &p);
		/*Визуализуем пункты*/
		for (j = 0; j <= menu->slots; j++) {
			p.x = 0 + menu->properties.coords.x;
			p.y = 1 + j * (menu->properties.height + 3) + menu->properties.coords.y;
			MassageBox(menu->text[j].str, menu->properties.height, &p);
		}
		/*----------------- */
		i = _getch();
		i = toupper(i);
		//printf_s("You pressed: %c\n",i);
		/*Провиряем Bind каждего пункта*/
		if (menu->slots > 0) {
			for (j = 0; j <= menu->slots; j++) {
				if (menu->binds[j].binds != NULL) {
					for (g = 0; g < menu->binds[j].count; g++) {
						if (menu->binds[j].binds[g] == i && menu->binds[j].binds[g] != NULL) {
							cls(hStdout);
							void(*does)() = (void*)menu->pointers[j];
							if (*does != NULL) {
								does();
							}
						}
					}
				}
			}
		}
		/*Проверка на перерывание если таковое имееться*/
		if (menu->properties.dbreak.binds != NULL) {
			for (j = 0; j < menu->properties.dbreak.count; j++) {
				if (i == menu->properties.dbreak.binds[j]) {
					d = 1;
				}
			}
		}
	} while (d == 0);
	//MenuFree(menu);
}

/*Очистить структуру Menu*/
void MenuFree(Menu *menu) {
	free(menu->binds);
	free(menu->pointers);
	free(menu->text);
	free(menu);
}

/*Вывести любой текст на екран по координатах*/
void Say(char* string, Point* p) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	int i;
	for (i = 0; i < strlen(string); i++) {
		Coord.X = i + p->x;
		Coord.Y = p->y;
		SetConsoleCursorPosition(consoleoutput, Coord);
		printf_s("%c", string[i]);
	}
}

/*Создание окантовки по ширене и высоте + стартовой координате*/
void CrateBorder(Point* p, Point* p1) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	int i, j;
	for (i = 0; i < p->y; i++) {
		for (j = 0; j <= p->x; j++) {
			Coord.X = j + p1->x;
			Coord.Y = i + p1->y;
			SetConsoleCursorPosition(consoleoutput, Coord);
			if (j == p->x && i == p->y - 1) {
				printf_s("/");
			}
			if (j == 0 && i == p->y - 1) {
				printf_s("‰");
			}
			if (j == 0 && i == 0) {
				printf_s("г");
			}
			if (j == p->x && i == 0) {
				printf_s("¬");
			}
			if (j == 0 || j == p->x && i != 0 && i != p->y - 1) {
				printf_s("¦");
			}
			if ((i == 0 || i == p->y - 1) && j != p->x) {
				printf_s("-");
			}
		}
	}
}

/*Вывесли сообщение на екран по координате + высоте окантовки*/
void MassageBox(char* string, int sl, Point* p) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	int er = 1, i, j;
	for (i = 0; i < sl + 3; i++) {
		for (j = 0; j <= strlen(string) + 1; j++) {
			Coord.X = j + p->x;
			Coord.Y = i + p->y;
			SetConsoleCursorPosition(consoleoutput, Coord);
			if (j == strlen(string) + 1 && i == sl + 2) {
				printf_s("/");
			}
			if (j == 0 && i == sl + 2) {
				printf_s("‰");
			}
			if (j == 0 && i == 0) {
				printf_s("г");
			}
			if (j == strlen(string) + 1 && i == 0) {
				printf_s("¬");
			}
			if (j == 0 || j == strlen(string) + 1 && i != 0 && i != sl + 2) {
				printf_s("¦");
			}
			else {
				er = 0;
			}
			if ((i == 0 || i == sl + 2) && j != strlen(string) + 1) {
				printf_s("-");
			}
			else {
				er = 0;
			}
			if (er == 0 && i == (sl + 3) / 2) {
				printf_s("%c", string[j - 1]);
			}
		}
	}
}

void stek_menu() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Главные функции";
	menu->binds[menu->slots].binds = "XЧ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "C)Дополнительные функции";
	menu->binds[menu->slots].binds = "CС";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->binds[menu->slots].count = 0;
	menu->pointers[menu->slots] = NULL;

	menu->properties.header = "Стек:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 19;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.dbreak.count = 2;
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

void stek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 6);

	menu->text[menu->slots].str = "D)Создать стек";
	menu->binds[menu->slots].binds = "DВ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "F)Добавление елемента";
	menu->binds[menu->slots].binds = "FА";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "G)Чтение первого елемента";
	menu->binds[menu->slots].binds = "GП";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "X)Удаление первого елемента";
	menu->binds[menu->slots].binds = "XЧ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера очереди";
	menu->binds[menu->slots].binds = "CС";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->binds[menu->slots].count = 0;
	menu->pointers[menu->slots] = NULL;

	menu->properties.header = "Главные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 22;
	menu->properties.size.width = 32;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.dbreak.count = 2;
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

void stek_dop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "D)Згенирировать рандомные елементы";
	menu->binds[menu->slots].binds = "DВ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "F)Показать весь стек";
	menu->binds[menu->slots].binds = "FА";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->binds[menu->slots].count = 0;
	menu->pointers[menu->slots] = NULL;

	menu->properties.header = "Дополнительные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 22;
	menu->properties.size.width = 39;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.dbreak.count = 2;
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

void sap() {
	printf_s("Дек!!!\n");
}
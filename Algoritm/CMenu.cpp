#include "Structs.cpp"
#include "Windows.h"

HANDLE hStdout;
void Say(char*, Point*);
void MassageBox(char*, int, Point*);
void CrateBorder(Point*, Point*);
void SmartChoose(Menu*);
Menu *CMenu(Menu*, int);
void MenuFree(Menu*);

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
						if (menu->binds[j].binds[g] == i && menu->binds[j].binds[g] != (int)NULL) {
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
	unsigned int i;
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
	int er = 1, i;
	unsigned int j;
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

#include "stdafx.h"
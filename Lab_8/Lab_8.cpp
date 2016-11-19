// Lab_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMenu.cpp"

#define wt _getch();
void _say(char *str) {
	printf_s("%s",str);
}
#define say(text) _say(text);
#define error say("Ошибка Ввода."); rewind(stdin); wt;

void NReTranslateToString();
void NIsPalendomizm();

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 2);

	menu->text[menu->slots].str = "D)Переобразование номера месяца в его название";
	menu->binds[menu->slots].binds = "DВ";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (int)(void*)&NReTranslateToString;
	menu->slots++;

	menu->text[menu->slots].str = "F)Проверка слова на палиндромизм";
	menu->binds[menu->slots].binds = "FА";
	menu->binds[menu->slots].count = 2;
	menu->pointers[menu->slots] = (int)(void*)&NIsPalendomizm;

	menu->properties.header = "Меню программы:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 11;
	menu->properties.size.width = 51;
	menu->properties.dbreak.binds = "PЗ";
	menu->properties.dbreak.count = 2;
	menu->properties.prioritet = 0;

	SmartChoose(menu);

	_getch();

	return 1;
}

void NReTranslateToString() {
	int num;
	say("Впишите число месяца: ");
	if (scanf_s("%d", &num)) {
		say("Выбраный месяц: ");
		switch (num)
		{
		case 1:
			say("Январь");
			break;
		case 2:
			say("Февраль");
			break;
		case 3:
			say("Март");
			break;
		case 4:
			say("Апрель");
			break;
		case 5:
			say("Май");
			break;
		case 6:
			say("Июнь");
			break;
		case 7:
			say("Июль");
			break;
		case 8:
			say("Август");
			break;
		case 9:
			say("Сентябрь");
			break;
		case 10:
			say("Октябрь");
			break;
		case 11:
			say("Ноябрь");
			break;
		case 12:
			say("Декабрь");
			break;
		default:
			say("Не коректное число месяца.");
			wt;
			break;
		}
	} else {
		error;
	}
	wt;
}

void NIsPalendomizm() {
	char *chr;
	int err = 0, lengh;
	chr = (char*)malloc(sizeof(chr));
	say("Введите слово: ");
	if (fgets(chr, 100, stdin)) {
		lengh = strlen(chr);
		for (int i = 0; i <= lengh - 2 && err == 0; i++) {
			if (toupper(chr[i]) != toupper(chr[lengh - i - 2])) {
				err = 1;
			}
		}
		if (err == 0) {
			say("YES");
		} else{ say("NO"); }
	} else {
		error;
	}
	wt;
}
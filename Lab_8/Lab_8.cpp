 // Lab_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMenu.cpp"
#include "Defs.h"

int main() {
	int slots = 0;
	Menu *menu = NULL;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu = CMenu(menu, 2);

	menu->text[menu->slots].str = "D)Переобразование номера месяца в его название";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&NReTranslateToString;
	menu->slots++;

	menu->text[menu->slots].str = "F)Проверка слова на палиндромизм";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&RecurStart;

	menu->properties.header = "Меню программы:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 11;
	menu->properties.size.width = 51;
	menu->properties.dbreak.binds = "PЗ";

	SmartChoose(menu);

	_getch();

	return 1;
}
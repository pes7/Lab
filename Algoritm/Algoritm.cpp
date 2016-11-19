// Algoritm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Defines.h"
#include "SDek.cpp"

/*--------Functions----------*/
void StekPush();
void StekCreateStek();
void StekDopRandElems();
void StekShowElems();
void StekHowMuchElems();
void StekPop();
void sap();
void stek_menu();
void stek_glavn();
void stek_dop();
void DekCreateDek();
void dek_glavn();
void dek_menu();
void DekPush(int);
void DekHowMuchElems();
void dek_menu_push();
void dek_push_up();
void dek_push_down();
void DekShowElems();
void dek_dop();
void DekPop(int);
void dek_pop_up();
void dek_menu_pop();
void dek_pop_down();
/*--------------------------*/

/*-----Globals----*/
Stek *GStek = NULL;
Dek *GDek = NULL;
int menu_mode = 0;
/*----------------*/

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "D)Стек";
	menu->binds[menu->slots].binds = "DВ";
	
	menu->pointers[menu->slots] = (int)(void*)&stek_menu;
	menu->slots++;

	menu->text[menu->slots].str = "F)Дек";
	menu->binds[menu->slots].binds = "FА";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_menu;
	menu->slots++;

	menu->text[menu->slots].str = "G)Лист";
	menu->binds[menu->slots].binds = "GП";
	
	menu->pointers[menu->slots] = (int)(void*)&sap;

	menu->properties.header = "Меню программы:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 30;
	menu->properties.dbreak.binds = "PЗ";
	
	menu->properties.prioritet = 0;

	SmartChoose(menu);

	_getch();
    return 0;
}

void StekDopRandElems() {
	cls(hStdout);
	int nums;
	say("Рандомные елементы от 0 до ");
	if (scanf_s("%d", &nums)) {
		GStek = GenerateNumsStek(GStek, nums);
	}
	else { error; }
}

void StekShowElems() {
	cls(hStdout);
	int nums;
	say("0:показать только заданые елементы стека\n1:показать все елементы стека\nВыбирите режим: ");
	if (scanf_s("%d", &nums)) {
		ShowStek(GStek, nums);
	}
	else { error; }
}

void StekCreateStek() {
	cls(hStdout);
	int nums;
	say("Введите количество елементов стека: ");
	if (scanf_s("%d", &nums)) {
		if (nums > 0) {
			GStek = CreateStek(nums);
			say("Стек создан!");
			wt;
		}
		else {
			error1;
		}
	}
	else {
		error;
	}
}

void StekPush(){
	cls(hStdout);
	int nums;
	if (CheckFreeStek(GStek, 1)) {
		say("Введите число: ");
		if (scanf_s("%d", &nums)) {
			GStek = PushStek(GStek, nums);
			say("Елемент добавлен");
			wt;
		}
		else {
			error;
		}
	}
}

void StekPop() {
	int last;
	cls(hStdout);
	err = 0;
	if (CheckFreeStek(GStek, 0)) {
		last = GetStekFirst(GStek);
		StekLoos(GStek);
		if (CheckFreeStek(GStek, 1)) {
			if (err == 0) {
				printf_s("Было взято число %d и теперь новое, (первое) число %d",last, GetStekFirst(GStek));
				wt;
			}
		}
	}
}

void StekHowMuchElems() {
	cls(hStdout);
	if (CheckFreeStek(GStek, 1)) {
		printf_s("\nВсего: %d елементов в стеке\n", GStek->top);
		wt;
	}
}

void sap() {
	printf_s("Дек!!!\n");
	wt;
}

/*Главное меню*/
void stek_menu() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Главные функции";
	menu->binds[menu->slots].binds = "XЧ";
	
	menu->pointers[menu->slots] = (int)(void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "C)Дополнительные функции";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&stek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Стек:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*Меню стека*/
void stek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)Создать стек";
	menu->binds[menu->slots].binds = "DВ";
	
	menu->pointers[menu->slots] = (int)(void*)&StekCreateStek;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH";
	menu->binds[menu->slots].binds = "FА";
	
	menu->pointers[menu->slots] = (int)(void*)&StekPush;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP";
	menu->binds[menu->slots].binds = "GП";
	
	menu->pointers[menu->slots] = (int)(void*)&StekPop;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера очереди";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&StekHowMuchElems;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 32;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Доп меню стека*/
void stek_dop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "D)Згенирировать рандомные елементы";
	menu->binds[menu->slots].binds = "DВ";
	
	menu->pointers[menu->slots] = (int)(void*)&StekDopRandElems;
	menu->slots++;

	menu->text[menu->slots].str = "F)Показать весь стек";
	menu->binds[menu->slots].binds = "FА";
	
	menu->pointers[menu->slots] = (int)(void*)&StekShowElems;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Дополнительные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 22;
	menu->properties.size.width = 39;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Dek global menu*/
void dek_menu() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Главные функции";
	menu->binds[menu->slots].binds = "XЧ";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "C)Дополнительные функции";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_dop;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Дек:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*Меню дека*/
void dek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)Создать Дек";
	menu->binds[menu->slots].binds = "DВ";
	
	menu->pointers[menu->slots] = (int)(void*)&DekCreateDek;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH";
	menu->binds[menu->slots].binds = "FА";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_push;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP";
	menu->binds[menu->slots].binds = "GП";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_pop;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера очереди";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&DekHowMuchElems;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 32;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Dek_push_vib*/
void dek_menu_push() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Положить на верх";
	menu->binds[menu->slots].binds = "XЧ";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_push_up;
	menu->slots++;

	menu->text[menu->slots].str = "C)Положить с низу";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_push_down;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Push:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*Доп меню дека*/
void dek_dop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 2);

	menu->text[menu->slots].str = "F)Показать весь стек";
	menu->binds[menu->slots].binds = "FА";
	
	menu->pointers[menu->slots] = (int)(void*)&DekShowElems;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Дополнительные функции:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 22;
	menu->properties.size.width = 39;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Dek_pop_vib*/
void dek_menu_pop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Снять с верху";
	menu->binds[menu->slots].binds = "XЧ";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_pop_up;
	menu->slots++;

	menu->text[menu->slots].str = "C)Снять с низу";
	menu->binds[menu->slots].binds = "CС";
	
	menu->pointers[menu->slots] = (int)(void*)&dek_pop_down;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Pop:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "ZЯ";
	
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

void dek_push_up() {
	DekPush(0);
}

void dek_push_down() {
	DekPush(1);
}

void DekCreateDek() {
		cls(hStdout);
		int nums;
		say("Введите количество елементов дека: ");
		if (scanf_s("%d", &nums)) {
			if (nums > 0) {
				GDek = CreateDek(nums);
				say("Дек создан!");
				wt;
			}
			else {
				error1;
			}
		}
		else {
			error;
		}
}

void DekPush(int l) {
	cls(hStdout);
	int nums;
	if (CheckFreeDek(GDek, 1)) {
		say("Введите число: ");
		if (scanf_s("%d", &nums)) {
			GDek = PushDek(GDek, nums, l);
			say("Елемент добавлен");
			wt;
		} else {
			error;
		}
	}
}

void DekHowMuchElems() {
	cls(hStdout);
	if (CheckFreeDek(GDek, 1)) {
		printf_s("\nВсего: %d елементов в стеке\n", (GDek->top - GDek->bottom));
		wt;
	}
}

void DekShowElems() {
	cls(hStdout);
	int nums;
	say("0:показать только заданые елементы стека\n1:показать все елементы стека\nВыбирите режим: ");
	if (scanf_s("%d", &nums)) {
		ShowDek(GDek, nums);
	}
	else { error; }
}


void dek_pop_up() {
	DekPop(0);
}

void dek_pop_down() {
	DekPop(1);
}

/*ДОДЕЛАТЬ, ТУТ НЕ ПРАВИЛЬНОЕ СНИМАНИЕ ЕЛЕМЕНТА*/
void DekPop(int l) {
	int last;
	cls(hStdout);
	err = 0;
	if (CheckFreeDek(GDek, 0)) {
		if (l == 0) {
			last = GDek->nums[GDek->top - 1];
			GDek = PopDek(GDek, 0);
			if (err == 0) {
				printf_s("Было взято число %d и теперь новое,(с начала) число %d", last, GDek->nums[GDek->top - 1]);
			}
			wt;
		} else {
			last = GDek->nums[GDek->bottom];
			GDek = PopDek(GDek, l);
			if (err == 0) {
				printf_s("Было взято число %d и теперь новое,(с конца) число %d", last, GDek->nums[GDek->bottom]);
			}
			wt;
		}
	}
}
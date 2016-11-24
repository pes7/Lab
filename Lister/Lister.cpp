// Lister.cpp : Defines the entry point for the console application.
//

/*
	1)Добавить, и немного дописать лист Test2
	2)Вынести всё в файлы
	
	3)Дописать какой елемент снят при последнем снятии в стеке
*/

#include "stdafx.h"
#include "CMenu.cpp"

#define error _error()
#define say(text) _say(text);

void _error() {
	printf_s("Ошибка ввода!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}

typedef struct {
	int number; /*Значение*/
	int *previus; /*Предыдущий елемент*/
} StekItem;

typedef struct {
	StekItem *first; /*Первый елемент*/
	int count; /*Размер*/
} StekDescr;

typedef struct {
	int number; /*Значение*/
	int *previus; /*Следующий елемент*/
	int *after; /*Предыдущий елемент*/
} DekItem;

typedef struct {
	DekItem *first; /*Первый елемент*/
	DekItem *last; /*Последний елемент*/
	int count; /*Размер*/
} DekDescr;

struct List { 
	int num; /*Число*/
	struct List *next; /*Ссылка не следующий узел*/
};

StekDescr *StekCreateItem(int, StekDescr*);
StekDescr* StekDeletItem(StekDescr*);
StekDescr* StekCreateDescr();
DekDescr* DekCreateItem(int, int , DekDescr*);
DekDescr* DekDeletItem(DekDescr*, int);
DekDescr* DekPop(DekDescr*, int);
DekDescr* DekPush(DekDescr*, int);
DekDescr* DekGeneration(DekDescr*, int);

void sap();
void stek_menu();
void stek_glavn();
void dek_glavn();
void dek_menu();
void DPD();
void DPU();
void DOU();
void DOD();
void dek_menu_push();
void dek_menu_pop();
int SetkError(StekDescr*);
int DekError(DekDescr*);
void StekShow();

void DekCount();
void StekGeneration(int);
void StekGenerations();
void spis_glavn();

void DekShow();

int menu_mode;
StekDescr *SDes;
DekDescr *DDes;

int main()
{
	int slots = 0;
	Menu *menu = NULL;

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "D)Стек";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "F)Дек";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&dek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "G)Лист";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&spis_glavn;

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

void StekGeneration(int count) {
	int i;
	for (i = 0; i < count; i++) {
		StekCreateItem(rand() % count + 1, SDes);
	}
}

void StekGenerations() {
	int num;
	if (SDes == NULL) {
		SDes = StekCreateDescr();
	}
	say("Сколько елементов сгенирировать: ");
	if (scanf_s("%d", &num)) {
		if (num < 25000000 && num > 0) {
			StekGeneration(num);
			say("Стек сгенирирован успешно.\n");
			StekShow();
			_getch();
		} if (num < 1) {
			say("Слишком мало елементов!");
			_getch();
		} if (num > 25000000) {
			say("Слишком много елементов!");
			_getch();
		}
	} else {
		error;
	}
}

StekDescr* StekCreateDescr() {
	StekDescr *des;
	des = (StekDescr*)malloc(sizeof(StekDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

StekDescr* StekCreateItem(int number, StekDescr *des) {
	if (des == NULL) {
		des = StekCreateDescr();
	}
	StekItem* item = (StekItem*)malloc(sizeof(StekItem));
	item->previus = (int*)des->first;
	item->number = number;

	des->first = item;
	des->count++;
	return des;
}

StekDescr* StekDeletItem(StekDescr *des) {
	if (des->count > 1) {
		StekItem *last;
		last = des->first;
		des->first = (StekItem*)des->first->previus;
		free(last);
		des->count--;
	} else {
		free(des);
		des = NULL;
	}
	return des;
}

int SetkError(StekDescr *des) {
	if (des != NULL) {
		if ((void*)des->count != NULL) {
			if (des->count < 1) {
				say("Ошибка. В стеке 0 елементов, снятие не возможно!");
				_getch();
				return 0;
			}
			else { return 1; }
		}
		else {
			say("Ошибка. Стек пустой!");
			_getch();
			return 0;
		}
	} else {
		say("Ошибка. Стек пустой!");
		_getch();
		return 0;
	}
}

void StekPush() {
	int num;
	say("Введите число: ");
	if (scanf_s("%d", &num)) {
		SDes = StekCreateItem(num, SDes);
		say("Новый елемент добавлен!\n");
		StekShow();
	} else {
		error;
	}
	_getch();
}

void StekPop() {
	if (SetkError(SDes)) {
		SDes = StekDeletItem(SDes);
		if (SDes != NULL) {
			printf_s("Верхннй елемент убран, теперь новый верхний елемент: %d\n", SDes->first->number);
			StekShow();
		}else{
			printf_s("Стек был полностью очисчен.");
		}
		_getch();
	}
}

void StekShow() {
	FILE *file;
	StekItem *dl = SDes->first;
	int i, count = 0, *arr;
	if (SDes->count < 500) {
		arr = (int*)malloc(sizeof(int)*SDes->count);
		for (i = 0; i < SDes->count; i++) {
			arr[i] = dl->number;
			dl = (StekItem*)dl->previus;
		}
		say("Стек: ");
		for (i = SDes->count - 1; i >= 0; i--) {
			printf_s("%d,", arr[i]);
		}
	}
	else if (SDes->count < 2000000) {
		dl = SDes->first;
		arr = (int*)malloc(sizeof(int)*SDes->count);
		for (i = 0; i < SDes->count; i++) {
			arr[i] = dl->number;
			dl = (StekItem*)dl->previus;
		}
		fopen_s(&file, "StekElems.txt", "w");
		for (i = SDes->count - 1; i >= 0; i--) {
			if (count >= 40) {
				fprintf_s(file, "\n");
				count = 0;
			}
			fprintf_s(file, "%d,", arr[i]);
			count++;
		}
		fclose(file);
		say("Слишком много елементов для вывода, вывод произвидён в файл StekElems.txt в папке с программой");
	}
	else {
		say("Слишком много елементов даже для вывода в файл, так что вы не увидете его :) ");
	}
}

void StekCount() {
	if (SetkError(SDes)) {
		printf_s("В стеке: %d елементов.\n", SDes->count);
		StekShow();
		_getch();
	}
}

/*DECK ZONE*/

DekDescr *DekCreation() {
	DekDescr *des;
	des = (DekDescr*)malloc(sizeof(DekDescr));
	des->count = 0;
	des->first = NULL;
	des->last = NULL;
	return des;
}

DekDescr *DekGeneration(DekDescr *des,int count) {
	int i;
	for (i = 0; i < count; i++) {
		des = DekCreateItem(rand() % count + 1,0, des);
	}
	return des;
}

void DekGenerations() {
	int num;
	if(DDes == NULL){
		DDes = DekCreation();
	}
	say("Сколько елементов сгенирировать: ");
	if (scanf_s("%d", &num)) {
		if (num < 24000000 && num > 0) {
			DDes = DekGeneration(DDes,num);
			say("Дек сгенирирован успешно.\n");
			DekShow();
			_getch();
		} if (num < 1) {
			say("Слишком мало елементов!");
			_getch();
		} if (num > 25000000) {
			say("Слишком много елементов!");
			_getch();
		}
	} else {
		error;
	}
}

DekDescr* DekCreateItem(int number,int type,DekDescr *des) {
	DekItem* item = (DekItem*)malloc(sizeof(DekItem));
	DekItem* iteml;
	if (des == NULL) {
		des = DekCreation();
	}
	switch (type) {
		case 0:
			if (des->last == NULL) {
				des->last = item;
			} else {
				iteml = des->first;
				iteml->previus = (int*)item;
				item->after = (int*)iteml;
			}
			item->number = number;

			des->first = item;
			des->count++;
			break;
		case 1:
			if (des->last == NULL) {
				des->last = item;
				des->first = item;
			} else {
				iteml = des->last;
				iteml->after = (int*)item;
				item->previus = (int*)iteml;
			}
			item->number = number;

			des->last = item;
			des->count++;
			break;
	}
	return des;
}

DekDescr* DekDeletItem(DekDescr *des,int type) {
	DekItem *last;
	if (des->count > 1) {
		switch (type)
		{
		case 0:
			last = des->first;
			des->first = (DekItem*)des->first->after;
			free(last);
			des->count--;
			break;
		case 1:
			last = des->last;
			des->last = (DekItem*)des->last->previus;
			free(last);
			des->count--;
			break;
		}
	} else {
		free(des->first);
		free(des);
		des = NULL;
	}
	return des;
}

int DekError(DekDescr *des) {
	if (des != NULL) {
		if ((void*)des->count != NULL) {
			if (des->count < 1) {
				say("Ошибка. В деке 0 елементов, снятие не возможно!");
				_getch();
				return 0;
			}
			else { return 1; }
		}
		else {
			say("Ошибка. Дек пустой!");
			_getch();
			return 0;
		}
	} else {
		say("Ошибка. Дек пустой!");
		_getch();
		return 0;
	}
}

void DPU() { DDes = DekPush(DDes, 0); DekShow(); _getch(); }
void DPD() { DDes = DekPush(DDes,1); DekShow(); _getch(); }
void DOU() { DDes = DekPop(DDes, 0); if (DDes != NULL) { DekShow(); _getch(); } }
void DOD() { DDes = DekPop(DDes, 1); if (DDes != NULL) { DekShow(); _getch(); } }

DekDescr *DekPush(DekDescr *des,int type) {
	int num;
	say("Введите число: ");
	if (scanf_s("%d", &num)) {
		des = DekCreateItem(num, type, des);
		say("Новый елемент добавлен!\n");
	} else {
		error;
	}
	return des;
}

DekDescr *DekPop(DekDescr* des,int type) {
	int last;
	DekItem *now;
	if (DekError(des)) {
		if (des->count > 1) {
			if (type == 0) {
				printf_s("Первый");
				last = des->first->number;
				des = DekDeletItem(des, type);
				now = (DekItem*)des->first->number;
			}
			else {
				printf_s("Последний");
				last = des->last->number;
				des = DekDeletItem(des, type);
				now = (DekItem*)des->last->number;
			}
			printf_s(" елемент %d снят, новый последний елемент %d\n", (int)last, (int)now);
		} else {
			now = (DekItem*)des->first->number;
			des = DekDeletItem(des, type);
			printf_s("Елемент %d был снят. Теперь дек полностью пуст.",(int)now);
			_getch();
		}
	}
	return des;
}

void DekShow() {
	FILE *file;
	DekItem *dl;
	int i, count = 0;
	if (DDes->count < 500) {
	    dl = DDes->last;
		say("Дек: ");
		for (i = 0; i < DDes->count; i++) {
			printf_s("%d,", dl->number);
			dl = (DekItem*)dl->previus;
		}
	} else if(DDes->count < 2000000){
		dl = DDes->last;
		fopen_s(&file, "DekElems.txt", "w");
		for (i = 0; i < DDes->count; i++) {
			if (count >= 40) {
				fprintf_s(file, "\n");
				count = 0;
			}
			fprintf_s(file, "%d,",dl->number);
			dl = (DekItem*)dl->previus;
			count++;
		}
		fclose(file);
		say("Слишком много елементов для вывода, вывод произвидён в файл DekElems.txt в папке с программой");
	} else {
		say("Слишком много елементов даже для вывода в файл, так что вы не увидете его :) ");
	}
}

void DekCount() {
	if (DDes != NULL) {
		printf_s("В деке %d елементов.\n", DDes->count);
		DekShow();
		_getch();
	} else { 
		printf_s("Дек пустой."); _getch();
	}
}

void sap() {

}

/*Меню стека*/
void stek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)Сгенирировать случайный стек";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&StekGenerations;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH(Положить в стек)";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&StekPush;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP(Взять с стека)";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&StekPop;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера стека";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&StekCount;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции Стека:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 35;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Меню дека*/
void dek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)Сгенирировать случайный дек";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&DekGenerations;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH(Положить в дек)";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_push;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP(Взять с дека)";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_pop;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера дека";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&DekCount;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции Дека:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 34;
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
	menu->pointers[menu->slots] = (int)(void*)&DPU;
	menu->slots++;

	menu->text[menu->slots].str = "C)Положить с низу";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&DPD;
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

/*Dek_pop_vib*/
void dek_menu_pop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)Снять с верху";
	menu->binds[menu->slots].binds = "XЧ";
	menu->pointers[menu->slots] = (int)(void*)&DOU;
	menu->slots++;

	menu->text[menu->slots].str = "C)Снять с низу";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&DOD;
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

/*Меню списка*/
void spis_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)Сгенирировать случайный список";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&sap;
	menu->slots++;

	menu->text[menu->slots].str = "F)Найти елемент с заданым свойством";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&sap;
	menu->slots++;

	menu->text[menu->slots].str = "F)Добавить узел в список";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&sap;
	menu->slots++;

	menu->text[menu->slots].str = "G)Убрать узел с списка";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&sap;
	menu->slots++;

	menu->text[menu->slots].str = "C)Получение размера списка";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&sap;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции Списка:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 23;
	menu->properties.size.width = 40;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}
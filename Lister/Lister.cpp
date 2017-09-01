#include "stdafx.h"
#include "CMenu.cpp"
#include "Defines.h"
#include "DekH.h"
#include "StekH.h"
#include "ListH.h"

StekDescr *SDes; /*Указатель на дескриптор стека*/
DekDescr *DDes; /*Указатель на дескриптор дека*/
SpisDescr *GList; /*Указатель на список*/

int main()
{
	int slots = 0; /*Количество пунктов меню*/
	Menu *menu = NULL; /*Указатель на меню*/
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));
	system("color F0");

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

	menu->text[menu->slots].str = "G)Лист(Кольцевой список)";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&list_glavn;

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

/*Генирация рандомного стека*/
void StekGeneration(int count) {
	int i; /*Счётчик цикла*/
	for (i = 0; i < count; i++) {
		StekCreateItem(rand() % count + 1, SDes);
	}
}

/*Генирация рандомного стека*/
void StekGenerations() {
	int num; /*Количество елементов*/
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

/*Создание дескриптора стека*/
StekDescr* StekCreateDescr() {
	StekDescr *des; /*Указатель на дескриптор стека*/
	des = (StekDescr*)malloc(sizeof(StekDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

/*Создание елемента стека*/
StekDescr* StekCreateItem(int number, StekDescr *des) {
	StekItem* item; /*Указатель на елемент стека*/
	if (des == NULL) {
		des = StekCreateDescr();
	}
	item = (StekItem*)malloc(sizeof(StekItem));
	item->previus = (int*)des->first;
	item->number = number;

	des->first = item;
	des->count++;
	return des;
}

/*Снятие(Удаление) елемента стека*/
StekDescr* StekDeletItem(StekDescr *des) {
	StekItem *last; /*Указатель на елемент стека*/
	if (des->count > 1) {
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

/*Проверка на некоторые ошибки при роботе с стеком*/
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

/*Вложение(Создание) елемента стека*/
void StekPush() {
	int num; /*Просто число*/
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

/*Снятие(Удаление) елемента стека*/
void StekPop() {
	int it; /*Первый елемент до снятия*/
	if (SetkError(SDes)) {
		it = SDes->first->number;
		SDes = StekDeletItem(SDes);
		if (SDes != NULL) {
			printf_s("Верхний елемент %d убран, теперь новый верхний елемент: %d\n",it, SDes->first->number);
			StekShow();
		}else{
			printf_s("Верхний елемент %d был снят, теперь стек полностью очисчен.", it);
		}
		_getch();
	}
}

/*Функция показа стека*/
void StekShow() {
	FILE *file; /*Указатель на файл вывода*/
	StekItem *dl = SDes->first; /*Указатель на елемент стека*/
	int i, /*счётчик*/
		count = 0, /*счётчик цифр в строке файла*/
		*arr; /*указатель на массив*/
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

/*Фукнция показа количеста елементов в стеке*/
void StekCount() {
	if (SetkError(SDes)) {
		printf_s("В стеке: %d елемент/та/тов.\n", SDes->count);
		StekShow();
		_getch();
	}
}

/*DECK ZONE*/

/*Создание дескриптора дека*/
DekDescr *DekCreation() {
	DekDescr *des; /*Указатель на дескриптор дека*/
	des = (DekDescr*)malloc(sizeof(DekDescr));
	des->count = 0;
	des->first = NULL;
	des->last = NULL;
	return des;
}

/*Генирация рандомных елементов для дека*/
DekDescr *DekGeneration(DekDescr *des,int count) {
	int i; /*Счётчик*/
	for (i = 0; i < count; i++) {
		des = DekCreateItem(rand() % count + 1,0, des);
	}
	return des;
}

/*Генирация рандомных елементов для дека*/
void DekGenerations() {
	int num; /*Количество елементов*/
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

/*Создание елемента дека*/
DekDescr* DekCreateItem(int number,int type,DekDescr *des) {
	DekItem* item = (DekItem*)malloc(sizeof(DekItem)); /*Указатель на елемент дека*/
	DekItem* iteml; /*Указатель на елемент дека*/
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

/*Удаление елемента дека*/
DekDescr* DekDeletItem(DekDescr *des,int type) {
	DekItem *last; /*Удаление елемента дека*/
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

/*Проверка на некоторые ошибки при работе с деком*/
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

/*Пару спареных функций, для меню (Создают елементы и убирают их)*/
void DPU() { DDes = DekPush(DDes, 0); DekShow(); _getch(); }
void DPD() { DDes = DekPush(DDes, 1); DekShow(); _getch(); }
void DOU() { DDes = DekPop(DDes, 0); if (DDes != NULL) { DekShow(); _getch(); } }
void DOD() { DDes = DekPop(DDes, 1); if (DDes != NULL) { DekShow(); _getch(); } }

/*Положить елемент в дек(Создать новый елемент)*/
DekDescr *DekPush(DekDescr *des,int type) {
	int num; /*Просто число*/
	say("Введите число: ");
	if (scanf_s("%d", &num)) {
		des = DekCreateItem(num, type, des);
		say("Новый елемент добавлен!\n");
	} else {
		error;
	}
	return des;
}

/*Снять елемент с дека(Удалить елемент)*/
DekDescr *DekPop(DekDescr* des,int type) {
	int last; /*Значение прошлого елемента*/
	DekItem *now; /*Указатель на дескриптор дека*/
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

/*Визуализация дека*/
void DekShow() {
	FILE *file; /*Указатель на файл*/
	DekItem *dl; /*Указатель на елемент дека*/
	int i, /*Счётчик*/ 
		count = 0; /*счётчик цифр в строке файла*/
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

/*Подсчёт елементов дека*/
void DekCount() {
	if (DDes != NULL) {
		printf_s("В деке %d елементов.\n", DDes->count);
		DekShow();
		_getch();
	} else { 
		printf_s("Дек пустой."); _getch();
	}
}


/*---Cycle-Spisok-Zone---*/

/*Создать дескриптор списка*/
SpisDescr *CreateSpisDescr() {
	/*Указатель на дескриптор списка*/
	SpisDescr *des = (SpisDescr*)malloc(sizeof(SpisDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

/*Вернуть первый елемент*/
SpisItem *GiveFirst(SpisDescr *des) {
	int i; /*Счётчик цикла*/
	/*Указатель на елемент списка*/
	SpisItem *first = des->first; 
	for (i = 0; i < des->count - 1; i++) {
		first = first->previus;
	}
	return first;
}

/*Добавить елемент в список*/
SpisDescr *SpisAddItem(SpisDescr *des, int num) {
	/*Указатели на елементы списка*/
	SpisItem *item = (SpisItem*)malloc(sizeof(SpisItem)),
		*last;
	if (!IsListZerro(des)) {
		des = CreateSpisDescr();
	}
	if (des->count == 0) {
		item->number = num;
		des->first = item;
		des->count++;
	} else {
		last = des->first;
		item->previus = last;
		item->number = num;
		last = GiveFirst(des);
		last->previus = item;

		des->first = item;
		des->count++;
	}
}

/*Проверка списка на пустоту*/
int IsListZerro(SpisDescr *des) {
	int is = 1; /*Ошибка есть или нету*/
	if (des == NULL) {
		is = 0;
	}
	return is;
}

/*Визуализировать список*/
void ListShow(SpisDescr *des) {
	int i, /*Счётчик цикла*/
		*arr; /*Массив чисел*/
	SpisItem *last; /*Указатель на елемент списка*/
	if (IsListZerro(des)) {
		if (des->count > 1) {
			last = des->first;
			arr = (int*)malloc(sizeof(int) * des->count);
			for (i = 0; i < des->count; i++) {
				arr[i] = last->number;
				last = last->previus;
			}
			for (i = des->count - 1; i >= 0; i--) {
				printf_s("%d,", arr[i]);
			}
		} else {
			printf_s("%d",des->first->number);
		}
		ListShowHigh();
	} else {
		printf_s("Список пуст.\n");
	}
}

/*Добавить подсказку клавиш*/
void ListShowHigh() {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	Coord.X = 90;
	Coord.Y = 21;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("Подсказка:");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("D) Двигаем список в право");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("S) Удалить елемент");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("A) Добавить елемент");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("A) Найти елемент");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("G) Сгенирировать елемнты");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("R) Количество елементов");
}

/*Установить первый елемент списка*/
SpisDescr *SetListFirst(SpisDescr *des, int index) {
	SpisItem *last = des->first; /*Указатель на елемент списка*/
	int i; /*Счётчик цикла*/
	if (des->count > 1) {
		for (i = 0; i < index; i++) {
			last = last->previus;
		}
		des->first = last;
	}
	return des;
}

/*Убрать елемент с списка*/
SpisDescr *RemoveItem(SpisDescr *des) {
	/*Указатели на елементы списка*/
	SpisItem *last = des->first, 
			 *bottom = GiveFirst(des);
	if (des->count > 1) {
		bottom->previus = last->previus;
		des->first = last->previus;
		free(last);
		des->count--;
	} else {
		free(des->first);
		free(des);
		des = NULL;
	}
	return des;
}

/*Найти елемент в списке*/
SpisDescr *FindItem(SpisDescr *des, int num) {
	/*Указатель на елемент списка*/
	SpisItem *now = des->first;
	int i; /*Счётчик цикла*/
	for (i = 0; i < des->count; i++) {
		if (now->number == num) {
			des = SetListFirst(des, i);
			printf_s("Елемент найден!\n", i);
			i = des->count;
			return des;
		}
		now = now->previus;
	}
	printf_s("Елемент не найден!\n");
	return des;
}

/*Интерактивный метод визуализации списка*/
void demo_show_loshadki() {
	int num, /*Просто число*/
		i; /*Счётчик цикла*/
	char c; /*Нажатый символ*/
	ListShow(GList);
	while (1) {
		c = _getch();
		c = toupper(c);
		system("cls");
		switch (c)
		{
		case 'D':
		case 'В':
			if (IsListZerro(GList)) {
				SetListFirst(GList, 1);
			} else {
				printf_s("Ошибка. Список пустой.\n");
			}
			break;
		case 'A':
		case 'Ф':
			printf_s("Введите число: ");
			if (scanf_s("%d", &num)) {
				GList = SpisAddItem(GList, num);
			} else {
				printf_s("Ошибка ввода!.");
				rewind(stdin);
			}
			break;
		case 'S':
		case 'Ы':
			if (IsListZerro(GList)) {
				GList = RemoveItem(GList);
			} else {
				printf_s("Ошибка. Список пустой, вы не можете удалить елемет.\n");
			}
			break;
		case 'F':
		case 'А':
			if (IsListZerro(GList)) {
				printf_s("Впишите искуемое число: ");
				if (scanf_s("%d", &num)) {
					GList = FindItem(GList, num);
				} else {
					printf_s("Ошибка ввода!.");
					rewind(stdin);
				}
			} else {
				printf_s("Ошибка. Список пустой.\n");
			}
			break;
		case 'G':
		case 'П':
			printf_s("Сколько елементов сгенирировать: ");
			if (scanf_s("%d", &num)) {
				if (num > 1 && num < 20000000) {
					for (i = 0; i < num; i++) {
						GList = SpisAddItem(GList, rand() % num + 1);
					}
					printf_s("%d елементов сгенирировано!\n", num);
				} else {
					printf_s("Не возможно сгенирировать %d елементов\n", num);
				}
			} else {
				printf_s("Ошибка ввода.");
			}
			break;
		case 'R':
			if (IsListZerro(GList)) {
				printf_s("В списке %d елемент/а/ов.\n", GList->count);
			} else {
				printf_s("Ошибка. Список пустой.\n");
			}
			break;
		default:

			break;
		}
		ListShow(GList);
	}
}

/*Генерация списка*/
void ListGeneration() {
	int num, /*Просто число*/
		i; /*Счётчик цикла*/
	printf_s("Сколько елементов сгенирировать: ");
	if (scanf_s("%d", &num)) {
		if (num > 1 && num < 20000000) {
			for (i = 0; i < num; i++) {
				GList = SpisAddItem(GList, rand() % num + 1);
			}
			printf_s("%d елементов сгенирировано!\n", num);
		} else {
			printf_s("Не возможно сгенирировать %d елементов\n", num);
		}
	} else {
		printf_s("Ошибка ввода.");
	}
	ListShow(GList);
	_getch();
}

/*Убрать узел с списка*/
void RemoveItemFromList() {
	if (IsListZerro(GList)) {
		GList = RemoveItem(GList);
	} else {
		printf_s("Ошибка. Список пустой, вы не можете удалить елемет.\n");
	}
	ListShow(GList);
	_getch();
}

/*Получить размер листа*/
void GetCountList() {
	if (IsListZerro(GList)) {
		printf_s("В списке %d елемент/а/ов.\n", GList->count);
	}
	else {
		printf_s("Ошибка. Список пустой.\n");
	}
	ListShow(GList);
	_getch();
}

/*Найти елемент в списке*/
void ListFindElement() {
	int num; /*Просто число*/
	if (IsListZerro(GList)) {
		printf_s("Впишите искуемое число: ");
		if (scanf_s("%d", &num)) {
			GList = FindItem(GList, num);
		}
		else {
			printf_s("Ошибка ввода!.");
			rewind(stdin);
		}
	}
	else {
		printf_s("Ошибка. Список пустой.\n");
	}
	ListShow(GList);
	_getch();
}

/*Добавить елемент в список*/
void ListAddSource() {
	int num; /*Просто число*/
	printf_s("Введите число: ");
	if (scanf_s("%d", &num)) {
		GList = SpisAddItem(GList, num);
	}
	else {
		printf_s("Ошибка ввода!.");
		rewind(stdin);
	}
	ListShow(GList);
	_getch();
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
void list_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 8);

	menu->text[menu->slots].str = "D)Сгенирировать случайный список";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&ListGeneration;
	menu->slots++;

	menu->text[menu->slots].str = "F)Найти елемент с заданым свойством";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&ListFindElement;
	menu->slots++;

	menu->text[menu->slots].str = "G)Добавить узел в список";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&ListAddSource;
	menu->slots++;

	menu->text[menu->slots].str = "C)Убрать узел с списка";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&RemoveItemFromList;
	menu->slots++;

	menu->text[menu->slots].str = "V)Получение размера списка";
	menu->binds[menu->slots].binds = "VМ";
	menu->pointers[menu->slots] = (int)(void*)&GetCountList;
	menu->slots++;

	menu->text[menu->slots].str = "B)Интирактивный вариант визуализации";
	menu->binds[menu->slots].binds = "BИ";
	menu->pointers[menu->slots] = (int)(void*)&demo_show_loshadki;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Главные функции Списка:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 25;
	menu->properties.size.width = 41;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

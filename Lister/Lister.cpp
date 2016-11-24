#include "stdafx.h"
#include "CMenu.cpp"
#include "Defines.h"
#include "DekH.h"
#include "StekH.h"
#include "ListH.h"

StekDescr *SDes; /*Указатель на дескриптор стека*/
DekDescr *DDes; /*Указатель на дескриптор дека*/
struct List *GList; /*Указатель на список*/

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

	menu->text[menu->slots].str = "G)Лист";
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
		printf_s("В стеке: %d елементов.\n", SDes->count);
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

/*------SPISOK-ZONE-------*/

/*Создание первого елемента списка*/
struct List *CreateFirstElem(int num) {
	/*Указатель на структуру списка*/
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list->num = num;
	list->next = list;
	return list;
}

/*Добавить елемент в список*/
struct List *AddItem(struct List *list, int num) {
	struct List *item, /*Указатель на елемент списка*/
				*p; /*Указатель на елемент списка*/
	if (IsListEmpty(list)) {
		item = (struct List*)malloc(sizeof(struct List));
		p = list->next;
		item->num = num;
		list->next = item;
		item->next = p;
	}
	else {
		list = CreateFirstElem(num);
	}
	return list;
}

/*Визуализация листа*/
void ListShow(struct List *list) {
	struct List *p; /*Указатель на список*/
	int *arra = (int*)malloc(sizeof(int)), /*Указатель на масив*/
		i = 0, /*Счётчик*/
		j = 0; /*Счётчик*/
	p = list;
	if (IsListEmpty(list)) {
		if (GiveCountOfList(list) < 500) {
			if (GiveCountOfList(list) > 1) {
				do {
					arra = (int*)realloc(arra, sizeof(int)*(i + 1));
					arra[i] = p->num;
					p = p->next;
					i++;
				} while (p != list);
				say("Список: ");
				while (i != 1) {
					if (j == 0) {
						printf_s("%d,", arra[0]);
						j++;
					}
					i--;
					printf_s("%d,", arra[i]);
				}
			} else {
				say("Список: ");
				printf_s("%d", list->num);
			}
		} else {
			say("Слишком много елементов для вывода.");
		}
	}
	else {
		printf_s("Ошибка. Лист пустой.");
	}
}

/*Добавить елемент в список по указаному индексу*/
struct List *ListAddIndexedElement(struct List *list, int index, int number, int method) {
	int i = 0; /*Счётчик*/
	struct List *item, /*Указатель на елемент списка*/
				*p, /*Указатель на елемент списка*/
				*l = list; /*Указатель на елемент списка*/
	item = (struct List*)malloc(sizeof(struct List));

	/*Вставить после*/
	if (method == 0) {
		for (i = 0; i < GiveCountOfList(list) - index + 1; i++) {
			l = l->next;
		}
	}
	else {
		/*Вставить перед*/
		for (i = 0; i < GiveCountOfList(list) - index ; i++) {
			l = l->next;
		}
	}
	p = l->next;
	item->num = number;
	l->next = item;
	item->next = p;

	return list;
}

/*Удаление указаного елемента по индексу*/
struct List *RemoveIndexedElement(struct List *list, int index) {
	int i; /*Счётчик*/
	struct List *l = list; /*Указатель на список*/
	if (GiveCountOfList(list) > 1) {
		for (i = 0; i < GiveCountOfList(list) - index; i++) {
			l = l->next;
		}
		l->next = l->next->next;
	} else {
		free(list);
		list = NULL;
	}
	return list;
}

/*Получить число елементов*/
int GiveCountOfList(struct List *list) {
	struct List *l = list; /*Указатель на список*/
	int i = 0; /*Счётчик*/
	if (IsListEmpty(list)) {
		do {
			l = l->next;
			i++;
		} while (l != list);
	}
	return i;
}

/*Проверка на пустой список*/
int IsListEmpty(struct List *list) {
	int i = 1; /*Ошибка*/
	if (list == NULL) {
		i = 0;
	}
	return i;
}

/*Убрать елемент с списка*/
void RemoveItemFromList() {
	int i; /*Счётчик*/
	if (IsListEmpty(GList)) {
		ListShow(GList);
		say("\nВведите номер елемента списка который вы хотите удалить: ");
		if (scanf_s("%d", &i)) {
			if (i > 1) {
				if (i <= GiveCountOfList(GList)) {
					GList = RemoveIndexedElement(GList, i);
					printf_s("Елемент с индексом %d был удалён.\n", i);
					ListShow(GList);
					_getch();
				} else {
					say("Ошибка. Вы ввели индекс не существующего елемента.");
					_getch();
				}
			} else {
				say("Ошибка. Удалить 1-вый елемент списка не возможно.");
				_getch();
			}
		} else {
			error;
		}
	} else {
		say("Ошибка. Список пустой!");
		_getch();
	}
}

/*Добавить елемент в список*/
void AddItemList() {
	int num;
	say("Введите число: ");
	if (scanf_s("%d", &num)) {
		GList = AddItem(GList, num);
		say("Узел добавлен!\n");
		ListShow(GList);
		_getch();
	} else {
		error;
	}
}

/*Добавить елемент в конкретное место списка по индексу*/
void AddIndexedItemList(int mode) {
	int num, /*Просто число*/
		index; /*Индекс после/до которого будет наш елемент*/
	ListShow(GList);
	say("\nВведите индекс узла: ");
	if (scanf_s("%d", &index)) {
		if (mode == 0) {
			if (index > 1 && index < GiveCountOfList(GList) + 1) {
				say("Введите число: ");
				if (scanf_s("%d", &num)) {
					GList = ListAddIndexedElement(GList, index, num, 0);
					say("Узел добавлен!\n");
					ListShow(GList);
					_getch();
				} else {
					error;
				}
			} else {
				say("Вы вышли за граници списка.");
				_getch();
			}
		} else {
			if (index > 0 && index < GiveCountOfList(GList) + 1) {
				say("Введите число: ");
				if (scanf_s("%d", &num)) {
					GList = ListAddIndexedElement(GList, index, num, 1);
					say("Узел добавлен!\n");
					ListShow(GList);
					_getch();
				} else {
					error;
				}
			} else {
				say("Вы вышли за граници списка.");
				_getch();
			}
		}
	} else {
		error;
	}
}

/*Получение количества елементов списка*/
void GetCountList() {
	if (IsListEmpty(GList)) {
		printf_s("В списке %d елемент/та/тов\n", GiveCountOfList(GList));
		ListShow(GList);
		_getch();
	} else {
		say("Ошибка. Список пустой!");
		_getch();
	}
}

/*Для меню, фукция добавления елемента в спиок*/
void ALU() {
	AddIndexedItemList(0);
}
/*Для меню, фукция добавления елемента в спиок*/
void ALD() {
	AddIndexedItemList(1);
}

/*Поиск елемента в списке по индексу*/
void ListSearchByIndex() {
	int index, /*Индекс*/
		i; /*Счётчик*/
	struct List *l = GList;
	if (GList != NULL) {
		say("Введите индекс искуемого елемента: ");
		if (scanf_s("%d", &index)) {
			if (index > 1 && index <= GiveCountOfList(GList)) {
				for (i = 0; i < GiveCountOfList(GList) - index + 1; i++) {
					l = l->next;
				}
				printf_s("Елемент найден, значение елемента: %d\n", l->num);
				ListShow(GList);
				_getch();
			} else {
				say("Ошибка. Вы ввели не существующий индекс.");
				_getch();
			}
		} else {
			error;
		}
	} else {
		say("Ошибка. Список пустой");
		_getch();
	}
}

/*Поиск елемента в спике по значению*/
void ListSearchByNum() {
	int i, /*Счётчик*/
		num, /*Число*/
		nen = 0, /*Нашло ли*/
		k = 0, /*Количество найденых индексов*/
		*arr = (int*)malloc(sizeof(int)*GiveCountOfList(GList));
	struct List *l = GList;
	if (GList != NULL) {
		say("Введите число которое содержит искуемый елемент: ");
		if (scanf_s("%d", &num)) {
			for (i = 0; i < GiveCountOfList(GList); i++) {
				if (l->num == num) {
					arr[k] = i + 1;
					k++;
					nen = 1;
				}
				l = l->next;
			}
			if (nen == 0) {
				say("Елемент не найден.");
			} else {
				if (k > 1) {
					say("Елементы найдены: [Индексы] ");
					for (i = 0; i < k; i++) {
						if (i > 0) {
							printf_s("%d,", (GiveCountOfList(GList) + 2 - arr[i]));
						}
						else {
							printf_s("%d,", arr[i]);
						}
					}
				} else {
					printf_s("Елемент найден: [Индекс] %d",arr[0]);
				}
			}
			say("\n");
			ListShow(GList);
			free(arr);
			_getch();
		}
		else {
			error;
		}
	} else {
		say("Ошибка. Список пустой");
		_getch();
	}
}

/*Генирация рандомного списка*/
void ListGeneration() {
	int co, /*Количество елементов*/
		i; /*Счётчик*/
	say("Сколько елементов сгенирировать: ");
	if (scanf_s("%d", &co)) {
		if (co > 1) {
			if (co < 25000000) {
				for (i = 0; i < co; i++) {
					GList = AddItem(GList, rand() % co + 1);
				}
			}
			else {
				say("Ошибка. Слишком много елементов.");
				_getch();
			}
		}
		else {
			say("Ошибка. Слишком мало елементов.");
			_getch();
		}
	} else {
		error;
	}
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

	menu = CMenu(menu, 6);

	menu->text[menu->slots].str = "D)Сгенирировать случайный список";
	menu->binds[menu->slots].binds = "DВ";
	menu->pointers[menu->slots] = (int)(void*)&ListGeneration;
	menu->slots++;

	menu->text[menu->slots].str = "F)Найти елемент с заданым свойством";
	menu->binds[menu->slots].binds = "FА";
	menu->pointers[menu->slots] = (int)(void*)&list_menu_search;
	menu->slots++;

	menu->text[menu->slots].str = "G)Добавить узел в список";
	menu->binds[menu->slots].binds = "GП";
	menu->pointers[menu->slots] = (int)(void*)&list_menu_add;
	menu->slots++;

	menu->text[menu->slots].str = "C)Убрать узел с списка";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&RemoveItemFromList;
	menu->slots++;

	menu->text[menu->slots].str = "V)Получение размера списка";
	menu->binds[menu->slots].binds = "VМ";
	menu->pointers[menu->slots] = (int)(void*)&GetCountList;
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

/*list_menu_add*/
void list_menu_add() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "X)Вставить в список";
	menu->binds[menu->slots].binds = "XЧ";
	menu->pointers[menu->slots] = (int)(void*)&AddItemList;
	menu->slots++;

	menu->text[menu->slots].str = "C)Вставить до елемента";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&ALU;
	menu->slots++;

	menu->text[menu->slots].str = "V)Вставить после елемента";
	menu->binds[menu->slots].binds = "VМ";
	menu->pointers[menu->slots] = (int)(void*)&ALD;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Добавить узел:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 17;
	menu->properties.size.width = 30;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*list_menu_add*/
void list_menu_search() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)По логическому номеру";
	menu->binds[menu->slots].binds = "XЧ";
	menu->pointers[menu->slots] = (int)(void*)&ListSearchByIndex;
	menu->slots++;

	menu->text[menu->slots].str = "C)По значению";
	menu->binds[menu->slots].binds = "CС";
	menu->pointers[menu->slots] = (int)(void*)&ListSearchByNum;
	menu->slots++;

	menu->text[menu->slots].str = "Z)Назад";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Поиск елемента по параметру:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 17;
	menu->properties.size.width = 30;
	menu->properties.dbreak.binds = "ZЯ";
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}
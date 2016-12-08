#include "stdafx.h"
#include "CMenu.cpp"
#include "Defines.h"
#include "DekH.h"
#include "StekH.h"
#include "ListH.h"

/*Лист*/
//struct List {
//	int num; /*Число*/
//	struct List *next; /*Ссылка не следующий узел*/
//};

//struct List *GList; /*Указатель на список*/

/*
extern struct List *CreateFirstElem(int num);
extern struct List *AddItem(struct List *list, int num);
extern struct List *ListAddIndexedElement(struct List *list, int index, int number, int method);
extern struct List *RemoveIndexedElement(struct List *list, int index);
extern int GiveCountOfList(struct List *list);
extern int IsListEmpty(struct List *list);
extern void AddIndexedItemList(int mode);
extern void ListShow(struct List *list);
extern void ALU();
extern void ALD();
extern void ListSearchByNum();
extern void GetCountList();
extern void list_glavn();
extern void list_menu_add();
extern void RemoveItemFromList();
extern void list_menu_search();
extern void ListSearchByIndex();
extern void ListGeneration();
extern void AddItemList();
*/

struct List *GList; /*Указатель на список*/
/*-----DEEP-DEAD-ZONE-----*/

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
			}
			else {
				say("Список: ");
				printf_s("%d", list->num);
			}
		}
		else {
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
		for (i = 0; i < GiveCountOfList(list) - index; i++) {
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
	}
	else {
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
				}
				else {
					say("Ошибка. Вы ввели индекс не существующего елемента.");
					_getch();
				}
			}
			else if (i == 1) {
				if (GiveCountOfList(GList) == 1) {
					GList = RemoveIndexedElement(GList, i);
					printf_s("Елемент с индексом %d был удалён.\n", i);
				}
				else {
					say("Ошибка. Удалить 1-вый елемент списка не возможно.");
				}
				_getch();
			}
			else if (i <= 0) {
				say("Ошибка. Вы ввели индекс не существующего елемента.");
				_getch();
			}
		}
		else {
			error;
		}
	}
	else {
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
	}
	else {
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
				}
				else {
					error;
				}
			}
			else {
				say("Вы вышли за граници списка.");
				_getch();
			}
		}
		else {
			if (index > 0 && index < GiveCountOfList(GList) + 1) {
				say("Введите число: ");
				if (scanf_s("%d", &num)) {
					GList = ListAddIndexedElement(GList, index, num, 1);
					say("Узел добавлен!\n");
					ListShow(GList);
					_getch();
				}
				else {
					error;
				}
			}
			else {
				say("Вы вышли за граници списка.");
				_getch();
			}
		}
	}
	else {
		error;
	}
}

/*Получение количества елементов списка*/
void GetCountList() {
	if (IsListEmpty(GList)) {
		printf_s("В списке %d елемент/та/тов\n", GiveCountOfList(GList));
		ListShow(GList);
		_getch();
	}
	else {
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
			}
			else {
				say("Ошибка. Вы ввели не существующий индекс.");
				_getch();
			}
		}
		else {
			error;
		}
	}
	else {
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
			}
			else {
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
				}
				else {
					printf_s("Елемент найден: [Индекс] %d", arr[0]);
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
	}
	else {
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
	}
	else {
		error;
	}
}

/*Получение первого елемената*/
void GetListFirstElemt() {
	struct List *l = GList; /*Указатель на список*/
	int i; /*Счётчик*/
	if (GList != NULL) {
		if (GiveCountOfList(GList) != 0) {
			for (i = 0; i < 1; i++) {
				l = l->next;
			}
			printf_s("Первый елемент списка: %d", l->num);
			_getch();
		}
		else {
			say("Ошибка. Стек пустой.");
			_getch();
		}
	}
	else {
		say("Ошибка. Стек пустой.");
		_getch();
	}
}
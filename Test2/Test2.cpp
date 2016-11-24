// Test2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define error _error();_getch();
#define say(text) _say(text);

void _error() {
	printf_s("Ошибка ввода!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}

typedef struct {
	int number;
	int *next;
} SpisItem;

typedef struct {
	int count;
	SpisItem *first;
} SpisDescr;

SpisDescr *SSDes;
//SpisDescr *SpisPushF(SpisDescr*, int, int, int);

struct List{
	int num;
	struct List *next;
};

struct List *CreateFirstElem(int num) {
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list->num = num;
	list->next = list;
	return list;
}

struct List *AddItem(struct List *list, int num) {
	struct List *item, *p;
	if (IsListEmpty(list)) {
		item = (struct List*)malloc(sizeof(struct List));
		p = list->next;
		item->num = num;
		list->next = item;
		item->next = p;
	} else {
		list = CreateFirstElem(num);
	}
	return list;
}

struct List *GetSelectedItem(struct List *list,int elem) {
	struct List *p = list;
	printf_s("[%d]\n",p->num);
	for (int i = 0; i < elem; i++) {
		p = p->next;
		printf_s("[%d]\n", p->num);
	}
	return p;
}

void ListShow(struct List *list) {
	struct List *p;
	int *arra = (int*)malloc(sizeof(int)), i = 0, j = 0;
	p = list;
	if (IsListEmpty(list)) {
		if (GiveCountOfList(list) > 1) {
			do {
				//printf("%d ", p->num);
				arra = (int*)realloc(arra, sizeof(int)*(i + 1));
				arra[i] = p->num;
				p = p->next;
				i++;
			} while (p != list);
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
			printf_s("%d", list->num);
		}
	} else {
		printf_s("Ошибка. Лист пустой.");
	}
}

struct List *ListAddIndexedElement(struct List *list, int index,int number, int method) {
	int i = 0;
	struct List *item, *p, *l = list;
	item = (struct List*)malloc(sizeof(struct List));

	/*Вставить после*/
	if (method == 0) {
		for (i = 0; i < GiveCountOfList(list) - index; i++) {
			l = l->next;
		}
	} else {
	/*Вставить перед*/
		for (i = 0; i < GiveCountOfList(list) - index - 1; i++) {
			l = l->next;
		}
	}
	p = l->next;
	item->num = number;
	l->next = item;
	item->next = p;

	return list;
}

struct List *RemoveIndexedElement(struct List *list, int index) {
	int i;
	struct List *l = list;
	if (GiveCountOfList(list) > 1) {
		for (i = 0; i < GiveCountOfList(list) - index - 1; i++) {
			l = l->next;
		}
		l->next = l->next->next;
	} else {
		free(list);
		list = NULL;
	}
	return list;
}

int GiveCountOfList(struct List *list) {
	struct List *l = list;
	int i = 0;
	if (IsListEmpty(list)) {
		do {
			l = l->next;
			i++;
		} while (l != list);
	}
	return i;
}

int IsListEmpty(struct List *list) {
	int i = 1;
	if (list == NULL) {
		i = 0;
	}
	return i;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	struct List *list;

	//list->num - first element
	//

	list = CreateFirstElem(30); //1
	list = AddItem(list, 40); //2
	list = AddItem(list, 50); //3
	list = AddItem(list, 60); //4
	list = AddItem(list, 70); //5
	list = AddItem(list, 80); //6
	list = AddItem(list, 90); //7

	list = ListAddIndexedElement(list, 2, 1488, 0);

	list = RemoveIndexedElement(list, 1);
	list = RemoveIndexedElement(list, 2);
	list = RemoveIndexedElement(list, 3);
	list = RemoveIndexedElement(list, 4);
	list = RemoveIndexedElement(list, 5);
	list = RemoveIndexedElement(list, 6);
	list = RemoveIndexedElement(list, 7);

	list = RemoveIndexedElement(list, 0);

	list = AddItem(list, 228);
	list = AddItem(list, 1);
	list = AddItem(list, 2);
	list = AddItem(list, 3);
	list = AddItem(list, 4);
	list = AddItem(list, 5);
	

	printf_s("count: %d\n", GiveCountOfList(list));
	_getch();
	ListShow(list);
	_getch();
	/*
	SSDes = (SpisDescr*)malloc(sizeof(SpisDescr));
	SSDes->count = 0;
	int cud, wher, num;
	Start:
	if (SSDes->count != 0) {
	Pcud:
		system("cls");
		say("Введите номер узла: ");
		if (!scanf_s("%d", &cud)) {
			error;
			goto Pcud;
		}
	Pwher:
		system("cls");
		say("Вставить 0)после него или 1)перед ним: ");
		if (!scanf_s("%d", &wher)) {
			error;
			goto Pwher;
		}
	} else {
		cud = 0; wher = 0;
	}
	Pnum:
		system("cls");
		say("Введите число: ");
		if (!scanf_s("%d", &num)) {
			error;
			goto Pnum;
		}

	SSDes = SpisPushF(SSDes,cud,wher,num);

	SpisItem *last = SSDes->first;
	for (int i = 0; i < SSDes->count; i++) {
		printf_s("%d,",last->number);
		last = (SpisItem*)last->next;
	}
	_getch();
	goto Start;
	*/
    return 0;
}

/*
SpisDescr *SpisPushF(SpisDescr* des, int cud, int wher, int num) {
	SpisItem *item = (SpisItem*)malloc(sizeof(SpisItem));
	SpisItem *litem = des->first;
	SpisItem *llitem;
	int i;
	
	if (des->count == 0) {
		item->number = num;
		item->next = (int*)item;
		des->first = item;
	} else {
		item->number = num;
		item->next = NULL;
		switch (wher) {
		case 0: //После него
			if (des->count != cud) {
				for (i = 1; i < cud; i++) {
					litem = (SpisItem*)litem->next;
				}

				if (litem->next != NULL) {
					llitem = (SpisItem*)litem->next;
				} else {
					llitem = NULL;
				}

				litem->next = (int*)item;
				item->next = (int*)llitem;
			} else {
				for (i = 1; i < cud; i++) {
					litem = (SpisItem*)litem->next;
				}
				item->next = (int*)des->first;
				litem->next = (int*)item;
			}
			break;
		case 1: //До него
			if (cud != 1) {
				for (i = 1; i < cud - 1; i++) {
					litem = (SpisItem*)litem->next;
				}

				if (litem->next != NULL) {
					llitem = (SpisItem*)litem->next;
				} else {
					llitem = NULL;
				}

				litem->next = (int*)item;
				item->next = (int*)llitem;
			} else {
				des->first = item;
				item->next = (int*)litem;
			}
			break;
		}
	}
	des->count++;
	return des;
}
*/
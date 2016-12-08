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
	int *previus;
} SpisItem;

typedef struct {
	int count;
	SpisItem *first;
} SpisDescr;

SpisDescr *SSDes;


SpisDescr *CreateSpisDescr() {
	SpisDescr *des = (SpisDescr*)malloc(sizeof(SpisDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

SpisItem *GiveFirst(SpisDescr *des) {
	int i;
	SpisItem *first = des->first;
	for (i = 0; i < des->count - 1; i++) {
		first = first->previus;
	}
	return first;
}

SpisDescr *SpisAddItem(SpisDescr *des,int num) {
	SpisItem *item = (SpisItem*)malloc(sizeof(SpisItem));
	SpisItem *last;
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

int IsListZerro(SpisDescr *des) {
	int is = 1;
	if (des == NULL) {
		is = 0;
	}
	return is;
}

void ListShow(SpisDescr *des) {
	int i, *arr;
	SpisItem *last;
	if (IsListZerro(des)) {
		if (des->count > 200) {
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
			printf_s("Вывод на екран такого количества елементов, не есть рациональным, по етому вывод будет произвидён в файл list.txt");
			/*Сделать вывод в файл*/
		}
	} else {
		printf_s("Список пуст.\n");
	}
}

SpisDescr *SetListFirst(SpisDescr *des, int index) {
	SpisItem *last = des->first;
	int i;
	for (i = 0; i < index; i++) {
		last = last->previus;
	}
	des->first = last;
	return des;
}

SpisDescr *RemoveItem(SpisDescr *des) {
	SpisItem *last = des->first, *bottom = GiveFirst(des);
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

SpisDescr *FindItem(SpisDescr *des,int num) {
	SpisItem *now = des->first;
	int i;
	for (i = 0; i < des->count; i++) {
		if (now->number == num) {
			des = SetListFirst(des,i);
			printf_s("Елемент найден!\n",i);
			i = des->count;
			return des;
		}
		now = now->previus;
	}
	printf_s("Елемент не найден!\n");
	return des;
}

SpisDescr *GList;

void demo_show_loshadki() {
	int num, i;
	char c;
	ListShow(GList);
	while (1) {
		c = _getch();
		c = toupper(c);
		system("cls");
		switch (c)
		{
		case 'D':
			if (IsListZerro(GList)) {
				SetListFirst(GList, 1);
			} else {
				printf_s("Ошибка. Список пустой.\n");
			}
			break;
		case 'A':
			printf_s("Введите число: ");
			if (scanf_s("%d", &num)) {
				GList = SpisAddItem(GList, num);
			} else {
				printf_s("Ошибка ввода!.");
				rewind(stdin);
			}
			break;
		case 'S':
			if (IsListZerro(GList)) {
				GList = RemoveItem(GList);
			} else {
				printf_s("Ошибка. Список пустой, вы не можете удалить елемет.\n");
			}
			break;
		case 'F':
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
			printf_s("Сколько елементов сгенирировать: ");
			if (scanf_s("%d", &num)) {
				if (num > 1 && num < 20000000) {
					for (i = 0; i < num; i++) {
						GList = SpisAddItem(GList, rand()%num+1);
					}
					printf_s("%d елементов сгенирировано!\n", num);
				} else {
					printf_s("Не возможно сгенирировать %d елементов\n",num);
				}
			} else {
				printf_s("Ошибка ввода.");
			}
			break;
		case 'R':
			printf_s("В списке %d елемент/а/ов.\n",GList->count);
			break;
		default:

			break;
		}
		ListShow(GList);
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	demo_show_loshadki();

	SetListFirst(GList, 0);

	ListShow(GList);

	_getch();
	/*

	list = CreateFirstElem(30); //1
	list = AddItem(list, 40); //2
	list = AddItem(list, 50); //3
	list = AddItem(list, 60); //4
	list = AddItem(list, 70); //5
	list = AddItem(list, 80); //6
	list = AddItem(list, 90); //7

	list = ListAddIndexedElement(list, 2, 1488, 0);

	list = RemoveIndexedElement(list, 5);

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
	*/
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
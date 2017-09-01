#include "stdafx.h"
#include "CMenu.cpp"
#include "Defines.h"
#include "DekH.h"
#include "StekH.h"
#include "ListH.h"

StekDescr *SDes; /*��������� �� ���������� �����*/
DekDescr *DDes; /*��������� �� ���������� ����*/
SpisDescr *GList; /*��������� �� ������*/

int main()
{
	int slots = 0; /*���������� ������� ����*/
	Menu *menu = NULL; /*��������� �� ����*/
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));
	system("color F0");

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "D)����";
	menu->binds[menu->slots].binds = "D�";
	menu->pointers[menu->slots] = (int)(void*)&stek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "F)���";
	menu->binds[menu->slots].binds = "F�";
	menu->pointers[menu->slots] = (int)(void*)&dek_glavn;
	menu->slots++;

	menu->text[menu->slots].str = "G)����(��������� ������)";
	menu->binds[menu->slots].binds = "G�";
	menu->pointers[menu->slots] = (int)(void*)&list_glavn;

	menu->properties.header = "���� ���������:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 30;
	menu->properties.dbreak.binds = "P�";
	menu->properties.prioritet = 0;

	SmartChoose(menu);

	_getch();
	return 0;
}

/*��������� ���������� �����*/
void StekGeneration(int count) {
	int i; /*������� �����*/
	for (i = 0; i < count; i++) {
		StekCreateItem(rand() % count + 1, SDes);
	}
}

/*��������� ���������� �����*/
void StekGenerations() {
	int num; /*���������� ���������*/
	if (SDes == NULL) {
		SDes = StekCreateDescr();
	}
	say("������� ��������� �������������: ");
	if (scanf_s("%d", &num)) {
		if (num < 25000000 && num > 0) {
			StekGeneration(num);
			say("���� ������������ �������.\n");
			StekShow();
			_getch();
		} if (num < 1) {
			say("������� ���� ���������!");
			_getch();
		} if (num > 25000000) {
			say("������� ����� ���������!");
			_getch();
		}
	} else {
		error;
	}
}

/*�������� ����������� �����*/
StekDescr* StekCreateDescr() {
	StekDescr *des; /*��������� �� ���������� �����*/
	des = (StekDescr*)malloc(sizeof(StekDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

/*�������� �������� �����*/
StekDescr* StekCreateItem(int number, StekDescr *des) {
	StekItem* item; /*��������� �� ������� �����*/
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

/*������(��������) �������� �����*/
StekDescr* StekDeletItem(StekDescr *des) {
	StekItem *last; /*��������� �� ������� �����*/
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

/*�������� �� ��������� ������ ��� ������ � ������*/
int SetkError(StekDescr *des) {
	if (des != NULL) {
		if ((void*)des->count != NULL) {
			if (des->count < 1) {
				say("������. � ����� 0 ���������, ������ �� ��������!");
				_getch();
				return 0;
			}
			else { return 1; }
		}
		else {
			say("������. ���� ������!");
			_getch();
			return 0;
		}
	} else {
		say("������. ���� ������!");
		_getch();
		return 0;
	}
}

/*��������(��������) �������� �����*/
void StekPush() {
	int num; /*������ �����*/
	say("������� �����: ");
	if (scanf_s("%d", &num)) {
		SDes = StekCreateItem(num, SDes);
		say("����� ������� ��������!\n");
		StekShow();
	} else {
		error;
	}
	_getch();
}

/*������(��������) �������� �����*/
void StekPop() {
	int it; /*������ ������� �� ������*/
	if (SetkError(SDes)) {
		it = SDes->first->number;
		SDes = StekDeletItem(SDes);
		if (SDes != NULL) {
			printf_s("������� ������� %d �����, ������ ����� ������� �������: %d\n",it, SDes->first->number);
			StekShow();
		}else{
			printf_s("������� ������� %d ��� ����, ������ ���� ��������� �������.", it);
		}
		_getch();
	}
}

/*������� ������ �����*/
void StekShow() {
	FILE *file; /*��������� �� ���� ������*/
	StekItem *dl = SDes->first; /*��������� �� ������� �����*/
	int i, /*�������*/
		count = 0, /*������� ���� � ������ �����*/
		*arr; /*��������� �� ������*/
	if (SDes->count < 500) {
		arr = (int*)malloc(sizeof(int)*SDes->count);
		for (i = 0; i < SDes->count; i++) {
			arr[i] = dl->number;
			dl = (StekItem*)dl->previus;
		}
		say("����: ");
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
		say("������� ����� ��������� ��� ������, ����� ��������� � ���� StekElems.txt � ����� � ����������");
	}
	else {
		say("������� ����� ��������� ���� ��� ������ � ����, ��� ��� �� �� ������� ��� :) ");
	}
}

/*������� ������ ��������� ��������� � �����*/
void StekCount() {
	if (SetkError(SDes)) {
		printf_s("� �����: %d �������/��/���.\n", SDes->count);
		StekShow();
		_getch();
	}
}

/*DECK ZONE*/

/*�������� ����������� ����*/
DekDescr *DekCreation() {
	DekDescr *des; /*��������� �� ���������� ����*/
	des = (DekDescr*)malloc(sizeof(DekDescr));
	des->count = 0;
	des->first = NULL;
	des->last = NULL;
	return des;
}

/*��������� ��������� ��������� ��� ����*/
DekDescr *DekGeneration(DekDescr *des,int count) {
	int i; /*�������*/
	for (i = 0; i < count; i++) {
		des = DekCreateItem(rand() % count + 1,0, des);
	}
	return des;
}

/*��������� ��������� ��������� ��� ����*/
void DekGenerations() {
	int num; /*���������� ���������*/
	if(DDes == NULL){
		DDes = DekCreation();
	}
	say("������� ��������� �������������: ");
	if (scanf_s("%d", &num)) {
		if (num < 24000000 && num > 0) {
			DDes = DekGeneration(DDes,num);
			say("��� ������������ �������.\n");
			DekShow();
			_getch();
		} if (num < 1) {
			say("������� ���� ���������!");
			_getch();
		} if (num > 25000000) {
			say("������� ����� ���������!");
			_getch();
		}
	} else {
		error;
	}
}

/*�������� �������� ����*/
DekDescr* DekCreateItem(int number,int type,DekDescr *des) {
	DekItem* item = (DekItem*)malloc(sizeof(DekItem)); /*��������� �� ������� ����*/
	DekItem* iteml; /*��������� �� ������� ����*/
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

/*�������� �������� ����*/
DekDescr* DekDeletItem(DekDescr *des,int type) {
	DekItem *last; /*�������� �������� ����*/
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

/*�������� �� ��������� ������ ��� ������ � �����*/
int DekError(DekDescr *des) {
	if (des != NULL) {
		if ((void*)des->count != NULL) {
			if (des->count < 1) {
				say("������. � ���� 0 ���������, ������ �� ��������!");
				_getch();
				return 0;
			}
			else { return 1; }
		}
		else {
			say("������. ��� ������!");
			_getch();
			return 0;
		}
	} else {
		say("������. ��� ������!");
		_getch();
		return 0;
	}
}

/*���� �������� �������, ��� ���� (������� �������� � ������� ��)*/
void DPU() { DDes = DekPush(DDes, 0); DekShow(); _getch(); }
void DPD() { DDes = DekPush(DDes, 1); DekShow(); _getch(); }
void DOU() { DDes = DekPop(DDes, 0); if (DDes != NULL) { DekShow(); _getch(); } }
void DOD() { DDes = DekPop(DDes, 1); if (DDes != NULL) { DekShow(); _getch(); } }

/*�������� ������� � ���(������� ����� �������)*/
DekDescr *DekPush(DekDescr *des,int type) {
	int num; /*������ �����*/
	say("������� �����: ");
	if (scanf_s("%d", &num)) {
		des = DekCreateItem(num, type, des);
		say("����� ������� ��������!\n");
	} else {
		error;
	}
	return des;
}

/*����� ������� � ����(������� �������)*/
DekDescr *DekPop(DekDescr* des,int type) {
	int last; /*�������� �������� ��������*/
	DekItem *now; /*��������� �� ���������� ����*/
	if (DekError(des)) {
		if (des->count > 1) {
			if (type == 0) {
				printf_s("������");
				last = des->first->number;
				des = DekDeletItem(des, type);
				now = (DekItem*)des->first->number;
			}
			else {
				printf_s("���������");
				last = des->last->number;
				des = DekDeletItem(des, type);
				now = (DekItem*)des->last->number;
			}
			printf_s(" ������� %d ����, ����� ��������� ������� %d\n", (int)last, (int)now);
		} else {
			now = (DekItem*)des->first->number;
			des = DekDeletItem(des, type);
			printf_s("������� %d ��� ����. ������ ��� ��������� ����.",(int)now);
			_getch();
		}
	}
	return des;
}

/*������������ ����*/
void DekShow() {
	FILE *file; /*��������� �� ����*/
	DekItem *dl; /*��������� �� ������� ����*/
	int i, /*�������*/ 
		count = 0; /*������� ���� � ������ �����*/
	if (DDes->count < 500) {
	    dl = DDes->last;
		say("���: ");
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
		say("������� ����� ��������� ��� ������, ����� ��������� � ���� DekElems.txt � ����� � ����������");
	} else {
		say("������� ����� ��������� ���� ��� ������ � ����, ��� ��� �� �� ������� ��� :) ");
	}
}

/*������� ��������� ����*/
void DekCount() {
	if (DDes != NULL) {
		printf_s("� ���� %d ���������.\n", DDes->count);
		DekShow();
		_getch();
	} else { 
		printf_s("��� ������."); _getch();
	}
}


/*---Cycle-Spisok-Zone---*/

/*������� ���������� ������*/
SpisDescr *CreateSpisDescr() {
	/*��������� �� ���������� ������*/
	SpisDescr *des = (SpisDescr*)malloc(sizeof(SpisDescr));
	des->first = NULL;
	des->count = 0;
	return des;
}

/*������� ������ �������*/
SpisItem *GiveFirst(SpisDescr *des) {
	int i; /*������� �����*/
	/*��������� �� ������� ������*/
	SpisItem *first = des->first; 
	for (i = 0; i < des->count - 1; i++) {
		first = first->previus;
	}
	return first;
}

/*�������� ������� � ������*/
SpisDescr *SpisAddItem(SpisDescr *des, int num) {
	/*��������� �� �������� ������*/
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

/*�������� ������ �� �������*/
int IsListZerro(SpisDescr *des) {
	int is = 1; /*������ ���� ��� ����*/
	if (des == NULL) {
		is = 0;
	}
	return is;
}

/*��������������� ������*/
void ListShow(SpisDescr *des) {
	int i, /*������� �����*/
		*arr; /*������ �����*/
	SpisItem *last; /*��������� �� ������� ������*/
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
		printf_s("������ ����.\n");
	}
}

/*�������� ��������� ������*/
void ListShowHigh() {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	Coord.X = 90;
	Coord.Y = 21;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("���������:");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("D) ������� ������ � �����");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("S) ������� �������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("A) �������� �������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("A) ����� �������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("G) ������������� �������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("R) ���������� ���������");
}

/*���������� ������ ������� ������*/
SpisDescr *SetListFirst(SpisDescr *des, int index) {
	SpisItem *last = des->first; /*��������� �� ������� ������*/
	int i; /*������� �����*/
	if (des->count > 1) {
		for (i = 0; i < index; i++) {
			last = last->previus;
		}
		des->first = last;
	}
	return des;
}

/*������ ������� � ������*/
SpisDescr *RemoveItem(SpisDescr *des) {
	/*��������� �� �������� ������*/
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

/*����� ������� � ������*/
SpisDescr *FindItem(SpisDescr *des, int num) {
	/*��������� �� ������� ������*/
	SpisItem *now = des->first;
	int i; /*������� �����*/
	for (i = 0; i < des->count; i++) {
		if (now->number == num) {
			des = SetListFirst(des, i);
			printf_s("������� ������!\n", i);
			i = des->count;
			return des;
		}
		now = now->previus;
	}
	printf_s("������� �� ������!\n");
	return des;
}

/*������������� ����� ������������ ������*/
void demo_show_loshadki() {
	int num, /*������ �����*/
		i; /*������� �����*/
	char c; /*������� ������*/
	ListShow(GList);
	while (1) {
		c = _getch();
		c = toupper(c);
		system("cls");
		switch (c)
		{
		case 'D':
		case '�':
			if (IsListZerro(GList)) {
				SetListFirst(GList, 1);
			} else {
				printf_s("������. ������ ������.\n");
			}
			break;
		case 'A':
		case '�':
			printf_s("������� �����: ");
			if (scanf_s("%d", &num)) {
				GList = SpisAddItem(GList, num);
			} else {
				printf_s("������ �����!.");
				rewind(stdin);
			}
			break;
		case 'S':
		case '�':
			if (IsListZerro(GList)) {
				GList = RemoveItem(GList);
			} else {
				printf_s("������. ������ ������, �� �� ������ ������� ������.\n");
			}
			break;
		case 'F':
		case '�':
			if (IsListZerro(GList)) {
				printf_s("������� �������� �����: ");
				if (scanf_s("%d", &num)) {
					GList = FindItem(GList, num);
				} else {
					printf_s("������ �����!.");
					rewind(stdin);
				}
			} else {
				printf_s("������. ������ ������.\n");
			}
			break;
		case 'G':
		case '�':
			printf_s("������� ��������� �������������: ");
			if (scanf_s("%d", &num)) {
				if (num > 1 && num < 20000000) {
					for (i = 0; i < num; i++) {
						GList = SpisAddItem(GList, rand() % num + 1);
					}
					printf_s("%d ��������� �������������!\n", num);
				} else {
					printf_s("�� �������� ������������� %d ���������\n", num);
				}
			} else {
				printf_s("������ �����.");
			}
			break;
		case 'R':
			if (IsListZerro(GList)) {
				printf_s("� ������ %d �������/�/��.\n", GList->count);
			} else {
				printf_s("������. ������ ������.\n");
			}
			break;
		default:

			break;
		}
		ListShow(GList);
	}
}

/*��������� ������*/
void ListGeneration() {
	int num, /*������ �����*/
		i; /*������� �����*/
	printf_s("������� ��������� �������������: ");
	if (scanf_s("%d", &num)) {
		if (num > 1 && num < 20000000) {
			for (i = 0; i < num; i++) {
				GList = SpisAddItem(GList, rand() % num + 1);
			}
			printf_s("%d ��������� �������������!\n", num);
		} else {
			printf_s("�� �������� ������������� %d ���������\n", num);
		}
	} else {
		printf_s("������ �����.");
	}
	ListShow(GList);
	_getch();
}

/*������ ���� � ������*/
void RemoveItemFromList() {
	if (IsListZerro(GList)) {
		GList = RemoveItem(GList);
	} else {
		printf_s("������. ������ ������, �� �� ������ ������� ������.\n");
	}
	ListShow(GList);
	_getch();
}

/*�������� ������ �����*/
void GetCountList() {
	if (IsListZerro(GList)) {
		printf_s("� ������ %d �������/�/��.\n", GList->count);
	}
	else {
		printf_s("������. ������ ������.\n");
	}
	ListShow(GList);
	_getch();
}

/*����� ������� � ������*/
void ListFindElement() {
	int num; /*������ �����*/
	if (IsListZerro(GList)) {
		printf_s("������� �������� �����: ");
		if (scanf_s("%d", &num)) {
			GList = FindItem(GList, num);
		}
		else {
			printf_s("������ �����!.");
			rewind(stdin);
		}
	}
	else {
		printf_s("������. ������ ������.\n");
	}
	ListShow(GList);
	_getch();
}

/*�������� ������� � ������*/
void ListAddSource() {
	int num; /*������ �����*/
	printf_s("������� �����: ");
	if (scanf_s("%d", &num)) {
		GList = SpisAddItem(GList, num);
	}
	else {
		printf_s("������ �����!.");
		rewind(stdin);
	}
	ListShow(GList);
	_getch();
}

/*���� �����*/
void stek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)������������� ��������� ����";
	menu->binds[menu->slots].binds = "D�";
	menu->pointers[menu->slots] = (int)(void*)&StekGenerations;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH(�������� � ����)";
	menu->binds[menu->slots].binds = "F�";
	menu->pointers[menu->slots] = (int)(void*)&StekPush;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP(����� � �����)";
	menu->binds[menu->slots].binds = "G�";
	menu->pointers[menu->slots] = (int)(void*)&StekPop;
	menu->slots++;

	menu->text[menu->slots].str = "C)��������� ������� �����";
	menu->binds[menu->slots].binds = "C�";
	menu->pointers[menu->slots] = (int)(void*)&StekCount;
	menu->slots++;

	menu->text[menu->slots].str = "Z)�����";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "������� ������� �����:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 35;
	menu->properties.dbreak.binds = "Z�";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*���� ����*/
void dek_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 5);

	menu->text[menu->slots].str = "D)������������� ��������� ���";
	menu->binds[menu->slots].binds = "D�";
	menu->pointers[menu->slots] = (int)(void*)&DekGenerations;
	menu->slots++;

	menu->text[menu->slots].str = "F)PUSH(�������� � ���)";
	menu->binds[menu->slots].binds = "F�";
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_push;
	menu->slots++;

	menu->text[menu->slots].str = "G)POP(����� � ����)";
	menu->binds[menu->slots].binds = "G�";
	menu->pointers[menu->slots] = (int)(void*)&dek_menu_pop;
	menu->slots++;

	menu->text[menu->slots].str = "C)��������� ������� ����";
	menu->binds[menu->slots].binds = "C�";
	menu->pointers[menu->slots] = (int)(void*)&DekCount;
	menu->slots++;

	menu->text[menu->slots].str = "Z)�����";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "������� ������� ����:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 20;
	menu->properties.size.width = 34;
	menu->properties.dbreak.binds = "Z�";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

/*Dek_push_vib*/
void dek_menu_push() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)�������� �� ����";
	menu->binds[menu->slots].binds = "X�";
	menu->pointers[menu->slots] = (int)(void*)&DPU;
	menu->slots++;

	menu->text[menu->slots].str = "C)�������� � ����";
	menu->binds[menu->slots].binds = "C�";
	menu->pointers[menu->slots] = (int)(void*)&DPD;
	menu->slots++;

	menu->text[menu->slots].str = "Z)�����";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Push:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "Z�";
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*Dek_pop_vib*/
void dek_menu_pop() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 3);

	menu->text[menu->slots].str = "X)����� � �����";
	menu->binds[menu->slots].binds = "X�";
	menu->pointers[menu->slots] = (int)(void*)&DOU;
	menu->slots++;

	menu->text[menu->slots].str = "C)����� � ����";
	menu->binds[menu->slots].binds = "C�";
	menu->pointers[menu->slots] = (int)(void*)&DOD;
	menu->slots++;

	menu->text[menu->slots].str = "Z)�����";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "Pop:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 14;
	menu->properties.size.width = 29;
	menu->properties.dbreak.binds = "Z�";
	menu->properties.prioritet = 1;

	SmartChoose(menu);
}

/*���� ������*/
void list_glavn() {
	int slots = 0;
	Menu *menu = NULL;

	menu = CMenu(menu, 8);

	menu->text[menu->slots].str = "D)������������� ��������� ������";
	menu->binds[menu->slots].binds = "D�";
	menu->pointers[menu->slots] = (int)(void*)&ListGeneration;
	menu->slots++;

	menu->text[menu->slots].str = "F)����� ������� � ������� ���������";
	menu->binds[menu->slots].binds = "F�";
	menu->pointers[menu->slots] = (int)(void*)&ListFindElement;
	menu->slots++;

	menu->text[menu->slots].str = "G)�������� ���� � ������";
	menu->binds[menu->slots].binds = "G�";
	menu->pointers[menu->slots] = (int)(void*)&ListAddSource;
	menu->slots++;

	menu->text[menu->slots].str = "C)������ ���� � ������";
	menu->binds[menu->slots].binds = "C�";
	menu->pointers[menu->slots] = (int)(void*)&RemoveItemFromList;
	menu->slots++;

	menu->text[menu->slots].str = "V)��������� ������� ������";
	menu->binds[menu->slots].binds = "V�";
	menu->pointers[menu->slots] = (int)(void*)&GetCountList;
	menu->slots++;

	menu->text[menu->slots].str = "B)������������� ������� ������������";
	menu->binds[menu->slots].binds = "B�";
	menu->pointers[menu->slots] = (int)(void*)&demo_show_loshadki;
	menu->slots++;

	menu->text[menu->slots].str = "Z)�����";
	menu->binds[menu->slots].binds = NULL;
	menu->pointers[menu->slots] = (int)NULL;

	menu->properties.header = "������� ������� ������:";
	menu->properties.height = 0;
	menu->properties.coords.x = 7;
	menu->properties.coords.y = 4;
	menu->properties.size.height = 25;
	menu->properties.size.width = 41;
	menu->properties.dbreak.binds = "Z�";
	menu->properties.prioritet = 2;

	SmartChoose(menu);
}

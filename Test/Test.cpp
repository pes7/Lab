// Test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#define arr_size(arr)  (sizeof arr / sizeof arr[0])
#define arrcopy(arr,maxer) _arrcopy(arr,maxer)
#define arrgen(maxe,nmax) _arrgen(maxe,nmax)
#define printarr(dee,maxe) printfer(dee,maxe)
#define error _error()
//#define cls _cls()
#define say(text) _say(text);
#define pause _pause();
#define MULT 2
#define error101 say("Ошибка. Неудачная попытка снять елемент с пустого стека!\n"); err = 1; wt;
#define error102 say("Ошибка. Вы неможите добавить новый елемент в стек, поскольку он не может больше рости!\n"); err = 1; wt;
#define error103 say("Ошибка. Нету больше елементов в стеке, стек - пустой!\n"); err = 1; wt;
#define error104 say("Ошибка. Стек не создан\n"); err = 1; wt;
#define error105 say("Ошибка. 0 елеметов в стеке!\n"); err = 1; wt;
#define error1 say("Неверное указания размера стека!\n"); err = 1; wt;
#define error2 say("Невозможно выполнить операцию, стек не создан!\n"); err = 1; wt;
#define wt _getch();
void _pause() {
	system("pause");
}

void _error() {
	printf_s("Ошибка ввода!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}

void _cls() {
	system("cls");
}

/*
int de;
void kek();
void keker();
void printfer(int*,int);
int* arrs;
int* idd;

typedef struct {
	char *str;
	int lengh;
} Word;

typedef struct {
	char *binds;
	int count;
} Binds;

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	int width;
	int height;
} Size;

typedef struct {
	Point coords;
	Size size;
	Binds dbreak;
	int height;
	int prioritet;
	char *header;
} Properties;

typedef struct {
	Word *text;
	Binds *binds;
	Properties properties;
	int *pointers;
	int slots;
} Menu;

void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}
enum WDek { Top, Down };
typedef struct {
	int *nums;
	size_t top;
	size_t bottom;
	size_t count;
} Dek;

void MassageBox(char*, int,Point*);
void CrateBorder(Point*, Point*);
void Say(char*, Point*);
void sap();
void sap1();
void SmartChoose(Menu*);
Menu *CMenu(Menu*,int);
Dek *CreateDek(int);
Dek *PutInDek(Dek*,int,int);
Dek *ReSizeStek(Dek*);
volatile void newer();


int err = 0;


//Создание дека
Dek* CreateDek(int size) {
	Dek *dek;
	dek = (Dek*)malloc(sizeof(Dek));
	dek->nums = (int*)malloc(sizeof(int) * size);
	dek->top = 0;
	dek->bottom = 0;
	dek->count = size;
	return dek;
}

//Переформатирование стека
Dek* ReSizeDek(Dek* dek) {
	if (dek->nums != NULL) {
		dek->count *= 2;
		dek->nums = (int*)realloc(dek->nums, dek->count * sizeof(int));
	}
	else {
		
	}
	return dek;
}


Dek* PutInDek(Dek* dek, int what, int wheres) {
	int i;
	switch (wheres) {
	case 0:
		if (dek->top >= dek->count) {
			ReSizeDek(dek);
		}
		dek->nums[dek->top] = what;
		dek->top++;
		break;
	case 1://Bottom
		if (dek->bottom == 0) {
			if (dek->top >= dek->count - 1) {
				ReSizeDek(dek);
			}
			for (i = dek->top - 1; i >= 0; i--) {
				dek->nums[i + 1] = dek->nums[i];
			}
			dek->top++;
			dek->nums[dek->bottom] = what;
		} else {
			dek->bottom--;
			dek->nums[dek->bottom] = what;
		}
		break;
	}
	return dek;
}

Dek* PopDek(Dek* dek, int wheres) {
	int i = 0, l;
	switch (wheres) {
	case 0:
		if (dek->top != 0) {
			dek->top--;
		} else {
			error103;
			err = 1;
		}
		break;
	case 1:
		if (dek->top != 0) {
			//Доробыть через зміну позиції bottom
			dek->bottom++;
		} else {
			error103;
			err = 1;
		}
		break;
	}
	return dek;
}

#define sh ShowDek(dek);_getch();

void ShowDek(Dek* dek) {
	int i;
	for (i = dek->bottom; i < dek->top; i++) {
		printf_s(" %d", dek->nums[i]);
	}
	printf_s("\n");
}
*/

typedef struct {
	int number;
	int *previus;
} Item;

typedef struct {
	Item *first; /*Первый елемент*/
	int count; /*Размер*/
} Descr;



int menu_mode;
Descr* createitem(int, Descr*);
int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	


	/*
	int num;
	Descr *dese;
	dese = (Descr*)malloc(sizeof(Descr));
	while (1) {
		say("Введите число: ");
		if (scanf_s("%d", &num)) {
			dese = createitem(num, dese);
		} else {
			error;
		}
		printf_s("%d", dese->count);
	}
	*/
	_getch();
    return 0;
}

Descr* createitem(int number, Descr *des) {
	Item* item = (Item*)malloc(sizeof(Item));
	item->previus = des->first;
	item->number = number;

	des->first = item;
	des->count++;
	return des;
}


/*
Menu *CMenu(Menu *menu, int slots) {
	menu = (Menu*)malloc(sizeof(Menu));
	menu->binds = (Binds*)malloc(sizeof(Binds) * slots);
	menu->properties.dbreak = *(Binds*)malloc(sizeof(Binds) * slots);
	menu->text = (Word*)malloc(sizeof(Word) * slots);
	menu->pointers = (int*)malloc(sizeof(int) * slots);
	menu->properties.dbreak.binds = NULL;
	menu->slots = 0;
	return menu;
}

void SmartChoose(Menu *menu) {
	char i;
	int d = 0, j, g;
	Point p, p1;
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	do {
		//cls;
		cls(hStdout);
		//Выщетка позиций окантовки
		p.x = menu->properties.size.width;
		p.y = menu->properties.size.height;
		p1.x = menu->properties.coords.x - 2;
		p1.y = menu->properties.coords.y - 2;
		CrateBorder(&p, &p1);
		//Выщетка позиции заголовка
		p.x = p.x / 2 - strlen(menu->properties.header) / 2 + menu->properties.coords.x - 2;
		p.y = menu->properties.coords.y - 1;
		Say(menu->properties.header, &p);
		//Визуализуем пункты
		for (j = 0; j < menu->slots; j++) {
			p.x = 0 + menu->properties.coords.x;
			p.y = 1 + j * (menu->properties.height + 3) + menu->properties.coords.y;
			MassageBox(menu->text[j].str, menu->properties.height, &p);
		}
		//-----------------
		i = _getch();
		i = toupper(i);
		//Провиряем Bind каждего пункта
		if (menu->slots > 0) {
			for (j = 0; j < menu->slots; j++) {
				if (menu->binds[j].binds != NULL) {
					for (g = 0; g < menu->binds[j].count; g++) {
						if (menu->binds[j].binds[g] == i && menu->binds[j].binds[j] != NULL) {
							cls(hStdout);
							void(*does)() = (void*)menu->pointers[j];
							if (*does != NULL) {
								does();
							}
						}
					}
				}
			}
		}
		//Проверка на перерывание если таковое имееться
		if (menu->properties.dbreak.binds != NULL) {
			for (j = 0; j < menu->properties.dbreak.count; j++) {
				if (i == menu->properties.dbreak.binds[j]) {
					d = 1;
				}
			}
		}
	} while (d == 0);
}

void Say(char* string, Point* p) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	for (int i = 0; i < strlen(string); i++) {
		Coord.X = i + p->x;
		Coord.Y = p->y;
		SetConsoleCursorPosition(consoleoutput, Coord);
		printf_s("%c",string[i]);
	}
}

void CrateBorder(Point* p, Point* p1) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	for (int i = 0; i < p->y; i++) {
		for (int j = 0; j <= p->x; j++) {
			Coord.X = j + p1->x;
			Coord.Y = i + p1->y;
			SetConsoleCursorPosition(consoleoutput, Coord);
			if (j == p->x && i == p->y - 1) {
				printf_s("/");
			}
			if (j == 0 && i == p->y - 1) {
				printf_s("‰");
			}
			if (j == 0 && i == 0) {
				printf_s("г");
			}
			if (j == p->x && i == 0) {
				printf_s("¬");
			}
			if (j == 0 || j == p->x && i != 0 && i != p->y - 1) {
				printf_s("|");
			}
			if ((i == 0 || i == p->y - 1) && j != p->x) {
				printf_s("-");
			}
		}
	}
}

void MassageBox(char* string,int sl, Point* p) {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	int er = 1;
	for (int i = 0; i < sl + 3; i++) {
		for (int j = 0; j <= strlen(string) + 1; j++) {
			Coord.X = j + p->x;
			Coord.Y = i + p->y;
			SetConsoleCursorPosition(consoleoutput, Coord);
			if (j == strlen(string) + 1 && i == sl + 2) {
				printf_s("/");
			}
			if (j == 0 && i == sl + 2) {
				printf_s("‰"); 
			}
			if (j == 0 && i == 0) {
				printf_s("г"); 
			}
			if (j == strlen(string) + 1 && i == 0) {
				printf_s("¬");
			}
			if (j == 0 || j == strlen(string) + 1 && i != 0 && i != sl + 2) {
				printf_s("|");
			} else {
				er = 0;
			}
			if ((i == 0 || i == sl + 2) && j != strlen(string) + 1) {
				printf_s("-");
			}
			else {
				er = 0;
			}
			if (er == 0 && i == (sl + 3) / 2) {
				printf_s("%c",string[j-1]);
			}
		}
	}
}

void sap1() {
	printf_s("Сап двач!\n");
}

void sap() {
	printf_s("КЕК!!!\n");
}

char *ReadText(char *str) {
	if (scanf_s("%s", &str, sizeof(str))) {
		return str;
	}
	else {
		error;
	}
}

int *_arrgen(int max, int nmax) {
	int *arre = (int*)(malloc(max * sizeof(int)));// 249999 максимум
	for (int i = 0; i < max; i++) {
		*(arre + i) = rand() % nmax + 1;
	}
	return arre;
}

int _arrcopy(int *arr, int max) {
	idd = (int*)(malloc(max * sizeof(int)));
	for (int j = 0; j < max; j++) {
		*(idd + j) = *(arr + j);
	}
	return idd;
}

void printfer(int *dee,int max) {
	printf_s("arrayer = {");
	for (int i = 0; i < max; i++) {
		printf_s("%d,", *(dee + i));
	}
	printf_s("}\n");
}

void kek() {
	int * ar = arrs;
	*(ar) = 0;
	*(ar + 1) = 0;
}

void keker() {
	int * ar = arrs;
	*(ar + 2) = 1;
	*(ar + 3) = 1;
}
*/

/*
Dek *dek = CreateDek(2);
PutInDek(dek, 5, Top);
PutInDek(dek, 1, Top);
PutInDek(dek, 6, Top);
PutInDek(dek, 7, Top);
PutInDek(dek, 8, Top);
PutInDek(dek, 2, Down);
PutInDek(dek, 12, Down);
sh;
PopDek(dek,Down);
sh;
PutInDek(dek, 44, Down);
PutInDek(dek, 13, Down);
sh;
PutInDek(dek, 42, Top);
sh;
PopDek(dek, Top);
PopDek(dek, Top);
sh;
PutInDek(dek, 6, Top);
sh;*/

/*
int x, *ara = NULL;
printf_s("Введите границы массивов через пробел: ");
scanf_s("%d", &x);
ara = (int)malloc(x * sizeof(int));
for (int i = 0; i < x; i++) {
printf_s("[%d] = ", i);
scanf_s("%d", (ara + i));
}
printf_s("%d\n", arr_size(ara));
*/
/*
kek();
*/

/*
int arr_max;
printf_s("Выберите размер массива: ");
scanf_s("%d", &arr_max);
arrs = (int*)(malloc(arr_max * sizeof(int)));
for (int i = 0; i < arr_max; i++) {
*(arrs + i) = rand() % arr_max + 1;
}
kek();
printfer();
keker();
printfer();
*/

/*
int arr_max;
printf_s("Выберите размер массива: ");
scanf_s("%d", &arr_max);

arrs = arrgen(arr_max,arr_max);

printfer(arrs,arr_max);



idd = arrcopy(arrs,arr_max);
*/

/*
idd = (int*)(malloc(arr_max * sizeof(int)));
for (int j = 0; j < arr_max; j++) {
*(idd + j) = *(arrs + j);
}
*/
/*
printfer(idd,arr_max);
*/
/*
de = arrgen(10, 10);
printfer(de, 10);
ke = (int*)(malloc(10 * sizeof(int)));
memcpy(ke, de, sizeof(int) * 10);
*(de + 1) = 0;
*(de) = 0;
printfer(ke, 10);
*/


/*
int i, he = 0, j, all = 0, size = 200, ce = 0;
char *src, *word;
Word *words;
src = (char*)malloc(sizeof(char) * size);
words = (Word*)malloc(sizeof(Word) * size);
gets(src);
printf_s("0123456789\n");
for (i = 0; i < size; i++) {
if (*(src + i) == ' ') {
he = 0;
(words + all)->end = i - 1;
for (j = (i - 1); j > 0 && he == 0; j--) {
if (*(src + j) == ' ') {
(words + all)->start = j + 1;
printf_s("faund word %d\n");
all++;
he = 1;
}
}
}
}

for (int de = 0; de < size; de++) {
if ((words + de)->start > 0) {
word = (char*)malloc(sizeof(char) * ((words + de)->end - (words + de)->start));
ce = 0;
for (i = (words + de)->start; i <= (words + de)->end; i++){
*(word + ce) = *(src + i);
ce++;
}
printf_s("слово %s starts %d and ends in %d\n", word,(words+de)->start,(words+de)->end);
}
}
*/

/*
char seps[] = " ";
int size = 200, i = 0, j;
char *str,*token, *nun;
Word *words;
words = (Word*)malloc(size / 2 * sizeof(Word));
str = (char*)malloc(size * sizeof(char));
gets(str);
token = strtok_s(str, seps, &nun);
while (token != NULL)
{
(words + i)->str = token;
(words + i)->lengh = strlen(token);
token = strtok_s(NULL, seps, &nun);
i++;
}

int cho;
scanf_s("%d",&cho);
if (cho <= i && i > 0) {
puts((words + cho - 1)->str);
} else { error; }
*/

/*
do {
i = _getch();
i = toupper(i);
switch (menu_mode) {
case 0:
string = "Программное меню:";
p.x = 10;
p.y = 5;
MassageBox(string, 2, &p);
string = "X)Стек";
p.x = 15;
p.y = 10;
MassageBox(string, 2, &p); pause;
break;
case 1:
string = "Программное меню:";
p.x = 10;
p.y = 5;
MassageBox(string, 2, &p);
string = "X)Стек";
p.x = 15;
p.y = 10;
MassageBox(string, 2, &p);
string = "X)Создать";
p.x = 19;
p.y = 12;
MassageBox(string, 2, &p);
string = "C)Покекать";
p.x = 19;
p.y = 17;
MassageBox(string, 2, &p); pause;
break;
}
switch (i) {
case 'Ч':
case 'X':
switch (menu_mode) {
case 0:
menu_mode = 1;
break;
case 1:

break;
}
cls;
break;
case 'С':
case 'C':
switch (menu_mode) {
case 0:

break;
case 1:

break;
}
cls;
break;
case 'V':
case 'М':
cls;
break;
default:

break;
}
} while (i != 'C' || i != 'X' || i != 'С' || i != 'Ч');
*/

/*
p.x = 118;
p.y = 30;
p1.x = 0;
p1.y = 0;
CrateBorder(&p,&p1);
string = "Программа Визуализации)";
p.x = 2;
p.y = 3;
MassageBox(string, 2, &p);
string = "Создала блудная псина";
p.x = 28;
p.y = 3;
MassageBox(string, 2, &p);
p.x = 50;
p.y = 7;
p1.x = 1;
p1.y = 2;
CrateBorder(&p, &p1);
string = "Супер кек";
p.x = 22;
p.y = 1;
Say(string, &p);
string = "Менюшечка:";
p.x = 10;
p.y = 12;
MassageBox(string, 2,&p);
string = "Покушать";
p.x = 16;
p.y = 14;
MassageBox(string, 2, &p);
string = "Покекать";
p.x = 22;
p.y = 16;
MassageBox(string, 2, &p);
*/
/*
int *arr, slots = 3;
Menu *menu = NULL;
Point start;

menu = CMenu(menu,slots);
menu->slots = 0;

menu->text[menu->slots].str = "D)Покекать";
menu->binds[menu->slots].binds = "DВ";
menu->binds[menu->slots].count = 2;
menu->pointers[menu->slots] = &sap;
menu->slots++;

menu->text[menu->slots].str = "F)Сап двач";
menu->binds[menu->slots].binds = "FА";
menu->binds[menu->slots].count = 2;
menu->pointers[menu->slots] = &sap1;
menu->slots++;

menu->properties.header = "Меню программы:";
menu->properties.height = 0;
menu->properties.coords.x = 7;
menu->properties.coords.y = 4;
menu->properties.size.height = 19;
menu->properties.size.width = 30;

SmartChoose(menu);
*/


/*
//Swap 1
__asm {
mov eax, i
mov edx, j
mov i, edx
mov j, eax
}
*/
/*
//Swap 2
__asm{
mov eax, i
push eax
mov eax, j
mov i, eax
pop eax
mov j, eax
}
*/
/*
//Вызов сохронённых функций
__asm {
mov eax, sap
push eax
mov eax, sap1
push eax
mov eax, i
pop eax
call eax
pop eax
call eax
}
*/

// Lab_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"

#define pause _pause()
#define cls _cls()
#define arr_size(arr)  (sizeof arr / sizeof arr[0])

void _cls() {
	system("cls");
}

void _pause() {
	system("pause");
}

int perim(int x, int y) {
	int num = (x + y) * 2;
	return num;
}

void again();
void start();
void l_start(int);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	start();
    return 0;
}

static int my_array[] = { 0,1,2,3,4,5,6,7,8,9,0,11 };

void l_start(int w) {
	if (w < arr_size(my_array)) {
		printf("%d", my_array[w]);
		w++;
		l_start(w);
	}
	else {
		printf("\n");
		pause;
	}
}

void choose() {
	int i,x,y,num;
	scanf_s("%d", &i);
	switch (i) {
	case 1:
		cls;
		printf_s("Введите сторону a: ");
		scanf_s("%d", &x);
		cls;
		printf_s("Введите сторону y: ");
		scanf_s("%d", &y);
		cls;
		num = perim(x,y);
		printf_s("Периметер прямоугольника (%d,%d) есть: %d \n",x,y,num);
		pause;
		break;
	case 2:
		cls;
		l_start(0);
		break;
	default:
		again();
		break;
	}
}

void start() {
	printf("Select lab:\n1)Переметер прямокутника\n2)Рекурсивный массив\n");
	choose();
}


void again() {
	cls;
	start();
}


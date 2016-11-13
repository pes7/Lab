// Lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"

#define pause "pause"
#define cls "cls"

#define AB x86
#if AB == x86
#define Wh 0
#elif AB == x64
#define Wh 1
#else
#define Wh 2
#endif

int a_plus_b(int a, int b) {
	int num = a + b;
	return num;
}

int a_minor_b(int a, int b) {
	int num = a - b;
	return num;
}

int a_b(int a, int b) {
	int num = a*b;
	return num;
}

void again();
void start();

int main()
{
	setlocale(LC_ALL, "RUS");
	start();
    return 0;
}

void choose() {
	int i,a,b;
	scanf_s("%d", &i);
	switch (i) {
	case 1:
		system(cls);
		printf("Введите a и b:\n");
		scanf_s("%d", &a);
		scanf_s("%d", &b);
		system(cls);
		printf_s("Вы ввели %d и %d\n", a,b);
		system(pause);
		break;
	case 2:
		system(cls);
		printf("Введите a и b:\n");
		scanf_s("%d", &a);
		scanf_s("%d", &b);
		system(cls);
		switch (Wh)
		{
		case 0:
			printf_s("Result: %d \n", a_plus_b(a, b));
			break;
		case 1:
			printf_s("Result: %d \n", a_minor_b(a, b));
			break;
		case 2:
			printf_s("Result: %d \n", a_b(a, b));
			break;
		default:
			printf_s("Unknown Error");
			break;
		}
		system(pause);
	}
}

void start() {
	printf("Select lab:\n1)prinf and scanf\n2)Pre Processor\n");
	choose();
}


void again() {
	system(cls);
	start();
}

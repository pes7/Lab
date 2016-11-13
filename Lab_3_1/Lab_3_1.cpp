// Lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"
#include <conio.h>

#define pause "pause"
#define cls "cls"

void if_num(int x) {
	if (x >= -3 && x <= 0) {
		system(cls);
		printf_s("Число в диапазоне от -3 к 0\n");
	}else if (x >= 3 && x <= 6) {
		system(cls);
		printf_s("Число в диапазоне от 3 к 6\n");
	}
	else {
		system(cls);
		printf_s("Число как и не в диапазоне (-3;0) не (3;6)\n");
	}
}

void switch_registr(int x) {
	system(cls);
	switch (x) {
	case 12:
	case 1:
	case 2:
		printf_s("У нас: Зима\n");
		break;
	case 3:
	case 4:
	case 5:
		printf_s("У нас: Весна\n");
		break;
	case 6:
	case 7:
	case 8:
		printf_s("У нас: Лето\n");
		break;
	case 9:
	case 10:
	case 11:
		printf_s("У нас: Осень\n");
		break;
	default:
		printf_s("Ваше число вне диапазона\n");
		break;
	}
}

void again();
void start();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	start();
	return 0;
}

void choose() {
	int  k, x;
	char i;
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
		case 'X':
			system(cls);
			printf_s("Впишите число: ");
			scanf_s("%d", &k);
			if_num(k);
			system(pause);
			break;
		case 'C':
			system(cls);
			printf_s("Введите число месяца(1-12): ");
			scanf_s("%d", &x);
			switch_registr(x);
			system(pause);
			break;
		default:
			again();
			break;
		}
	} while (i != 'C' || i != 'X');
}

void start() {
	printf("Выберите работу:\nX)Задание if\nC)Задание switch\n");
	choose();
}


void again() {
	system(cls);
	start();
}

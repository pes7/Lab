// Lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"

#define pause "pause"
#define cls "cls"

void if_num(int x) {
	if (x >= -2 && x <= 2) {
		system(cls);
		printf_s("Num in range from -2 to 2\n");
	}
	else {
		system(cls);
		printf_s("Num out of range(-2,2)\n");
	}
}

void switch_registr(char x) {
	char new_charer;
	switch (x) {
		case 'A':
			new_charer = 'a';
		break;
		case 'B':
			new_charer = 'b';
			break;
		case 'C':
			new_charer = 'c';
			break;
		case 'D':
			new_charer = 'd';
			break;
		case 'E':
			new_charer = 'e';
			break;
		case 'F':
			new_charer = 'f';
			break;
		default:
			new_charer = 'N';
			break;
	}
	system(cls);
	printf_s("Your char %c now %c",x,new_charer);
}

void again();
void start();
void again();

int main()
{
	setlocale(LC_ALL, "RUS");
	start();
    return 0;
}

void choose() {
	int i,k;
	char x;
	scanf_s("%d", &i);
	switch (i) {
	case 1:
		system(cls);
		printf_s("Please put any number\n");
		scanf_s("%d",&k);
		if_num(k);
		system(pause);
		break;
	case 2:
		system(cls);
		printf_s("Please put any char\n");
		scanf("%c", &x);
		switch_registr(x);
		system(pause);
		break;
	default:
		again();
		break;
	}
}

void start() {
	printf("Select lab:\n1)Task If\n2)Task switch\n");
	choose();
}


void again() {
	system(cls);
	start();
}

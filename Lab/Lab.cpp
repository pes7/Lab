// Lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"	
#include "Math.h"
#include "locale.h"
#include "string.h"

#define pause _pause()
#define cls _cls()


int gloc_int(int x,double y) {
	int num = (int)pow(x*y, 0.5);
	return(num);
}

double gloc_double(int x, double y) {
	double num = pow(x*y, 0.5);
	return(num);
}

double func(double x) {
	double num = (pow(x, 2) - (7 * x) + 10) / (pow(x, 2) - (8 * x) + 12);
	return num;
}

void _pause() {
	system("pause");
}

void _cls() {
	system("cls");
}

void again();
void start();

int main()
{
	setlocale(LC_ALL,"RUS");
	start();
    return 0;
}

void choose() {
	int i;
	scanf_s("%d", &i);
	switch (i) {
	case 1:
		cls;
		printf("First(int): %d \n", gloc_int(10, 20));
		printf("First(double): %f \n", gloc_double(10, 20));
		pause;
		break;
	case 2:
		cls;
		printf("Function returned(double): %d \n", func(10));
		pause;
		break;
	default:
		again();
		break;
	}
}

void start() {
	printf("Select lab:\n1)Middel geomentr of two nums\n2)Function\n");
	choose();
}


void again() {
	cls;
	start();
}


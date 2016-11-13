// Lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"
#include "conio.h"

#define pause _pause()
#define cls _cls()
#define arr_size(arr)  (sizeof arr / sizeof arr[0])
#define lab_sel "Выбрать лаб роботу"

void _cls() {
	system("cls");
}

void _pause() {
	system("pause");
}

void booble() {//Пузырьковый метод
	int arrayer[50000];// 249999 максимум
	for (int i = 0; i < arr_size(arrayer); i++) {
		arrayer[i] = rand() % 500 + 1;//цифры от 0 до 1000
	}
	int j = 0, x, y, u = 0;
	int ee = 2;
	while(ee == 2) {
		if (j < arr_size(arrayer) - 1) {
			if (arrayer[j] > arrayer[j + 1]) {
				x = arrayer[j];
				y = arrayer[j + 1];
				arrayer[j + 1] = x;
				arrayer[j] = y;
				u = 0;
				j++;
			}
			else {
				u++;
				if (u == arr_size(arrayer)) {
					ee = 1;
				}
				j++;
			}
		}
		else {
			j = 0;
		}
	}
	pause;
}

void go_array() {
	int x, z, *ara = NULL;
	printf_s("Введите границы массивов через пробел: ");
	scanf_s("%d %d",&x,&z);
	ara = (int*)malloc(x*z*sizeof(int));
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < z; j++) {
			printf_s("[%d][%d] = ", i,j );
			scanf_s("%d", (ara + i * z + j));
		}
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < z; j++) {
			if (j == 0) {
				printf_s("|%d,", *(ara + i*z + j));
			} else if (j == z - 1) {
				printf_s("%d|\n", *(ara + i*z + j));
			}
			else {
				printf_s("%d,", *(ara + i*z + j));
			}
		}
	}
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
	char i;
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
		case 'C':
			cls;
			go_array();
			pause;
			break;
		case 'X':
			cls;
			booble();
			pause;
			break;
		default:
			again();
			break;
		}
	} while (i != 'C'|| i != 'X');
}

void start() {
	printf("%s : \nC)Метод пузырька и двухмерный массив\nX)Сортировка пузырком", lab_sel);
	choose();
}


void again() {
	cls;
	start();
}

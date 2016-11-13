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

int factorial(int x) {
	int num = 1;
	for (int i = 1; i <= x; i++) {
		num = num * i;
	}
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
	int  x, nums[4], min;
	char i;
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
		case 'X':
			cls;
			printf_s("Введите число: ");
			scanf_s("%d", &x);
				if (x < 0 || x > 23) {
					printf_s("Введено недопустимое значение\n");
					rewind(stdin);
					return;
				}
				else {
					printf_s("Факториал %d есть %d\n", x, factorial(x));
				}	
			break;
		case 'C':
			cls;
			printf_s("Введите числа через пробел: ");
			scanf_s("%d %d %d %d %d",&nums[0], &nums[1], &nums[2], &nums[3], &nums[4]);
			for (int te = 0; te < arr_size(nums); te++) {
				if (nums[te] < -800000000) {
					printf_s("Введено недопустимое значение\n");
					rewind(stdin);
					return;
				}
			}
			int i = 0;
			do {
				if (i == 0) {
					min = nums[i];
				}
				if (nums[i] < min) {
					min = nums[i];
				}
				i++;
			} while (i <= arr_size(nums));
			printf_s("Минимальное число: %d\n", min);
			break;
		default:
			again();
			break;
		}
	} while (i != 'C' || i != 'X');
}

void start() {
	printf("%s : \nX)Факториал числа\nC)Выбор минимального числа методом перебора for", lab_sel);
	choose();
}


void again() {
	cls;
	start();
}

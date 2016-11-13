// Lab_7_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"

#define cls _cls()
#define error _error()
#define say(text) _say(text);

void _say(char *text) {
	printf_s(text);
}

void _cls() {
	system("cls");
}

void _error() {
	printf_s("Ошибка ввода!\n");
	rewind(stdin);
}

int *CrateArray(int, int);
int *SortArray(int*,int, int);
int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 70");

	int *arr, n, m, i, j;
	start:
	/*Задаём границы*/
	cls;
	say("Введите граници массива min(2x2): \n");
	err1:
	say("n = ");
	if (!scanf_s("%d", &n) || n < 2) {
		error;
		goto err1;
	}
	err2:
	say("m = ");
	if (!scanf_s("%d", &m) || m < 2) {
		error;
		goto err2;
	}
	/*--------------*/
	cls;
	/*Создаём массив*/
	arr = CrateArray(n, m);
	say("Отсортированый массив: \n");
	/*Отсортируем массив*/
	arr = SortArray(arr,n,m);
	say("arr = |");
	/*Выводим массив*/
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf_s(" %d", *(arr + i * m + j));
		}
		if (i != n - 1) {
			say(" |\n      |");
		}
		else {
			say(" |");
		}
	}
	_getch();
	say("\n");
	goto start;
    return 0;
}

/*Сортировка пузырьком*/
int *SortArray(int  *arr, int n, int m) {
	int u = 0, i, j, last, ee = 1;
	while (ee) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < m - 1; j++) {
				if (*(arr + i * m + j) > *(arr + i * m + j + 1)) {
					last = *(arr + i * m + j);
					*(arr + i * m + j) = *(arr + i * m + j + 1);
					*(arr + i * m + j + 1) = last;
					u = 0;
				} else {
					u++;
				}
				if (u >= n*m) {
					ee = 0;
				}
			}
		}
		if (i == n - 1) {
			i = 0;
			j = 0;
		}
	}
	return arr;
}

/*Создание массива*/
int *CrateArray(int n, int m) {
	int **arr, i, j;
	arr = (int**)malloc(sizeof(int) * n * m);
	say("Заполните массив: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			de:
			printf_s("arr[%d][%d] = ",i,j);
			if (scanf_s("%d", (arr + i * m + j))) {
				if (!Check(n,m,arr,i,j)) {
					say("\nВы ввели повторяющийся елемент!\n");
					goto de;
				}
			} else {
				error;
				goto de;
			}
		}
		say("\n");
	}
	return arr;
}

/*Проверка на совпадение елементов в строке*/
int Check(int n, int m, int *arr, int cur_i, int cur_j) {
	int j, err = 1;
	for (j = 0; j < n; j++) {
		if (*(arr + cur_i * m + cur_j) == *(arr + j * m + cur_j) && j != cur_i) {
			err = 0;
		}
	}
	return err;
}

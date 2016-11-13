// Sort.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "stdio.h"
#include "locale.h"
#include "Windows.h"
#include <time.h>

#define pause _pause()
#define cls _cls()
#define error _error()
#define arr_size(arr)  (sizeof arr / sizeof arr[0])
#define arrcopy(arr,maxer) _arrcopy(arr,maxer)
#define arrgen(maxe,nmax) _arrgen(maxe,nmax)
#define prarr(dee,maxe) _printfer(dee,maxe)
#define gt() _gettime()

clock_t t;
int _gettime() {
	t = clock();
	return t;
}

int _arrgen(int max, int nmax) {
	int *arre = (int*)(malloc(max * sizeof(int)));// 249999 максимум
	for (int i = 0; i < max; i++) {
		*(arre + i) = rand() % nmax + 1;
	}
	return arre;
}

int _arrcopy(int *arr, int max) {
	int *arre = (int*)(malloc(max * sizeof(int)));
	for (int j = 0; j < max; j++) {
		*(arre + j) = *(arr + j);
	}
	return arre;
}


void _printfer(int *dee, int max) {
	printf_s("arrayer = {");
	for (int i = 0; i < max; i++) {
		printf_s("%d,", *(dee + i));
	}
	printf_s("}\n");
}

void _cls() {
	system("cls");
}

void _pause() {
	system("pause");
}

void _error() {
	printf_s("Ошибка ввода!");
	rewind(stdin);
}

void again();
void start();
void booble();
void shacer(int*,int);
void shella(int*,int);
void counte(int*,int);
int create_array();
void speed_test();
void shell_speed();
void shacke_speed();
void count_speed();

int Gmode = 0;
int* arrs;
int arr_max = 0;
int menu_ix = 0;
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	start();
	return 0;
}

int create_array() { /*Отводим место для учебного единого массива*/
	printf_s("Выберите размер массива: ");
	if (scanf_s("%d", &arr_max)) {
		if (arr_max > 1) {
			arrs = arrgen(arr_max, arr_max);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void choose(int mode) {
	char i;
	if (mode == 1) {
		printf_s("Выберите вид сортировки: \nX)Шейкерная \nC)Шелла\nV)Подсчётом");
	}
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
		case 'X':
			cls;
			if (mode == 0) {
				Gmode = 0;
				if (create_array()) {
					choose(1);
				}
				else {
					error;
				}
			} else {
				shacer(NULL,NULL);
				free(arrs);
			}
			break;
		case 'C':
			cls;
				if (mode == 0) {
					menu_ix = 1;
					if (menu_ix == 0) {
						Gmode = 0;
							choose(1);
					} else {
						Gmode = 1;
						speed_test();
					}
				} else {
					shella(NULL, NULL);
					free(arrs);
				}
			break;
		case 'V':
			cls;
			if (mode == 0) {
				cls;
				printf_s("Ошибка: не выбран учебный метод");
			} else {
				counte(NULL, NULL);
				free(arrs);
			}
			break;
		default:
			again();
			break;
		}
	} while (i != 'C' || i != 'X' || i != 'V');
}

void speed_test() {
	int *arr, elem;
	if (create_array()) {
		shell_speed();
		shacke_speed();
		count_speed();
	} else {
		error;
	}
}

void shell_speed() {
	double time1, time2;
	time1 = gt();
	shella(arrs,arr_max);
	time2 = gt();
	printf_s("Шелла для елементов %d: %f сек.\n", arr_max, (time2 - time1) / CLOCKS_PER_SEC);
}

void shacke_speed() {
	double time1, time2;
	time1 = gt();
	shacer(arrs,arr_max);
	time2 = gt();
	printf_s("Шейкерная для елементов %d: %f сек.\n",arr_max, (time2 - time1) / CLOCKS_PER_SEC);
}

void count_speed() {
	double time1, time2;
	time1 = gt();
	counte(arrs,arr_max);
	time2 = gt();
	printf_s("Подсчётом для елементов %d: %f сек.\n", arr_max, (time2 - time1) / CLOCKS_PER_SEC);
}

void start() {
	printf("Выбирите главную цель: \nX)Учебно-визуальная \nC)Быстрый режим");
	choose(0);
}


void again() {
	cls;
	start();
}

void shella(int *pointer, int maxer) {
	int temp, //до переменная для обмена ячейками 
		size, //размер массив
		step, //
		*arrayer,
		j,
		i;
	size = arr_max;
	arrayer = arrs;
	step = size / 2;
	if (Gmode) {
		arrayer = arrcopy(pointer, maxer);
		size = maxer;
	}
	else {
		size = arr_max;
		arrayer = arrs;
	}
	if (!Gmode) {
		prarr(arrayer, size);
	}
	while (step > 0)//пока шаг не 0
	{
		for (i = 0; i < (size - step); i++)
		{
			j = i;
			/*	пока не пришли к началу массива
			и пока рассматриваемый элемент больше
			чем элемент находящийся на расстоянии шага */
			while (j >= 0 && *(arrayer + j) > *(arrayer + j + step))
			{
				//меняем их местами
				temp = *(arrayer + j);
				*(arrayer + j) = *(arrayer + j + step);
				*(arrayer + j + step) = temp;
				j--;
				if (!Gmode) {
					prarr(arrayer, size);
				}
			}
		}
		step = step / 2;//уменьшаем шаг
	}
	if (!Gmode) {
		prarr(arrayer, size);
	}
}

void shacer(int *pointer,int maxer) {//Метод шейкера
	int j = 0, x, y, u = 0, mode = 0, size;
	int* arrayer;
	int ee = 2;
	if (Gmode) {
		arrayer = arrcopy(pointer, maxer);
		size = maxer;
	}
	else {
		size = arr_max;
		arrayer = arrs;
	}
	while (ee == 2) {
		if (mode == 0) {
			if (j < size - 1) {
				if (*(arrayer + j) > *(arrayer + j + 1)) {
					x = *(arrayer + j);
					y = *(arrayer + j + 1);
					*(arrayer + j + 1) = x;
					*(arrayer + j) = y;
					u = 0;
					j++;
				}
				else {
					u++;
					if (u == size) {
						ee = 1;
					}
					j++;
				}
			}
			else {
				mode = 1;
			}
		}
		else {
			if (j > 0) {
				if (*(arrayer + j) < *(arrayer + j - 1)) {
					x = *(arrayer + j);
					y = *(arrayer + j - 1);
					*(arrayer + j - 1) = x;
					*(arrayer + j) = y;
					u = 0;
					j--;
				}
				else {
					u++;
					if (u == size) {
						ee = 1;
					}
					j--;
				}
			}
			else {
				mode = 0;
			}
		}

		if (!Gmode) {
			//Блок визуализации, оптималь которого массив с 12 елементов
			printf_s("arrayer = {");
			for (int i = 0; i < size; i++) {
				printf_s("%d,", *(arrayer + i));
			}
			printf_s("}\n");
			//
		}
	}
}

void counte(int *pointer, int maxer) {
	int size, cou_size, d = 0,
		ee = 2, j = 0, x,
		y, u = 0, elem = 0,
		dd, g, i , i_1;
	int *arrayer, *cou, *nums;
	if (Gmode) {
		arrayer = arrcopy(pointer, maxer);
		size = arr_max;
		cou_size = arr_max;
	}
	else {
		size = arr_max;
		arrayer = arrs;
		cou_size = arr_max;
	}

	if (!Gmode) {
		printf_s("arrayer = {");
		for (int i = 0; i < size; i++) {
			printf_s("%d,", *(arrayer + i));
		}
		printf_s("}\n");
	}

	cou = (int*)(malloc(size * sizeof(int)));
	nums = (int*)(malloc(size * sizeof(int)));
	/*
	cou - массив с таким же числом етементов как и максимальное значение
	в массиве arrayer
	*/
	for (int i = 0; i < cou_size; i++) {//Набиваем нолями масcив nums
		*(nums + i) = 0;
	}
	for (int j = 0; j < size; j++) {//Проверяем массив arrayer
		dd = 0;
		for (g = 0; g < cou_size; g++) {
			if (*(cou+g) == *(arrayer+j)) {// Ишем такие же числа как в елементе массива cou, 
				dd = 1;
			}
		}
		if (dd == 0) {
			*(cou+d) = *(arrayer+j);
			d++;
		}
	}
	while (ee == 2) {
		if (j < cou_size - 1) {
			if (*(cou + j) > *(cou + j + 1)) {
				x = *(cou+j);
				y = *(cou + j + 1);
				*(cou + j + 1) = x;
				*(cou + j) = y;
				u = 0;
				j++;
			} else {
				u++;
				if (u == cou_size) {
					ee = 1;
				}
				j++;
			}
		}
		else {
			j = 0;
		}
	}
	for (int i = 0; i < size; i++) {
		for ( j = 0; j < cou_size; j++) {
			if (*(cou+j) == *(arrayer+i)) {
				(*(nums+j))++;
			}
		}
	}
	for (int j_1 = 0; j_1 < cou_size; j_1++) {
		for ( i_1 = 0; i_1 < *(nums+j_1); i_1++) {
			*(arrayer+elem) = *(cou+j_1);
			elem++;
		}
	}

	if (!Gmode) {
		printf_s("arrayer = {");
		for ( i = 0; i < size; i++) {
			printf_s("%d,", *(arrayer + i));
		}
		printf_s("}\n");
	}
}
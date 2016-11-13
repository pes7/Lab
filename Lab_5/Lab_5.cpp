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

void _cls() { /*Очистить екран*/
	system("cls");
}

void _pause() { /*Пауза*/
	system("pause");
}


void again();
void start();
void get_chars();
void pidrahunok_aref();

int main()
{
	setlocale(LC_ALL, "RUS");
	start();
	return 0;
}

void choose() { /*Выбор лабараторной работы*/
	char i;
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
		case 'X':
			cls;
			get_chars();
			pause;
			break;
		case 'C':
			cls;
			pidrahunok_aref();
			pause;
			break;
		default:
			again();
			break;
		}
	} while (i != 'C' || i != 'X');
}

void pidrahunok_aref() { /*Функция подсчёта среднего арефмитического столбцов массива*/
	int i = 0, /*Счётчик второго порядка массива*/
		j = 0, /*Счётчик первого порядка массива*/
		co = 0 /*Общий счётчик количества елемантов*/;
	int x, z, *arr = NULL;
	printf_s("Введите границы массива через пробел: ");
	scanf_s("%d %d", &x, &z);
	if (x > 0) {
		arr = (int*)malloc(x*z * sizeof(int));
		do { /*Осуществляем ввод в массив*/
			if (i == x) {
				i = 0;
				j++;
			}
			printf_s("arr[%d][%d] = ", j, i);
			if (!scanf_s("%d", (arr + i * z + j))) { /*Проверка на ошибку ввода*/
				printf_s("Ошибка ввода\n");
				rewind(stdin);
				return;
			}
			i++;
			co++;
		} while (co < x * z);
		for (i = 0; i < x; i++) { /*Подсчёт среднего арефмитического столбцов*/
			co = 0;
			for (j = 0; j < z; j++) {
				co = co + *(arr + i * z + j);
			}
			co = co / x;
			printf_s("Средние Арифметическое %d-го столбика: %d\n", i, co);
		}
	}else {
		printf_s("Введена недопустимая граница массива\n");
	}
}

void get_chars() { /*Функция проверки на одинаковый елемент массива*/
	int i = 0; /*Количество цыклов записи*/
	int x; /* Количестово елементов */
	int *arr = NULL; /* Генирируем пустой указатель */
	int err = 0; /*Переменная отвичающая за результат*/
	printf_s("Введите границы массива: ");
	scanf_s("%d", &x);
	if (x > 0) {
		arr = malloc(x * sizeof(int));
		do {  /*Вводим массив*/
			printf_s("%d-ое число: ", i + 1);
			if (!scanf_s("%d", &arr[i])) { /*Проверка на ошибку ввода*/
				printf_s("Ошибка ввода\n");
				rewind(stdin);
				return;
			}
			i++;
		} while (i < x);

		for (int i = 0; i < x; i++) { /*Проверяем на совпадение*/
			for (int j = 0; j < x; j++) {
				if (arr[i] == arr[j] && i != j) {
					err = 1;
				}
			}
		}
		if (err == 1) { /*Вывод результата*/
			printf_s("В массиве есть одинаковые элеманты\n");
		}
		else {
			printf_s("В массиве нету одинаковых элементов\n");
		}
	}else {
		printf_s("Введена недопустимая граница массива\n");
	}
}

void start() { /*Запуск выбора лабараторных работ*/
	printf("%s : \nX)Провера массива на одинаковые елементы\nC)Средние арифметическое столбцов метрицы n елементов", lab_sel);
	choose();
}


void again() {
	cls;
	start();
}

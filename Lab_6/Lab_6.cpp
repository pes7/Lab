#include "stdafx.h"
#include "stdio.h"
#include "locale.h"
#include "Windows.h"
#include <time.h>

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
	printf_s("Ошибка ввода!");
	rewind(stdin); 
}

/*Структура слова*/
typedef struct {
	char *str;
	int *lengh;
} Word;

void start();
void again();
void UpPoint();
void GetWord();
Word *chack(Word *arr);

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	start();
	return 0;
}

void UpPoint() {
	int i, /*Счётчик для цикла*/
		size = 150; /*Размер строки*/
	char *src, *estr;
	src = (char*)malloc(sizeof(char) * size);
	say("Введите строку с точками: ");
	estr = fgets(src, size, stdin);
	if (estr != NULL)
	{
		/*Подносим к верхниму регистру
		следующий симвот после точки*/
		for (i = 0; i <= size; i++) {
			if (*(src + i) == '.') {
				*(src + i + 1) = toupper(*(src + i + 1));
			}
		}
		/*Выводим новую строку*/
		if (strlen(src) != 0) {
			say("\nВыходная строка: ");
			puts(src);
			say("Нажмите любую клавишу...");
		}
		else {
			say("Вы ввели пустую строку");
		}
	}
}

void GetWord() {
	char seps[] = " "; /*Разделитель*/
	int size = 151, /*Размер строки*/
		h = 0, /*Счётчик слов*/
		i, /*Счётчик цикла*/
		cho; /*Номер выбраного слова*/
	char *str, /*Указатель вводиму строку*/
		*token, /*Раздилённое слово*/
		*nun, /*Пустой указатель для функции*/
		*estr;
	Word *words; /*Указатель на массив структур Word*/
	/*Выдиляем память под массивы*/
	words = (Word*)malloc(size / 2 * sizeof(Word)); 
	str = (char*)malloc(size * sizeof(char));
	
	say("Введите строку: ");
	estr = fgets(str,size, stdin);
	if (estr != NULL)
	{
		/*Проверка на пустоту*/
		if (strlen(str) != 0) {
			/*Делим строку разделителём seps*/
			token = strtok_s(str, seps, &nun);
			while (token != NULL)
			{
				(words + h)->str = token;
				(words + h)->lengh = strlen(token);
				token = strtok_s(NULL, seps, &nun);
				h++;
			}

			i = h;
			if (i > 1) { /*Проверка на 1 слово*/
				say("Введите номер слова: ");
				if (scanf_s("%d", &cho)) {
					/*Проверка на коректный ввод*/
					if (cho <= i && i > 0) {
						say("\nВаше слово: ");
						*(words + cho - 1) = *chack(words + cho - 1);
						puts((words + cho - 1)->str);
						say("\nНажмите любую клавишу...");
					}
					else { error; }
				}
				else { error; }
			}
			else {
				printf_s("В стоке всего одно слово: %s", words->str);
			}
		}
		else {
			say("Ошибка. Вы ввели пустую строку");
		}
	}
	rewind(stdin);
}

/*Удаление лишних символов*/
Word *chack(Word *arr) {
	char sec[] = { ',','.',';',':','>','<','-','+','(',')','@','#','$','%','^','&','*','!' };
	int i, j;
	char *fe;
	fe = arr->str;
	for (i = 0; i < arr->lengh; i++) {
		for (j = 0; j < strlen(sec); j++) {
			if (*(fe + i) == *(sec + j) && *(fe + i) != 'ф' && *(fe + i) != 'а' && *(fe + i) != 'с'){
				*(fe + i) = ' ';
			}
		}
	}
	arr->str = fe;
	return arr;
}

/*Выбор елемента меню*/
void choose(int mode) {
	char i;
	do {
		i = _getch();
		i = toupper(i);
		switch (i) {
			case 'Ч':
			case 'X':
				cls;
				UpPoint();
				break;
			case 'С':
			case 'C':
				cls;
				GetWord();
				break;
			default:
				again();
				break;
		}
	} while (i != 'C' || i != 'X' || i != 'С' || i != 'Ч');
}

void start() {
	printf("Выбирите главную цель: \nX)Перевод след. символа после точки в верхний регистр \nC)Вывод слова по номеру");
	choose(0);
}


void again() {
	cls;
	start();
}
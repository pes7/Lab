// Lab_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"

#define say(text) _say(text)
void _say(char *s) {
	printf_s("%s", s);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE *str;
	char *c,k[100];
	/*
	fopen_s(&str, "C:/Users/ukolo/OneDrive/Документы/Visual Studio 2015/Projects/Lab/Debug/str.IN", "r");
	if (str == NULL) {
		puts("Не удалось открыть файл");
	}
	while (fgets(c,100,str) != NULL) {
		printf_s("%s", c);
	}
	*/
	/*
	while (1) {
		fopen_s(&str, "test.txt", "a+");
		fprintf_s(str, "-------------------------------\n");
		say("Введите название отеля: ");
		fgets(k, 98, stdin);
		fprintf_s(str, "[n]%s", &k);
		say("Населённый пункт: ");
		fgets(k, 98, stdin);
		fprintf_s(str, "[l]%s", &k);
		say("Количество номеров: ");
		fgets(k, 98, stdin);
		fprintf_s(str, "[c]%s", &k);
		say("Количество звёзд: ");
		fgets(k, 98, stdin);
		fprintf_s(str, "[z]%s", &k);
		fclose(str);
		say("Запись завершина!\n");
		_getch();
	}
	*/
	int i = 0, j = 0;
	fopen_s(&str, "test.txt", "r");
	if (str == NULL) {
		puts("Не удалось открыть файл");
	}
	while (1) {
		c = fgets(k, sizeof(k),str);
		if (c == NULL) {
			if (feof(k) != 0)
			{
				say("\nЧтение файла закончено\n");
				break;
			} else {
				say("\nОшибка чтения из файла\n");
				break;
			}
		}
		printf("/n%s", str);
	}
	_getch();
	return 0;
}


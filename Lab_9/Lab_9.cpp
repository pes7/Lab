// Lab_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"
#include <malloc.h>

typedef struct {
	char *str;
	int sovpad;
}Word;

int main()
{
	int i, j, count = 0, word_count = 0,max = 0, is_screen = 1, can_read = 1;
	FILE *str, *f, *out;
	char ce[34], k[200], *istr, sepr[] = " ", *nun;
	Word *reiting;

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	reiting = (Word*)malloc(sizeof(Word));
	
	vivod:
	printf_s("Выводить на екран? 0)Нет 1)Да\n");
	if (!scanf_s("%d",&is_screen)) {
		printf_s("Ошибка ввода.");
		rewind(stdin);
		goto vivod;
	}
	system("cls");


	/*
		Переделать:
			1) Ввод букв с клавиатуры
			2) Запуск программы с параметрами с консоли
			3) 
	*/
	if (!fopen_s(&out,"test.out", "w+")) {
		if (!fopen_s(&str, "latters.in", "r")) {
			if (getc(str) != EOF) {
				rewind(str);
				fgets(ce, 200, str);
				fclose(str);
				if (is_screen == 1) {
					printf_s("Буквы: %s\n", ce);
				}
				fprintf_s(out, "Буквы: %s\n", ce);
				if (!fopen_s(&f, "test.in", "r")) {
					if (getc(f) != EOF) {
						rewind(f);
						while (can_read) {
							fgets(k, 200, f);
							if (feof(f) != 0) {
								can_read = 0;
							}
							istr = strtok_s(k, sepr, &nun);
							while (istr != NULL)
							{
								reiting = (Word*)realloc(reiting, sizeof(Word) * (word_count + 1));
								count = 0;
								for (i = 0; i < strlen(istr); i++) {
									for (j = 0; j < strlen(ce); j++) {
										if (istr[i] == ce[j]) {
											count++;
										}
									}
								}		
								reiting[word_count].str = (char*)malloc(sizeof(char) * strlen(istr) + 2);
								strcpy_s(reiting[word_count].str,strlen(istr) + 2, istr);
								reiting[word_count].sovpad = count;
								if (is_screen == 1) {
									printf_s("[%d]%s ", count, istr);
								}
								fprintf_s(out, "[%d]%s ", count, istr);
								istr = strtok_s(NULL, sepr, &nun);
								word_count++;
							}
						}
						fclose(f);
						printf_s("\n");
						
						for (i = 0; i < word_count; i++) {
							//printf_s("%d > %d\n", reiting[i].sovpad, reiting[max].sovpad);
							if (reiting[i].sovpad == reiting[max].sovpad && i != 0) {
								if (is_screen == 1) {
									//printf_s("Было обнаружено слово: {%s} с таким же количеством совпадений, старшое слово {%s} было перезаписано.\n",reiting[i].str,reiting[max]);
								}
								//fprintf_s(out, "Было обнаружено слово: {%s} с таким же количеством совпадений, старшое слово {%s} было перезаписано.\n", reiting[i].str, reiting[max]);
							}
							if (reiting[i].sovpad >= reiting[max].sovpad) {
								max = i;
							}
						}
						if (is_screen == 1) {
							printf_s("Максимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
						}
						fprintf_s(out, "Максимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
						printf_s("Операция произведина.");
					} else {
						printf_s("Ошибка. Файл test.in абсолютно пуст.");
					}
				} else {
					printf_s("Ошибка. Файл test.in не может быть открыт.");
				}
			} else {
				printf_s("Ошибка. Файл latters.in абсолютно пуст.");
			}
		} else {
			printf_s("Ошибка. Файл latters.in не может быть открыт.");
		}
	} else {
		printf_s("Ошибка открытия test.out!");
	}
	fclose(out);
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
	/*
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
	*/
	_getch();
	return 0;
}


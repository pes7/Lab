#include "stdafx.h"

/*Структура содержащая слово и
количество совпадений*/
typedef struct {
	char *str;
	int sovpad;
}Word;

/*Структура которая содержит
имена входного и выходного файла*/
typedef struct {
	char *in;
	char *out;
}NameOfFile;

void StartNormal(int argc, char ** argv) {
	int i, /*Счётчик цикла*/
		j = 0, /*Счётчик цикла*/
		count = 0, /*Количество совпадений*/
		word_count = 0, /*Всего слов в тексте*/
		max = 0, /*Индекс слова с максимальным количеством совпадений*/
		is_screen = 1, /*Выводить ли на екран*/
		can_read = 1, /*Можно ли читать файл дальше*/
		nashloli = 0; /*Нашло ли совпадениее вообще*/
	FILE *f, /*Файл текста*/
		*out; /*Файл вывода*/
	char k[200], /*Слово*/
		*istr, /*Слово*/
		sepr[] = " ", /*Разделитель*/
		*nun, /*Пустой указатель*/
		*chre; /*Букавы для поиска совпадений*/
	Word *reiting, /*Слова с количеством совпадений*/
		*words; /*Слова с одинаковым рейтингом*/
	NameOfFile *NameOfFiles; /*Названия входного и выходного файла*/

	reiting = (Word*)malloc(sizeof(Word));
	chre = (char*)malloc(sizeof(char) * 32);

	NameOfFiles = (NameOfFile*)malloc(sizeof(NameOfFile));
	NameOfFiles->in = (char*)malloc(sizeof(char) * 50);
	NameOfFiles->out = (char*)malloc(sizeof(char) * 55);
	if (argc > 1) {
		strcpy_s(NameOfFiles->in, strlen(argv[1]) * sizeof(char) + 16, argv[1]);
	} else {
		printf_s("Введите название файла с .in: ");
		if (!scanf_s("%s", NameOfFiles->in, 10)) {
			printf_s("Error");
		}
	}
	strcpy_s(NameOfFiles->out, 50, NameOfFiles->in);
	strcat_s(NameOfFiles->out, 55, ".out");
	//NameOfFiles->out = "../CLab9/OUT.out";
	printf_s("%s\n%s\n", NameOfFiles->in, NameOfFiles->out);

vivod:
	printf_s("Выводить на екран? 0)Нет 1)Да\n");
	if (!scanf_s("%d", &is_screen)) {
		printf_s("Ошибка ввода.");
		rewind(stdin);
		goto vivod;
	}

	if (!fopen_s(&out, NameOfFiles->out, "w+")) {
		printf_s("Введите символы: ");
		if (scanf_s("%s", chre, 30)) {
			if (is_screen == 1) {
				printf_s("Буквы: %s\n", chre);
			}
			fprintf_s(out, "Буквы: %s\n", chre);
			if (!fopen_s(&f, NameOfFiles->in, "r")) {
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
							reiting = (Word*)realloc(reiting, sizeof(Word) * (word_count + 3));
							if (reiting != NULL) {
								count = 0;
								for (i = 0; i < strlen(istr); i++) {
									for (j = 0; j < strlen(chre); j++) {
										if (istr[i] == chre[j]) {
											count++;
											nashloli = 1;
										}
									}
								}
								reiting[word_count].str = (char*)malloc(sizeof(istr));
								strcpy_s(reiting[word_count].str, strlen(istr) + 4, istr);
								reiting[word_count].sovpad = count;
								if (is_screen == 1) {
									printf_s("[%d]%s ", count, istr);
								}
								fprintf_s(out, "[%d]%s ", count, istr);
								istr = strtok_s(NULL, sepr, &nun);
								word_count++;
							} else {
								printf_s("Ошибка выдиления памяти");
							}
						}
					}
					fclose(f);
					printf_s("\n");
					words = (Word*)malloc(sizeof(Word)*word_count);
					if (words != NULL) {
						j = 0;
						for (i = 0; i < word_count; i++) {
							if (reiting[i].sovpad >= reiting[max].sovpad) {
								max = i;
							}
						}
						for (i = 0; i < word_count; i++) {
							if (reiting[i].sovpad == reiting[max].sovpad) {
								words[j].sovpad = reiting[i].sovpad;
								words[j].str = (char*)malloc(sizeof(char)*strlen(reiting[i].str) + 16);
								strcpy_s(words[j].str, strlen(reiting[i].str) + 2, reiting[i].str);
								j++;
							}
						}
						if (is_screen == 1) {
							if (nashloli == 1) {
								if (j == 1) {
									printf_s("Максимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
									fprintf_s(out, "\nМаксимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
								} else {
									printf_s("Максимальное количество совпадений в %d словах: ", j);
									fprintf_s(out, "\nМаксимальное количество совпадений в %d словах: ", j);
									for (i = 0; i < j; i++) {
										printf_s("%s,", words[i].str);
										fprintf_s(out, "%s,", words[i].str);
									}
									printf_s("\n");
								}
							} else {
								printf_s("Совпадений не найдено.\n");
								fprintf_s(out, "Совпадений не найдено.\n");
							}
						}
					} else {
						printf_s("Ошибка выдиления памяти");
					}
					fclose(out);
					printf_s("Операция произведина.\n");
				} else {
					printf_s("Ошибка. Файл %s абсолютно пуст.", NameOfFiles->in);
				}
			} else {
				printf_s("Ошибка. Файл %s не может быть открыт.", NameOfFiles->in);
			}
		} else {
			printf_s("Ошибка ввода");
			rewind(stdin);
		}
	} else {
		printf_s("Ошибка открытия %s!", NameOfFiles->out);
	}
}
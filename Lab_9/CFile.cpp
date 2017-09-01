#include "stdafx.h"
#include "Structures.cpp"
/*Получение имени файлов с консоли*/
NameOfFile* GiveNamesPlease(int argc, char ** argv) {
	NameOfFile *names; /*Структура имен файлов*/
	char *nname, /*Имя входного файла*/
		*name, /*Имя файла введеного юзером*/
		*div, /*Суфикс файла*/
		*oname; /*Имя выходного файла*/
	int eerr = 1, /*Нашли ли точку в названии*/
		ie, /*Счётчик цикла*/
		je = 0; /*Счётчик цикла*/
	name = (char*)malloc(sizeof(char) * 50);
	div = (char*)malloc(sizeof(char) * 10);
	names = (NameOfFile*)malloc(sizeof(NameOfFile));
	if (argc > 1) {
		nname = (char*)malloc(sizeof(char)*strlen(argv[1]) + 10);
		strcpy_s(nname, strlen(argv[1]) + 20, argv[1]);
	}
	else {
	vopr:
		printf_s("Введите имя входного файла: ");
		if (scanf_s("%s", &name, 50)) {
			for (ie = 0; ie < strlen(name); ie++) {
				if (name[ie] == '.') {
					eerr = 0;
					while (ie < strlen(name)) {
						div[je] = name[ie];
						ie++;
						je++;
					}
				}
			}
			nname = (char*)malloc(sizeof(name)+32);
			strcpy_s(nname, strlen(name) + 2, name);
			if (eerr == 0) {
				if (je < 2) {
					strcat_s(nname, 8, "in");
				}
			} else {
				strcat_s(nname, 8, ".in");
			}
		}
		else {
			printf_s("Ошибка ввода.");
			rewind(stdin);
			goto vopr;
		}
	}

	eerr = 0;
	for (ie = 0; ie < strlen(nname) & eerr == 0; ie++) {
		if (argc > 1) {
			if (ie > 2) {
				if (nname[ie] != '.') {
					je++;
				} else {
					eerr = 1;
				}
			}
		} else {
			if (nname[ie] != '.') {
				je++;
			}
			else {
				eerr = 1;
			}
		}
	}
	oname = (char*)malloc(sizeof(char) * je + 4);
	strncpy_s(oname, sizeof(char)*je + 32,nname,je*sizeof(char));

	oname = (char*)realloc(oname, sizeof(char) * (strlen(oname) + 4) + 4);
	strcat_s(oname, 32, ".out");

	names->in = nname;
	names->out = oname;
	return names;
}

void StartComperative(int argc, char ** argv) {
	int i, /*Счётчик цикла*/
		j = 0, /*Счётчик цикла*/
		count = 0, /*Количество совпадений*/
		word_count = 0, /*Всего слов в тексте*/
		max = 0, /*Индекс слова с максимальным количеством совпадений*/
		is_screen = 1, /*Выводить ли на екран*/
		can_read = 1; /*Можно ли читать файл дальше*/
	FILE *f, /*Файл текста*/
		*out; /*Файл вывода*/
	char k[200], /*Слово*/
		*istr, /*Слово*/
		sepr[] = " ", /*Разделитель*/
		*nun, /*Пустой указатель*/
		*chre; /*Букавы для поиска совпадений*/
	Word *reiting, /*Слова с количеством совпадений*/
		*words; /*Слова с одинаковым рейтингом*/
	NameOfFile *NameOfFile; /*Названия входного и выходного файла*/

	reiting = (Word*)malloc(sizeof(Word));
	chre = (char*)malloc(sizeof(char) * 32);

	NameOfFile = GiveNamesPlease(argc, argv);

vivod:
	printf_s("Выводить на екран? 0)Нет 1)Да\n");
	if (!scanf_s("%d", &is_screen)) {
		printf_s("Ошибка ввода.");
		rewind(stdin);
		goto vivod;
	}

	printf_s("%s\n", NameOfFile->in);
	printf_s("%s\n",NameOfFile->out);
	if (!fopen_s(&out, NameOfFile->out, "w+")) {
		printf_s("Введите символы: ");
		if (scanf_s("%s", chre, 30)) {
			if (is_screen == 1) {
				printf_s("Буквы: %s\n", chre);
			}
			fprintf_s(out, "Буквы: %s\n", chre);
			if (!fopen_s(&f, NameOfFile->in, "r")) {
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
							reiting = (Word*)realloc(reiting, sizeof(Word) * (word_count + 2));
							count = 0;
							for (i = 0; i < strlen(istr); i++) {
								for (j = 0; j < strlen(chre); j++) {
									if (istr[i] == chre[j]) {
										count++;
									}
								}
							}
							reiting[word_count].str = (char*)malloc(sizeof(char) * strlen(istr)+16);
							strcpy_s(reiting[word_count].str, strlen(istr) + 2, istr);
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
					words = (Word*)malloc(sizeof(Word)*word_count);
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
						if (j == 1) {
							printf_s("Максимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
							fprintf_s(out, "\nМаксимальное количество совпадений(%d) в слове: %s\n", reiting[max].sovpad, reiting[max].str);
						}
						else {
							printf_s("Максимальное количество совпадений в %d словах: ", j);
							fprintf_s(out, "\nМаксимальное количество совпадений в %d словах: ", j);
							for (i = 0; i < j; i++) {
								printf_s("%s,", words[i].str);
								fprintf_s(out, "%s,", words[i].str);
							}
							printf_s("\n");
						}
					}
					fclose(out);
					free(reiting);
					free(words);
					free(NameOfFile);
					free(f);
					free(out);
					printf_s("Операция произведина.\n");
				}
				else {
					printf_s("Ошибка. Файл %s абсолютно пуст.", NameOfFile->in);
				}
			}
			else {
				printf_s("Ошибка. Файл %s не может быть открыт.", NameOfFile->in);
			}
		}
		else {
			printf_s("Ошибка ввода");
			rewind(stdin);
		}
	}
	else {
		printf_s("Ошибка открытия %s!", NameOfFile->out);
	}
}
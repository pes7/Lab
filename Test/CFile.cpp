#include "stdafx.h"
#include "Structures.cpp"
/*Получение имени файлов с консоли*/
NameOfFile* GiveNamesPlease(int argc, char ** argv) {
	NameOfFile *names; /*Структура имен файлов*/
	char *nname, /*Имя входного файла*/
		name[50], /*Имя файла введеного юзером*/
		div[10], /*Суфикс файла*/
		*oname; /*Имя выходного файла*/
	int eerr = 1, /*Нашли ли точку в названии*/
		i, /*Счётчик цикла*/
		j = 0; /*Счётчик цикла*/
	names = (NameOfFile*)malloc(sizeof(NameOfFile));
	if (argc > 1) {
		nname = (char*)malloc(sizeof(char)*strlen(argv[1]) + 10);
		strcpy_s(nname, strlen(argv[1]) + 20, argv[1]);
	}
	else {
	vopr:
		printf_s("Введите имя входного файла: ");
		if (scanf_s("%s", &name, 50)) {
			for (i = 0; i < strlen(name); i++) {
				if (name[i] == '.') {
					eerr = 0;
					while (i < strlen(name)) {
						div[j] = name[i];
						i++;
						j++;
					}
				}
			}
			nname = (char*)malloc(sizeof(char)*strlen(name) + 10);
			strcpy_s(nname, strlen(name) + 2, name);
			if (eerr == 0) {
				if (j < 2) {
					strcat_s(nname, 16, "in");
				}
			}
			else {
				strcat_s(nname, 16, ".in");
			}
		}
		else {
			printf_s("Ошибка ввода.");
			rewind(stdin);
			goto vopr;
		}
	}

	oname = (char*)malloc(sizeof(char) * strlen(nname) + 2);
	strcpy_s(oname, strlen(nname) + 4, nname);
	oname = (char*)realloc(oname, sizeof(char) * (strlen(oname) + 2));
	oname[strlen(oname) - 1] = 'u';
	oname[strlen(oname) - 2] = 'o';
	strcat_s(oname, 16, "t");

	names->in = nname;
	names->out = oname;
	return names;
}
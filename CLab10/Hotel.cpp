#include "stdafx.h"
#include "Structures.cpp"
/*Получить название входного и выходного файла*/
NameOfFile *GetFiles(int argc, char ** argv, NameOfFile *NameOfFiles) {
	char set[100], /*Строка*/
		 c; /*Символ*/
	FILE *file; /*Файл*/
	if (NameOfFiles == NULL) {
		NameOfFiles = (NameOfFile*)malloc(sizeof(NameOfFile));
		NameOfFiles->in = (char*)malloc(sizeof(char) * 50);
		NameOfFiles->out = (char*)malloc(sizeof(char) * 55);
	}
	if (argc > 1) {
		strcpy_s(NameOfFiles->in, strlen(argv[1]) * sizeof(char) + 16, argv[1]);
	} else {
		starter:
		printf_s("Введите название файла: ");
		if (!scanf_s("%s", NameOfFiles->in, 48)) {
			printf_s("Error\n");
		}
		if (fopen_s(&file, NameOfFiles->in, "r")) {
			printf_s("Файл пуст или не найден. Создать ли новый файл? T)Да F)Нет E)Выйти с программы\n");
			c = _getch();
			c = toupper(c);
			if (c == 'F' || c == 'А') {
				goto starter;
			} else if (c == 'T' || c == 'Е') {
				fopen_s(&file, NameOfFiles->in, "w+");
				fclose(file);
			} else {
				printf_s("Программа будет закрыта\n");
				NameOfFiles = NULL;
				_getch();
			}
		} else {
			fclose(file);
			strcpy_s(NameOfFiles->out, 50, NameOfFiles->in);
			strcat_s(NameOfFiles->out, 55, ".out");
		}
	}
	return NameOfFiles;
}

/*Проверка на ошибку работы с файлом*/
void CFE(FILE *file) {
	if (ferror(file)) {
		printf_s("Ошибка при работе с файлом.");
	}
}

/*Визуализировать отели*/
void ShowHotels(GHotels *hotels, NameOfFile *NameOfFiles) {
	int i = 0; /*Счётчик*/
	Hotel *ht = hotels->first; /*Отель*/
	FILE *fl; /*Файл*/
	fopen_s(&fl, NameOfFiles->out, "w+");
	CFE(fl);
	for (i; i < hotels->count; i++) {
		printf_s("Название: %s", ht->name);
		fprintf_s(fl, "%s", ht->name);
		CFE(fl);
		printf_s("Насл. пункт: %s", ht->city);
		fprintf_s(fl, "%s", ht->city);
		CFE(fl);
		printf_s("Кол. комнат: %d\n", ht->rooms);
		fprintf_s(fl, "%d\n", ht->rooms);
		CFE(fl);
		printf_s("Кол. звёзд: %d\n\n", ht->zvezd);
		fprintf_s(fl, "%d\n", ht->zvezd);
		CFE(fl);
		ht = ht->previus;
	}
	fclose(fl);
}

/*Получить отель за индексом*/
Hotel *GetIndexedHotel(GHotels *hotel, int index) {
	Hotel *ht = hotel->first; /*Отель*/
	int i = 0;
	for (i; i < index; i++) {
		ht = ht->previus;
	}
	return ht;
}

/*Сортировка отелей*/
GHotels *SortHotel(GHotels *hotels) {
	Hotel *ht = hotels->first, /*Отель*/
		*first, /*Первый отель*/
		*pre; /*Предыдущий отель*/
	int i = 0, /*Счётчик*/
		is = 1, /*Условие цыкла*/
		go = 0; /*Отсортировали ли*/
	if (hotels->count > 1) {
		while (is)
		{
			if (i == hotels->count) {
				i = 0;
				ht = hotels->first;
			}
			if (ht != NULL) {
				if (ht->previus != NULL) {
					if (ht->zvezd < ht->previus->zvezd) {
						go = 0;
						if (ht != hotels->first) {
							pre = ht->previus;
							first = ht;
							first->previus = pre->previus;
							pre->previus = first;
							GetIndexedHotel(hotels, i - 1)->previus = pre;
						}
						else {
							pre = ht->previus;
							first = ht;
							first->previus = pre->previus;
							pre->previus = first;
							hotels->first = pre;
						}
						ht = pre->previus;
					}
					else {
						go++;
						if (go >= hotels->count) {
							is = 0;
						}
						ht = ht->previus;
					}
				}
			}
			i++;
		}
	}
	return hotels;
}

/*Добавление отеля в структуру*/
GHotels *GAddHotel(GHotels *hotels, char *name, char *city, int rooms, int zvezd) {
	Hotel *ht = (Hotel*)malloc(sizeof(Hotel)), /*Отель*/
		*lht; /*Предыдущий отель*/
	ht->name = (char*)malloc(sizeof(char) * 100);
	ht->city = (char*)malloc(sizeof(char) * 100);

	strcpy_s(ht->name, 100, name);
	strcpy_s(ht->city, 100, city);
	ht->rooms = rooms;
	ht->zvezd = zvezd;
	ht->previus = NULL;
	if (hotels->first != NULL) {
		lht = hotels->first;
		ht->previus = lht;
	}
	hotels->first = ht;
	hotels->count++;
	return hotels;
}

/*Чтение отелей с файла*/
GHotels *GetHotel(GHotels *hotels, NameOfFile *NameOfFiles) {
	FILE *str; /*Файл*/
	char *k, /*Строка*/
		name[100] = { 0 }, /*Название*/
		city[100] = { 0 }; /*Местоположение*/
	int count = 0, /*Нужно для чтения*/
		rooms = 0, /*Количество комнат*/
		zvezd = 0; /*Количество звёзд*/
	if (hotels == NULL) {
		hotels = (GHotels*)malloc(sizeof(GHotels));
		hotels->count = 0;
		hotels->first = NULL;
	}
	k = (char*)malloc(sizeof(char) * 100);
	fopen_s(&str, NameOfFiles->in, "r");
	CFE(str);
	if (str == NULL) {
		puts("Не удалось открыть файл.");
	} else {
		while (fgets(k, 100, str) != NULL) {
			CFE(k);
			switch (count)
			{
			case 0:
				strcpy_s(name, 98, k);
				break;
			case 1:
				strcpy_s(city, 98, k);
				break;
			case 2:
				rooms = atoi(k);
				break;
			case 3:
				zvezd = atoi(k);
				break;
			}
			if (count == 3) {
				hotels = GAddHotel(hotels, name, city, rooms, zvezd);
				count = 0;
			}
			else {
				count++;
			}
		}
		fclose(str);
	}
	free(k);
	return hotels;
}

/*Добавить отель в файл*/
void AddHotel(NameOfFile *NameOfFiles) {
	FILE *str; /*Файл отеля*/
	char D, /*Просто символ*/
		ce[150], /*Название*/
		k[150]; /*Местоположение*/
	int count = 0, /*Проверка на ввод*/
		is = 1; /*Условие цыкла*/
	while (is) {
		fopen_s(&str, NameOfFiles->in, "a+");
		CFE(str);
		system("cls");
		fflush(stdin);
		rewind(stdin);
	n:
		printf_s("Введите название отеля: ");
		fgets(&ce, 147, stdin);
		if (strlen(&ce) == 1) {
			printf_s("Ошибка. Строка пуста.\n");
			goto n;
		}
		fprintf_s(str, "%s", &ce);
	l:
		printf_s("Населённый пункт: ");
		fgets(&k, 147, stdin);
		if (strlen(&k) == 1) {
			printf_s("Ошибка. Строка пуста.\n");
			goto l;
		}
		fprintf_s(str, "%s", &k);
		CFE(str);
	c:
		printf_s("Количество номеров: ");
		if (!scanf_s("%d", &count)) {
			printf_s("Ошибка ввода.\n");
			rewind(stdin);
			goto c;
		}
		if (count < 1 || count > 3000) {
			printf_s("Неверное количество номеров.\n");
			rewind(stdin);
			goto c;
		}
		fprintf_s(str, "%d\n", count);
		CFE(str);
	z:
		printf_s("Количество звёзд: ");
		if (!scanf_s("%d", &count)) {
			printf_s("Ошибка ввода.\n");
			rewind(stdin);
			goto z;
		}
		if (count < 1 || count > 5) {
			printf_s("Неверное количество звёзд.\n");
			rewind(stdin);
			goto z;
		}
		fprintf_s(str, "%d\n", count);
		CFE(str);
		printf_s("Запись завершина!\n");
		fclose(str);
		printf_s("Записать еще один отель? D)Да F)Нет\n");
		D = _getch();
		D = toupper(D);
		if (D == 'F' || D == 'А') {
			is = 0;
			return;
		}
	}
}
// CLab10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Structures.cpp"
#include "Functions.h"

int main(int argc, char ** argv)
{
	GHotels *hotels; /*Дескриптор отеля*/
	char L; /*Просто символ*/
	NameOfFile *NameOfFiles = NULL; /*Название Файлов*/
	FILE *file;
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	NameOfFiles = GetFiles(argc, argv, NameOfFiles);
	if (NameOfFiles == NULL) {
		return 0;
	}
	printf_s("In: %s\nOut: %s\n", NameOfFiles->in, NameOfFiles->out);
	system("cls");

	while (1) {
		printf_s("D)Добавить отель в файл\n");
		printf_s("F)Отсортировать файл с отелями, по количеству звёзд\n");
		printf_s("C)Вывод отелей\n");
		printf_s("G)Выбрать другой файл\n");
		printf_s("P)Выход\n");

		L = _getch();
		L = toupper(L);
		switch (L)
		{
		case'D':
		case'В':
			AddHotel(NameOfFiles);
			break;
		case'F':
		case'А':
			system("cls");
			fopen_s(&file, NameOfFiles->in, "r");
			if (!feof(file)) {
				fclose(file);
				printf_s("Прочитаные отели:\n");
				hotels = NULL;
				hotels = GetHotel(hotels, NameOfFiles);
				if (hotels != NULL) {
					ShowHotels(hotels, NameOfFiles);
					printf_s("Нажмите любую клавишу для получения отсортированых отелей.\n");
					_getch();
					system("cls");
					printf_s("Отсортированые отели:\n");
					hotels = SortHotel(hotels);
					ShowHotels(hotels, NameOfFiles);
					printf_s("Отсортированый файл с отелями записан с названием %s", NameOfFiles->out);
				}
				_getch();
			} else {
				fclose(file);
				printf_s("Не возможно отсортировать пустой файл.\n");
				_getch();
			}
			break;
		case'C':
		case'С':
			system("cls");
			fopen_s(&file,NameOfFiles->in,"r");
			if (!feof(file)) {
				fclose(file);
				hotels = NULL;
				hotels = GetHotel(hotels, NameOfFiles);
				ShowHotels(hotels, NameOfFiles);
				_getch();
			} else {
				fclose(file);
				printf_s("Файл пуст, вывод не возможен.\n");
				_getch();
			}
			break;
		case'G':
		case'П':
			system("cls");
			NameOfFiles = NULL;
			NameOfFiles = GetFiles(argc, argv, NameOfFiles);
			break;
		case'P':
		case'З':
			return 0;
			break;
		}
		system("cls");
	}
	
    return 0;
}


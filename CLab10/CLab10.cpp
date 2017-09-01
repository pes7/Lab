// CLab10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Structures.cpp"
#include "Functions.h"

int main(int argc, char ** argv)
{
	GHotels *hotels; /*���������� �����*/
	char L; /*������ ������*/
	NameOfFile *NameOfFiles = NULL; /*�������� ������*/
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
		printf_s("D)�������� ����� � ����\n");
		printf_s("F)������������� ���� � �������, �� ���������� ����\n");
		printf_s("C)����� ������\n");
		printf_s("G)������� ������ ����\n");
		printf_s("P)�����\n");

		L = _getch();
		L = toupper(L);
		switch (L)
		{
		case'D':
		case'�':
			AddHotel(NameOfFiles);
			break;
		case'F':
		case'�':
			system("cls");
			fopen_s(&file, NameOfFiles->in, "r");
			if (!feof(file)) {
				fclose(file);
				printf_s("���������� �����:\n");
				hotels = NULL;
				hotels = GetHotel(hotels, NameOfFiles);
				if (hotels != NULL) {
					ShowHotels(hotels, NameOfFiles);
					printf_s("������� ����� ������� ��� ��������� �������������� ������.\n");
					_getch();
					system("cls");
					printf_s("�������������� �����:\n");
					hotels = SortHotel(hotels);
					ShowHotels(hotels, NameOfFiles);
					printf_s("�������������� ���� � ������� ������� � ��������� %s", NameOfFiles->out);
				}
				_getch();
			} else {
				fclose(file);
				printf_s("�� �������� ������������� ������ ����.\n");
				_getch();
			}
			break;
		case'C':
		case'�':
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
				printf_s("���� ����, ����� �� ��������.\n");
				_getch();
			}
			break;
		case'G':
		case'�':
			system("cls");
			NameOfFiles = NULL;
			NameOfFiles = GetFiles(argc, argv, NameOfFiles);
			break;
		case'P':
		case'�':
			return 0;
			break;
		}
		system("cls");
	}
	
    return 0;
}


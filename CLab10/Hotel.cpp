#include "stdafx.h"
#include "Structures.cpp"
/*�������� �������� �������� � ��������� �����*/
NameOfFile *GetFiles(int argc, char ** argv, NameOfFile *NameOfFiles) {
	char set[100], /*������*/
		 c; /*������*/
	FILE *file; /*����*/
	if (NameOfFiles == NULL) {
		NameOfFiles = (NameOfFile*)malloc(sizeof(NameOfFile));
		NameOfFiles->in = (char*)malloc(sizeof(char) * 50);
		NameOfFiles->out = (char*)malloc(sizeof(char) * 55);
	}
	if (argc > 1) {
		strcpy_s(NameOfFiles->in, strlen(argv[1]) * sizeof(char) + 16, argv[1]);
	} else {
		starter:
		printf_s("������� �������� �����: ");
		if (!scanf_s("%s", NameOfFiles->in, 48)) {
			printf_s("Error\n");
		}
		if (fopen_s(&file, NameOfFiles->in, "r")) {
			printf_s("���� ���� ��� �� ������. ������� �� ����� ����? T)�� F)��� E)����� � ���������\n");
			c = _getch();
			c = toupper(c);
			if (c == 'F' || c == '�') {
				goto starter;
			} else if (c == 'T' || c == '�') {
				fopen_s(&file, NameOfFiles->in, "w+");
				fclose(file);
			} else {
				printf_s("��������� ����� �������\n");
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

/*�������� �� ������ ������ � ������*/
void CFE(FILE *file) {
	if (ferror(file)) {
		printf_s("������ ��� ������ � ������.");
	}
}

/*��������������� �����*/
void ShowHotels(GHotels *hotels, NameOfFile *NameOfFiles) {
	int i = 0; /*�������*/
	Hotel *ht = hotels->first; /*�����*/
	FILE *fl; /*����*/
	fopen_s(&fl, NameOfFiles->out, "w+");
	CFE(fl);
	for (i; i < hotels->count; i++) {
		printf_s("��������: %s", ht->name);
		fprintf_s(fl, "%s", ht->name);
		CFE(fl);
		printf_s("����. �����: %s", ht->city);
		fprintf_s(fl, "%s", ht->city);
		CFE(fl);
		printf_s("���. ������: %d\n", ht->rooms);
		fprintf_s(fl, "%d\n", ht->rooms);
		CFE(fl);
		printf_s("���. ����: %d\n\n", ht->zvezd);
		fprintf_s(fl, "%d\n", ht->zvezd);
		CFE(fl);
		ht = ht->previus;
	}
	fclose(fl);
}

/*�������� ����� �� ��������*/
Hotel *GetIndexedHotel(GHotels *hotel, int index) {
	Hotel *ht = hotel->first; /*�����*/
	int i = 0;
	for (i; i < index; i++) {
		ht = ht->previus;
	}
	return ht;
}

/*���������� ������*/
GHotels *SortHotel(GHotels *hotels) {
	Hotel *ht = hotels->first, /*�����*/
		*first, /*������ �����*/
		*pre; /*���������� �����*/
	int i = 0, /*�������*/
		is = 1, /*������� �����*/
		go = 0; /*������������� ��*/
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

/*���������� ����� � ���������*/
GHotels *GAddHotel(GHotels *hotels, char *name, char *city, int rooms, int zvezd) {
	Hotel *ht = (Hotel*)malloc(sizeof(Hotel)), /*�����*/
		*lht; /*���������� �����*/
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

/*������ ������ � �����*/
GHotels *GetHotel(GHotels *hotels, NameOfFile *NameOfFiles) {
	FILE *str; /*����*/
	char *k, /*������*/
		name[100] = { 0 }, /*��������*/
		city[100] = { 0 }; /*��������������*/
	int count = 0, /*����� ��� ������*/
		rooms = 0, /*���������� ������*/
		zvezd = 0; /*���������� ����*/
	if (hotels == NULL) {
		hotels = (GHotels*)malloc(sizeof(GHotels));
		hotels->count = 0;
		hotels->first = NULL;
	}
	k = (char*)malloc(sizeof(char) * 100);
	fopen_s(&str, NameOfFiles->in, "r");
	CFE(str);
	if (str == NULL) {
		puts("�� ������� ������� ����.");
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

/*�������� ����� � ����*/
void AddHotel(NameOfFile *NameOfFiles) {
	FILE *str; /*���� �����*/
	char D, /*������ ������*/
		ce[150], /*��������*/
		k[150]; /*��������������*/
	int count = 0, /*�������� �� ����*/
		is = 1; /*������� �����*/
	while (is) {
		fopen_s(&str, NameOfFiles->in, "a+");
		CFE(str);
		system("cls");
		fflush(stdin);
		rewind(stdin);
	n:
		printf_s("������� �������� �����: ");
		fgets(&ce, 147, stdin);
		if (strlen(&ce) == 1) {
			printf_s("������. ������ �����.\n");
			goto n;
		}
		fprintf_s(str, "%s", &ce);
	l:
		printf_s("��������� �����: ");
		fgets(&k, 147, stdin);
		if (strlen(&k) == 1) {
			printf_s("������. ������ �����.\n");
			goto l;
		}
		fprintf_s(str, "%s", &k);
		CFE(str);
	c:
		printf_s("���������� �������: ");
		if (!scanf_s("%d", &count)) {
			printf_s("������ �����.\n");
			rewind(stdin);
			goto c;
		}
		if (count < 1 || count > 3000) {
			printf_s("�������� ���������� �������.\n");
			rewind(stdin);
			goto c;
		}
		fprintf_s(str, "%d\n", count);
		CFE(str);
	z:
		printf_s("���������� ����: ");
		if (!scanf_s("%d", &count)) {
			printf_s("������ �����.\n");
			rewind(stdin);
			goto z;
		}
		if (count < 1 || count > 5) {
			printf_s("�������� ���������� ����.\n");
			rewind(stdin);
			goto z;
		}
		fprintf_s(str, "%d\n", count);
		CFE(str);
		printf_s("������ ���������!\n");
		fclose(str);
		printf_s("�������� ��� ���� �����? D)�� F)���\n");
		D = _getch();
		D = toupper(D);
		if (D == 'F' || D == '�') {
			is = 0;
			return;
		}
	}
}
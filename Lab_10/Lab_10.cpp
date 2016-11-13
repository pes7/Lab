// Lab_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Windows.h"
#include "Math.h"
#include "locale.h"
#include "string.h"

#define pause _pause()
#define cls _cls()
#define arr_size(arr)  (sizeof arr / sizeof arr[0])

void _cls() {
	system("cls");
}

void _pause() {
	system("pause");
}


struct worker{
	char last[100];
	char name[100];
	char otch[100];
	char grou[10];
	char kafe[50];
};

struct book {
	char name[100];
	char autor[100];
	int age;
};

void show_struct(struct worker man);
struct worker get_struct();
void again();
void start();
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	start();
    return 0;
}

void show_struct(struct worker man) {
	printf_s("Ф.И.О: %s %s %s \nГруппа: %s \nКафедра: %s \n",man.last,man.name,man.otch,man.grou,man.kafe);
}

struct worker get_struct() {
	struct worker man;
	printf_s("Имя: ");
	scanf_s("%s", &man.name, sizeof(man.name));
	printf_s("Фамилия: ");
	scanf_s("%s", &man.last, sizeof(man.last));
	printf_s("Отчиство: ");
	scanf_s("%s", &man.otch, sizeof(man.otch));
	printf_s("Группа: ");
	scanf_s("%s", &man.grou, sizeof(man.grou));
	printf_s("Кафедра: ");
	scanf_s("%s", &man.kafe, sizeof(man.kafe));
	return man;
}

void choose() {
	int i;
	char what[100];
	struct book books[5] = {
		{ "Ярость на коне","Мариа Гезе",1999 },
		{ "Я. Волки. Фронт.","Юлиан Молер",1942 },
		{ "Последняя подземка","Ян Вышевский",2007 },
		{ "Hell on the Earth","Jack Ruby",2001 },
		{ "Червоние Прапоры","Масим Куля",1899 }
	};
	scanf_s("%d", &i);
	switch (i) {
	case 1:
		cls;
		struct worker man;
		man = get_struct();
		cls;
		show_struct(man);
		pause;
		break;
	case 2:
		cls;
		for (int i = 0; i < arr_size(books); i++) {
			printf_s("%s [%s] %d года \n", books[i].name, books[i].autor, books[i].age);
		}
		/*
		printf_s("Что удалить (Автор): ");
		scanf_s("%s", what, sizeof(what));
		struct book books_l[arr_size(books) - 1];
		for (int i = 0; i < arr_size(books); i++) {
			if (books[i].autor == what) {
				books_l[i].age = books[i].age;
				books_l[i].name = books[i].name;
				books_l[i].autor = books[i].autor;
				for (int j = i; j < arr_size(books); j++) {
					if (j < arr_size(books) - 1) {
						books_l[j].age = books[j + 1].age;
						books_l[j].name = books[j + 1].name;
						books_l[j].autor = books[j + 1].autor;
					}
				}
			}
		}

		cls;
		for (int i = 0; i < arr_size(books); i++) {
			printf_s("%s [%s] %d года \n", books_l[i].name, books_l[i].autor, books_l[i].age);
		}
		*/
		pause;
		break;
	default:
		again();
		break;
	}
}

void start() {
	printf("Select lab:\n1)Добавить Сотрудника\n2)Удаление книг по автору\n");
	choose();
}


void again() {
	cls;
	start();
}

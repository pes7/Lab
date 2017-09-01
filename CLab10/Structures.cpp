#include "stdafx.h"
/*Структура отеля*/
typedef struct Hotel {
	struct Hotel *previus; /*Предыдущий отель*/
	char *name; /*Название отеля*/
	char *city; /*Город в котором расположен отель*/
	short int rooms; /*Количество комнат*/
	short int zvezd; /*Количество звёзд*/
}Hotel;

/*Десриптор отеля*/
typedef struct {
	int count; /*Сколько всего отелей*/
	Hotel *first; /*1вый отель*/
}GHotels;

/*Название входного и выходного файла*/
typedef struct {
	char *in; /*Входной*/
	char *out; /*Выходной*/
}NameOfFile;
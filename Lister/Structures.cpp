#include "stdafx.h"

typedef struct {
	char *str;
	int lengh;
} Word;

typedef struct {
	char *binds;
} Binds;

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	int width;
	int height;
} Size;

/*Структура настрек меню*/
typedef struct {
	Point coords;
	Size size;
	Binds dbreak;
	int height;
	int prioritet;
	char *header;
} Properties;

/*Структура меню*/
typedef struct {
	Word *text;
	Binds *binds;
	Properties properties;
	int *pointers;
	unsigned int slots;
} Menu;

typedef struct {
	int number; /*Значение*/
	int *previus; /*Предыдущий елемент*/
} StekItem;

typedef struct {
	StekItem *first; /*Первый елемент*/
	int count; /*Размер*/
} StekDescr;

typedef struct {
	int number; /*Значение*/
	int *previus; /*Следующий елемент*/
	int *after; /*Предыдущий елемент*/
} DekItem;

typedef struct {
	DekItem *first; /*Первый елемент*/
	DekItem *last; /*Последний елемент*/
	int count; /*Размер*/
} DekDescr;

struct List {
	int num; /*Число*/
	struct List *next; /*Ссылка не следующий узел*/
};
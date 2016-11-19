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
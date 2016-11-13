#include "stdafx.h"

typedef struct {
	char *str;
	int lengh;
} Word;

typedef struct {
	char *binds;
	int count;
} Binds;

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	int width;
	int height;
} Size;

typedef struct {
	Point coords;
	Size size;
	Binds dbreak;
	int height;
	int prioritet;
	char *header;
} Properties;

typedef struct {
	Word *text;
	Binds *binds;
	Properties properties;
	int *pointers;
	int slots;
} Menu;
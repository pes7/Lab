#include "stdafx.h"
/*Структура содержащая слово и
количество совпадений*/
typedef struct {
	char *str;
	int sovpad;
}Word;

/*Структура которая содержит
имена входного и выходного файла*/
typedef struct {
	char *in;
	char *out;
}NameOfFile;
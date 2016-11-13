#include "CMenu.cpp"
#include "Defines.h"

/*------Stek-Functions-------*/
Stek* CreateStek(int);
Stek* PushStek(Stek*, int);
Stek* ReSizeStek(Stek*);
void StekLoos(Stek*);
int GetStekTop(Stek*);
int GetStekFirst(Stek*);
void DeletStek(Stek**);
int CheckFreeStek(Stek*, int);
/*---------------------------*/

int err = 0;

/*Создание стека*/
Stek* CreateStek(int size) {
	Stek *stek;
	stek = (Stek*)malloc(sizeof(Stek));
	stek->nums = (int*)malloc(sizeof(int) * size);
	stek->top = 0;
	stek->count = size;
	return stek;
}

/*Положить что то в стек*/
Stek* PushStek(Stek* stek, int what) {
	if (stek->top >= stek->count) {
		ReSizeStek(stek);
	}
	stek->nums[stek->top] = what;
	stek->top++;
	return stek;
}

/*Переформатирование стека*/
Stek* ReSizeStek(Stek* stek) {
	if (stek->nums != NULL) {
		stek->count *= MULT;
		stek->nums = (int*)realloc(stek->nums, stek->count * sizeof(int));
	}
	else {
		error102;
	}
	return stek;
}

/*Убираем из стека значение*/
void StekLoos(Stek* stek) {
	if (stek->top != 0) {
		stek->top--;
	}
	else {
		error103;
		err = 1;
	}
}

/*Число елементов стека*/
int GetStekTop(Stek* stek) {
	return stek->top;
}

/*Получить первый елемент стека*/
int GetStekFirst(Stek* stek) {
	return (stek->nums[stek->top - 1]);
}

/*Очистить стек*/
void DeletStek(Stek **stek) {
	free((*stek)->nums);
	free(*stek);
	*stek = NULL;
}

/*Проверка на что то ;) */
int CheckFreeStek(Stek *stek, int mode) {
	if (stek == NULL) {
		error104;
		return 0;
	}
	if (mode == 0) {
		if (stek->top == 0) {
			error105;
			return 0;
		}
		else {
			if (stek->top == 1) {
				error5;
				return 0;
			} else {
				return 1;
			}
		}
	} else {
		return 1;
	}
}

/*Визуализировать стек*/
void ShowStek(Stek *stek, int mode) {
	int ffe;
	if (CheckFreeStek(stek, 1)) {
		if (mode == 0) {
			ffe = stek->top;
		} else {
			ffe = stek->count;
		}
		printf_s("\nВсего: %d елементов\n", stek->top);
		for (int d = 0; d < ffe; d++) {
			printf_s("%d,", stek->nums[d]);
		}
		wt;
	}
}

/*Рандомно сгенирировать стек*/
Stek* GenerateNumsStek(Stek *stek, int max) {
	unsigned int i;
	if (stek != NULL) {
		stek->top = 0;
		for (i = 0; i < stek->count; i++) {
			stek->nums[i] = rand() % max + 1;
			stek->top++;
		}
		say("Стек наполнен рандомными елементами.");
	}
	else {
		error2;
	}
	return stek;
}
#include "stdafx.h"
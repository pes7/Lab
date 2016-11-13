#include "Stek.cpp"

/*-------Dek-Functions-------*/
Dek *CreateDek(int);
Dek *PushDek(Dek*, int, int);
Dek *ReSizeDek(Dek*);
int CheckFreeDek(Dek*,int);
void ShowDek(Dek*, int);
/*---------------------------*/

enum WDek {Top,Down};

/*Создание дека*/
Dek* CreateDek(int size) {
	Dek *dek;
	dek = (Dek*)malloc(sizeof(Dek));
	dek->nums = (int*)malloc(sizeof(int) * size);
	dek->top = 0;
	dek->bottom = 0;
	dek->count = size;
	return dek;
}

/*Переформатирование стека*/
Dek* ReSizeDek(Dek* dek) {
	if (dek->nums != NULL) {
		dek->count *= 2;
		dek->nums = (int*)realloc(dek->nums, dek->count * sizeof(int));
	}
	else {
		error107;
	}
	return dek;
}

/*PUSH*/
Dek* PushDek(Dek* dek, int what, int wheres) {
	int i;
	switch (wheres) {
	case 0:
		if (dek->top >= dek->count) {
			ReSizeDek(dek);
		}
		dek->nums[dek->top] = what;
		dek->top++;
		break;
	case 1://Bottom
		if (dek->bottom == 0) {
			if (dek->top >= dek->count - 1) {
				ReSizeDek(dek);
			}
			for (i = dek->top - 1; i >= 0; i--) {
				dek->nums[i + 1] = dek->nums[i];
			}
			dek->top++;
			dek->nums[dek->bottom] = what;
		}
		else {
			dek->bottom--;
			dek->nums[dek->bottom] = what;
		}
		break;
	}
	return dek;
}

/*POP*/
Dek* PopDek(Dek* dek, int wheres) {
	int i = 0;
	switch (wheres) {
	case 0:
		if (dek->top - 1 > dek->bottom) {
			if (dek->top != 0) {
				dek->top--;
			}
			else {
				error108;
				err = 1;
			}
		} else {
			err = 1;
			error8;
		}
		break;
	case 1://Bottom
		if (dek->bottom < dek->top - 1) {
			if (dek->top != 0) {
				//Доробыть через зміну позиції bottom
				dek->bottom++;
			}
			else {
				error108;
				err = 1;
			}
		} else {
			err = 1;
			error7;
		}
		break;
	}
	return dek;
}

int CheckFreeDek(Dek *dek, int mode) {
	if (dek == NULL) {
		error109;
		return 0;
	}
	if (mode == 0) {
		if (dek->top == 0) {
			error110;
			return 0;
		} else {
			if (dek->top == 1) {
				error6;
				return 0;
			}
			else {
				return 1;
			}
		}
	} else {
		return 1;
	}
}

/*Визуализировать стек*/
void ShowDek(Dek *dek, int mode) {
	int ffe, cee;
	if (CheckFreeDek(dek, 1)) {
		if (mode == 0) {
			ffe = dek->top;
			cee = dek->bottom;
		}
		else {
			ffe = dek->count;
			cee = 0;
		}
		printf_s("\nВсего: %d елементов\n", dek->top);
		for (int d = cee; d < ffe; d++) {
			printf_s("%d,", dek->nums[d]);
		}
		wt;
	}
}

#include "stdafx.h"
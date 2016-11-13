// Ukaz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"

int main()
{

	/*
	int i = 10;
	int *m = &i;
	int g = *m;
	printf_s("%d\n",g);
	*/
	/*
	int ar[30000];
	for (int i = 0; i < 30000; i++) {
		ar[i] = rand() % 100 + 1;
	}
	int *p = ar;
	printf_s("%d\n", *(p + 4));
	*/
	/*
	int ar = (int*)malloc(5*5*sizeof(int));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			&(ar+i*5+j) = rand() % 5 + 1;
		}
	}
	*/
	system("pause");
    return 0;
}


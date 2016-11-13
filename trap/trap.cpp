// trap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"

void drow(int,int);
int main()
{
	//drow(10,20);
	system("pause");
    return 0;
}

void drow(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (i == 0 || i == x - 1 && j != y - 1) {
				printf_s("#");
			} else if (j == 0 && i != 1) {
				printf_s("#");
			}
			else if (j == y - 1) {
				printf_s("#\n");
			}
			else {
				printf_s(" ");
			}
		}
	}
}

// Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"

int main()
{
	int x, y = 1, z = 9;
	for (int i = 0; i < z; i++) {
		for (int ge = z; ge > y; ge--) {
			printf_s(" ");
		}
		for (int ge = y; ge > 0; ge--) {
			printf_s("%d", y);
		}
		for (int ge = 0; ge < y; ge++) {
			printf_s("%d", y);
		}
		y++;
		printf_s("\n");
	}
	system("pause");
    return 0;
}


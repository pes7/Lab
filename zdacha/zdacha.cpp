#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "string.h"


void sladkiy_keks(int);
int main()
{
	setlocale(LC_ALL, "rus");
	sladkiy_keks(500);
	return 0;
}

void sladkiy_keks(int x) {
	int y1 = 0, y2 = 0, y3 = 0, y4 = 0;
	int xe = 0;
	while (x > 0) {
		switch (xe)
		{
		case 0://25
			if (x > 25) {
				x = x - 25;
				y1++;
			}
			xe++;
			break;
		case 1://10
			if (x > 10) {
				x = x - 10;
				y2++;
			}
			xe++;
			break;
		case 2://5
			if (x > 5) {
				x = x - 5;
				y3++;
			}
			xe++;
			break;
		case 3://1
			if (x >= 1) {
				x = x - 1;
				y4++;
				xe = 0;
			}
			break;
		}
	}
	printf_s("Мы похерели: \n%d - 25 минеток\n%d - 10 минеток\n%d - 5 минеток\n %d - 1 минеток\n", y1, y2, y3, y4);
	system("pause");
}
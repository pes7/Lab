#include "stdafx.h"
void NReTranslateToString() {
	int num; /*Число месяца*/
	say("Впишите число месяца: ");
	if (scanf_s("%d", &num)) {
		say("Выбраный месяц: ");
		switch (num)
		{
		case 1:
			say("Январь");
			break;
		case 2:
			say("Февраль");
			break;
		case 3:
			say("Март");
			break;
		case 4:
			say("Апрель");
			break;
		case 5:
			say("Май");
			break;
		case 6:
			say("Июнь");
			break;
		case 7:
			say("Июль");
			break;
		case 8:
			say("Август");
			break;
		case 9:
			say("Сентябрь");
			break;
		case 10:
			say("Октябрь");
			break;
		case 11:
			say("Ноябрь");
			break;
		case 12:
			say("Декабрь");
			break;
		default:
			say("Не коректное число месяца.");
			break;
		}
	}
	else {
		error;
	}
	wt;
}
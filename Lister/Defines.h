#pragma once
#define error _error(); _getch();
#define say(text) _say(text);

void _error() {
	printf_s("Ошибка ввода!\n ");
	rewind(stdin);
}

void _say(char *text) {
	printf_s(text);
}
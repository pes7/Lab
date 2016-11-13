#pragma once
#include "Windows.h"
#define error _error()
#define say(text) _say(text);
#define pause _pause();

void _say(char *text) {
	printf_s(text);
}

void _error() {
	printf_s("Ошибка ввода!");
	rewind(stdin);
}

void _pause() {
	system("pause");
}

#define wt _getch();

#define MULT 2
#define error101 say("Ошибка. Неудачная попытка снять елемент с пустого стека!\n"); err = 1; wt;
#define error102 say("Ошибка. Вы неможите добавить новый елемент в стек, поскольку он не может больше рости!\n"); err = 1; wt;
#define error103 say("Ошибка. Нету больше елементов в стеке, стек - пустой!\n"); err = 1; wt;
#define error104 say("Ошибка. Стек не создан\n"); err = 1; wt;
#define error105 say("Ошибка. 0 елеметов в стеке!\n"); err = 1; wt;
#define error1 say("Неверное указания размера стека!\n"); err = 1; wt;
#define error2 say("Невозможно выполнить операцию, стек не создан!\n"); err = 1; wt;
#define error5 say("Ошибка. Стек имеет всего 1 елемент, и невозможно снятие елемента"); err = 1; wt;

#define error106 say("Ошибка. Неудачная попытка снять елемент с пустого дека!\n"); err = 1; wt;
#define error107 say("Ошибка. Вы неможите добавить новый елемент в дек, поскольку он не может больше рости!\n"); err = 1; wt;
#define error108 say("Ошибка. Нету больше елементов в деке, дек - пустой!\n"); err = 1; wt;
#define error109 say("Ошибка. Дек не создан\n"); err = 1; wt;
#define error110 say("Ошибка. 0 елеметов в Деке!\n"); err = 1; wt;
#define error3 say("Неверное указания размера дека!\n"); err = 1; wt;
#define error4 say("Невозможно выполнить операцию, дек не создан!\n"); err = 1; wt;
#define error6 say("Ошибка. Дек имеет всего 1 елемент, и невозможно снятие елемента"); err = 1; wt;
#define error7 say("Ошибка. Вы не больше не моите снять елементы с низу дека, поскольку у вас осталось только одно значение"); err = 1; wt;
#define error8 say("Ошибка. Вы не больше не моите снять елементы с верху дека, поскольку у вас осталось только одно значение"); err = 1; wt;
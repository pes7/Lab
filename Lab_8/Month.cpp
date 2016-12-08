#include "stdafx.h"

typedef struct{
	char name[40];
}Word;

void _say(char *str) {
	printf_s("%s", str);
}

void NReTranslateToString() {
	int num; /*×èñëî ìåñÿöà*/
	/*Ìåñÿöà*/
	Word month[] = {"NULL","ßíâàğü","Ôåâğàëü","Ìàğò","Àïğåëü","Ìàé","Èşíü","Èşëü","Àâãóñò","Ñåíòÿáğü","Îêòÿáğü","Íîÿáğü","Äåêàáğü"};
	say("Âïèøèòå ÷èñëî ìåñÿöà: ");
	if (scanf_s("%d", &num)) {
		if (num > 12 || num < 1) {
			say("Âû îøèáëèñü, â ïğèğîäå òàêîãî ìåñÿöà íå ñóùåñòâóåò!");
		} else {
			say("Âûáğàíûé ìåñÿö: ");
			printf_s("%s", month[num].name);
		}
	} else {
		error;
	}
	wt;
}
#include "stdafx.h"

void NIsPalendomizm() {
	char *chr; /*Слово*/
	int err = 0, /* если 1 то не полиндром*/
		lengh; /*Длинна слова*/
	chr = (char*)malloc(sizeof(chr));
	say("Введите слово не меньше 3 символов: ");
	if (fgets(chr, 100, stdin)) {
		lengh = strlen(chr);
		if (lengh < 3) {
				for (int i = 0; i <= lengh - 2 && err == 0; i++) {
					if (toupper(chr[i]) != toupper(chr[lengh - i - 2])) {
						err = 1;
					}
				}
			if (err == 0) {
				say("YES");
			} else { say("NO"); }
		}else{
			say("Ошилка, слово меньше 3 символов.");
		}
	} else {
		error;
	}
	wt;
}
// Rus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "locale.h"
#include "RusLanguage.h"

пустота local();
число главная()
{
	число кек = 0;
	локализировать;
	вывод("Да - ето русский код!)\n");
	система(пауза);
	цыкл(число и = 0; и < 5; и++) {
		вывод("русское число: %d\n",кек);
	}
	система(пауза);
	возвратить 0;
}

пустота local() {
	язык(LC_ALL, "RUS");
}


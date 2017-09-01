// CLab9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//StartComperative(argc,argv);
	StartNormal(argc,argv);

	_getch();
    return 0;
}


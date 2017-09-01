// Lab_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Structures.cpp"

NameOfFile* GiveNamesPlease(int argc, char ** argv);
void StartComperative(int argc, char ** argv);
int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	StartComperative(argc,argv);
	
	_getch();
	return 0;
}



//oname = (char*)realloc(oname, sizeof(char) * (strlen(oname) + 4) + 4);

/*
eerr = 0;
for (i = 0; i < strlen(nname) & eerr == 0; i++) {
if (argc > 1) {
if (i > 2) {
if (nname[i] != '.') {
j++;
}
else {
eerr = 1;
}
}
}
else {
if (nname[i] != '.') {
j++;
}
else {
eerr = 1;
}
}
}
oname = (char*)malloc(sizeof(char) * j + 4);
strncpy_s(oname, sizeof(char)*j + 32, nname, j * sizeof(char));

oname = (char*)realloc(oname, sizeof(char) * (strlen(oname) + 4) + 4);
strcat_s(oname, 32, ".out");
*/
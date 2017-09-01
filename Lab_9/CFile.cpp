#include "stdafx.h"
#include "Structures.cpp"
/*��������� ����� ������ � �������*/
NameOfFile* GiveNamesPlease(int argc, char ** argv) {
	NameOfFile *names; /*��������� ���� ������*/
	char *nname, /*��� �������� �����*/
		*name, /*��� ����� ��������� ������*/
		*div, /*������ �����*/
		*oname; /*��� ��������� �����*/
	int eerr = 1, /*����� �� ����� � ��������*/
		ie, /*������� �����*/
		je = 0; /*������� �����*/
	name = (char*)malloc(sizeof(char) * 50);
	div = (char*)malloc(sizeof(char) * 10);
	names = (NameOfFile*)malloc(sizeof(NameOfFile));
	if (argc > 1) {
		nname = (char*)malloc(sizeof(char)*strlen(argv[1]) + 10);
		strcpy_s(nname, strlen(argv[1]) + 20, argv[1]);
	}
	else {
	vopr:
		printf_s("������� ��� �������� �����: ");
		if (scanf_s("%s", &name, 50)) {
			for (ie = 0; ie < strlen(name); ie++) {
				if (name[ie] == '.') {
					eerr = 0;
					while (ie < strlen(name)) {
						div[je] = name[ie];
						ie++;
						je++;
					}
				}
			}
			nname = (char*)malloc(sizeof(name)+32);
			strcpy_s(nname, strlen(name) + 2, name);
			if (eerr == 0) {
				if (je < 2) {
					strcat_s(nname, 8, "in");
				}
			} else {
				strcat_s(nname, 8, ".in");
			}
		}
		else {
			printf_s("������ �����.");
			rewind(stdin);
			goto vopr;
		}
	}

	eerr = 0;
	for (ie = 0; ie < strlen(nname) & eerr == 0; ie++) {
		if (argc > 1) {
			if (ie > 2) {
				if (nname[ie] != '.') {
					je++;
				} else {
					eerr = 1;
				}
			}
		} else {
			if (nname[ie] != '.') {
				je++;
			}
			else {
				eerr = 1;
			}
		}
	}
	oname = (char*)malloc(sizeof(char) * je + 4);
	strncpy_s(oname, sizeof(char)*je + 32,nname,je*sizeof(char));

	oname = (char*)realloc(oname, sizeof(char) * (strlen(oname) + 4) + 4);
	strcat_s(oname, 32, ".out");

	names->in = nname;
	names->out = oname;
	return names;
}

void StartComperative(int argc, char ** argv) {
	int i, /*������� �����*/
		j = 0, /*������� �����*/
		count = 0, /*���������� ����������*/
		word_count = 0, /*����� ���� � ������*/
		max = 0, /*������ ����� � ������������ ����������� ����������*/
		is_screen = 1, /*�������� �� �� �����*/
		can_read = 1; /*����� �� ������ ���� ������*/
	FILE *f, /*���� ������*/
		*out; /*���� ������*/
	char k[200], /*�����*/
		*istr, /*�����*/
		sepr[] = " ", /*�����������*/
		*nun, /*������ ���������*/
		*chre; /*������ ��� ������ ����������*/
	Word *reiting, /*����� � ����������� ����������*/
		*words; /*����� � ���������� ���������*/
	NameOfFile *NameOfFile; /*�������� �������� � ��������� �����*/

	reiting = (Word*)malloc(sizeof(Word));
	chre = (char*)malloc(sizeof(char) * 32);

	NameOfFile = GiveNamesPlease(argc, argv);

vivod:
	printf_s("�������� �� �����? 0)��� 1)��\n");
	if (!scanf_s("%d", &is_screen)) {
		printf_s("������ �����.");
		rewind(stdin);
		goto vivod;
	}

	printf_s("%s\n", NameOfFile->in);
	printf_s("%s\n",NameOfFile->out);
	if (!fopen_s(&out, NameOfFile->out, "w+")) {
		printf_s("������� �������: ");
		if (scanf_s("%s", chre, 30)) {
			if (is_screen == 1) {
				printf_s("�����: %s\n", chre);
			}
			fprintf_s(out, "�����: %s\n", chre);
			if (!fopen_s(&f, NameOfFile->in, "r")) {
				if (getc(f) != EOF) {
					rewind(f);
					while (can_read) {
						fgets(k, 200, f);
						if (feof(f) != 0) {
							can_read = 0;
						}
						istr = strtok_s(k, sepr, &nun);
						while (istr != NULL)
						{
							reiting = (Word*)realloc(reiting, sizeof(Word) * (word_count + 2));
							count = 0;
							for (i = 0; i < strlen(istr); i++) {
								for (j = 0; j < strlen(chre); j++) {
									if (istr[i] == chre[j]) {
										count++;
									}
								}
							}
							reiting[word_count].str = (char*)malloc(sizeof(char) * strlen(istr)+16);
							strcpy_s(reiting[word_count].str, strlen(istr) + 2, istr);
							reiting[word_count].sovpad = count;
							if (is_screen == 1) {
								printf_s("[%d]%s ", count, istr);
							}
							fprintf_s(out, "[%d]%s ", count, istr);
							istr = strtok_s(NULL, sepr, &nun);
							word_count++;
						}
					}
					fclose(f);
					printf_s("\n");
					words = (Word*)malloc(sizeof(Word)*word_count);
					j = 0;
					for (i = 0; i < word_count; i++) {
						if (reiting[i].sovpad >= reiting[max].sovpad) {
							max = i;
						}
					}
					for (i = 0; i < word_count; i++) {
						if (reiting[i].sovpad == reiting[max].sovpad) {
							words[j].sovpad = reiting[i].sovpad;
							words[j].str = (char*)malloc(sizeof(char)*strlen(reiting[i].str) + 16);
							strcpy_s(words[j].str, strlen(reiting[i].str) + 2, reiting[i].str);
							j++;
						}
					}
					if (is_screen == 1) {
						if (j == 1) {
							printf_s("������������ ���������� ����������(%d) � �����: %s\n", reiting[max].sovpad, reiting[max].str);
							fprintf_s(out, "\n������������ ���������� ����������(%d) � �����: %s\n", reiting[max].sovpad, reiting[max].str);
						}
						else {
							printf_s("������������ ���������� ���������� � %d ������: ", j);
							fprintf_s(out, "\n������������ ���������� ���������� � %d ������: ", j);
							for (i = 0; i < j; i++) {
								printf_s("%s,", words[i].str);
								fprintf_s(out, "%s,", words[i].str);
							}
							printf_s("\n");
						}
					}
					fclose(out);
					free(reiting);
					free(words);
					free(NameOfFile);
					free(f);
					free(out);
					printf_s("�������� �����������.\n");
				}
				else {
					printf_s("������. ���� %s ��������� ����.", NameOfFile->in);
				}
			}
			else {
				printf_s("������. ���� %s �� ����� ���� ������.", NameOfFile->in);
			}
		}
		else {
			printf_s("������ �����");
			rewind(stdin);
		}
	}
	else {
		printf_s("������ �������� %s!", NameOfFile->out);
	}
}
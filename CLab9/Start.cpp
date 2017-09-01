#include "stdafx.h"

/*��������� ���������� ����� �
���������� ����������*/
typedef struct {
	char *str;
	int sovpad;
}Word;

/*��������� ������� ��������
����� �������� � ��������� �����*/
typedef struct {
	char *in;
	char *out;
}NameOfFile;

void StartNormal(int argc, char ** argv) {
	int i, /*������� �����*/
		j = 0, /*������� �����*/
		count = 0, /*���������� ����������*/
		word_count = 0, /*����� ���� � ������*/
		max = 0, /*������ ����� � ������������ ����������� ����������*/
		is_screen = 1, /*�������� �� �� �����*/
		can_read = 1, /*����� �� ������ ���� ������*/
		nashloli = 0; /*����� �� ����������� ������*/
	FILE *f, /*���� ������*/
		*out; /*���� ������*/
	char k[200], /*�����*/
		*istr, /*�����*/
		sepr[] = " ", /*�����������*/
		*nun, /*������ ���������*/
		*chre; /*������ ��� ������ ����������*/
	Word *reiting, /*����� � ����������� ����������*/
		*words; /*����� � ���������� ���������*/
	NameOfFile *NameOfFiles; /*�������� �������� � ��������� �����*/

	reiting = (Word*)malloc(sizeof(Word));
	chre = (char*)malloc(sizeof(char) * 32);

	NameOfFiles = (NameOfFile*)malloc(sizeof(NameOfFile));
	NameOfFiles->in = (char*)malloc(sizeof(char) * 50);
	NameOfFiles->out = (char*)malloc(sizeof(char) * 55);
	if (argc > 1) {
		strcpy_s(NameOfFiles->in, strlen(argv[1]) * sizeof(char) + 16, argv[1]);
	} else {
		printf_s("������� �������� ����� � .in: ");
		if (!scanf_s("%s", NameOfFiles->in, 10)) {
			printf_s("Error");
		}
	}
	strcpy_s(NameOfFiles->out, 50, NameOfFiles->in);
	strcat_s(NameOfFiles->out, 55, ".out");
	//NameOfFiles->out = "../CLab9/OUT.out";
	printf_s("%s\n%s\n", NameOfFiles->in, NameOfFiles->out);

vivod:
	printf_s("�������� �� �����? 0)��� 1)��\n");
	if (!scanf_s("%d", &is_screen)) {
		printf_s("������ �����.");
		rewind(stdin);
		goto vivod;
	}

	if (!fopen_s(&out, NameOfFiles->out, "w+")) {
		printf_s("������� �������: ");
		if (scanf_s("%s", chre, 30)) {
			if (is_screen == 1) {
				printf_s("�����: %s\n", chre);
			}
			fprintf_s(out, "�����: %s\n", chre);
			if (!fopen_s(&f, NameOfFiles->in, "r")) {
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
							reiting = (Word*)realloc(reiting, sizeof(Word) * (word_count + 3));
							if (reiting != NULL) {
								count = 0;
								for (i = 0; i < strlen(istr); i++) {
									for (j = 0; j < strlen(chre); j++) {
										if (istr[i] == chre[j]) {
											count++;
											nashloli = 1;
										}
									}
								}
								reiting[word_count].str = (char*)malloc(sizeof(istr));
								strcpy_s(reiting[word_count].str, strlen(istr) + 4, istr);
								reiting[word_count].sovpad = count;
								if (is_screen == 1) {
									printf_s("[%d]%s ", count, istr);
								}
								fprintf_s(out, "[%d]%s ", count, istr);
								istr = strtok_s(NULL, sepr, &nun);
								word_count++;
							} else {
								printf_s("������ ��������� ������");
							}
						}
					}
					fclose(f);
					printf_s("\n");
					words = (Word*)malloc(sizeof(Word)*word_count);
					if (words != NULL) {
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
							if (nashloli == 1) {
								if (j == 1) {
									printf_s("������������ ���������� ����������(%d) � �����: %s\n", reiting[max].sovpad, reiting[max].str);
									fprintf_s(out, "\n������������ ���������� ����������(%d) � �����: %s\n", reiting[max].sovpad, reiting[max].str);
								} else {
									printf_s("������������ ���������� ���������� � %d ������: ", j);
									fprintf_s(out, "\n������������ ���������� ���������� � %d ������: ", j);
									for (i = 0; i < j; i++) {
										printf_s("%s,", words[i].str);
										fprintf_s(out, "%s,", words[i].str);
									}
									printf_s("\n");
								}
							} else {
								printf_s("���������� �� �������.\n");
								fprintf_s(out, "���������� �� �������.\n");
							}
						}
					} else {
						printf_s("������ ��������� ������");
					}
					fclose(out);
					printf_s("�������� �����������.\n");
				} else {
					printf_s("������. ���� %s ��������� ����.", NameOfFiles->in);
				}
			} else {
				printf_s("������. ���� %s �� ����� ���� ������.", NameOfFiles->in);
			}
		} else {
			printf_s("������ �����");
			rewind(stdin);
		}
	} else {
		printf_s("������ �������� %s!", NameOfFiles->out);
	}
}
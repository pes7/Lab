#include "stdafx.h"
/*��������� �����*/
typedef struct Hotel {
	struct Hotel *previus; /*���������� �����*/
	char *name; /*�������� �����*/
	char *city; /*����� � ������� ���������� �����*/
	short int rooms; /*���������� ������*/
	short int zvezd; /*���������� ����*/
}Hotel;

/*��������� �����*/
typedef struct {
	int count; /*������� ����� ������*/
	Hotel *first; /*1��� �����*/
}GHotels;

/*�������� �������� � ��������� �����*/
typedef struct {
	char *in; /*�������*/
	char *out; /*��������*/
}NameOfFile;
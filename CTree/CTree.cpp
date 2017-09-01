#include "stdafx.h"

/*������� ������*/
typedef struct TreeTop{
	int num; /*�������� ��������*/
	struct TreeTop *left; /*����� �����*/
	struct TreeTop *right; /*������ �����*/
	struct TreeTop *parent; /*��������*/
}TreeTop;

TreeTop *CreateTree(TreeTop *treesub, int num);
void ShowTreeAsLine(TreeTop *tree, int level);
int FindElelm(TreeTop *tree, int level, int find);
TreeTop *DelelemFromTree(TreeTop *tree, int level, int delitemnum);
TreeTop ReplaceTreeElemRec(TreeTop *tree, int level);
void ListShowHigh();

int main()
{
	int num; /*�����*/
	char fd; /*���������� ������ ����*/
	/*���� ������*/
	struct TreeTop *tree = NULL;

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ListShowHigh();

	while (1) {
		fd = _getch();
		fd = _toupper(fd);
		system("cls");
		ListShowHigh();
		switch(fd) {
			case '�':
			case 'A':
				vvod1:
				printf_s("������� ������� ������� ������ ��������: ");
				if (!scanf_s("%d", &num)) {
					printf_s("������ �����.\n");
					rewind(stdin);
					goto vvod1;
				}
				if (num == 0) {
					printf_s("�������� �� � ����� ������������, ������ �������� ������ ��� �����������, � �� ����� ���� �������.\n");
					goto vvod1;
				}
				tree = CreateTree(tree, num);
			break;
			case 'F':
			case '�':
				vvod3:
				printf_s("������� ������� ������� ������: ");
				if (!scanf_s("%d", &num)) {
					printf_s("������ �����.\n");
					rewind(stdin);
					goto vvod3;
				}
				if (FindElelm(tree, 0, num) == 0) {
					printf_s("������� �� ������.\n");
				}
				break;
			case 'D':
			case '�':
				vvod2:
				printf_s("������� ������� ������� ������ �������: ");
				if (!scanf_s("%d", &num)) {
					printf_s("������ �����.\n");
					rewind(stdin);
					goto vvod2;
				}
				DelelemFromTree(tree, 0, num);
				break;
		}
		ShowTreeAsLine(tree, 0);
	}
	_getch();
    return 0;
}

/*����� ���������*/
void ListShowHigh() {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	Coord.X = 92;
	Coord.Y = 24;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("��������� (������):");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("�) �������� �������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("F) ����� ��������");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("D) �������� ��������");
	Coord.X = 0;
	Coord.Y = 0;
	SetConsoleCursorPosition(consoleoutput, Coord);
}

/*������ �������� � ������, ����
  ���� ����������� ��������*/
TreeTop ReplaceTreeElemRec(TreeTop *tree, int level) {
	if (tree->right != NULL) {
		tree->num = tree->right->num;
		ReplaceTreeElemRec(tree->right,level + 1);
	} else {
		if (tree->left != NULL){
			tree->num = tree->left->num;
			ReplaceTreeElemRec(tree->left, level + 1);
		} else {
			tree->parent->right = NULL;
		}
	}
}

/*�������� �������� � ������*/
TreeTop *DelelemFromTree(TreeTop *tree, int level, int delitemnum) {
	if (tree != NULL)
	{
		if (tree->left != NULL) {
			if (tree->left->num == delitemnum) {
				ReplaceTreeElemRec(tree->left,level);
			}
			DelelemFromTree(tree->left, level + 1, delitemnum);
		}
		if (tree->right != NULL) {
			if (tree->right->num == delitemnum) {
				ReplaceTreeElemRec(tree->right, level);
			}
			DelelemFromTree(tree->right, level + 1, delitemnum);
		}
	}
	return tree;
}

/*����� ������ �� ������ int*/
int FindElelm(TreeTop *tree, int level, int find) {
	int result = 0; /*����� �� ������� ��� ���*/
	if (tree != NULL)
	{
		if (tree->num == find && level == 0) {
			printf_s("������ ������� (%d), � ���� ���� ��������� ��������� �� ��� ��������� ������ ������.\n",find);
			return 1;
		}
		if (result == 1) {
			return 1;
		}
		if (tree->left != NULL) {
			if (tree->left->num == find) {
				printf_s("������ ������� (%d), �������� �������� - (%d)\n", find, tree->num);
				return 1;
			}
			result =  FindElelm(tree->left, level + 1, find);
		}
		if (tree->right != NULL) {
			if (tree->right->num == find) {
				printf_s("������ ������� (%d), �������� �������� - (%d)\n", find, tree->num);
				return 1;
			}
			result = FindElelm(tree->right, level + 1, find);
		}
	}
	return result;
}

/*�������� ������*/
void ShowTreeAsLine(TreeTop *tree, int level) {
		if (tree != NULL)
		{
			if (tree->left != NULL) {
				ShowTreeAsLine(tree->left, level + 1);
			}
			printf_s("%d,",tree->num);
			if (tree->right != NULL) {
				ShowTreeAsLine(tree->right, level + 1);
			}
		}
}

/*�������� �������� ������*/
TreeTop *CreateTree(TreeTop *treesub, int num) {
	/*������� ������*/
	TreeTop *NTree;
	/*���� �� ������ TreeTop, �� �������*/
	if (treesub == NULL) {
		treesub = (TreeTop*)malloc(sizeof(TreeTop));
		treesub->left = NULL;
		treesub->right = NULL;
		treesub->num = num;
	} else {
		/*���� �������� ������ ����� �� �� ����� ���, ��������� �� ����*/
		if (num > treesub->num) {
			/*���� ������ ����� �� �������, �� ������� � ������ ����� ������*/
			if (treesub->right == NULL) {
				treesub->right = NTree = (TreeTop*)malloc(sizeof(TreeTop));
				NTree->parent = treesub;
				NTree->left = NULL;
				NTree->right = NULL;
				NTree->num = num;
				return treesub;
			} else {
				/*���� �������, �� ������� ������� �����*/
				CreateTree(treesub->right, num);
			}
		} else {
			if (treesub->left == NULL) {
				treesub->left = NTree = (TreeTop*)malloc(sizeof(TreeTop));
				NTree->parent = treesub;
				NTree->left = NULL;
				NTree->right = NULL;
				NTree->num = num;
				return treesub;
			} else {
				CreateTree(treesub->left, num);
			}
		}
	}
	return treesub;
}
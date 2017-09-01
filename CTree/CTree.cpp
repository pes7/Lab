#include "stdafx.h"

/*Елемент дерева*/
typedef struct TreeTop{
	int num; /*Значение елемента*/
	struct TreeTop *left; /*Левая ветка*/
	struct TreeTop *right; /*Правая ветка*/
	struct TreeTop *parent; /*Родитель*/
}TreeTop;

TreeTop *CreateTree(TreeTop *treesub, int num);
void ShowTreeAsLine(TreeTop *tree, int level);
int FindElelm(TreeTop *tree, int level, int find);
TreeTop *DelelemFromTree(TreeTop *tree, int level, int delitemnum);
TreeTop ReplaceTreeElemRec(TreeTop *tree, int level);
void ListShowHigh();

int main()
{
	int num; /*Число*/
	char fd; /*Переменная выбора меню*/
	/*Само дерево*/
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
			case 'Ф':
			case 'A':
				vvod1:
				printf_s("Введите елемент который хотите добавить: ");
				if (!scanf_s("%d", &num)) {
					printf_s("Ошибка ввода.\n");
					rewind(stdin);
					goto vvod1;
				}
				if (num == 0) {
					printf_s("Простите но в целях безопасности, данное значение попало под ограничение, и не может быть введено.\n");
					goto vvod1;
				}
				tree = CreateTree(tree, num);
			break;
			case 'F':
			case 'А':
				vvod3:
				printf_s("Введите елемент который исчите: ");
				if (!scanf_s("%d", &num)) {
					printf_s("Ошибка ввода.\n");
					rewind(stdin);
					goto vvod3;
				}
				if (FindElelm(tree, 0, num) == 0) {
					printf_s("Елемент не найден.\n");
				}
				break;
			case 'D':
			case 'В':
				vvod2:
				printf_s("Введите елемент который хотите удалить: ");
				if (!scanf_s("%d", &num)) {
					printf_s("Ошибка ввода.\n");
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

/*Вывод подсказки*/
void ListShowHigh() {
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;
	Coord.X = 92;
	Coord.Y = 24;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("Подсказка (Дерево):");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("А) Добавить елемент");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("F) Поиск елемента");
	Coord.Y++;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("D) Удаление елемента");
	Coord.X = 0;
	Coord.Y = 0;
	SetConsoleCursorPosition(consoleoutput, Coord);
}

/*Замена елемента в дереве, если
  было произведено удаление*/
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

/*Удаление елемента с дерева*/
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

/*Найти елмент за ключом int*/
int FindElelm(TreeTop *tree, int level, int find) {
	int result = 0; /*Нашли ли елемент или нет*/
	if (tree != NULL)
	{
		if (tree->num == find && level == 0) {
			printf_s("Найден елемент (%d), у него нету родителей поскольку он сам являеться корнем дерева.\n",find);
			return 1;
		}
		if (result == 1) {
			return 1;
		}
		if (tree->left != NULL) {
			if (tree->left->num == find) {
				printf_s("Найден елемент (%d), родитель елемента - (%d)\n", find, tree->num);
				return 1;
			}
			result =  FindElelm(tree->left, level + 1, find);
		}
		if (tree->right != NULL) {
			if (tree->right->num == find) {
				printf_s("Найден елемент (%d), родитель елемента - (%d)\n", find, tree->num);
				return 1;
			}
			result = FindElelm(tree->right, level + 1, find);
		}
	}
	return result;
}

/*Показать дерево*/
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

/*Создание елемента дерева*/
TreeTop *CreateTree(TreeTop *treesub, int num) {
	/*Елемент дерева*/
	TreeTop *NTree;
	/*Если не создан TreeTop, то создать*/
	if (treesub == NULL) {
		treesub = (TreeTop*)malloc(sizeof(TreeTop));
		treesub->left = NULL;
		treesub->right = NULL;
		treesub->num = num;
	} else {
		/*Если значение больше корня то на право его, наооборот на лево*/
		if (num > treesub->num) {
			/*Если правая ветка не создана, то создать и задать нашим числом*/
			if (treesub->right == NULL) {
				treesub->right = NTree = (TreeTop*)malloc(sizeof(TreeTop));
				NTree->parent = treesub;
				NTree->left = NULL;
				NTree->right = NULL;
				NTree->num = num;
				return treesub;
			} else {
				/*Если создана, то вызвать функцию опять*/
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
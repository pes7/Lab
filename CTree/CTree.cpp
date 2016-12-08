// CTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "Windows.h"

typedef struct TreeTop{
	int num;
	struct TreeTop *left;
	struct TreeTop *right;
}TreeTop;

typedef struct {
	int count;
	struct TreeTop *first;
}TreeRoot;

/*
TreeRoot *CreateRoot() {
	TreeRoot *root = (TreeRoot*)malloc(sizeof(TreeRoot));
	root->first = CreateTree(root,NULL);
	return root;
}
*/

TreeTop *CreateTree(TreeTop *treesub, int num);
void ShowTree(TreeTop *tree,int raz);
int main()
{
	struct TreeTop *tree = NULL;
	tree = CreateTree(tree, 5);
	tree = CreateTree(tree, 4);
	tree = CreateTree(tree, 6);
	tree = CreateTree(tree, 3);
	tree = CreateTree(tree, 23);
	tree = CreateTree(tree, 5);
	ShowTree(tree, 1);
	_getch();
    return 0;
}

/*Всё работает, только вывод над сделать красивый*/
void ShowTree(TreeTop *tree, int raz) {
	int n1 = 0, n2 = 0, n3 = 0;
	int absolute_x = 110;
	HANDLE consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coord;

	if (tree->num != NULL) {
		n1 = tree->num;
	}
	if (tree->left != NULL) {
		if (tree->left->num != NULL) {
			n2 = tree->left->num;
		}
	}
	if (tree->right != NULL) {
		if (tree->right->num != NULL) {
			n3 = tree->right->num;
		}
	}

	Coord.X = (absolute_x / 2) - (8 * raz);
	Coord.Y = raz;
	SetConsoleCursorPosition(consoleoutput, Coord);
	printf_s("%d<-%d->%d\n", n2, n1, n3);
	raz++;

	if (tree->left != NULL) {
		ShowTree(tree->left, raz);
	}
	if (tree->right != NULL) {
		ShowTree(tree->right, raz);
	}
}

TreeTop *CreateTree(TreeTop *treesub, int num) {
	TreeTop *NTree;
	/*Если не создан TreeTop, то создать*/
	if (treesub == NULL) {
		treesub = (TreeTop*)malloc(sizeof(TreeTop));
		treesub->left = NULL;
		treesub->right = NULL;
		treesub->num = NULL;
	}
	/*Если создан, но не задан, то задать*/
	if ((void*)treesub->num != NULL) {
		/*Если значение больше корня то на право его, наооборот на лево*/
		if (num > treesub->num) {
			/*Если правая ветка не создана, то создать и задать нашим числом*/
			if (treesub->right == NULL) {
				treesub->right = NTree = (TreeTop*)malloc(sizeof(TreeTop));
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
				NTree->left = NULL;
				NTree->right = NULL;
				NTree->num = num;
				return treesub;
			} else {
				CreateTree(treesub->left, num);
			}
		}
	} else {
		treesub->num = num;
		return treesub;
	}
	return treesub;
}
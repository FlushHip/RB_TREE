#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "rb_tree.h"

void print_RB_TREE(pRB_TREE T)
{
	pRB_TREE_NODE stack[20];
	int head = 0, tail = 0;

	if (T->root == T->nil)
		return ;

	stack[tail++] = T->root;
	while (head != tail) {
		pRB_TREE_NODE pre = stack[head++];
		printf("num : %2d\tcolor : %d\n", pre->key, pre->color);
		if (pre->left != T->nil)
			stack[tail++] = pre->left;
		if (pre->right != T->nil)
			stack[tail++] = pre->right;
	}
}

int main()
{
	int i;
	int array[] = {2, 3, 7, -4, 5, 11, -11, 0, 56, 78, -100, 30}, size = (int)sizeof(array) / sizeof(int);

	pRB_TREE T = (pRB_TREE)malloc(sizeof(RB_TREE));
	T->nil = (pRB_TREE_NODE)malloc(sizeof(RB_TREE_NODE));

	memset(T->nil, 0, sizeof(RB_TREE_NODE));
	T->nil->color = BLACK;
	T->nil->parent = T->nil->left = T->nil->right = NULL;
	T->root = T->nil;

	for (i = 0; i < size; i++)
		RB_TREE_INSERT(T, array[i]);
	print_RB_TREE(T);
	return 0;
}
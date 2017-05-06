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
	int array[] = {2, 3, 7, -4, 5, 11, -11, 0, 56, 78, -100, 30}, size = sizeof(array) / sizeof(int);
	int b[] = {7, 99999, -4, 5}, b_size = sizeof(b) / sizeof(int);

	pRB_TREE T = (pRB_TREE)malloc(sizeof(RB_TREE));
	INIT_RB_TREE(T);

	for (i = 0; i < size; i++)
		printf("%d%s", array[i], i == size - 1 ? "\n" : ", ");
	for (i = 0; i < size; i++)
		T->RB_TREE_INSERT(T, array[i]);
	print_RB_TREE(T);
	
	for (i = 0; i < b_size; i++) {
		pRB_TREE_NODE is_ok = T->search(T, b[i]);
		
		printf("NO.%d\n", i);
		if (is_ok != NULL) {
			T->dele(T, is_ok);
			print_RB_TREE(T);
		} else
			puts("not find!!!");
	}
	
	print_RB_TREE(T);
	
	return 0;
}

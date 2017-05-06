#include "rb_tree.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

pRB_TREE_NODE RB_TREE_SEARCH(pRB_TREE T, int key)
{
	pRB_TREE_NODE pNode;

	if (T == NULL)
		return NULL;

	for (pNode = T->root; pNode != NULL; pNode = pNode->key > key ? pNode->left : pNode->right)
		if (pNode->key == key)
			return pNode;
	return NULL;
}

void RB_TREE_INSERT(pRB_TREE T, int key)
{
    pRB_TREE_NODE pre = T->nil, now = T->root;
    pRB_TREE_NODE node = (pRB_TREE_NODE)malloc(sizeof(RB_TREE_NODE));

    assert(node != NULL);

    node->key = key;

	while (now != T->nil) {
		pre = now;
		now = node->key < now->key ? now->left : now->right;
	}

	node->parent = pre;

	if (pre == T->nil)
		T->root = node;
	else if (node->key < pre->key)
		pre->left = node;
	else
		pre->right = node;

	node->left = node->right = T->nil;
	node->color = RED;

	RB_TREE_INSERT_FIX(T, node);
}

void RB_TREE_INSERT_FIX(pRB_TREE T, pRB_TREE_NODE node)
{
	while (node->parent->color == RED) {
		pRB_TREE_NODE uncle = T->nil;
		if (node->parent == node->parent->parent->left) {
			uncle = node->parent->parent->right;

			if (uncle->color == RED) {						// 11
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node = node->parent->parent;
				node->color = RED;
			} else if (node == node->parent->right) {		// 21
				node = node->parent;
				ROTATE_LEFT(T, node);
			} else {										// 31
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ROTATE_RIGHT(T, node->parent->parent);
			}
		} else {
			uncle = node->parent->parent->left;

			if (uncle->color == RED) {						// 21
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node = node->parent->parent;
				node->color = RED;
			} else if (node == node->parent->left) {		// 22
				node = node->parent;
				ROTATE_RIGHT(T, node);
			} else {										// 23
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				ROTATE_LEFT(T, node->parent->parent);
			}
		}
	}

	T->root->color = BLACK;
}

void ROTATE_LEFT(pRB_TREE T, pRB_TREE_NODE node)
{
	if (node == node->parent->left)
		node->parent->left = node->right;
	else
		node->parent->right = node->right;

	node->right->parent = node->parent;

	node->parent = node->right;

	node->right->left->parent = node;

	node->right = node->right->left;

	node->parent->left = node;
}

void ROTATE_RIGHT(pRB_TREE T, pRB_TREE_NODE node)
{
	if (node == node->parent->left)
		node->parent->left = node->left;
	else
		node->parent->right = node->left;

	node->left->parent = node->parent;

	node->parent = node->left;

	node->left->right->parent = node;

	node->left = node->left->right;

	node->parent->right = node;
}

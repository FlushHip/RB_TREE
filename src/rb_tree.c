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
	if (node == T->root)
		T->root = node->right;

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
	if (node == T->root)
		T->root = node->left;

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

void RB_TRANSPLANT(pRB_TREE T, pRB_TREE_NODE u, pRB_TREE_NODE v)
{
    if (u->parent == T->nil)
    	T->root = v;
    else if (u->parent->left == u)
    	u->parent->left = v;
    else
    	u->parent->right = v;
    v->parent = u->parent;
}

pRB_TREE_NODE RB_TREE_FIND_MININUM(pRB_TREE T, pRB_TREE_NODE start)
{
	pRB_TREE_NODE now = start, pre = now;
	for (; now != T->nil; pre = now, now = now->left);
	return pre;
}

pRB_TREE_NODE RB_TREE_FIND_MAXINUM(pRB_TREE T, pRB_TREE_NODE start)
{
	pRB_TREE_NODE now = start, pre = now;
	for (; now != T->nil; pre = now, now = now->right);
	return pre;
}

void RB_TREE_DELETE(pRB_TREE T, pRB_TREE_NODE node)
{
	pRB_TREE_NODE y = node, x = NULL;
	COLOR y_original_color = y->color;
	
	if (node->left == T->nil) {
		x = node->right;
		RB_TRANSPLANT(T, node, x);
	} else if (node->right == T->nil) {
		x = node->left;
		RB_TRANSPLANT(T, node, x);
	} else {
		y = RB_TREE_FIND_MININUM(T, node->right);
		x = y->right;
		
		if (y->parent != node) {
			RB_TRANSPLANT(T, y, x);
			y->right = node->right;
			y->right->parent = y;
		}
		
		RB_TRANSPLANT(T, node, y);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}
	
	if (y_original_color == BLACK)
		RB_TREE_DELETE_FIX(T, x);
	
	free(node);
}

void RB_TREE_DELETE_FIX(pRB_TREE T, pRB_TREE_NODE node)
{
	while (node != T->root && node->color == BLACK) {
		if (node == node->parent->left) {
			pRB_TREE_NODE brother = node->parent->right;
			
			if (brother->color == RED) {													// 11
				brother->color = BLACK;
				node->parent->color = RED;
				ROTATE_LEFT(T, node->parent);
			} else if (brother->left->color == BLACK && brother->right->color == BLACK) {	// 12
				brother->color = RED;
				node = node->parent;
			} else if (brother->right->color == BLACK) {									// 13
				brother->color = RED;
				brother->left->color = BLACK;
				ROTATE_RIGHT(T, brother);
			} else {																		// 14
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->right->color = BLACK;
				ROTATE_LEFT(T, node->parent);
				node = T->root;		// break;
			}
		} else {
			pRB_TREE_NODE brother = node->parent->left;
			
			if (brother->color == RED) {													// 21
				brother->color = BLACK;
				node->parent->color = RED;
				ROTATE_RIGHT(T, node->parent);
			} else if (brother->right->color == BLACK && brother->left->color == BLACK) {	// 22
				brother->color = RED;
				node = node->parent;
			} else if (brother->left->color == BLACK) {										// 23
				brother->color = RED;
				brother->right->color = BLACK;
				ROTATE_LEFT(T, brother);
			} else {																		// 24
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->left->color = BLACK;
				ROTATE_RIGHT(T, node->parent);
				node = T->root;		// break;
			}
		}
	}
	node->color = BLACK;
}



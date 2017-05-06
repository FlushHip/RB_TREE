#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED

typedef enum {RED, BLACK} COLOR;

typedef struct tagRB_TREE_NODE RB_TREE_NODE;
typedef struct tagRB_TREE RB_TREE;

typedef RB_TREE *pRB_TREE;
typedef RB_TREE_NODE *pRB_TREE_NODE;

struct tagRB_TREE_NODE {
	int key;
	pRB_TREE_NODE parent;
	pRB_TREE_NODE left, right;
	COLOR color;
};

struct tagRB_TREE {
	pRB_TREE_NODE root;
	pRB_TREE_NODE nil;
};

extern pRB_TREE_NODE RB_TREE_SEARCH(pRB_TREE T, int key);
extern void RB_TREE_INSERT(pRB_TREE T, int key);
extern void RB_TREE_DELETE(pRB_TREE T, pRB_TREE_NODE node);
extern void RB_TREE_INSERT_FIX(pRB_TREE T, pRB_TREE_NODE node);
extern void ROTATE_LEFT(pRB_TREE T, pRB_TREE_NODE node);
extern void ROTATE_RIGHT(pRB_TREE T, pRB_TREE_NODE node);

#endif // RB_TREE_H_INCLUDED

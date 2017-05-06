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
	
	// member function
	pRB_TREE_NODE (*search)(pRB_TREE T, int key);
	pRB_TREE_NODE (*find_mininum)(pRB_TREE T, pRB_TREE_NODE start);
	pRB_TREE_NODE (*find_maxinum)(pRB_TREE T, pRB_TREE_NODE start);
	void (*insert)(pRB_TREE T, int key);
	void (*dele)(pRB_TREE T, pRB_TREE_NODE node);
};

extern pRB_TREE_NODE RB_TREE_SEARCH(pRB_TREE T, int key);
extern pRB_TREE_NODE RB_TREE_FIND_MININUM(pRB_TREE T, pRB_TREE_NODE start);
extern pRB_TREE_NODE RB_TREE_FIND_MAXINUM(pRB_TREE T, pRB_TREE_NODE start);
extern void RB_TREE_INSERT(pRB_TREE T, int key);
extern void RB_TREE_DELETE(pRB_TREE T, pRB_TREE_NODE node);
extern void RB_TREE_INSERT_FIX(pRB_TREE T, pRB_TREE_NODE node);
extern void RB_TREE_DELETE_FIX(pRB_TREE T, pRB_TREE_NODE node);
extern void ROTATE_LEFT(pRB_TREE T, pRB_TREE_NODE node);
extern void ROTATE_RIGHT(pRB_TREE T, pRB_TREE_NODE node);
extern void RB_TRANSPLANT(pRB_TREE T, pRB_TREE_NODE u, pRB_TREE_NODE v);

#define INIT_RB_TREE(T) (T)->search = RB_TREE_SEARCH;\
						(T)->find_mininum = RB_TREE_FIND_MININUM;\
						(T)->find_maxinum = RB_TREE_FIND_MAXINUM;\
						(T)->insert = RB_TREE_INSERT;\
						(T)->dele = RB_TREE_DELETE;\
						(T)->nil = (pRB_TREE_NODE)malloc(sizeof(RB_TREE_NODE));\
						memset((T)->nil, 0, sizeof(RB_TREE_NODE));\
						(T)->nil->color = BLACK;\
						(T)->nil->parent = (T)->nil->left = (T)->nil->right = NULL;\
						(T)->root = (T)->nil

#endif // RB_TREE_H_INCLUDED

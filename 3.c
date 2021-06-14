#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	char elem;
	struct node* left;
	struct node* right;
	struct node* parent;

}NODE;

typedef struct tmp {

	char elem, left, right;
	struct tmp* next;

}tmp;

NODE* getnode();
tmp* gett();
tmp* findRoot();
tmp* findNode();
NODE* makeTree();
void freetree();
void preOrder();
void push();
char pop();
int height();
NODE* find();
NODE* inOrder();

void main() {

	NODE* T = NULL, * sc;
	tmp* L = NULL, * t = NULL, * tp;
	int i, n, top = -1;
	char e, l, r, * S, * A;

	scanf("%d", &n);
	getchar();

	S = (char*)malloc((n + 1) * sizeof(char));
	A = (char*)malloc((n + 1) * sizeof(char));

	for (i = 0; i < n; i++) {
		scanf("%c %c %c", &e, &l, &r);
		getchar();

		t = gett(e, l, r);

		t->next = L;
		L = t;
	}

	t = findRoot(L);

	T = makeTree(t, L);
	
	
	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {

		scanf("%c", &e);
		getchar();

		sc = inOrder(find(T, e));

		if (sc == NULL) {
			printf("No Data\n");
			continue;
		}

		printf("%c\n", sc->elem);

	}

	for (t = L; t != NULL;) {

		tp = t->next;
		free(t);
		t = tp;

	}

	freetree(T);
	free(S);
	free(A);

}

NODE* getnode(char e) {

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));

	newnode->elem = e;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;

	return newnode;

}

tmp* gett(char e, char l, char r) {

	tmp* newnode;

	newnode = (tmp*)malloc(sizeof(tmp));

	newnode->elem = e;
	newnode->left = l;
	newnode->right = r;
	newnode->next = NULL;

	return newnode;

}

tmp* findRoot(tmp* L) {

	tmp* t, * p;

	for (t = L; t != NULL;) {

		for (p = L; p != NULL;) {
			if (t->elem == p->left || t->elem == p->right) {
				break;
			}
			p = p->next;
		}

		if (p == NULL) break;

		t = t->next;

	}

	return t;

}

tmp* findNode(tmp* L, char e) {

	tmp* t;

	for (t = L; t != NULL; ) {

		if (t->elem == e) break;

		t = t->next;

	}

	return t;

}

NODE* makeTree(tmp* v, tmp* L) {

	NODE* t;

	t = getnode(v->elem);

	if (v->left != '0') {
		t->left = makeTree(findNode(L, v->left), L);
		t->left->parent = t;
	}
	if (v->right != '0') {
		t->right = makeTree(findNode(L, v->right), L);
		t->right->parent = t;
	}

	return t;

}


void freetree(NODE* v) {

	if (v->left != NULL) {
		freetree(v->left);
	}
	if (v->right != NULL) {
		freetree(v->right);
	}

	free(v);

}

void preOrder(NODE* v, char* S, int* t) {

	push(S, t, v->elem);

	if (v->left != NULL) {
		preOrder(v->left, S, t);
	}

	if (v->right != NULL) {
		preOrder(v->right, S, t);
	}


}

void push(char* S, int* t, char e) {

	(*t)++;
	*(S + *t) = e;	

}

char pop(char* S, int* t) {

	char tmp;

	tmp = *(S + *t);

	(*t)--;

	return tmp;

}

int height(NODE* v) {

	int h = 0, x, y;

	if (v->left == NULL && v->right == NULL) {
		return 0;
	}

	if (v->left != NULL) {
		x = height(v->left);
	}
	else x = 0;

	if (v->right != NULL) {
		y = height(v->right);
	}
	else y = 0;

	if (x > y) {
		return x + 1;
	}
	else
		return y + 1;


}

NODE* find(NODE* v, char e) {

	NODE* tmp = NULL;

	if (v->elem == e) return v;

	if (v->left != NULL) {
		tmp = find(v->left, e);
	}

	if (tmp == NULL && v->right != NULL) {
		tmp = find(v->right, e);
	}

	return tmp;

}

NODE* inOrder(NODE* v) {

	NODE* t, * p;

	if (v->right != NULL) {
		for (t = v->right; t->left !=NULL;) {
			t = t->left;
		}
		return t;
	}

	p = v->parent;

	for (t = v; p->left != t;) {

		if (p->parent == NULL) {
			return NULL;
		}

		t = p;
		p = p->parent;

	}

	return p;

}
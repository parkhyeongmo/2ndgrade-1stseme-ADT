#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	int weight, id;
	struct node* left, * right;

}NODE;

typedef struct tmp {

	int weight, id, left, right;

	struct tmp* next;

}tmp;

NODE* getnode();
tmp* gett();
tmp* findRoot();
tmp* findt();
NODE* makeTree();
void freetree();
int height();
NODE* findNode();

void postOrder(NODE* v) {

	if (v->left != NULL) {
		postOrder(v->left);
	}
	if (v->right != NULL) {
		postOrder(v->right);
	}

	printf(" %d", v->weight);

}

void main() {

	tmp* L = NULL,* t,* tp;
	NODE* T, * p;
	char cmd;
	int i, j, n, l, r, id, w;

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {

		scanf("%c", &cmd);

		if (cmd == 'A'){

			scanf("%d%d%d%d", &id, &l, &r, &w);
			getchar();
			t = gett(id, l, r, w);
			t->next = L;
			L = t;
		}

		else if (cmd == 'M') {
			scanf("%d%d", &id, &w);
			getchar();
			findt(L, id)->weight = w;

		}

	}

	t = findRoot(L);	
	T = makeTree(L, t);
	
	postOrder(T);
	printf("\n");

	scanf("%d", &n);

	for (i = 0; i < n; i++) {

		scanf("%d", &id);
		p = findNode(T, id);
		printf(" %d", height(p));

	}

	for (t = L; t != NULL;) {
		tp = L->next;
		free(t);
		t = tp;
	}

	freetree(T);

}


NODE* getnode(int id, int weight) {

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));

	newnode->id = id;
	newnode->weight = weight;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;

}

tmp* gett(int id, int left, int right, int weight) {

	tmp* newnode;

	newnode = (tmp*)malloc(sizeof(tmp));

	newnode->id = id;
	newnode->weight = weight;
	newnode->left = left;
	newnode->right = right;

	return newnode;

}

tmp* findt(tmp* L, int id) {

	tmp* t;
	
	for (t = L; t != NULL;) {
		if (id == t->id) {
			break;
		}
		t = t->next;
	}
	
	return t;

}


tmp* findRoot(tmp* L) {

	tmp* t, * p;

	for (t = L; t != NULL;) {

		for (p = L; p != NULL;) {
			if (t->id == p->left || t->id == p->right) {
				break;
			}
			p = p->next;
		}

		if (p == NULL) break;

		t = t->next;

	}

	return t;

}


NODE* makeTree(tmp* L, tmp* r) {

	NODE* v;

	v = getnode(r->id, r->weight);

	if (r->left != 0) {
		v->left = makeTree(L, findt(L, r->left));
	}
	if (r->right != 0) {
		v->right = makeTree(L, findt(L, r->right));
	}

	return v;

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


int height(NODE* v) {

	int x = 0, y = 0;

	if (v->left != NULL) {
		x = 1 + height(v->left);
	}
	if (v->right != NULL) {
		y = 1 + height(v->right);
	}

	if (x > y) return x;
	else return y;

}

NODE* findNode(NODE* v, int id) {

	NODE* tmp = NULL;

	if (v->id == id) return v;

	if (v->left != NULL) {
		tmp = findNode(v->left, id);
	}
	if (tmp == NULL && v->right != NULL) {
		tmp = findNode(v->right, id);
	}

	return tmp;

}
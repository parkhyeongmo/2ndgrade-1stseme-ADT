#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	char name[21];
	char id[11];
	double score;

	struct node* next;

}Node;

Node* getnode();
void init();
void add();


void main() {

	Node* H, * T, * p, * q;
	int i, n;

	init(&H, &T);

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {

		add(H, T);

	}

	p = H->next;

	for (; p != T; p = p->next) {

		printf("%s %s %.1lf\n", p->name, p->id, p->score);

	}

	p = H;

	for (; p != NULL;) {

		q = p->next;
		free(p);
		p = q;

	}

}



Node* getnode() {

	Node* newnode;

	newnode = (Node*)malloc(sizeof(Node));
	newnode->next = NULL;

	return newnode;

}



void init(Node** H, Node** T) {

	Node* h, * t;

	h = getnode();
	t = getnode();

	h->next = t;

	*H = h;
	*T = t;

}



void add(Node* H, Node* T) {

	int i;
	Node* p, * q;
	Node* newnode;

	newnode = getnode();

	scanf("%s", newnode->name);
	scanf("%s", newnode->id);
	scanf("%lf", &(newnode->score));
	getchar();

	p = H;
	q = p->next;

	for (; q != T;) {

		if (strcmp(newnode->id, q->id) > 0) {
			p = p->next;
			q = q->next;
		}
		else if (strcmp(newnode->id, q->id) < 0) {
			break;
		}
		else if (strcmp(newnode->id, q->id) == 0) {
			p->next = newnode;
			newnode->next = q->next;
			free(q);
			return;
		}

	}
	

	newnode->next = q;
	p->next = newnode;

}
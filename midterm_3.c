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

void init();
Node* getnode();
void add();
void delete();
void print();
void over();

void main() {

	Node* H, * T, * k, * p;
	int i, n, d;
	char cmd[7];

	init(&H, &T);
	k = H;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {

		scanf("%s", cmd);
		getchar();

		if (strcmp(cmd, "ADD") == 0) {
			add(&T);
		}

		else if (strcmp(cmd, "DELETE") == 0) {
			
			scanf("%d", &d);
			getchar();
			delete(H, T, d);
		}

		else if (strcmp(cmd, "P") == 0) {
			if (H->next == T) {

				printf("Empty\n");
				continue;

			}
			print(H->next, T);
		}

		else if (strcmp(cmd, "OVER") == 0) {
			over(H, T);
		}

	}

	for (k = H; k != NULL;) {

		p = k->next;
		free(k);
		k = p;

	}

}

/* O(1) */
Node* getnode() {

	Node* newnode;
	newnode = (Node*)malloc(sizeof(Node));
	newnode->next = NULL;

	return newnode;

}

/* O(1) */
void init(Node** H, Node** T) {

	Node* h, * t;

	h = getnode();
	t = getnode();

	h->next = t;

	*H = h;
	*T = t;

}

/* 항상 마지막에 노드가 추가될 때 입력크기와 상관없이 상수시간이 소요되므로 O(1) 시간 소요*/

void add(Node** T) {

	Node* newnode;

	newnode = getnode();

	(*T)->next = newnode;

	scanf("%s", (*T)->name);
	getchar();
	scanf("%s", (*T)->id);
	getchar();
	scanf("%lf", &((*T)->score));

	*T = newnode;

}

/* 삭제할 노드의 위치를 찾기위해 순회하는 시간이 최대 n회 소요되므로 O(n) 시간 소요 */

void delete(Node* H, Node* T, int n) {

	int i;
	Node* p, * q;

	if (H->next == T) {
		printf("invalid position\n");
		return;
	}

	if (n <= 0) {
		printf("invalid position\n");
		return;
	}

	p = H;
	q = H->next;

	for (i = 1; i < n; i++) {

		p = p->next;
		q = q->next;

		if (q == T) {
			printf("invalid position\n");
			return;
		}

	}

	p->next = q->next;
	free(q);

}

/* 노드의 수만큼 출력하기 때문에 O(n) 시간 소요 */

void print(Node* H, Node* T) {

	if (H == T) {
		return;
	}

	else {
		printf("%s %s %.1lf\n", H->name, H->id, H->score);
		print(H->next, T);
	}

}

/* 평균을 구하기 위해 순회하는 시간이 n회, 출력을 위해 다시 한 번 n회 순회하는 시간이 소요되므로 O(n) 시간 소요 */

void over(Node* H, Node* T) {

	int n = 0;
	double aver = 0;
	Node* p = H->next;

	if (H->next == T) {
		printf("Empty\n");
		return;
	}

	for (; p != T; p = p->next) {
		aver += p->score;
		n++;
	}

	aver /= n;

	printf("%.1lf\n", aver);

	for (p = H->next; p != T; p = p->next) {
		if (p->score >= aver) {
			printf("%s\n", p->id);
		}
	}

}
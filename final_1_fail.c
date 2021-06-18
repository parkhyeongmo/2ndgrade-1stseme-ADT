// 나의 IP 주소 : 125.178.152.237
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void push(char* S, int s, int* t, char c, int v) {

	if (*t + 1 == s) {
		return;
	}

	(*t)++;
	*(S + 2 * (*t)) = c;
	*(S + 2 * (*t) + 1) = v;

}

void enqueue(char* Q, int q, int* f, int* r, char c, int v) {

	if ((*r + 1) % q == *f) return;

	*r = (*r + 1) % q;

	*(Q + (*r * 2)) = c;

	*(Q + (*r * 2) + 1) = v;

}

void pop(char* S, int s, int* t, char* Q, int q, int* f, int* r) {

	enqueue(Q, q, f, r, *(S + 2 * (*t)), *(S + 2 * (*t) + 1));
	(*t)--;

}

void dequeue(char* Q, int q, int* f, int* r, char* S, int s, int* t) {

	if (*f == *r) return;

	*f = (*f + 1) % q;

	if (*(Q + (*f * 2) + 1) == 0) {
		printf(" %c", *(Q + (*f * 2)));
		return;
	}

	else {

		push(S, s, t, *(Q + (*f * 2)), *(Q + (*f * 2) + 1) - 1);
		return;

	}

}

void main() {

	char* Q, * S, c;
	int f = 0, r = 0, t = -1;
	int i, q, s, n, v;

	scanf("%d%d", &q, &s);

	Q = (char*)malloc((q * 2) * sizeof(char));
	S = (char*)malloc((s * 2) * sizeof(char));

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {

		scanf("%c", &c);
		scanf("%d", &v);
		getchar();

		enqueue(Q, q, &f, &r, c, v);

	}

	for (;;) {
		if ((f + 1) % q == r) {
			break;
		}
		for (;;) {
			if ((f+1) % q == r) {
				break;
			}
			dequeue(Q, q, &f, &r, S, s, &t);
		}

		for (;t!=-1;) {
			pop(S, s, &t, Q, q, &f, &r);
		}

	}






	free(Q);
	free(S);

}

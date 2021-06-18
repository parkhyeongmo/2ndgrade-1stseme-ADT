// ���� IP �ּ� : 125.178.152.237
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // ť�� ������ ������ �迭�� ���� ����ü
	char c;
	int rank;
}NODE;

void push(NODE* S, int sc, int* t, char c, int v) { // ���ÿ� ������ �Է��ϴ� �Լ�

	if ((*t + 1) == sc) return; // ���� ��ȭ ���·� ���� ���� ó��

	(*t)++; // t�� 1 ������Ų �� ���� �Է�

	(S + *t)->c = c;
	(S + *t)->rank = v;

}

void enqueue(NODE* Q, int qc, int* f, int* r, char c, int v) { // ť�� ������ �Է��ϴ� �Լ�

	if ((*r + 1) % qc == *f) return; // queue ��ȭ ���·� ���� ���� ó��

	(*r) = (*r + 1) % qc; // r�� 1 ������Ų �� ���� �Է�
	
	(Q + *r)->c = c;
	(Q + *r)->rank = v;

}

NODE pop(NODE* S, int s, int* t) {

	NODE tmp; // ��ȯ�� ������ ������ ����ü ����

	tmp.c = (S + *t)->c; // ��ȯ�� ������ ������ ����ü�� ���� �Է�
	tmp.rank = (S + *t)->rank;

	(*t)--; // t�� 1 ���ҽ��� ������ top �ֽ�ȭ

	return tmp; // ������ ���� t�� ��ġ�� �ִ� ���� ��ȯ

}

NODE dequeue(NODE* Q, int qc, int* f, int* r) {

	NODE tmp; // ��ȯ�� ������ ������ ����ü ����

	*f = (*f + 1) % qc; // f�� 1 �������� front �ֽ�ȭ

	tmp.c = (Q + *f)->c; // ��ȯ�� ������ ������ ����ü�� ���� �Է�
	tmp.rank = (Q + *f)->rank;

	return tmp; // ť�� front ���� ��ȯ

}

int is_queue_empty(int f, int r) { // ť�� ����ִ� ���¸� 1�� ��ȯ�ϴ� �Լ�
	if (f == r)	return 1;
	else return 0;
}

int is_stack_empty(int t) { // ������ ����ִ� ���¸� 1�� ��ȯ�ϴ� �Լ�
	if (t == -1) return 1;
	else return 0;
}


void main() {

	NODE* Q, * S, tmp;
	int qc, sc, t = -1, f = 0, r = 0, i, j, n;
	char c;

	scanf("%d", &sc); // ������ �迭 ũ�� �Է� �� �����Ҵ�
	S = (NODE*)malloc(sc * sizeof(NODE));
	
	scanf("%d", &qc); // ť�� �迭 ũ�� �Է� �� �����Ҵ�
	Q = (NODE*)malloc(qc * sizeof(NODE));

	scanf("%d", &n); // �۾� Ƚ�� �Է�
	getchar();

	for (i = 0; i < n; i++) {

		scanf("%c %d", &c, &j); // �۾� ID�� �켱���� �Է�
		getchar();

		enqueue(Q, qc, &f, &r, c, j); // �Է� ���� ���� ť�� �Է�
		
	}

	while (is_queue_empty(f, r) != 1) {

		tmp = dequeue(Q, qc, &f, &r); // ť�� front�� �ִ� ������ ��ȯ�ް� ť���� ����

		if (tmp.rank == 0) { // ��ȯ ���� ������ �켱������ 0�̸� ��� �� ���� �ܰ�� ����
			printf(" %c", tmp.c);
		}

		else { // �켱������ 0�� �ƴ� ��� ���ÿ� push
			push(S, sc, &t, tmp.c, tmp.rank - 1);
		}

	}

	while (is_stack_empty(t) != 1) {

		tmp = pop(S, sc, &t); // ������ top�� �ִ� ������ ��ȯ�ް� ���ÿ��� ����

		enqueue(Q, qc, &f, &r, tmp.c, tmp.rank); // ��ȯ ���� ������ ť�� enqueue

	}

	while (is_queue_empty(f, r) != 1) {

		tmp = dequeue(Q, qc, &f, &r); // ť�� front�� �ִ� ������ ��ȯ�ް� ť���� ����

		if (tmp.rank == 0) { // ��ȯ ���� ������ �켱������ 0�̸� ��� �� ���� �ܰ�� ����
			printf(" %c", tmp.c);
		}

		else { // �켱������ 0�� �ƴ� ��� ť�� enqueue
			enqueue(Q, qc, &f, &r, tmp.c, tmp.rank - 1);
		}

	}

	

	free(Q); // ť�� ���� �迭�� ���� �޸� �Ҵ� ����
	free(S);

}

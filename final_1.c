// 나의 IP 주소 : 125.178.152.237
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // 큐와 스택을 구현할 배열에 사용될 구조체
	char c;
	int rank;
}NODE;

void push(NODE* S, int sc, int* t, char c, int v) { // 스택에 정보를 입력하는 함수

	if ((*t + 1) == sc) return; // 스택 포화 상태로 인한 예외 처리

	(*t)++; // t를 1 증가시킨 후 정보 입력

	(S + *t)->c = c;
	(S + *t)->rank = v;

}

void enqueue(NODE* Q, int qc, int* f, int* r, char c, int v) { // 큐에 정보를 입력하는 함수

	if ((*r + 1) % qc == *f) return; // queue 포화 상태로 인한 예외 처리

	(*r) = (*r + 1) % qc; // r을 1 증가시킨 후 정보 입력
	
	(Q + *r)->c = c;
	(Q + *r)->rank = v;

}

NODE pop(NODE* S, int s, int* t) {

	NODE tmp; // 반환할 정보를 저장할 구조체 선언

	tmp.c = (S + *t)->c; // 반환할 정보를 저장할 구조체에 정보 입력
	tmp.rank = (S + *t)->rank;

	(*t)--; // t를 1 감소시켜 스택의 top 최신화

	return tmp; // 스택의 원래 t의 위치에 있던 정보 반환

}

NODE dequeue(NODE* Q, int qc, int* f, int* r) {

	NODE tmp; // 반환할 정보를 저장할 구조체 선언

	*f = (*f + 1) % qc; // f를 1 증가시켜 front 최신화

	tmp.c = (Q + *f)->c; // 반환할 정보를 저장할 구조체에 정보 입력
	tmp.rank = (Q + *f)->rank;

	return tmp; // 큐의 front 정보 반환

}

int is_queue_empty(int f, int r) { // 큐가 비어있는 상태면 1을 반환하는 함수
	if (f == r)	return 1;
	else return 0;
}

int is_stack_empty(int t) { // 스택이 비어있는 상태면 1을 반환하는 함수
	if (t == -1) return 1;
	else return 0;
}


void main() {

	NODE* Q, * S, tmp;
	int qc, sc, t = -1, f = 0, r = 0, i, j, n;
	char c;

	scanf("%d", &sc); // 스택의 배열 크기 입력 후 동적할당
	S = (NODE*)malloc(sc * sizeof(NODE));
	
	scanf("%d", &qc); // 큐의 배열 크기 입력 후 동적할당
	Q = (NODE*)malloc(qc * sizeof(NODE));

	scanf("%d", &n); // 작업 횟수 입력
	getchar();

	for (i = 0; i < n; i++) {

		scanf("%c %d", &c, &j); // 작업 ID와 우선순위 입력
		getchar();

		enqueue(Q, qc, &f, &r, c, j); // 입력 받은 정보 큐에 입력
		
	}

	while (is_queue_empty(f, r) != 1) {

		tmp = dequeue(Q, qc, &f, &r); // 큐의 front에 있는 정보를 반환받고 큐에서 삭제

		if (tmp.rank == 0) { // 반환 받은 정보의 우선순위가 0이면 출력 후 다음 단계로 진행
			printf(" %c", tmp.c);
		}

		else { // 우선순위가 0이 아닐 경우 스택에 push
			push(S, sc, &t, tmp.c, tmp.rank - 1);
		}

	}

	while (is_stack_empty(t) != 1) {

		tmp = pop(S, sc, &t); // 스택의 top에 있는 정보를 반환받고 스택에서 삭제

		enqueue(Q, qc, &f, &r, tmp.c, tmp.rank); // 반환 받은 정보를 큐에 enqueue

	}

	while (is_queue_empty(f, r) != 1) {

		tmp = dequeue(Q, qc, &f, &r); // 큐의 front에 있는 정보를 반환받고 큐에서 삭제

		if (tmp.rank == 0) { // 반환 받은 정보의 우선순위가 0이면 출력 후 다음 단계로 진행
			printf(" %c", tmp.c);
		}

		else { // 우선순위가 0이 아닐 경우 큐에 enqueue
			enqueue(Q, qc, &f, &r, tmp.c, tmp.rank - 1);
		}

	}

	

	free(Q); // 큐와 스택 배열에 사용된 메모리 할당 해제
	free(S);

}

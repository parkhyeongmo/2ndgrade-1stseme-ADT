#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 노드로 사용할 구조체 선언

	int elem;
	struct node* next;

}Node;

Node* getnode();
void appendTerm();
int subset();

void main() {

	Node* A = NULL, * B = NULL, * k, *ptrn;
	int i, n, num;

	scanf("%d", &num); // 집합 A에 들어갈 원소의 수 입력

	if (num > 0) { // 공집합이 아닌 경우 첫번째 노드를 할당하고 원소 입력
		A = getnode();
		k = A;
		scanf("%d", &n);
		k->elem = n;
	}

	for (i = 1; i < num; i++) { // 이후 남은 개수만큼 원소 입력

		scanf("%d", &n);

		appendelem(&k, n);

	}

	scanf("%d", &num); // 집합 B에 들어갈 원소의 수 입력

	if (num > 0) { // 공집합이 아닌 경우 첫번째 노드를 할당하고 원소 입력
		B = getnode();
		k = B;
		scanf("%d", &n);
		k->elem = n;
	}

	for (i = 1; i < num; i++) { // 이후 남은 개수만큼 원소 입력

		scanf("%d", &n);

		appendelem(&k, n);

	}

	printf("%d", subset(A, B)); // 함수 호출 및 출력

	for (k = A; k != NULL;) { // 메모리 할당 해제

		ptrn = k->next;
		free(k);
		k = ptrn;

	}

	for (k = B; k != NULL;) {

		ptrn = k->next;
		free(k);
		k = ptrn;

	}

}

Node* getnode() { // 새로운 노드를 동적할당 받을때 사용하는 getnode 함수

	Node* new;

	new = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적할당

	new->next = NULL; // next를 NULL로 초기화

	return new; // 새로 할당된 노드 주소 반환

}

void appendelem(Node** k, int n) { // 집합 연결리스트에 새로운 원소를 입력하는 함수

	Node* new;

	new = getnode(); // 새로운 노드를 할당 받는다

	new->elem = n; // 새로운 노드에 원소 값 입력

	(*k)->next = new; // 원래 마지막 순서인 노드에 next에 연결
	*k = new; // 마지막 순서를 새로운 노드로 바꿔준다.

}

int subset(Node* A, Node* B) { // 두 집합의 부분집합 여부를 확인하는 함수

	Node* pa,* pb;

	if (A == NULL) return 0; // 공집합은 모든 집합의 부분집합이므로 A가 공집합이면 바로 0 반환

	pa = A;
	pb = B;

	for (; pb != NULL; pb = pb->next) { // 두 집합의 원소들을 비교하며 포인터를 이동시키다가 A의 모든 원소가 B에 포함되어 NULL에 도달할 경우 부분집합이므로 0 반환

		if (pb->elem == pa->elem) {
			pa = pa->next;
		}

		if (pa == NULL) return 0;

	}

	
	return pa->elem; // A가 B의 부분집합이 아닐 경우 마지막으로 포함되던 원소 이후로 더 이상 포인터가 이동하지 않았으므로 B에 속하지 않은 A의 가장 작은 원소 반환

}
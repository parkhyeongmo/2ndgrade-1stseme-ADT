#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // 트리에 사용될 노드의 구조체
	int id;
	struct node* left, * right;
}NODE;

typedef struct tnode { // 트리의 정보를 입력 받는 연결리스트에 사용될 노드의 구조체

	int id, left, right;
	struct tnode* prev,* next;

}tNODE;

NODE* getnode();
tNODE* gettnode();
NODE* makeTree();
tNODE* findRoot();
tNODE* findNode();
void treeFree();
void print();

void main() {

	int i, j, n, id, left, right;
	NODE* R;
	tNODE* H,* T,* t,* tp;
	char s[101];

	scanf("%d", &n); // 노드의 개수 입력

	H = gettnode(0, 0, 0); // 정보를 입력 받을 연결리스트의 헤더 노드와 트레일러 노드 초기화
	T = gettnode(0, 0, 0);

	H->next = T;
	T->prev = H;
	

	for (i = 0; i < n; i++) { // n개의 노드 정보를 연결리스트에 입력

		scanf("%d%d%d", &id, &left, &right);

		t = gettnode(id, left, right);

		t->prev = T->prev;
		t->next = T;

		T->prev->next = t;
		T->prev = t;

	}

	t = findRoot(H, T); // 연결리스트에서 트리의 루트 탐색

	R = makeTree(t, H, T); // 루트 노드의 정보를 바탕으로 트리 구축

	for (t = H; t != NULL;) { // 연결리스트에 사용된 메모리 할당 해제
	
		tp = t->next;
		free(t);
		t = tp;

	}

	scanf("%d", &n); // 출력 횟수 입력

	for (i = 0; i < n; i++) { // n회 반복하며 출력

		scanf("%s", s); // 탐색 정보 입력

		print(R, s); // print 함수 호출

	}

	treeFree(R); // 메모리 할당 해제

}

tNODE* gettnode(int id, int left, int right) { // 연결리스트의 노드를 새로 만드는 함수

	tNODE* newnode;

	newnode = (tNODE*)malloc(sizeof(tNODE)); // 새로운 노드를 동적 할당 받아 전달 받은 값으로 초기화
	newnode->id = id;
	newnode->left = left;
	newnode->right = right;
	newnode->prev = newnode->next = NULL;

	return newnode; // 새로운 노드 주소 반환

}

tNODE* findRoot(tNODE* H, tNODE* T) { // 입력 받은 정보를 바탕으로 트리의 루트를 찾는 함수

	tNODE* t,* p;
	int id;
	
	for (t = H->next; t != T; t = t->next) { // 연결리스트의 처음부터 끝까지 탐색

		id = t->id;

		for (p = H->next; p != T; p = p->next) { // 해당 순서의 id가 다른 노드의 left나 right에서 발견될 경우 break
			if (id == p->left || id == p->right) {
				break;
			}
		}

		if (p == T) { // 해당 순서의 id가 다른 노드의 left나 right가 아닐 경우 트리 최상단의 루트 노드이므로 break
			break;
		}

	}

	return t; // 루트 반환

}

tNODE* findNode(int n, tNODE* H, tNODE* T) { // 연결리스트에서 특정 id를 가진 노드를 찾는 함수

	tNODE* t;

	for (t = H->next; t != T; t = t->next) { // 연결리스트의 처음부터 순회하다 발견시 break 후 반환

		if (t->id == n) break;

	}

	return t;

}

NODE* getnode(int id) { // 새로운 노드를 만드는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE)); // 새로운 노드를 동적할당하여 id 입력 후 left, right를 NULL로 초기화
	newnode->id = id;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode; // 새로운 노드 반환

}

NODE* makeTree(tNODE* v, tNODE* H, tNODE* T) { // 루트 노드의 정보를 담은 tNODE와 연결리스트를 바탕으로 트리를 구축하는 함수

	NODE* n;
	tNODE* t;

	n = getnode(v->id); // 해당 순서의 id를 가진 노드를 생성

	if (v->left != 0) { // 왼쪽 자식 노드가 있을 경우 연결리스트 탐색 후 다시 함수 호출

		t = findNode(v->left, H, T);

		n->left = makeTree(t, H, T);

	}

	if (v->right != 0) { // 오른쪽 자식 노드가 있을 경우 연결리스트 탐색 후 다시 함수 호출

		t = findNode(v->right, H, T);

		n->right = makeTree(t, H, T);

	}

	return n; // 해당 순서에서 생성된 노드 반환

}

void treeFree(NODE* F) { // 후위순회로 트리의 메모리 할당 해제

	if (F->left != NULL) { // 왼쪽 자식 노드가 NULL이 아닌 경우 다시 호출
		treeFree(F->left);
	}

	if (F->right != NULL) { // 오른쪽 자식 노드가 NULL이 아닌 경우 다시 호출
		treeFree(F->right);
	}

	free(F); // 외부노드에 도달하거나 자손노드이 모두 free되면 해당 노드 메모리 할당해제

}

void print(NODE* T, char* S) { // 입력 받은 탐색 정보를 바탕으로 트리 내부 정보를 출력하는 함수
	
	printf(" %d", T->id); // 해당 순서의 노드 id 출력

	if (*S == 'L') { // 탐색 정보의 다음이 L일 경우 왼쪽 자식 노드로 print 함수 다시 호출
		print(T->left, S + 1);
	}
	else if (*S == 'R') { // 탐색 정보의 다음이 R일 경우 오른쪽 자식 노드로 print 함수 다시 호출
		print(T->right, S + 1);
	}

	else if (*S == NULL) { // 탐색 정보의 문자열이 끝났을 경우 개행 후 종료
		printf("\n");
		return;
	}

}
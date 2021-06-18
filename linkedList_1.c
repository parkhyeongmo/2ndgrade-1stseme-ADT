#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE { // NODE로 사용할 구조체 선언

	struct NODE* pre; // 이전 순서의 노드를 가리키는 포인터
	struct NODE* next; // 다음 순서의 노드를 가리키는 포인터
	char elem; // 노드의 원소

}NODE;

NODE* init() { // 연결리스트 초기화 함수

	NODE* header, * trailer;

	header = (NODE*)malloc(sizeof(NODE)); // 헤더 노드와 트레일러 노드 동적할당
	trailer = (NODE*)malloc(sizeof(NODE));

	header->next = trailer; // 헤더 노드와 트레일러 노드를 연결
	trailer->pre = header;
	header->pre = NULL; // 헤더 노드의 pre 포인터에 NULL 입력
	trailer->next = NULL; // 트레일러 노드의 next 포인터에 NULL 입력

	return header; // 리스트의 시작 부분인 헤더 노드의 주소 반환

}

void add(NODE* L, int num, char new, int* n) { // 연결리스트에 새로운 원소를 가지는 노드를 지정한 순위에 추가하는 함수

	NODE* newnode, * p, * q;
	int i;

	p = L; // 두개의 포인터로 해당 순서의 노드와 그 이전 순서의 노드를 찾는데 사용할 포인터 초기화
	q = L->next;

	newnode = (NODE*)malloc(sizeof(NODE)); // 새로운 노드 동적할당 후 elem에 원소 입력
	newnode->elem = new;

	for (i = 0; i < num - 1; i++) { // 새로 추가될 위치까지 p와 q의 위치 이동
		p = p->next;
		q = p->next;
	}

	p->next = newnode; // p와 q 사이에 새로운 노드 추가
	newnode->pre = p;
	q->pre = newnode;
	newnode->next = q;

	*n = *n + 1; // 연결리스트의 총 노드의 수를 나타내는 n에 1을 더해준다

}

void delete(NODE* L, int num, int* n) { // 연결리스트에서 지정한 순위의 노드를 삭제하는 함수

	NODE* p, * q, * del;
	int i;

	p = L; // 삭제하는 노드의 위치를 찾기 위해 p, q, del 포인터를 연결리스트의 첫 부분을 가리키게 함
	del = L->next;
	q = del->next;

	for (i = 1; i < num; i++) { // del 포인터에 삭제될 노드 주소를 초기화하고 그 이전과 그 다음 노드를 각각 p와 q가 가리키게 함

		p = p->next;
		del = del->next;
		q = q->next;

	}

	p->next = q; // 삭제되는 노드를 제외하고 p와 q가 가리키는 노드를 연결
	q->pre = p;

	free(del); // 삭제된 노드 메모리 할당 해제

	*n = *n - 1; // 노드가 하나 줄었기 때문에 n에서 1을 빼준다

}

char get(NODE* L, int n) { // 연결리스트에서 지정한 순위의 노드가 가진 원소를 반환하는 함수

	int i = 1;
	NODE* ptr;

	ptr = L->next; // 연결리스트에서 지정한 순위의 노드까지 이동하기 위해 ptr 포인터에 연결리스트의 첫번째 노드 연결

	while (1) {

		if (i == n) { // 지정한 순위를 가리키게 되면 반복문 종료
			break;
		}

		i++; // 첫번째 노드부터 n번째 노드가 될때까지 ptr을 다음 노드로 옮겨가며 반복
		ptr = ptr->next;

	}

	return ptr->elem; // 지정한 순위의 노드가 가진 원소 반환

}

void print(NODE* L) { // 연결리스트의 모든 원소들을 저장 순위대로 출력

	NODE* ptr;

	ptr = L->next; // ptr 포인터를 연결리스트의 첫번째 노드에 연결

	for (; ptr->next != NULL;) { // 트레일러 노드가 나올때까지 각 노드가 가진 원소들을 출력

		printf("%c", ptr->elem);

		ptr = ptr->next; // 출력 후 다음 노드로 ptr 포인터 이동

	}

}


void main() {

	NODE* L, *ptr, *ptrn;
	int n = 0, i, j, ctrl;
	char order, alpha;

	L = init(); // 연결리스트 초기화

	scanf("%d", &j); // 몇 번의 명령을 받을지 입력
	getchar();

	for (i = 0; i < j; i++) { // 위에서 입력한 수만큼 반복하며 연산

		scanf("%c", &order); // 해당 회차에서 무슨 명령을 내릴지 입력
		getchar();

		if (order == 'A') { // 'A'가 입력 될 경우 지정할 순위와 추가할 원소 입력

			scanf("%d %c", &ctrl, &alpha);
			getchar();

			if (ctrl > n + 1) { // 지정된 순위가 연결리스트의 총 크기보다 클 경우 유효하지 않은 위치라는 경고문 출력 후 다음 회차로 진행
				printf("invalid position\n");
				continue;
			}

			add(L, ctrl, alpha, &n); // 유효한 순위가 지정되면 add 함수 호출

		}

		else if (order == 'D') { // 'D'가 입력 될 경우 지정할 순위 입력

			scanf("%d", &ctrl);
			getchar();

			if (ctrl > n) { // 지정된 순위가 연결리스트의 총 크기보다 클 경우 유효하지 않은 위치라는 경고문 출력 후 다음 회차로 진행
				printf("invalid position\n");
				continue;
			}

			delete(L, ctrl, &n); // 유효한 순위가 지정되면 delete 함수 호출

		}

		else if (order == 'G') { // 'G'가 입력 될 경우 지정할 순위 입력

			scanf("%d", &ctrl);
			getchar();

			if (ctrl > n) { // 지정된 순위가 연결리스트의 총 크기보다 클 경우 유효하지 않은 위치라는 경고문 출력 후 다음 회차로 진행
				printf("invalid position\n");
				continue;
			}

			printf("%c", get(L, ctrl)); // 유효한 순위가 지정되면 get 함수 호출 후 반환 받은 원소를 출력

		}

		else if (order == 'P') { // 'P'가 입력 될 경우 print 함수를 호출

			if (n == 0) continue; // 비어있는 연결리스트의 경우 함수 호출 없이 다음 회차로 진행

			print(L);

		}

	}

	ptr = L; // ptr 포인터가 연결리스트를 가리키게 함

	for (; ptr->next != NULL;) { // 헤더 노드부터 트레일러 노드 직전까지 옮겨가며 메모리 할당 해제
	
		ptrn = ptr->next;
		free(ptr);
		ptr = ptrn;
	
	}

	free(ptr); // 마지막으로 트레일러 노드 메모리 할당 해제

}
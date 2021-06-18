#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct mono { // 다항식의 각 항으로 사용될 노드 선언

	int coef; // 항의 계수
	int exp; // 항의 차수
	struct mono* next; // 다음 노드를 가리키는 링크

}Mono;

struct mono* getnode();
Mono* init();
void appendTerm();
Mono* addPoly();

void main() {

	Mono* X,* Y,* R,* ptr, * ptrn;
	int i, cnt, c, e;

	X = init(); // 연산에 사용할 두 연결리스트 초기화
	Y = init();

	scanf("%d", &cnt); // 첫 번째 다항식의 항의 개수 입력

	ptr = X;

	for (i = 0; i < cnt; i++) { // 첫 번째 다항식 입력

		scanf("%d%d", &c, &e);
		appendTerm(&ptr, c, e);

	}

	scanf("%d", &cnt); // 두 번째 다항식의 항의 개수 입력

	ptr = Y;

	for (i = 0; i < cnt; i++) { // 두 번째 다항식 입력

		scanf("%d%d", &c, &e);
		appendTerm(&ptr, c, e);

	}

	R = addPoly(X, Y); // addPoly 함수 호출

	for (ptr = R->next; ptr != NULL; ptr = ptr->next) { // 연산 결과 출력

		printf(" %d %d", ptr->coef, ptr->exp);

	}

	for (ptr = X;ptr != NULL;) { // 프로그램에 사용된 연결리스트 X, Y, R 메모리 할당 해제
		ptrn = ptr->next;
		free(ptr);
		ptr = ptrn;
	}

	for (ptr = Y; ptr != NULL;) {
		ptrn = ptr->next;
		free(ptr);
		ptr = ptrn;
	}

	for (ptr = R; ptr != NULL;) {
		ptrn = ptr->next;
		free(ptr);
		ptr = ptrn;
	}

}

struct mono* getnode() { // 새로운 노드를 동적할당 받을때 사용하는 getnode 함수

	Mono* new;

	new = (Mono*)malloc(sizeof(Mono)); // 새로운 노드 동적할당

	new->next = NULL; // next를 NULL로 초기화

	return new; // 새로 할당된 노드 주소 반환

}

Mono* init() { // 새로운 연결리스트를 초기화하는 init 함수

	Mono* header;

	header = getnode(); // header를 동적할당

	return header;// 헤더 단일연결리스트이기 때문에 header의 주소 반환

}

void appendTerm(Mono** k, int c, int e) { // 다항식을 표현하는 연결리스트에 새로운 항을 붙이는 함수

	Mono* t;

	t = getnode(); // 새로운 항 동적할당

	t->coef = c; // 계수를 뜻하는 c를 새로운 항의 계수로 입력
	t->exp = e; // 차수를 뜻하는 e를 새로운 항의 차수로 입력

	(*k)->next = t; // 기존 마지막 항의 next에 새로운 노드의 주소 입력
	*k = t; // 다항식의 마지막 항을 가리키는 k 포인터를 새로운 노드 주소로 변경, 주소 값을 함수 밖에서도 변경된 상태로 유지해야하기 때문에 함수 인자를 이중포인터로 받아 내부에서 변경하여 준다.

}

Mono* addPoly(Mono* X, Mono* Y) { // 두 다항식을 더해주는 함수

	Mono* R,* ptr, * i,* j;
	int sum;

	R = init(); // 결과 값을 저장할 새로운 연결리스트 초기화
	
	ptr = R;
	i = X->next;
	j = Y->next;
	
	while (i != NULL && j != NULL) { // 두 다항식 중 하나라도 마지막 항까지의 연산이 끝날때까지 반복

		if (i->exp > j->exp) { // 해당 차례의 X 다항식의 차수가 Y 다항식의 차수보다 클때 X 다항식의 항을 R 연결리스트에 추가
			appendTerm(&ptr, i->coef, i->exp);
			i = i->next; // 해당 차례의 연산이 끝나면 포인터를 다음 차수의 항으로 넘겨준다.
		}

		else if(i->exp < j->exp) { // 해당 차례의 Y 다항식의 차수가 X 다항식의 차수보다 클때 Y 다항식의 항을 R 연결리스트에 추가
			appendTerm(&ptr, j->coef, j->exp);
			j = j->next; // 해당 차례의 연산이 끝나면 포인터를 다음 차수의 항으로 넘겨준다.
		}

		else { // X 다항식의 항과 Y 다항식에서의 항의 차수가 같을 때 두 항의 계수를 더하여 0이 아닐시 R 연결리스트에 추가
			sum = i->coef + j->coef;

			if (sum != 0){
				appendTerm(&ptr, sum, i->exp);				
			}

			i = i->next; // 두 다항식 모두 다음 차수로 포인터를 옮겨 준다.
			j = j->next;
		}

	}

	while (i != NULL) { // Y 다항식이 먼저 끝나 X 다항식의 항이 남아있을 경우 나머지를 R 연결리스트에 포함시킨다.

		appendTerm(&ptr, i->coef, i->exp);
		i = i->next;

	}

	while (j != NULL) { // X 다항식이 먼저 끝나 Y 다항식의 항이 남아있을 경우 나머지를 R 연결리스트에 포함시킨다.

		appendTerm(&ptr, j->coef, j->exp);
		j = j->next;

	}

	return R; // X와 Y 다항식이 합쳐진 R 다항식을 반환

}
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	char c;
	int p;
	struct node* next;

}NODE;

NODE* getnode() {

	NODE* newnode;
	newnode = (NODE*)malloc(sizeof(NODE));

	return newnode;

}

void push(NODE** S, char c, int p) { // 스택의 top에 새로운 데이터를 추가하는 함수	

	NODE* newnode;

	newnode = getnode();
	newnode->next = *S;
	newnode->c = c;
	newnode->p = p;

	*S = newnode;

}

char pop(NODE** S) { // 스택의 top에 있는 데이터를 반환하고 제거하는 함수

	char tc;
	NODE* tmp;

	if (*S == NULL) {
		return -1;
	}

	tmp = *S;
	tc = (*S)->c;

	*S = (*S)->next;

	free(tmp);

	return tc;

}

int P(char c) { // 연산자 우선순위를 판별하는 함수

	if (c == '!') return 6;
	else if (c == '*' || c == '/') return 5;
	else if (c == '+' || c == '-') return 4;
	else if (c == '>' || c == '<') return 3;
	else if (c == '&') return 2;
	else if (c == '|') return 1;
	else if (c == '(') return 0;

}

void convert(char* a) { // 문자열로 입력받은 중위수식을 후위수식으로 출력하는 함수

	NODE* S = NULL, * p, * q;
	char c;
	int i, n, ctr = 0;


	n = strlen(a);

	for (i = 0; i < n; i++) { // 문자열의 끝까지 진행하며 후위수식으로 변환

		if (*(a + i) >= 'A' && *(a + i) <= 'Z') { // 해당 차례의 문자가 피연산자일 경우 그대로 출력

			printf("%c", *(a + i));

		}

		else if (*(a + i) == '(') { // 괄호가 열리면 스택에 push

			push(&S, '(', P('('));

		}

		else if (*(a + i) == ')') { // 괄호가 닫히면 열리는 괄호 이후 나온 피연산자들을 모두 pop하며 출력

			while (S->c != '(') {

				c = pop(&S);
				printf("%c", c);

				if (c == '&') printf("%c", c); // &&과 ||의 경우 연산의 간편화를 위해 &와 |로 하나만 저장했기 때문에 하나 더 출력해준다.
				else if (c == '|') printf("%c", c);

			}

			pop(&S); // 열리는 괄호 pop

		}

		else { // 피연산자와 괄호가 아닌 연산자

			if (*(a + i) == '&' && *(a + i - 1) == '&') { // &&의 경우 & 하나만 저장하므로 continue 해준다.
				continue;
			}
			else if (*(a + i) == '|' && *(a + i - 1) == '|') { // ||의 경우 | 하나만 저장하므로 continue 해준다.
				continue;
			}

			if (*a == '+' && i == 0) { // 첫 번째 문자가 단항연산자 '+'일 경우 스택에 단항연산자 '+'를 push 해준 뒤 continue
				push(&S, '+', 6);
				continue;
			}			
			else if (*a == '-' && i == 0) { // 첫 번째 문자가 단항연산자 '-'일 경우 스택에 단항연산자 '-'를 push 해준 뒤 continue
				push(&S, '-', 6);
				continue;
			}

			if (*(a + i) == '-' && (*(a + i - 1) < 'A' || *(a + i - 1) > 'Z') && *(a + i - 1) != ')') { // 첫 번째 문자가 아닌 곳에서 단항연산자 '-'가 나오면 스택에 push 후 continue
				push(&S, '-', 6);
				continue;
			}
			else if (*(a + i) == '+' && (*(a + i - 1) < 'A' || *(a + i - 1) > 'Z') && *(a + i - 1) != ')') { // 첫 번째 문자가 아닌 곳에서 단항연산자 '+'가 나오면 스택에 push 후 continue
				push(&S, '+', 6);
				continue;
			}			

			if (*(a + i - 1) == '-' && (S->p == 6) && *(a + i) == '!') { // 단항연산자 '-' 이후 '!'가 나왔을 경우 스택에 '!'를 push
				push(&S, '!', 6);
				continue;
			}
			else if (*(a + i - 1) == '+' && (S->p == 6) && *(a + i) == '!') { // 단항연산자 '+' 이후 '!'가 나왔을 경우 스택에 '!'를 push
				push(&S, '!', 6);
				continue;
			}
			
			while (S != NULL && P(*(a + i)) <= S->p) { // 스택에 다른 연산자가 들어있을 경우 해당 차례의 문자보다 우선순위가 높은 연산자들을 pop하여 출력

				c = pop(&S);
				printf("%c", c);

				if (c == '&') printf("%c", c); // &&과 ||의 경우 연산의 간편화를 위해 &와 |로 하나만 저장했기 때문에 하나 더 출력해준다.
				else if (c == '|') printf("%c", c);

			}

			push(&S, *(a + i), P(*(a + i))); // 연산자의 출력이 끝나면 해당 차례의 연산자를 스택에 push

		}

	}

	while (S != NULL) { // 중위수식의 끝까지 출력한 뒤 스택에 남아있는 연산자를 모두 pop하여 출력

		c = pop(&S);
		if (c == '(') continue;
		printf("%c", c);

		if (c == '&') printf("%c", c); // &&과 ||의 경우 연산의 간편화를 위해 &와 |로 하나만 저장했기 때문에 하나 더 출력해준다.
		else if (c == '|') printf("%c", c);

	}

	printf("\n");

	for (p = S; p != NULL;) { // 스택 메모리 할당 해제

		q = p->next;
		free(p);
		p = q;

	}

}

void main() {

	char a[101];
	int n, i;

	scanf("%d", &n); // 시행 횟수 입력
	getchar();

	for (i = 0; i < n; i++) { // 입력 받은 횟수만큼 반복 시행

		scanf("%s", a); // 중위수식 문자열 입력
		getchar();

		convert(a); // convert 함수 호출

	}

}
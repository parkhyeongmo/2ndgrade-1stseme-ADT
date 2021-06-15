#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push();
char pop();
int isBalanced();

void main() {

	int i, max;
	char str[1000];
	
	scanf("%s", str);

	max = isBalanced(str);

	if (max != -1) {
		printf("%d\n", max);
	}

}


void push(char* S, int* t, char e) {

	(*t)++;
	*(S + *t) = e;	

}

char pop(char* S, int* t) {

	char tmp;

	tmp = *(S + *t);

	(*t)--;

	return tmp;

}

int isBalanced(char* str) {

	int i, l, max = 0, n = 0, cnt = 0, t = -1;
	char S[1000];

	l = strlen(str);

	for (i = 0; i < l; i++) {

		if (l == 1) break;

		if (*(str + i) == '(' || *(str + i) == '{' || *(str + i) == '[') {
			push(S, &t, *(str + i));
			cnt++;
		}

		else if (t != -1 && *(str + i) != ')' && *(str + i) != '}' && *(str + i) != ']') {
			push(S, &t, *(str + i));
			
		}

		else if(*(str + i) == ')' || *(str + i) == '}' || *(str + i) == ']') {

			for (;;) {

				if (S[t] == '(' || S[t]== '{' || S[t]== '[') {
					break;
				}
				pop(S, &t);
				n++;
			}

			if (*(str + i) == ')' && S[t] == '(') {
				pop(S, &t);
				cnt++;
				if (t != -1) n += 2;
			}
			else if (*(str + i) == '}' && S[t] == '{') {
				pop(S, &t);
				cnt++;
				if (t != -1) n += 2;
			}
			else if (*(str + i) == ']' && S[t] == '[') {
				pop(S, &t);
				cnt++;
				if (t != -1) n += 2;
			}

			
			if (n > max) max = n;
			if (t == -1) n = 0;

			
		}
	}

	/*for (;t != -1;) {

		if (S[t] == '(' || S[t] == '{' || S[t] == '[') break;

		pop(S, &t);

	}*/

	if (t == -1) printf("OK_%d\n", cnt);
	else printf("Wrong_%d\n", cnt);
	
	if (t == -1) return max;
	else return -1;

}
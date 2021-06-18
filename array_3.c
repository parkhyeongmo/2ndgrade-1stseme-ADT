#pragma warning(disable:4996)
#include <stdio.h>

void insert(int N) { // 이차원 배열을 반환하기 위해 int형 이중포인터를 반환하는 함수 선언

	int A[100][100], n, i = 0, j = 0;

	for (n = 1; n <= (N * N); n++) { // 숫자를 1부터 N*N까지 입력한다.

		if (i % 2 == 0) { // 짝수행의 경우 정방향으로 숫자를 입력한다.
			A[i][j] = n;
			j++;
		}

		else { // 홀수행의 경우 역방향으로 숫자를 입력한다.
			A[i][j] = n;
			j--;
		}

		if (j < 0) { // 홀수행에서 역방향으로 진행중 배열의 첫번째 열에 도달할 경우 i와 j를 +1 해준다.
			i++;
			j++;
		}

		if (j > N - 1) { // 짝수행에서 정방향으로 진행중 배열의 마지막 열에 도달할 경우 i를 +1 해주고 배열의 최대크기를 벗어난 j를 -1 해준다.
			i++;
			j--;
		}

	}

	for (i = 0; i < N; i++) { // 행렬 출력
	
		for (j = 0; j < N; j++) {
			printf(" %d", A[i][j]);
		}
		
		printf("\n");
		
	}

}

void main() {

	int N, i, j;

	scanf("%d", &N); // 행렬의 크기인 정수 N을 입력 받는다.

	insert(N); // insert 함수 호출

}


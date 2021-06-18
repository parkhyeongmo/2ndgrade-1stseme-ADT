#pragma warning(disable:4996)
#include <stdio.h>

void check();

void main() {

	int N, M; 

	scanf("%d%d", &N, &M); // 행렬의 크기를 정할 정수 N과 M을 입력
	
	check(N, M); // 함수 호출

}

void check(int N, int M) {

	int a[100][100] = { 0, }, i = 0, j = 0, n = 1, cntj = 0;

	for (n = 1; n <= N * M;) { // 1부터 N*M까지의 숫자를 채울때까지 반복

		a[i][j] = n; // 해당 순서에 맞는 정수를 행렬에 입력
		i++; // 대각선으로 내리기 위해 위치 조정하며 n을 1씩 증가
		j--;
		n++;



		if (i >= N || j < 0) { // 대각선으로 향하던 n의 위치가 행렬의 범위를 벗어났을때 가장 위 열의 다음 행으로 이동 
			cntj++;
			i = 0;
			j = cntj;
		}

		for (;j >= M;) { // 가장 위 열의 다음행으로 이동했을때 행렬의 범위를 벗어난다면 대각선으로 움직여 행렬의 범위 안으로 위치 조정
			i++;
			j--;
		}

	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {

			printf(" %d", a[i][j]);

		}
		printf("\n");
	}

}

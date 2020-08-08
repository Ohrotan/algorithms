//SW Academy, 홀수 피라미드 문제
//조란 2020.08.08.12:35~13:40
//getNum이 왜문제?
#include<cstdio>
using namespace std;

int T;
long long N;
long long left;
long long right;

int main(void) {
	scanf("%d", &T);
	for (int i = 0; i < T; ++i) {
		scanf("%d", &N);
		right = 2 * N * N - 1;
		left = right - 4 * (N - 1);
		N == 1 ? left = right = 1 : 1;
		printf("#%d %lld %lld\n", i + 1, left, right);
	}

	return 0;
}
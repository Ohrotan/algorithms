//2020.10.08
//Ǯ��(7) 14:51 ~ 14:58
//�ڵ�(10) 14:58 ~ 15:08
//ó���� long long�� �ƴ϶� int�� �ؼ� ���� Ʋ�Ⱦ���~!!
//��(17)
#define DEBUG 0
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int n;

long long f[85];
long long res;
int main(void) {
	input();
	scanf("%d", &n);
	f[0] = 0; f[1] = 1; f[2] = 1;
	if (n == 1) {
		printf("4");
		return 0;
	}
	for (int i=3; i <= n; ++i) {
		f[i] = f[i - 1] + f[i - 2];

	}
	printf("%lld", ((long long)4 * f[n] + (long long)2 * f[n - 1]));
	return 0;
}
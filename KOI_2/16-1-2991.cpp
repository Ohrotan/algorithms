//2020.10.08
//읽기(3) 19:55 ~ 19:58
//코딩(8) 19:59 ~ 20:07
//합(11)

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int n, k;

int st[7][2] = { 0 };
int res;

int main(void) {
	input();
	scanf("%d %d", &n, &k);
	int s, g;//성별, 학년
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &s, &g);
		st[g][s]++;
	}

	for (int i = 1; i <= 6; ++i) {
		res += st[i][0] / k;
		if (st[i][0] % k > 0) {
			++res;
		}
		res += st[i][1] / k;
		if (st[i][1] % k > 0) {
			++res;
		}
	}
	printf("%d", res);
	return 0;
}
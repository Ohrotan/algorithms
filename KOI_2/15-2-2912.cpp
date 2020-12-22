//2020.10.08
//읽기(7) 20:58 ~ 21:05
//풀이(2) 21:05 ~ 21:07
//차트() 
//코딩(14) 21:07 ~ 21:21
//디버깅 답이랑 1 차이가 나네 소수점 문제인거 같은데..
//디버깅(10) 09:21 ~ 09:31
// double 에서 int로 바꾸니까 숫자가 하나 버려짐
// %.lf를 이용해서 소수점 버리자
//합(33)
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

int n;
int resmin, resdir;


int main(void) {
	input();
	double res = 1;
	double first, second;
	int d,dir=0;//방향

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf %lf %d",&first,&second,&d);
		res = res * (second / first);
		dir ^= d;
	}
	printf("%d %.lf", dir, res);
	return 0;
}
//2020.10.14
//읽기(3) 10:10 ~ 10:13
//풀이(7) 10:13 ~ 10:20
//차트() 
//코딩(6) 10:21 ~ 10:27
//디버깅() 
//합(16)

//이것도 조건이 까다롭지 않고 그냥 전체탐색 DFS로 풀었다.

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

int N;
bool cal[16]; //예약잡히면 true
int t[16], p[16]; //걸리는 일수, 보수
int res=0;

void accept(int day, int pay) {
	if (day == N + 1) {
		res = res < pay ? pay : res;
		return;
	}
	if (day + t[day] <= N + 1) {
		for (int i = 0; i < t[day]; ++i) {
			cal[day+i] = true;
		}
		accept(day + t[day], pay + p[day]);
	}
	cal[day] = false;
	accept(day + 1, pay);
}

int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &t[i], &p[i]);
	}
	accept(1, 0);
	printf("%d", res);
	return 0;
}
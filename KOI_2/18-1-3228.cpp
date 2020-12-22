//2020.10.05
//읽기() 
//풀이() 
//차트() 
//코딩(6) 16:41 ~ 16:47
//디버깅() 
//합(6)

#pragma warning(disable:4996)
#include <stdio.h>
#include<algorithm>
using namespace std;


int n;
int in;
int best=0, worst=1000;

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &in);
		best = max(in,best);
		worst = min(in, worst);
	}
	printf("%d", best - worst);
	return 0;
}
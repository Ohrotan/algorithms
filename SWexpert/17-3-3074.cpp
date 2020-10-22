//2020.10.07
//읽기(5) 02:10 ~ 02:15
//풀이() 
//차트() 
//코딩(30) 18:00 ~ 18:30 dfs 풀었는데 시간초과!
//코딩2(94) 18:40 ~ 18:50, 21:00 ~ 22:24 dp로 푸니 시간초과는 안났는데 답이 틀렸음!
//디버깅(74) 22:24 ~ 23:38 
//답이 틀린 이유를 보니 dp[100000]으로 해서 dp[83][100000]의 값이 dp[84][0]에 저장되는 참사가 발생함..!
//한참만에 찾음.. 메모리 접근 반성합니다..
//합(203)

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include<algorithm>

#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N, T; //도시수, 제한시간
int res = 0; //최대 모금액

int dp[100][100001] = { 0, };//dp[n][t] = n 번째 도시에서 t 시간일 때 최대 모금액

int wp[100]; //도보 모금액 1부터 시작?
int wt[100]; //도보 시간
int bp[100]; //자전거 모금액
int bt[100]; //자전거 시간



//n=0일때 초기화 해줘야함
void sol(int n) { //구간 번호, 누적 시간
	for (int i = 1; i <= T - wt[n]; ++i) {//합해도 제한 시간을 안 넘는 경우만 체크
		if (dp[n - 1][i] != 0) {
			
			dp[n][i + wt[n]] = max(dp[n - 1][i] + wp[n], dp[n][i + wt[n]]);
		}
	}

	//자전거
	for (int i = 1; i <= T - bt[n]; ++i) {//합해도 제한 시간을 안 넘는 경우만 체크 
		if (dp[n - 1][i] != 0) { //이전 단계에서 0이 아닌 애들만
			dp[n][i + bt[n]] = max(dp[n - 1][i] + bp[n], dp[n][i + bt[n]]);
		}
	}

}

void dfs(int p, int t, int n) { //모금액, 남은 시간, 직전 구간번호
	if (n == 0) {
		res = max(res, p);
		return;
	}
	if (t - wt[n - 1] >= 0) {
		dfs(p + wp[n - 1], t - wt[n - 1], n - 1);
	}
	if (t - bt[n - 1] >= 0) {
		dfs(p + bp[n - 1], t - bt[n - 1], n - 1);
	}
}
int main(void) {
	input();
	int a, b, c, d;
	scanf("%d %d", &N, &T);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		wt[i] = a;
		wp[i] = b;
		bt[i] = c;
		bp[i] = d;
	}
	//dfs(0, T, N);

	dp[0][wt[0]] = wp[0];
	dp[0][bt[0]] = bp[0];

	//sol(N - 1);

	for (int i = 1; i < N; ++i) {
		sol(i);
	}
	for (int i = N-1; i < N; ++i) {
		//printf("%d : ", i+1);
		for (int j = 0; j <= T; ++j) {
			if (dp[i][j] !=0) {
				//printf("(%6d분): %6d ", j,dp[i][j]);
			}
		}
		//printf("\n");
	}
	
	int* resid = (max_element(dp[N - 1], dp[N - 1]+T+1));
	log("몇 분일 때 최대값?", resid-dp[N-1]);
	printf("%d", *resid);
	return 0;
}
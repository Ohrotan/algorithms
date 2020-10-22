//2020.10.14
//읽기(4) 09:26 ~ 09:30
//풀이(9) 09:30 ~ 09:39
//차트() 
//코딩(15) 09:40 ~ 09:55
//디버깅(7) 09:55 ~ 10:02
//합(35)

//이번것도 문제가 쉬워서 금방 풀었다.
//이번처럼 정답이 틀렸을 때 앞에것부터 함수가 제대로 작성된게 맞는지 단계별로 확인해나가자
//그래서 쉽게 오류를 찾을 수 있었다!
//이번처럼 다른 답도 쉽게 될 수 있는 경우는 꼭 주어진 예제 통과했다고 넘기지 말고
//직접 테스트 케이스 만들어서 다시 테스트 꼭해보자

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N;
int map[21][21];
bool team[21] = { false, };

int res = 987654321;

void printT() {
	for (int i = 1; i <= N; ++i) {
		printf("%2d", team[i]);
	}
	printf("\n");
}
void compute() {
	int team1 = 0, team2 = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (i == j) continue;
			if (team[i] == team[j]) {
				if (team[i]) {
					team1 += map[i][j];
				}
				else {
					team2 += map[i][j];
				}
			}
		}
	}
	res = min(res, abs(team1 - team2));
}
void pick(int p, int cnt) { //사람번호, 뽑아야될 사람수
	if (cnt == 0) { //다뽑았다
		//printT();
		compute();
		return;
	}
	if (p > N) {//사람 넘쳐~
		return;
	}
	team[p] = true;
	pick(p + 1, cnt - 1);//뽑
	team[p] = false;
	pick(p + 1, cnt);//안뽑
	
}

int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	team[1] = true;
	pick(2, N / 2 - 1);

	printf("%d", res);
	return 0;
}
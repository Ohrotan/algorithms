//2020.10.09
//읽기(6) 15:54 16:00
//풀이(15) 16:00 ~ 16:15(가지치기 해보려고 시도) , 16:40 ~ 17:00(DFS,BFS 방법) 
//코딩(29) 17:03 ~ 17:32 bfs 풀었는데 메모리 초과! 
//dp코딩(30) 17:32 ~ 18:02 코딩은 다한거 같은데.. 오류 찾자..!!

//디버깅(60) 19:43 ~ 20:47 이정도했는데 자꾸 틀리면 모르는거다.. 정답보자
//정답(10) 20:47 ~ 20:58 
//답이 틀린 이유: 오른쪽이 작아도 버리는 경우 체크했어야함
//시간 초과 이유: sol()의 재귀형태가 아니라 dp 배열로 순차적으로 올라갔어야함
//합(150)
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG 1 
#include <stdio.h>
#include <vector>
#include <queue>
#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
#define MAX(a,b) (a>b?a:b)

#define MAX_N 2000

using namespace std;
struct turn {
	int lid; //left Id
	int rid; //right Id
	int score;// accumulated score
};
int n;
vector<int> left;
vector<int> right;
int score[2001][2001]; //왼카 아이디, 오카 아이디 일 때 최대 점수 기록
queue<turn> q;
int res = 0;

int N;
int lcard[MAX_N + 1], rcard[MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1];

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]); //왼쪽카드만 버렸을 때와 양쪽 카드를 모두 버렸을 때 중에서 최댓값
			if (rcard[j] < lcard[i]) //왼쪽카드보다 오른쪽카드에 적힌 수가 더 클때
				dp[i][j] = max(dp[i][j], dp[i][j - 1] + rcard[j]); //오른쪽카드를 버렸을 때와 버리지 않을 떄의 최댓값
		}
	}
	printf("%d", dp[N][N]);
}

void sprint() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%3d", score[i][j]);
			//res = MAX(score[n - 1][j], res);
		}
		printf("\n");
	}
	printf("\n");
}
//자 문제는 이제 이 sol을 처음에 어떻게 호출할 것인가!
int sol(int i, int j) {
	
	if (score[i][j] == -1) {

		//오른쪽이 작았거나
		if (j > 0 && left[i] > right[j - 1]) {
			int a = sol(i, j - 1);
			score[i][j] = MAX(a, 0) + right[j - 1];
		}
		else if (i > 0 && j > 0) {
			int a = sol(i - 1, j);
			int b = sol(i - 1, j - 1);
			score[i][j] = MAX(a, b);
		}
	}
	sprint();
	return score[i][j];
}

int main(void) {
	input();
	scanf("%d", &N);
	//최하단 카드는 1번에 넣고 최상단 카드는 N번으로
	for (int i = N; i > 0; i--) scanf("%d", &lcard[i]);
	for (int i = N; i > 0; i--) scanf("%d", &rcard[i]);

	solve();
	return 0;



	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			score[i][j] = -1;
		}
	}
	



	//아래는 내코드
	int tmp;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		left.push_back(tmp);
	}
	left.push_back(tmp);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		right.push_back(tmp);
	}
	right.push_back(tmp);
	score[0][0] = 0;
	score[1][0] = 0;
	score[0][1] = left[0] > right[0] ? right[0] : 0;
	for (int i = n; i >= 0; --i) {
		for (int j = 0; j <= n; ++j) {
			res = sol(i, j);
		}
	}
	//sprint();
	//mlog("\n", 0);
	for (int j = 0; j <= n; ++j) {
		//printf("score[%d][%d]:%d\n", j, n - 1, score[j][n - 1]);
		res = MAX(score[j][n], res);
	}
	for (int j = 0; j <= n; ++j) {
		//printf("score[%d][%d]:%d\n", j, n - 1, score[j][n - 1]);
		res = MAX(score[n][j], res);
	}
	

	//이 아래는 그냥 BFS
	//q.push(turn{ 0,0,0 });
	while (q.size() > 0) {
		turn now = q.front(); q.pop();
		if (now.lid >= n || now.rid >= n) {
			res = MAX(res, now.score);
			continue;
		}
		if (left[now.lid] > right[now.rid]) {
			//score[now.lid, ]
			q.push(turn{ now.lid,now.rid + 1,now.score + right[now.rid] });
		}
		else {
			q.push(turn{ now.lid + 1,now.rid,now.score });
			q.push(turn{ now.lid + 1,now.rid + 1,now.score });
		}
	}


	printf("%d", res);
	return 0;
}
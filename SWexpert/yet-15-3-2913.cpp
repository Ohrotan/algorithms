//2020.10.09
//�б�(6) 15:54 16:00
//Ǯ��(15) 16:00 ~ 16:15(����ġ�� �غ����� �õ�) , 16:40 ~ 17:00(DFS,BFS ���) 
//�ڵ�(29) 17:03 ~ 17:32 bfs Ǯ���µ� �޸� �ʰ�! 
//dp�ڵ�(30) 17:32 ~ 18:02 �ڵ��� ���Ѱ� ������.. ���� ã��..!!

//�����(60) 19:43 ~ 20:47 �������ߴµ� �ڲ� Ʋ���� �𸣴°Ŵ�.. ���亸��
//����(10) 20:47 ~ 20:58 
//���� Ʋ�� ����: �������� �۾Ƶ� ������ ��� üũ�߾����
//�ð� �ʰ� ����: sol()�� ������°� �ƴ϶� dp �迭�� ���������� �ö󰬾����
//��(150)
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
int score[2001][2001]; //��ī ���̵�, ��ī ���̵� �� �� �ִ� ���� ���
queue<turn> q;
int res = 0;

int N;
int lcard[MAX_N + 1], rcard[MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1];

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]); //����ī�常 ������ ���� ���� ī�带 ��� ������ �� �߿��� �ִ�
			if (rcard[j] < lcard[i]) //����ī�庸�� ������ī�忡 ���� ���� �� Ŭ��
				dp[i][j] = max(dp[i][j], dp[i][j - 1] + rcard[j]); //������ī�带 ������ ���� ������ ���� ���� �ִ�
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
//�� ������ ���� �� sol�� ó���� ��� ȣ���� ���ΰ�!
int sol(int i, int j) {
	
	if (score[i][j] == -1) {

		//�������� �۾Ұų�
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
	//���ϴ� ī��� 1���� �ְ� �ֻ�� ī��� N������
	for (int i = N; i > 0; i--) scanf("%d", &lcard[i]);
	for (int i = N; i > 0; i--) scanf("%d", &rcard[i]);

	solve();
	return 0;



	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			score[i][j] = -1;
		}
	}
	



	//�Ʒ��� ���ڵ�
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
	

	//�� �Ʒ��� �׳� BFS
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
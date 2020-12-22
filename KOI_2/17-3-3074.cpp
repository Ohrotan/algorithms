//2020.10.07
//�б�(5) 02:10 ~ 02:15
//Ǯ��() 
//��Ʈ() 
//�ڵ�(30) 18:00 ~ 18:30 dfs Ǯ���µ� �ð��ʰ�!
//�ڵ�2(94) 18:40 ~ 18:50, 21:00 ~ 22:24 dp�� Ǫ�� �ð��ʰ��� �ȳ��µ� ���� Ʋ����!
//�����(74) 22:24 ~ 23:38 
//���� Ʋ�� ������ ���� dp[100000]���� �ؼ� dp[83][100000]�� ���� dp[84][0]�� ����Ǵ� ���簡 �߻���..!
//�������� ã��.. �޸� ���� �ݼ��մϴ�..
//��(203)

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

int N, T; //���ü�, ���ѽð�
int res = 0; //�ִ� ��ݾ�

int dp[100][100001] = { 0, };//dp[n][t] = n ��° ���ÿ��� t �ð��� �� �ִ� ��ݾ�

int wp[100]; //���� ��ݾ� 1���� ����?
int wt[100]; //���� �ð�
int bp[100]; //������ ��ݾ�
int bt[100]; //������ �ð�



//n=0�϶� �ʱ�ȭ �������
void sol(int n) { //���� ��ȣ, ���� �ð�
	for (int i = 1; i <= T - wt[n]; ++i) {//���ص� ���� �ð��� �� �Ѵ� ��츸 üũ
		if (dp[n - 1][i] != 0) {
			
			dp[n][i + wt[n]] = max(dp[n - 1][i] + wp[n], dp[n][i + wt[n]]);
		}
	}

	//������
	for (int i = 1; i <= T - bt[n]; ++i) {//���ص� ���� �ð��� �� �Ѵ� ��츸 üũ 
		if (dp[n - 1][i] != 0) { //���� �ܰ迡�� 0�� �ƴ� �ֵ鸸
			dp[n][i + bt[n]] = max(dp[n - 1][i] + bp[n], dp[n][i + bt[n]]);
		}
	}

}

void dfs(int p, int t, int n) { //��ݾ�, ���� �ð�, ���� ������ȣ
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
				//printf("(%6d��): %6d ", j,dp[i][j]);
			}
		}
		//printf("\n");
	}
	
	int* resid = (max_element(dp[N - 1], dp[N - 1]+T+1));
	log("�� ���� �� �ִ밪?", resid-dp[N-1]);
	printf("%d", *resid);
	return 0;
}
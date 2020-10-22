//2020.10.14
//�б�(4) 09:26 ~ 09:30
//Ǯ��(9) 09:30 ~ 09:39
//��Ʈ() 
//�ڵ�(15) 09:40 ~ 09:55
//�����(7) 09:55 ~ 10:02
//��(35)

//�̹��͵� ������ ������ �ݹ� Ǯ����.
//�̹�ó�� ������ Ʋ���� �� �տ��ͺ��� �Լ��� ����� �ۼ��Ȱ� �´��� �ܰ躰�� Ȯ���س�����
//�׷��� ���� ������ ã�� �� �־���!
//�̹�ó�� �ٸ� �䵵 ���� �� �� �ִ� ���� �� �־��� ���� ����ߴٰ� �ѱ��� ����
//���� �׽�Ʈ ���̽� ���� �ٽ� �׽�Ʈ ���غ���

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
void pick(int p, int cnt) { //�����ȣ, �̾ƾߵ� �����
	if (cnt == 0) { //�ٻ̾Ҵ�
		//printT();
		compute();
		return;
	}
	if (p > N) {//��� ����~
		return;
	}
	team[p] = true;
	pick(p + 1, cnt - 1);//��
	team[p] = false;
	pick(p + 1, cnt);//�Ȼ�
	
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
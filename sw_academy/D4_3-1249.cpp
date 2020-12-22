//2020.10.03 
//�б�(3) 16:30 ~ 16:33
//Ǯ��(5) 16:33 ~ 16:38
//��Ʈ(10) 16:38 ~ 16:48
//�ڵ�(50) 16:50 ~ 17:40
//(68) ���� ������ dfs�� �ð��ʰ�

//bfs(35)  17:40~18:15
//�ڵ�(20) 18:25 ~ 18:45 (Ǯ��� �ߴµ� ���� Ʋ��)
//�����(10) 19:53 ~ 20:04 - init���� �ʱ�ȭ �߸���
//(65)
#pragma warning(disable:4996)
#include<stdio.h>

#include<vector>
#include<queue>
#include<algorithm>
#include<limits.h>

using namespace std;

int res = INT_MAX;
int tc = 1, TC;
int num = 100;
int map[100][100] = { 0, };
int tmap[100][100] = { INT_MAX, }; //�� �ڸ��� ���� �����ð�

int mr[4] = { 0,0,1,-1 };
int mc[4] = { 1,-1,0,0 };

char buf[102];
queue<int> qc, qr;

void init() {
	res = INT_MAX;
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			map[i][j] = 0;
			tmap[i][j] = INT_MAX;
		}
	}
	tmap[0][0] = 0;
}
bool valid(int r, int c) {
	if (r < num && r >= 0 && c < num && c >= 0) { //�� �ȿ� ����
		//if (map[r][c] >= 0) { //(dfs)������ �� ����
		return true;
		//}
	}
	return false;
}
void dfs(int r, int c, int t) {
	if (t >= res) {
		return;
	}
	if (r == num - 1 && c == num - 1) {
		res = min(res, t);
		return;
	}


	int nr, nc;
	for (int i = 0; i < 4; ++i) {
		nr = r + mr[i];
		nc = c + mc[i];
		if (valid(nr, nc)) {
			map[nr][nc] *= -1; //�������ٴ� ǥ��
			dfs(nr, nc, t - map[nr][nc] - 1);
			//-1�� ����: ó�� �� �Է��Ҷ� 1�� ������� ������
			map[nr][nc] *= -1; //�ٽ� �� ������ ô
		}
	}
}

void bfs() {
	qr.push(0);
	qc.push(0);

	int r, c;
	while (qr.size() > 0) {
		r = qr.front(); qr.pop();
		c = qc.front(); qc.pop();

		int nc, nr;
		for (int i = 0; i < 4; ++i) {
			nr = r + mr[i];
			nc = c + mc[i];
			if (valid(nr, nc)) {
				if (tmap[nr][nc] > tmap[r][c] + map[nr][nc]) {
					tmap[nr][nc] = tmap[r][c] + map[nr][nc];
					qr.push(nr);
					qc.push(nc);
				}
			}
		}
	}
	res = tmap[num - 1][num - 1];
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (; tc <= TC; ++tc) {
		init();
		scanf("%d", &num);
		
		getchar();
		for (int i = 0; i < num; ++i) {
			gets_s(buf);
			for (int j = 0; j < num; ++j) {
				//bfs ���
				map[i][j] = buf[j] - '0';
				
				//dfs ���
				//map[i][j] = buf[j] - '0' + 1;
				//+1 ���� ������ �����ð��� 0�� �ڸ��� -1�� 1�� ���������� �����ϱ� ���ؼ�
				//���߿� �ð��� ���� �� �׻� 1�� ���ֱ�
			
				
			}
		}

		
		bfs();
		//dfs(0, 0, 0);
		printf("#%d %d\n", tc, res);
	}
	return 0;
}
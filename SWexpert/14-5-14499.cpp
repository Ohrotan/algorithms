//2020.10.15
//�б�(7) 13:43 ~ 13:50
//Ǯ��(13) 13:50 ~ 14:03
//�ڵ�(16) 14:05 ~ 14:21
//��(36)

//�巡���� ���ƻ�� ���� Ǯ���Ҷ� ������ �׷��� ��Ģ�� ������������� �ڵ��ؼ� �������� ���� ������.
//���������� ���ƻ�� �迭�� ���� ����� �����ߴ��� ������ ������.
//�迭 ���簡 �ʿ��Ҷ� vector����

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include<vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int map[20][20]; //zero
//�� �ϵ����� �ٴ�
vector<int> d(7, 0); //no zero 1�� ����, 6�� �ٴ�
vector<int> nd(7, 0); //no zero

//���� ����
int mr[5] = { 0,0,0,-1,1 };//nz
int mc[5] = { 0,1,-1,0,0 };//nz

int N, M, r, c, K;

int dir;
bool valid(int r, int c) {
	if (r >= 0 && c >= 0 && r < N && c < M) {
		return true;
	}
	return false;
}
bool roll() {
	r += mr[dir];
	c += mc[dir];
	//
	if (!valid(r, c)) {
		r -= mr[dir];
		c -= mc[dir];
		return false;
	}


	switch (dir) {
	case 1:
		nd[1] = d[4];
		nd[2] = d[2];
		nd[3] = d[1];
		nd[4] = d[6];
		nd[5] = d[5];
		nd[6] = d[3];
		break;
	case 2:
		nd[1] = d[3];
		nd[2] = d[2];
		nd[3] = d[6];
		nd[4] = d[1];
		nd[5] = d[5];
		nd[6] = d[4];
		break;
	case 3:
		nd[1] = d[5];
		nd[2] = d[1];
		nd[3] = d[3];
		nd[4] = d[4];
		nd[5] = d[6];
		nd[6] = d[2];
		break;
	case 4:
		nd[1] = d[2];
		nd[2] = d[6];
		nd[3] = d[3];
		nd[4] = d[4];
		nd[5] = d[1];
		nd[6] = d[5];
		break;
	}
	d = nd;

	if (map[r][c] == 0) {
		map[r][c] = d[6];
	}
	else {
		d[6] = map[r][c];
		map[r][c] = 0;
	}

	return true;
}

int main(void) {
	input();
	scanf("%d %d %d %d %d", &N, &M, &r, &c, &K);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 0; i < K; ++i) {
		scanf("%d", &dir);
		if (roll()) {
			printf("%d\n", d[1]);
		}
	}
	return 0;
}
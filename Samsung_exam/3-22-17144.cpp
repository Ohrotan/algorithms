//2020.10.11
//�б�(8) 13:29 ~ 13:37
//Ǯ��(8) 13:37 ~ 13:45
//��Ʈ(30) 13:45 ~ 14:15
//�ڵ�(40) 14:17 ~ 14:57
//�����(6) 14:57 ~15:03

//��Ʈ�� �Ĳ����ؼ��� ������, ���� ��ü�� �ּҰ�,�ִ밪�� �ƴ϶� �׳� �ùķ��̼��̾ ����� �������̾���
//��ü������ ������ ���Ƽ� if�� ������ ����, for���� ���� �Ἥ �ε��� �򰥸��� ������ ����
//�ڵ� �ӵ��� �� �� ������
//�׷��ϱ� ������ �򰥸��� �ʰ� ����� �� ����
//i,j �����Ŵ� �Լ� ��ǲ���� ������� ����
//���� �׽�Ʈ���̽� ���� �����Ƿ� dfs, ��Ʈ��ŷ �ٽᵵ �ɵ�

//��(92)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int R, C, T;
int r1 = -1, r2 = -1;//û���� ��
int dr[4] = { -1,1,0,0 }; //�����¿�
int dc[4] = { 0,0,-1,1 };

int res = 0;

vector<vector<int>> map(250);
vector<vector<int>> nmap(250);

void mapPrint() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			printf("%3d",map[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}

void init() {
	map.reserve(R);
	nmap.reserve(R);
	for (int i = 0; i < R; ++i) {
		map[i].resize(C, 0);
		nmap[i].resize(C, 0);
	}
}
void spread4(int i, int j) {
	int ni, nj, cnt = 0, amount = map[i][j] / 5;
	for (int k = 0; k < 4; ++k) {
		ni = i + dr[k];
		nj = j + dc[k];

		if (ni >= 0 && ni < R && nj >= 0 && nj < C) {
			if (nmap[ni][nj] != -1) {
				nmap[ni][nj] += amount;
				++cnt;
			}
		}
	}
	nmap[i][j] += map[i][j] - (amount * cnt);
}
void copyMap() {

	map = nmap;
	for (int i = 0; i < R; ++i) {
		nmap[i].clear();
		nmap[i].resize(C, 0);
		
	}
	//û����
	nmap[r1][0] = -1;
	nmap[r2][0] = -1;
}
void spread() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] > 0) {
				spread4(i, j);
			}
		}
	}
	copyMap();
}
void wind() {
	//���� û����
	//������ �Ʒ���
	for (int i = r1 - 2; i >= 0; --i) {
		map[i + 1][0] = map[i][0];
	}
	//�������� ��
	for (int j = 1; j < C; ++j) {
		map[0][j - 1] = map[0][j];
	}
	//�Ʒ����� ����
	for (int i = 1; i <= r1; ++i) {
		map[i - 1][C - 1] = map[i][C - 1];
	}
	//�޿��� ��
	for (int j = C - 2; j >= 0; --j) {
		map[r1][j + 1] = map[r1][j];
	}
	map[r1][1] = 0;

	//�Ʒ��� û����
	//�Ʒ����� ����
	for (int i = r2 + 2; i <= R - 1; ++i) {
		map[i - 1][0] = map[i][0];
	}
	//�������� ��
	for (int j = 1; j < C; ++j) {
		map[R - 1][j - 1] = map[R - 1][j];
	}
	//������ �Ʒ���
	for (int i = R-2; i >= r2; --i) {
		map[i + 1][C - 1] = map[i][C - 1];
	}
	//�޿��� ��
	for (int j = C - 2; j >= 0; --j) {
		map[r2][j + 1] = map[r2][j];
	}
	map[r2][1] = 0;
}
void afterT() {
	for (int t = 0; t < T; ++t) {
		spread();
		wind();
	}
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			res += map[i][j];
		}
	}
	printf("%d", res + 2);//��û+2
}
int main(void) {
	input();
	int tmp;
	scanf("%d %d %d", &R, &C, &T);
	init();
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			scanf("%d", &tmp);
			map[i][j] = tmp;
			if (tmp == -1) {
				nmap[i][j] = -1;
				if (r1 == -1) {
					r1 = i;
				}
				else {
					r2 = i;
				}
			}
		}
	}
	afterT();
	return 0;
}
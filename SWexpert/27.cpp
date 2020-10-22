//2020.10.16
//�б�(13) 19:42 19:55
//Ǯ��() 
//��Ʈ() 
//�ڵ�(25) 1956 2021
//�����(5) 2031
//�ִ� ���� 2036
// �� �ٵ� Ʋ��..?
//bfs �������� ���� Ʋ��
//�� 99�� �ʹ� �۾��� 99�� �Ѵ� ��쿡 Ʋ��������
//�����(41) 2038 2119
//��(84)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <queue>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define mlog(s,a){}
#define input(){}
#endif
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

int N, M;

int map[50][50];//������
int t[50][50];//�ð�

int vcnt = 0;//��ü ��Ȱ�� ���̷��� ����
int vr[10];
int vc[10];
bool active[10];

int mr[4] = { -1,1,0,0 };
int mc[4] = { 0,0,-1,1 };

int res = 987654321;
void printT() {
	return;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%3d", t[i][j]);
		}
		nn()
	}
	for (int i = 0; i < vcnt; ++i) {
		printf("%d", active[i] ? i : -1);
	}
	line()

}
void init() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			t[i][j] = 9999;
			if (map[i][j] == 1) {
				t[i][j] = 0;
			}
		}
	}
}
bool inBorder(int r, int c) {
	if (r >= 0 && c >= 0 && r < N && c < N) {
		return true;
	}
	return false;
}

void maxtime() {
	int m = 0;

	//��� ���̷��� �ڸ��� �ð����� ���ֱ�
	for (int i = 0; i < vcnt; ++i) {
		t[vr[i]][vc[i]] = 0;
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (m < t[i][j]) {
				m = t[i][j];
			}
		}
	}
	res = min(m, res);
	printT();
}
void spread() {
	init(); //t�迭 �ʱ�ȭ
	queue<int> rq;
	queue<int> cq;
	for (int i = 0; i < vcnt; ++i) {
		if (active[i]) {
			rq.push(vr[i]);
			cq.push(vc[i]);
			t[vr[i]][vc[i]] = 0;
		}
	}
	int nr, nc;
	while (rq.size() > 0) {
		int r = rq.front(); rq.pop();
		int c = cq.front(); cq.pop();

		for (int i = 0; i < 4; ++i) {
			nr = r + mr[i];
			nc = c + mc[i];
			if (!inBorder(nr, nc)) continue;

			if (t[nr][nc] > t[r][c] + 1) {
				rq.push(nr);
				cq.push(nc);
				t[nr][nc] = t[r][c] + 1;
			}
		}
	}
}

void pick(int num, int cnt) {
	if (cnt == M) {
		for (int i = 0; i < vcnt; ++i) {
			//printf("%d", active[i] ? i : -1);
		}
		//line()
		spread();
		maxtime();
		return;
	}
	if (num == vcnt) {
		return;
	}

	active[num] = true;
	pick(num + 1, cnt + 1);

	active[num] = false;
	pick(num + 1, cnt);
}



int main(void) {
	input();
	int tmp;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &tmp);
			map[i][j] = tmp;
			if (tmp == 2) {
				vr[vcnt] = i;
				vc[vcnt] = j;
				active[vcnt++] = false;
			}
		}
	}
	pick(0, 0);
	if (res == 99) {
		res = -1;
	}
	printf("%d", res);


	return 0;
}
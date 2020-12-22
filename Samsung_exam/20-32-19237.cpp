//2020.10.16
//�б�(10) 16:47 16:57
//Ǯ��(26) 17:02 17:28
//�ڵ�(32) 17:28 1800
//�����(14) 1800 1814
//win üũ ������, for�� �� �ʱ�ȭ ����
//��(82)

//�� Ʋ���� ������. ���亸�� ������ ����ã��
//�ܼ� �ù��̾ �����ð� ���� �ɸ��� �ʰ�

#define DEBUG 1 
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <stdio.h>

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

int N, M, K;
int t[20][20] = { 0, };//�����ð�
int s[20][20] = { 0, };//��������

int map[20][20];//��� ��ġ��
int sr[401]; //��� ��ġ
int sc[401];
int sd[401]; //������
int pri[401][5][5];//�̵� �켱���� [���,������,�켱����] =����

//�̵�
int mr[5] = { 0,-1,1,0,0 };
int mc[5] = { 0,0,0,-1,1 };

void printMap() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%4d", map[i][j]);
		}
		nn()
	}
	line()
}

bool inBorder(int r, int c) {
	if (r >= 0 && c >= 0 && r < N && c < N) {
		return true;
	}
	return false;
}

void move() {

	for (int i = 1; i <= M; ++i) {
		int fr = -1, fc = -1, fd = -1;
		int r, c, d, nr, nc, nd;//���� ��� ��ġ, ����, ������
		if (sr[i] == -1) continue;//�������
		r = sr[i];
		c = sc[i];
		d = sd[i];

		//���� ã��
		for (int j = 1; j <= 4; ++j) {
			nd = pri[i][d][j]; //i�� d�����϶� j��° �켱���� ����
			nr = r + mr[nd];
			nc = c + mc[nd];
			if (!inBorder(nr, nc)) continue;

			if (s[nr][nc] == 0) {
				fr = nr;
				fc = nc;
				fd = nd;
				break;
			}
			if (s[nr][nc] == i && fr == -1) {
				fr = nr;
				fc = nc;
				fd = nd;
			}
		}

		//���� �ڸ� ���
		map[r][c] = 999;

		//���ڸ��� ������ ���� ��� ������
		if (map[fr][fc] < i) {
			//�� ����
			sr[i] = -1;
			sc[i] = -1;
			sd[i] = -1;
			continue;
		}
		
		//�̵�
		map[fr][fc] = i;
		sr[i] = fr;
		sc[i] = fc;
		sd[i] = fd;
		
	}
}
void second() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (t[i][j] <= 0) {
				continue;
			}
			t[i][j]-=1;
			if (t[i][j] == 0) {
				s[i][j] = 0;
			}
		}
	}
}
void smell() {
	int r, c;
	for (int i = 1; i <= M; ++i) {
		if (sr[i] < 0) {//���� ���
			continue;
		}
		r = sr[i];
		c = sc[i];
		s[r][c] = i;
		t[r][c] = K;
	}

}
bool win() {
	//printMap();
	for (int i = 2; i <= M; ++i) {
		//����ִ� �� �ִٸ�
		if (sr[i] != -1) {
			return false;
		}
	}
	return true;
}
void sol() {

	smell();
	move();
	second();
}



int main(void) {
	input();
	int tmp;
	scanf("%d %d %d", &N, &M, &K);
	//�����ġ �б�
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &tmp);
			map[i][j] = 999; //�������� 999��
			//���
			if (tmp > 0) {
				map[i][j] = tmp;
				sr[tmp] = i;
				sc[tmp] = j;
			}

		}
	}
	//�������б�
	for (int i = 1; i <= M; ++i) {
		scanf("%d", &sd[i]);
	}
	//�켱�����б�
	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= 4; ++j) {
			for (int k = 1; k <= 4; ++k) {
				scanf("%d", &pri[i][j][k]);
			}
		}
	}
	//printMap();
	int res = 0;
	while (!win()&&res<1001) {
		sol();
		++res;
	}
	if (res > 1000) {
		res = -1;
	}
	printf("%d", res);

	return 0;
}
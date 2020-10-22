//2020.10.
//�б�() 15
//Ǯ��() 
//��Ʈ() 
//�ڵ�() 45
//�����() 20
//��(80)
//�ͼ��� ����, �׷��� ���������� break�� �ƴ϶� �����߾����
//����� ��ȯ���� �ʰ� �ٸ� ���� ��ȯ��
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
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

class pos {
public:
	int cnt;//�̵�Ƚ��
	int r;
	int c;
	int desr;//����
	int desc;
	pos(int ccnt, int rr, int cc, int dr, int dc) : cnt(ccnt), r(rr), c(cc), desr(dr), desc(dc) {}
	bool operator<(pos& a)const {
		if (cnt < a.cnt) { return true; }
		if (cnt == a.cnt && r < a.r) {
			return true;
		}
		if (cnt == a.cnt && r == a.r && c < a.c) {
			return true;
		}
		return false;
	}
	bool operator==(pos& a)const {
		if (r == a.r && c == a.c) {
			return true;
		}return false;
	}
};
int N, M, e,res;

bool wall[21][21];//��false�� ��true

vector<pos> cus;//�մ������

int dis[21][21];//�ýú��� �Ÿ�

int tr, tc;//�ý� ��ġ

int mr[4] = { -1,0,0,1 };
int mc[4] = { 0,-1,1,0 };


void printMaps() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (wall[i][j]) {
				printf("0");
			}
			else {
				if (i == tr && j == tc) {
					printf("#");
				}
				else {
					printf("_");
				}
			}
		}nn()
	}line()
}
void init() {
	cus.clear();
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			dis[i][j] = 0;
		}
	}
}
void initDis() {
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= N; ++j) {
			dis[i][j] = 0;
		}
	}
}
bool valid(int r, int c) {
	if (r > 0 && c > 0 && r <= N && c <= N) {
		return !wall[r][c] && dis[r][c] == 0;
		//���� �ƴϰ�, �Ÿ��� 0�� ��
	}
	return false;
}

//���������� �Ÿ�����
void hombfs(pos customer) {
	vector<pos> q;
	initDis();
	customer.cnt = 0;
	q.push_back(customer);
	int nr, nc;
	while (q.size() > 0) {
		pos here = q.front(); q.erase(q.begin());

		if (here.c == customer.desc && here.r == customer.desr) {
			//������ ����!
			if (e >= here.cnt) {
				e += here.cnt;
				tr = here.r;
				tc = here.c;
				


				//�մԻ���
				for (int i = 0; i < M; ++i) {
					if (cus[i] == customer) {
						cus.erase(cus.begin()+i);
						break;
					}
				}
			}
			else {
				e = 0;
				res = -1;
			}
			break;
		}

		int r = here.r;
		int c = here.c;

		for (int i = 0; i < 4; ++i) {
			nr = r + mr[i];
			nc = c + mc[i];
			if (!valid(nr, nc)) continue;
			dis[nr][nc] = dis[r][c] + 1;
			q.push_back(pos(here.cnt + 1, nr, nc, 0, 0));
		}
	}

}
//�մԱ��� �Ÿ�����
void cusbfs() {
	vector<pos> q;
	initDis();
	q.push_back(pos(0,tr, tc,0,0));
	int nr, nc;
	while (q.size() > 0) {
		sort(q.begin(), q.end());
		for (auto item : q) {
			//printf("%d:(%d,%d)\n",item.cnt,item.r,item.c);
		}
		pos here = q.front(); q.erase(q.begin());
		
		//�մ��ΰ�?
		for (auto cu : cus) {
			if (cu == here) {
				//�մ� �¿췯 ����
				tr = cu.r;
				tc = cu.c;
				if (e < here.cnt) {
					//�������
					e = 0;
					res = -1;
				}
				else {
					e -= here.cnt;
					hombfs(cu);
					//
				}
				//printMaps();
				return;
			}
		}

		int r = here.r;
		int c = here.c;

		for (int i = 0; i < 4; ++i) {
			nr = r + mr[i];
			nc = c + mc[i];
			if (!valid(nr, nc)) continue;
			dis[nr][nc] = dis[r][c] + 1;
			q.push_back(pos(here.cnt+1, nr, nc,0,0));
		}
	}

}

int main(void) {
	input();
	int t1, t2, t3, t4;
	scanf("%d %d %d", &N, &M, &e);
	init();
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &wall[i][j]);
		}
	}
	scanf("%d %d", &tr, &tc);

	for (int i = 0; i < M; ++i) {
		scanf("%d %d %d %d", &t1, &t2, &t3, &t4);
		cus.push_back(pos(0,t1, t2,t3,t4));

	}
	int lastcus, laste;
	while (cus.size() > 0 && e > 0) {
		lastcus = cus.size();
		cusbfs();
		if (lastcus == cus.size()) {
			//�մ��� �ƹ��� ���¿��
			res = -1;
			printf("%d", res);
			return 0;
		}
	}
	res = e;
	printf("%d", res);

	return 0;
}
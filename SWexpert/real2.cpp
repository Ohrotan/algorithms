//2020.10.
//읽기() 
//풀이() 
//차트() 
//코딩()
//디버깅() 
//합()
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
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

struct star {
	int z, s, d;
};

int N, M, K, res;

vector<star> stars;
vector<star> map[51][51];
vector<star> tmap[51][51];
vector<star> clean[51][51];

vector<int> crush_r;
vector<int> crush_c;


int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };


void sumZ() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			while (map[i][j].size() > 0) {
				res += map[i][j].back().z;
				//printf("(%d, %d) z: %d\n", i,j,map[i][j].back().z);
				map[i][j].pop_back();
			}
		}
	}
}

void crush() {
	int  ns, nz, nd;
	int sum_s = 0, sum_z = 0, cnt = 0, size = 0;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (tmap[i][j].size() == 0) continue;

			if (tmap[i][j].size() == 1) {
				map[i][j].push_back(tmap[i][j].back()); tmap[i][j].pop_back();
				continue;
			}
			sum_s = 0, sum_z = 0, cnt = 0, size = 0;
			while (tmap[i][j].size() > 0) {
				star old = tmap[i][j].back(); tmap[i][j].pop_back();
				sum_s += old.s;
				sum_z += old.z;
				if (old.d % 2) ++cnt;
				++size;
			}
			if (sum_z < 5) continue;

			ns = sum_s / size;
			nz = sum_z / 5;
			nd = (cnt == 0 || cnt == size) ? 0 : 1;
			for (int dir = 0; dir < 4; ++dir) {
				map[i][j].push_back(star{ nz,ns,nd });
				nd += 2;
			}
		}
	}
}


void move() {
	int ns, nr, nc;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			while (map[i][j].size() > 0) {
				star me = map[i][j].back(); map[i][j].pop_back();
				ns = me.s % N;

				nr = i + dr[me.d] * ns;
				nc = j + dc[me.d] * ns;

				if (nr <= 0) {
					nr = nr + N;
				}
				else if (nr > N) {
					nr = nr - N;
				}
				if (nc <= 0) {
					nc = nc + N;
				}
				else if (nc > N) {
					nc = nc - N;
				}

				tmap[nr][nc].push_back(me);

			}
		}
	}
	crush();
}
int main(void) {

	input();
	int t1, t2, t3, t4, t5;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; ++i) {
		scanf("%d %d %d %d %d", &t1, &t2, &t3, &t4, &t5);
		map[t1][t2].push_back(star{ t3,t4,t5 });
	}

	while (K--) {
		move();
	}
	sumZ();
	printf("%d", res);
	return 0;
}
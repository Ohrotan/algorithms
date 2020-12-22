//2020.10.16
//읽기(10) 16:47 16:57
//풀이(26) 17:02 17:28
//코딩(32) 17:28 1800
//디버깅(14) 1800 1814
//win 체크 순서랑, for문 전 초기화 오류
//합(82)

//답 틀려도 괜찮다. 정답보고 빠르게 오류찾자
//단순 시뮬이어서 디버깅시간 오래 걸리지 않고

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
int t[20][20] = { 0, };//냄새시간
int s[20][20] = { 0, };//냄새주인

int map[20][20];//상어 위치맵
int sr[401]; //상어 위치
int sc[401];
int sd[401]; //상어방향
int pri[401][5][5];//이동 우선순위 [상어,현방향,우선순위] =방향

//이동
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
		int r, c, d, nr, nc, nd;//현재 상어 위치, 방향, 새방향
		if (sr[i] == -1) continue;//죽은상어
		r = sr[i];
		c = sc[i];
		d = sd[i];

		//갈곳 찾기
		for (int j = 1; j <= 4; ++j) {
			nd = pri[i][d][j]; //i상어가 d방향일때 j번째 우선순위 방향
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

		//기존 자리 비움
		map[r][c] = 999;

		//갈자리에 나보다 작은 상어 있으면
		if (map[fr][fc] < i) {
			//나 죽음
			sr[i] = -1;
			sc[i] = -1;
			sd[i] = -1;
			continue;
		}
		
		//이동
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
		if (sr[i] < 0) {//죽은 상어
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
		//살아있는 상어가 있다면
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
	//상어위치 읽기
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &tmp);
			map[i][j] = 999; //상어없으면 999로
			//상어
			if (tmp > 0) {
				map[i][j] = tmp;
				sr[tmp] = i;
				sc[tmp] = j;
			}

		}
	}
	//상어방향읽기
	for (int i = 1; i <= M; ++i) {
		scanf("%d", &sd[i]);
	}
	//우선순위읽기
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
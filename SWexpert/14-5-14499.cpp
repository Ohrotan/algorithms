//2020.10.15
//읽기(7) 13:43 ~ 13:50
//풀이(13) 13:50 ~ 14:03
//코딩(16) 14:05 ~ 14:21
//합(36)

//드래곤을 교훈삼아 먼저 풀이할때 방향을 그려서 규칙을 적어놓은다음에 코딩해서 오류없이 쉽게 끝났다.
//저번문제를 교훈삼아 배열을 새로 만들어 복사했더니 문제가 쉬웠다.
//배열 복사가 필요할때 vector쓰자

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
//윗 북동서남 바닥
vector<int> d(7, 0); //no zero 1이 윗면, 6이 바닥
vector<int> nd(7, 0); //no zero

//움직 방향
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
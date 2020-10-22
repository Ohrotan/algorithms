//2020.10.15
//읽기(4) 15:37 ~ 15:41
//풀이(11) 15:47 ~ 15:58
//코딩(30) 15:58 ~ 16:28
//디버깅(26) 16:28 ~ 16:54
//합(71)

//전형적인 백트래킹 문제
//그러나! 내가 왔다간 흔적을 지우면서 남이 해놓은 흔적도 같이 지워버려서 답이 틀렸었다.
//이번 경우는 테케가 적었더라면 모르고 지나갔을 뻔하다
//백트래킹할 때 왔다간 흔적 지울때는 남이 한것까지 지우는지 잘 확인하자

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include<vector>
#include <algorithm>


#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

int N, M;
int office[8][8];
vector<vector<bool>> map(8);


int tv_cnt, wall_cnt=0;
int tv_r[8];
int tv_c[8];
int tv_t[8];//tv type
int res=987654321;

void printMap() {
	return;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%s",map[i][j]?"o":office[i][j]==6?"X":"_");
		}
		nn();
	}

}

void up(int r, int c, bool observing) {
	for (int i = r-1; i >= 0; --i) {
		//벽이면
		if (office[i][c] == 6) {
			return;
		}
		map[i][c] = observing;
	}
}
void down(int r, int c, bool observing) {
	for (int i = r+1; i < N; ++i) {
		//벽이면
		if (office[i][c] == 6) {
			return;
		}
		map[i][c] = observing;
	}
}
void left(int r, int c, bool observing) {
	for (int j = c-1; j >= 0; --j) {
		//벽이면
		if (office[r][j] == 6) {
			return;
		}
		map[r][j] = observing;
	}
}
void right(int r, int c, bool observing) {
	for (int j = c+1; j < M; ++j) {
		//벽이면
		if (office[r][j] == 6) {
			return;
		}
		map[r][j] = observing;
	}

}

void count() {
	int tmp = 0;
	printMap();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (!map[i][j]) {
				++tmp;
			}
		}
	}
	res = min(res, tmp - wall_cnt);
	//mlog("res", tmp - wall_cnt);
	//line()
}

//검사할 cctv번호
void dfs(int num) {

	if (num == tv_cnt) {
		count();
		return;
	}
	vector<vector<bool>> original(8);
	for (int i = 0; i < 8; ++i) {
		original[i].resize(8, 0);
	}
	int r = tv_r[num];
	int c = tv_c[num];
	int t = tv_t[num];
	map[r][c] = true;
	switch (t) {
	case 1:
		original = map;

		up(r, c, true);
		dfs(num + 1);
		map = original;

		down(r, c, true);
		dfs(num + 1);
		map = original;


		left(r, c, true);
		dfs(num + 1);
		map = original;


		right(r, c, true);
		dfs(num + 1);
		map = original;

		break;
	case 2:
		original = map;

		up(r, c, true);
		down(r, c, true);
		dfs(num + 1);
		map = original;

		left(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;

		break;

	case 3:
		original = map;

		//상좌
		up(r, c, true);
		left(r, c, true);
		dfs(num + 1);
		map = original;

		//하좌
		down(r, c, true);
		left(r, c, true);
		dfs(num + 1);
		map = original;

		//하우
		down(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;

		//상우
		up(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;
		break;
	case 4:
		original = map;

		//상하좌
		up(r, c, true);
		down(r, c, true);
		left(r, c, true);
		dfs(num + 1);
		map = original;

		//하좌우
		down(r, c, true);
		left(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;

		//상좌우
		up(r, c, true);		
		left(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;

		//상하우
		up(r, c, true);
		down(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		map = original;
		break;
	case 5:
		up(r, c, true);
		down(r, c, true);
		left(r, c, true);
		right(r, c, true);
		dfs(num + 1);
		break;
	}

}

int main(void) {
	input();
	int tmp;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &tmp);
			office[i][j] = tmp;
			if (tmp == 0) {
				;
			}
			else if (tmp == 6) {
				wall_cnt++;
			}
			else {
				tv_r[tv_cnt] = i;
				tv_c[tv_cnt] = j;
				tv_t[tv_cnt++] = tmp;
			}
		}
	}
	for (int i = 0; i < 8; ++i) {
		map[i].resize(8, 0);
	}
	//printMap();
	dfs(0);
	printf("%d", res);
	return 0;
}
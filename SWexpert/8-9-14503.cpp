//2020.10.13
//읽기(10) 21:22 ~ 21:32
//풀이() 
//차트() 
//코딩(28) 21:32 ~ 22:00
//디버깅(17) 22:00 ~ 22:17
//합(55)

//문제가 쉬웠다.
//디버깅하는데 시간이 걸렸던것은
//r,c가 0을 포함하는지 안하는지 문제 조건을 명확히 안 본것
//후진할 때, 제대로 후진 안 한 것
//둘다 정확하지 않다는 것을 알았지만, 귀찮아서 일단 해보고 안되면 확인해야지 라는 마음으로 했다
//정확하지 않을 때는 조금 참고, 그때 바로 이게 정확한지 확인해보자

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N,M,r,c,d;

//현재방향의 왼쪽으로 이동하는 값
int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

bool map[51][51] = { false };
bool clean[51][51] = { false };

void printMap() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <M; ++j) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
}
void printClean() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%d", clean[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(void) {
	input();

	int t,nr,nc;

	scanf("%d %d", &N,&M);
	scanf("%d %d %d", &r, &c, &d);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &t);
			map[i][j] = !t;

			//printf("%d", map[i][j]);
		}
	}
	while (1) {
		//printf("now: %d %d\n", r, c);
		if (map[r][c]&&!clean[r][c]) {
			clean[r][c] = true;
		}
		//왼쪽칸
		nr = r + dr[d];
		nc = c + dc[d];

		//갈수 있고, 미청소면
		if (map[nr][nc] && !clean[nr][nc])
		{
			d = (d+3)%4;//회전
			r = nr, c = nc;//이동
			clean[nr][nc] = true;//청소
		}
		//사방이 벽이거나 청소했거나
		else if ((!map[r+1][c]||clean[r+1][c])&&
			(!map[r - 1][c] || clean[r - 1][c])&&
			(!map[r][c+1] || clean[r ][c+1])&&
			(!map[r][c-1] || clean[r][c-1])) {
			//후진
			nr = r + dr[(d+3)%4];
			nc = c + dc[(d+3)%4];
			if (!map[nr][nc]) {
				//뒤가 벽이면
				break;//중지
			}
			//한칸 후진
			r = nr;
			c = nc;
		}
		//왼쪽벽만 벽이거나, 청소했거나
		else {
			d = (d + 3) % 4;//회전
		}

		//printClean();
	}
	int res = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (clean[i][j]) ++res;
		}
	}
	//printMap();

	printf("%d", res);
	return 0;
}
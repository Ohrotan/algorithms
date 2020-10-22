//2020.10.09
//읽기(9) 21:18 ~ 21:27
//풀이(4) 21:27 ~ 21:31
//차트() 
//코딩(75) 21:31 ~ 22:46 흠 dfs 백트래킹으로 하려고 했는데 이거는 좀 아닌거 같기도 하고.. 내일 다시 생각해보자
//디버깅(60) 결국 백트래킹으로 푼게 맞았네.. 계속 어디가 틀렸는지 맵 출력하고 디버깅하니까 맞췄다
//아이디어가 어렵다기보다 이것 저것 조건이 많고 코드가 지저분해지고, 
//조건이 많고 코드가 길어지다보니까 실수도 많아져서 푸는데 오래걸렸다
//괜찮아, 조금 익숙해지면 되고, 실수 안하게 꼼꼼히 체크하면 돼
//차트 작성해서 풀어보자
//합(180)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <array>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int n;
vector<int> anshis;
vector<int> history;
array<int, 17> fx; //1번 물고기의 x좌표
array<int, 17> fy;
array<int, 17> fd; //물고기의 방향

array<array<int, 4>, 4> map; //물고기 위치맵
array<array<int, 4>, 4> dir; //물고기 방향맵
array<int, 9> movex = { 0,-1,-1,0,1,1,1,0,-1 };
array<int, 9> movey = { 0,0,-1,-1,-1,0,1,1,1 };

int sx = -1; //상어 위치
int sy = -1; //상어 위치
int sd = 6; //상어 방향

int res = 0; //먹은 물고기번호 합

int answer =0;

void mapPrint() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == sx && j == sy) {
				printf("  S/%d ",sd);
			}
			else {
				printf("%3d/%d ", map[i][j], dir[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n");
}

void moveFish() {
	int x, y, d;
	int mx, my;
	for (int i = 1; i < 17; ++i) {
		if (fx[i] == -1) {
			//상어한테 먹힌 물고기
			continue;
		}
		//printf("%d번 물고기 위치 바꿈\n",i);
		bool nowhere = false;
		x = fx[i];
		y = fy[i];
		d = fd[i];

		mx = x + movex[d];
		my = y + movey[d];

		int cnt = 1; //물고기가 방향 찾는 횟수
		//바깥이거나 상어가 있으면
		while (mx > 3 || mx < 0 || my>3 || my < 0 || (mx == sx && my == sy)) {
			//반시계로 돌림
			if (cnt == 8) {
				//다 찾아봐도 이동못함
				nowhere = true;
				break;
			}

			d = d == 8 ? 1 : d + 1;
			mx = x + movex[d];
			my = y + movey[d];
			++cnt;
		}
		if (nowhere) {
			continue; //물고기가 더이상 갈자리 없어서 다음 물고기한테 감
		}
		fx[i] = mx;
		fy[i] = my;
		int other = map[mx][my];
		map[mx][my] = map[x][y];
		map[x][y] = other;
		fx[other] = x;
		fy[other] = y;


		fd[i] = d;
		dir[x][y] = dir[mx][my];
		dir[mx][my] = d;
		//교환
		

	}
	//mapPrint();
	//printf("------fish moved---------\n");
}
void eat(int x, int y) {
	history.push_back(map[x][y]);
	res += map[x][y];
	sx = x;
	sy = y;
	sd = dir[x][y];

	fx[map[x][y]] = -1;
	fy[map[x][y]] = -1;
	fd[map[x][y]] = -1;
	map[x][y] = 0;
	dir[x][y] = 0;
	//mapPrint();
	
}

void eat() {
	int newx = sx + movex[sd];
	int newy = sy + movey[sd];

	//상어가 이동할 수 있을 때
	while (newx >= 0 && newy >= 0 && newx < 4 && newy < 4) {
		//직전 상태 기록
		int lres = res;
		array<int, 17> lfx = fx; //1번 물고기의 x좌표
		array<int, 17> lfy = fy;
		array<int, 17> lfd = fd; //물고기의 방향


		array<array<int, 4>, 4> lmap = map; //물고기 위치맵
		array<array<int, 4>, 4> ldir = dir; //물고기 방향맵
		int lsx = sx; //상어 위치
		int lsy = sy; //상어 위치
		int lsd = sd; //상어 방향

		//기록
		vector<int> lh(history);


		if (map[newx][newy] != 0) {

			res += map[newx][newy];
			eat(newx, newy);
			moveFish();
			eat();
		}
		if (answer < res) {
			answer = res;
			anshis = history;
		}
		//printf("-----------------back--------------\n");

		//복구
		res = lres;
		fx = lfx;
		fy = lfy;
		fd = lfd;
		map = lmap;
		dir = ldir;
		sx = lsx;
		sy = lsy;
		sd = lsd;
		history = lh;
	/*	mapPrint();
		printf("-------------------이전 맵---------------------\n");
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				printf("%3d/%d ", lmap[i][j], ldir[i][j]);
			}
			printf("\n");
		}
		printf("\n");*/


		newx += movex[sd];
		newy += movey[sd];
		while (newx >= 0 && newy >= 0 && newx < 4 && newy < 4&&map[newx][newy] == 0) {
			newx += movex[sd];
			newy += movey[sd];
		}
	}
}
int main(void) {
	input();
	for (int i = 0; i < 4; ++i) {
		scanf("%d %d %d %d %d %d %d %d", &map[i][0], &dir[i][0], &map[i][1],
			&dir[i][1], &map[i][2], &dir[i][2], &map[i][3], &dir[i][3]);
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int fish = map[i][j];
			fx[fish] = i;
			fy[fish] = j;
			fd[fish] = dir[i][j];
		}
	}

	//mapPrint();
	//상어가 먹음
	eat(0, 0);
	moveFish();
	eat();
	//mapPrint();
	//printf("----------------------------------------\n");
	//printf("----------------------------------------\n");
	//mapPrint();
	answer = 0;
	for (auto h : anshis) {
		answer+= h;
	}
	printf("%d", answer);
	return 0;
}
//2020.10.03 
//읽기(3) 16:30 ~ 16:33
//풀이(5) 16:33 ~ 16:38
//차트(10) 16:38 ~ 16:48
//코딩(50) 16:50 ~ 17:40
//(68) 답은 맞으나 dfs는 시간초과

//bfs(35)  17:40~18:15
//코딩(20) 18:25 ~ 18:45 (풀기는 했는데 답이 틀림)
//디버깅(10) 19:53 ~ 20:04 - init에서 초기화 잘못함
//(65)
#pragma warning(disable:4996)
#include<stdio.h>

#include<vector>
#include<queue>
#include<algorithm>
#include<limits.h>

using namespace std;

int res = INT_MAX;
int tc = 1, TC;
int num = 100;
int map[100][100] = { 0, };
int tmap[100][100] = { INT_MAX, }; //각 자리별 누적 복구시간

int mr[4] = { 0,0,1,-1 };
int mc[4] = { 1,-1,0,0 };

char buf[102];
queue<int> qc, qr;

void init() {
	res = INT_MAX;
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			map[i][j] = 0;
			tmap[i][j] = INT_MAX;
		}
	}
	tmap[0][0] = 0;
}
bool valid(int r, int c) {
	if (r < num && r >= 0 && c < num && c >= 0) { //맵 안에 있음
		//if (map[r][c] >= 0) { //(dfs)지나간 적 없음
		return true;
		//}
	}
	return false;
}
void dfs(int r, int c, int t) {
	if (t >= res) {
		return;
	}
	if (r == num - 1 && c == num - 1) {
		res = min(res, t);
		return;
	}


	int nr, nc;
	for (int i = 0; i < 4; ++i) {
		nr = r + mr[i];
		nc = c + mc[i];
		if (valid(nr, nc)) {
			map[nr][nc] *= -1; //지나갔다는 표시
			dfs(nr, nc, t - map[nr][nc] - 1);
			//-1인 이유: 처음 값 입력할때 1씩 더해줬기 때문에
			map[nr][nc] *= -1; //다시 안 지나간 척
		}
	}
}

void bfs() {
	qr.push(0);
	qc.push(0);

	int r, c;
	while (qr.size() > 0) {
		r = qr.front(); qr.pop();
		c = qc.front(); qc.pop();

		int nc, nr;
		for (int i = 0; i < 4; ++i) {
			nr = r + mr[i];
			nc = c + mc[i];
			if (valid(nr, nc)) {
				if (tmap[nr][nc] > tmap[r][c] + map[nr][nc]) {
					tmap[nr][nc] = tmap[r][c] + map[nr][nc];
					qr.push(nr);
					qc.push(nc);
				}
			}
		}
	}
	res = tmap[num - 1][num - 1];
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (; tc <= TC; ++tc) {
		init();
		scanf("%d", &num);
		
		getchar();
		for (int i = 0; i < num; ++i) {
			gets_s(buf);
			for (int j = 0; j < num; ++j) {
				//bfs 방식
				map[i][j] = buf[j] - '0';
				
				//dfs 방식
				//map[i][j] = buf[j] - '0' + 1;
				//+1 해준 이유는 복구시간이 0인 자리를 -1과 1로 지나갔는지 구분하기 위해서
				//나중에 시간을 더할 때 항상 1씩 빼주기
			
				
			}
		}

		
		bfs();
		//dfs(0, 0, 0);
		printf("#%d %d\n", tc, res);
	}
	return 0;
}
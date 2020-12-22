#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct space {
	bool visited;
	int r, c, color, area;
};

struct comp {
	bool operator()(space& a, space& b) {
		return a.area < b.area;
	}
};

int C, R;

//space map[100][100];
int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };
int area_num = 0;

vector<vector<bool>> visited;
int map[100][100];

priority_queue<space, vector<space>, comp> q;
/*
vector<int> count() {
	vector<int> cnt(area_num + 10);

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j].area < 0) continue;
			cnt[map[i][j].area]++;
		}
	}

	int t = 0;

	for (auto item : cnt) {
		if (item > 0) {
			++t;
		}
	}

	cout << t << "/" << *max_element(cnt.begin(), cnt.end());


	return vector<int>{t, * max_element(cnt.begin(), cnt.end()) };
}
void bfs() {
	q.push(map[0][0]);
	while (q.size() > 0) {

		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				printf("%4d", map[i][j].area);
			}
			printf("\n");
		}
		printf("--------------------\n");
		space s = q.top(); q.pop();
		int nr = s.r;
		int nc = s.c;
		if (s.area != map[nr][nc].area) {
			continue;
		}
		for (int i = 0; i < 4; ++i) {
			nr = s.r + dr[i];
			nc = s.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= R || nc >= C) {
				continue;
			}
			space& tmp = map[nr][nc];

			if (tmp.visited) {
				if (tmp.color == s.color && tmp.area != s.area) {
					tmp.area = s.area;
				}
			}
			else {
				tmp.visited = true;

				if (tmp.color != 0) {
					if (tmp.color == s.color) {
						tmp.area = s.area;
					}
					else {
						tmp.area = area_num++;
					}
				}
				q.push(tmp);
			}
		}
	}
}
*/
int findArea() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			printf("%c", visited[i][j] ? '#' : ' ');
		}
		printf("\n");
	}
	queue<int> rq;
	queue<int> cq;
	int cnt = 0;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (visited[i][j] == false) {
				visited[i][j] = true;
				rq.push(i);
				cq.push(j);
				cnt++;
				break;
			}
		}
		if (rq.size() > 0) break;
	}

	while (rq.size() > 0) {
		int r = rq.front(); rq.pop();
		int c = cq.front(); cq.pop();

		int nr, nc;
		for (int i = 0; i < 4; ++i) {
			nr = r + dr[i];
			nc = c + dc[i];
			if (nr < 0 || nc < 0 || nr >= R || nc >= C) {
				continue;
			}
			if (!visited[nr][nc] && map[nr][nc] == map[r][c]) {
				visited[nr][nc] = true;

				rq.push(nr);
				cq.push(nc);
				++cnt;
			}
		}
	}
	return cnt;
}
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	R = m;
	C = n;
	visited.resize(R);
	for (int i = 0; i < R; ++i) {
		visited[i].resize(C);
		for (int j = 0; j < C; ++j) {

			map[i][j] = picture[i][j];
			if (map[i][j] == 0) { 
				visited[i][j] = true; 
			}
			else {
				visited[i][j] = false;
			}
			//map[i][j] = space{ false,i,j,picture[i][j],-1 };

		}
	}
	//map[0][0].visited = true;
	//map[0][0].area = area_num++;
	vector<int> res;
	int cnt = findArea();

	while (cnt != 0) {
		res.push_back(cnt);
		cnt = findArea();
	}
	max_element(res.begin(), res.end());
	cnt = res.size();
	cout << cnt << "/" << *max_element(res.begin(), res.end());
	return vector<int>{ cnt, * max_element(res.begin(), res.end()) };

}

void solution1() {
	/*solution(6, 4,
		{
		{1, 1, 1, 0},
		{1, 2, 2, 0},
		{1, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 3},
		{0, 0, 0, 3} });
	*/
	solution(8, 15, {
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,2,1,1,2,1,1,1,0,0,0},
		{0,0,1,1,2,1,2,1,1,2,1,1,1,0,0},
		{0,1,1,4,1,1,1,1,1,1,1,4,1,1,0},
		{0,1,1,3,3,3,3,3,3,3,3,3,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0} });
}
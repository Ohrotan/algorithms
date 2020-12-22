#pragma warning(disable: 4996)
#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;

int n;
int map[25][25];
int houseNum[323];
int townNum = 0;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool isValidPositoin(int x, int y) {
	return (x >= 0 && x < n) && (y >= 0 && y < n);
}

void bfs(int x, int y, int key) {
	queue<pair<int, int>> q;
	q.push(pair<int, int>(x, y));
	map[x][y] = key;

	while (!q.empty()) {
		//pair<int, int> p;
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int dx = x + dir[i][0];
			int dy = y + dir[i][1];
			if (isValidPositoin(dx, dy) && map[dx][dy] == 1) {
				map[dx][dy] = key;
				q.push(pair<int, int>(dx, dy));
			}
		}
	}
}

void Solution(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {
				bfs(i, j, townNum + 2);
				townNum++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > 1) {
				houseNum[map[i][j] - 2]++;
			}
		}
	}
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
	Solution(n);
	sort(houseNum, houseNum + townNum);

	cout << townNum << endl;
	for (int i = 0; i < townNum; i++) {
		cout << houseNum[i] << endl;
	}
}
#pragma warning(disable: 4996)
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

int map[25][25];
int houseNum[323];

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int townNum = 0;

int n;

bool isValidPositoin(int x, int y) {
	return (x >= 0 && x < n) && (y >= 0 && y < n);
}

void dfs(int x, int y, int key) {
	map[x][y] = key;

	for (int i = 0; i < 4; i++) {
		int dx = x + dir[i][0];
		int dy = y + dir[i][1];

		if (isValidPositoin(dx, dy) && map[dx][dy] == 1) {
			dfs(dx, dy, key);
		}
	}
}

void Solution(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {
				townNum++;
				dfs(i, j, townNum + 1);
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
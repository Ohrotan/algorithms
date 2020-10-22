//2020.09.27 17:00 ~ 17:48
//bfs 어렵네~

#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int map[51][51];
vector<string> maze;
queue<int> qRow;//방문할 곳
queue<int> qCol;//방문할 곳
int num; //map 크기
int sRow, sCol;//시작점

vector<int> mRow;  //사용자 움직이는 방향
vector<int> mCol;  //사용자 움직이는 방향

void input() {
	//1
	maze = { "...", "...", "..." };
	sRow = 0;
	sCol = 1;
	mRow = { 1, 0, -1, 0 };
	mCol = { 0, 1, 0, -1 };

	//2
	maze = { "...", "...", "..." };
	sRow = 0;
	sCol = 1;
	mRow = { 1, 0, -1, 0, 1, 1, -1, -1 }; 
	mCol = { 0, 1, 0, -1, 1, -1, 1, -1 };

	//3
	maze = { "X.X", "...", "XXX", "X.X" };
	sRow = 0;
	sCol = 1;
	mRow = { 1, 0, -1, 0 };
	mCol = { 0, 1, 0, -1 };

	//4
	maze = { ".......", "X.X.X..", "XXX...X", "....X..", "X....X.", "......." };
	sRow = 5;
	sCol = 0;
	mRow = { 1, 0, -1, 0, -2, 1 };
	mCol = { 0, -1, 0, 1, 3, 0 };

	
}
int main(void) {
	input();
	for (int i = 0; i < maze.size(); ++i) {
		for (int j = 0; j < maze[0].size(); ++j) {
			if (maze[i][j] == '.') {
				map[i][j] = 0;
			}
			else {
				map[i][j] = -1;
			}
		}
	}
	

	qRow.push(sRow);
	qCol.push(sCol);



	//길 찾기
	while (qRow.size() != 0) {
		int r = qRow.front(); qRow.pop();
		int c = qCol.front(); qCol.pop();

		for (int i = 0; i < mRow.size(); ++i) {
			int nr = r + mRow[i];
			int nc = c + mCol[i];

			//보드판을 벗어나는 범위이면
			if (nr > maze.size() - 1 || nr < 0 || nc > maze[0].size() - 1 || nc < 0) {
				continue;
			}
			//길이고 내가 간 적 없으면
			if (map[nr][nc] == 0) {
				map[nr][nc] = map[r][c] + 1;//이동횟수 
				qRow.push(nr);
				qCol.push(nc);
			}
		}
	}

	map[sRow][sCol] = -1;//시작점은 다시 가면 안 되고, 출구로 선정도 되면 안 되니 -1
	int maxCnt = 0;

	for (int i = 0; i < maze.size(); ++i) {
		for (int j = 0; j < maze[0].size(); ++j) {
			if (map[i][j] == 0) {
				printf("result: %d", -1);
				return 0;
			}
			else {
				maxCnt = max(map[i][j], maxCnt);
			}
		}
	}
	printf("result: %d", maxCnt);
	return 0;
}
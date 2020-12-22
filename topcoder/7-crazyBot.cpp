//2020.09.26 17:26
//dfs 성공 bfs 실패ㅠ

#include<queue>
using namespace std;
class Pos {
public:
	int x;
	int y;
	double prob;
	int n;

	Pos(int _x, int _y, double _p, int _n) :x(_x), y(_y), prob(_p), n(_n) {

	}
};
double n = 2;
double prob[4] = { 0.25, 0.25, 0.25, 0.25 };//east, west, south, north
double result;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

bool map[30][30] = { false, };
queue<Pos> q;

double dfs(int x, int y, int n) {
	if (map[x][y]) return 0;
	if (n == 0) return 1;

	double ret = 0;
	map[x][y] = true;
	for (int i = 0; i < 4; ++i) {
		ret += dfs(x + dx[i], y + dy[i], n - 1) * prob[i];
	}
	map[x][y] = false;
	return ret;
}

//못짜겠다..
void bfs() {

	q.push(Pos(15, 15, 1.0, 1));
	int x, y;
	while (!q.empty()) {
		Pos pos = q.front();
		q.pop();
		if (n == 0) { result += pos.prob; continue; }//마지막 노드이면 확률 합
		//if (map[pos.x, pos.y]) return;//다시 들러버림~
		for (int i = 0; i < 4; ++i) {
			x = pos.x + dx[i];
			y = pos.y + dy[i];
			if (!map[x][y])
			{
				q.push(Pos(x, y, pos.prob * prob[i], n - 1));
			}
		}
	}

}
int main(void) {

	//result = dfs(15, 15, n);
	//bfs();
	printf("result: %f", result);

	return 0;
}
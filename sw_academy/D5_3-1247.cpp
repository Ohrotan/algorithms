//2020.10.03 14:55~ 15:54
#pragma warning(disable:4996)
#include <stdio.h>


#include <algorithm>
#include <vector>
#include <limits.h>
using namespace std;

int tc = 1, TC; //테스트 케이스
int num = 0; //방문할 고객집

int sx, sy; //회사
int ex, ey; //집
vector<int> hx; //고객 집
vector<int> hy;
int ret = INT_MAX; //가장 짧은 이동거리


void printX() {
	for (int a : hx) {
		printf("%d ", a);
	}
	printf("\n");
}

int dis(int x, int y, int a, int b) {
	return abs(x - a) + abs(y - b);
}

void dfs(int x, int y, int d) {
	if (hx.size() == 0) {
		ret = min(d + dis(x, y, ex, ey), ret);
		return;
	}
	else {
		for (int i = 0; i < hx.size(); ++i) {
			int lcnt = cnt;
			int nd = d + dis(x, y, hx[i], hy[i]);
			if (nd > ret) {
				continue;
			}
			int x = hx[i];
			int y = hy[i];
			hx.erase(hx.begin() + i);
			hy.erase(hy.begin() + i);
			//printf("cnt=%d / ",lcnt);  printX();
			++cnt;
			dfs(x, y, nd);
			hx.insert(hx.begin() + i, x);
			hy.insert(hy.begin() + i, y);
			//printf("cnt=%d / ", lcnt); printX();
		}
	}

}

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (; tc <= TC; ++tc) {
		scanf("%d", &num);
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		int x, y;
		hx.clear(); hy.clear(); ret = INT_MAX;
		for (int i = 0; i < num; ++i) {
			scanf("%d %d", &x, &y);
			hx.push_back(x);
			hy.push_back(y);
		}
		dfs(sx, sy, 0);
		printf("#%d %d\n", tc, ret);
	}

	fclose(stdin);
	return 0;
}
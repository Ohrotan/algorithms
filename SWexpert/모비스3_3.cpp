/*
사각형들을 아래로 한번 왼쪽으로 한번 끝까지 이동

흠 두가지 방법?
1. 맵에다 사각형을 그림그려서 일일이 맵의 값을 바꿔주기
2. 사각형의 꼭지점을 이용해서 이동할때마다 내가 침범하는경우가 있는지 체크하는것
*/

//#define MOBIS3_3
#ifdef MOBIS3_3
#pragma warning(disable:4996)

#include <vector>
#include <stdio.h>
#include <queue>
#include <algorithm>


#include <chrono>

using namespace std;

struct square {
	int r1, c1, r2, c2;
	//좌상단, 우하단좌표
};
//아래에 있는 사각형부터 정렬
bool ysort(square a, square b) {
	return a.r2 > b.r2;
}
//왼쪽에 있는 사각형부터 정렬
bool xsort(square a, square b) {
	return a.c1 < b.c1;
}

vector<vector<int>> map;
vector<square> sq;
int N;
void printMap() {
	for (auto row : map) {
		for (auto item : row) {
			printf("%3d", item);
		}
		printf("\n");
	}
	printf("-----------------------------------\n");
}

void mobis3() {
	freopen("mobis3.txt", "r", stdin);
	//while (true) {
	int num; // 전체크기, 사각형 개수
	scanf("%d", &N);
	scanf("%d", &num);
	//if (N == 0) break;
	map.resize(N, vector<int>(N, 0));


	int r1, c1, r2, c2;


	for (int cnt = 0; cnt < num; ++cnt) {
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		sq.push_back({ r1,c1,r2,c2 });
		for (int i = r1; i <= r2; ++i) {
			for (int j = c1; j <= c2; ++j) {
				map[i][j] = cnt + 1;
			}
		}
	}

	vector<vector<int>> init = map;
	long long elap = 0;
	for (int time = 0; time < 1000; ++time) {
		auto start = std::chrono::high_resolution_clock::now();


		//printMap();

		//아래로 밀기
		sort(sq.begin(), sq.end(), ysort);
		square s;
		int low, left;
		for (int i = 0; i < num; ++i) { //사각형
			s = sq[i];
			low = N - 1;
			for (int j = i-1; j >=0 ; --j) {
				if (s.c1 > sq[j].c2 || s.c2 < sq[j].c1) {
					continue;
				}
				if (s.r2 < sq[j].r1 && low > sq[j].r1 - 1) {
					low = sq[j].r1 - 1;
				}
			}
			sq[i].r1 += low - s.r2;
			sq[i].r2 = low;
		}



		//왼쪽으로 밀기
		sort(sq.begin(), sq.end(), xsort);
		for (int i = 0; i < num; ++i) { //사각형
			s = sq[i];
			left = 0;
			for (int j = i-1; j >= 0; --j) {
				if (s.r1 > sq[j].r2 || s.r2 < sq[j].r1) {
					continue;
				}
				if (s.c1 > sq[j].c2 && left < sq[j].c2 + 1) {
					left = sq[j].c2 + 1;
				}
			}
			sq[i].c2 -= s.c1 - left;
			sq[i].c1 = left;
		}


		
		/*for (auto s : sq) {
			printf("%d,%d,%d,%d\n", s.r1, s.c1, s.r2, s.c2);
		}*/
		
		auto finish = std::chrono::high_resolution_clock::now();
		elap += std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
		/*
		map.clear();
		map.resize(N, vector<int>(N, 0));

		int cnt = 1;
		for (auto s: sq) {
			for (int i = s.r1; i <= s.r2; ++i) {
				for (int j = s.c1; j <= s.c2; ++j) {
					map[i][j] = cnt;
				}
			}
			cnt++;
		}
		printMap();
		*/
	}
	printf("%lld", elap / 1000);
}

#endif
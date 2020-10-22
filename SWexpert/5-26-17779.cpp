//2020.10.12
//읽기(9) 11:53 ~ 12:02
//풀이(7) 12:02 ~ 12:09
//차트(4) 13:50 ~ 13:54
//코딩(75) 13:54 ~ 14:30, 15:10 ~ 15:49
//또 코드가 복잡해지면서 디버깅하기 힘들어짐
//새로운 풀이로 다시도전

//2차차트(39) 15:50 ~ 16:29
//2차코딩(21) 16:29 ~ 16:50
//디버깅(10) 16:50 ~ 17:00

//1차합(95)
//2차합(86)

//총합(165)

//문제점!!
//단순 전체탐색으로 알고리즘이 어려운 문제가 아니었다
//그런데 좀더 쉽게 해보려고 생각했던 풀이방법이 오히려 조건이 여러개가 만들어지면서 헷갈렸고
//규칙이라고 생각했던 것은 반례가 있어서 반례에 맞춘 코드를 또 짜야했다
//이런식으로 조건식이 계속 추가되면서 디버깅이 더 힘들어졌다.

//다시 풀었을 때는 디버깅 시간이 많이 줄었다.
//차트에서 시간이 좀 걸려서 앞으로 더 줄여야하긴 한다.
//최대한 일반적인 방법으로, 변수를 많이 사용하면서 단계를 나누자

//많은 if문, for문을 거쳐도 된다.
//규칙을 찾아서 쉽게 코딩하려 하지말고, 있는 그대로 if, for 많이 많이 돌리고
//변수 많이 만들어서 활용하자

//실수가 쌓인만큼 이 실수는 실전에서 안 한다는 보장이다.
//시험전까지 최대한 실수 많이 하고, 최대한 기록하자.

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif

#define MAX(a,b)(a>b?a:b)
#define MIN(a,b)(a<b?a:b)

using namespace std;

int N;

int people[21][21]; //0행 0열 안씀
int map[21][21] = { 0, }; //0행 0열 안씀

int x, y, d1, d2;

int res = 987654321;

vector<int> popular(6,0);//구역별 인구수
int tmp, maxp, minp;//최대 인구, 최소 인구

void init() {
	popular = vector<int>(6, 0);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			map[i][j] = 0;
		}
	}
}
void mapPrint() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%2d", map[i][j]);
		}
		printf("\n");
	}

	printf("\n");

}

bool valid() {
	if (x + d1 + d2 <= N && 1 <= y - d1 && y + d2 <= N) {
		return true;
	}
	return false;
}
void border() {
	int r, c;
	for (r = x,c=y; r < x + d1; ++r,--c) {
		map[r][c] = 5;
	}
	for (r = x, c = y; r < x + d2; ++r, ++c) {
		map[r][c] = 5;
	}
	for (r = x+d1, c = y-d1; r < x + d1+d2; ++r, ++c) {
		map[r][c] = 5;
	}
	for (r = x+d2, c = y+d2; r <= x + d1+d2; ++r, --c) {
		map[r][c] = 5;
	}
}

void inborder() {
	int r, c;
	for (r = x + 1; r < x + d1 + d2; ++r) {
		for (c = 1; c <= N; ++c) {
			if (map[r][c - 1] == 5) {
				if (map[r][c] == 0) map[r][c] = 5;
				else if (map[r][c] == 5) {
					break;
				}
			}
		}
	}
}

void fillPartition() {
	int r, c;
	for (r = 1; r < x + d1; ++r) {
		for (c = 1; c <= y;++c) {
			if (map[r][c] == 5) break;
			map[r][c] = 1;
		}
	}
	for (r = 1; r <= x + d2; ++r) {
		for (c = y + 1; c <= N; ++c) {
			if (map[r][c] == 5) continue;
			map[r][c] = 2;
		}
	}
	for (r = x + d1; r <= N; ++r) {
		for (c = 1; c < y - d1 + d2; ++c) {
			if (map[r][c] == 5) break;
			map[r][c] = 3;
		}
	}
	for (r = x + d2 + 1; r <= N; ++r) {
		for (c = y - d1 + d2; c <= N; ++c) {
			if (map[r][c] == 5)continue;
			map[r][c] = 4;
		}
	}
}

void count() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			popular[map[i][j]] += people[i][j];
		}
	}
	maxp = *max_element(popular.begin()+1, popular.end());
	minp = *min_element(popular.begin()+1, popular.end());
	res = min(res, maxp - minp);
	if (maxp - minp == res) {
		mlog("maxp", maxp);
		mlog("minp", minp);

		//mapPrint();
	}
	
}
int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &people[i][j]);
		}
	}


	for (x = 1; x < N - 1; ++x) {
		for (y = 2; y < N - 1; ++y) {
			for (d1 = 1; d1 < N - 1; ++d1) {
				for (d2 = 1; d2 < N - 1; ++d2) {
					if (!valid()) {
						continue;
					}
					init();
					border();
					inborder();
					fillPartition();
					count();
				}
			}
		}

	}

	printf("%d", res);
	return 0;
}

/*

int popular1() {
	//1 ≤ r < x + d1, 1 ≤ c ≤ y
	int tot = 0;
	for (int r = 1; r < x + d1; ++r) {
		for (int c = 1; c <= y; ++c) {
			tot += map[r][c];
		}
	}
	mlog("1", tot);
	return tot;
}
int popular2() {
	//1 ≤ r ≤ x + d2, y < c ≤ N
	int tot = 0;
	for (int r = 1; r < x + d2; ++r) {
		for (int c = y + 1; c <= N; ++c) {
			tot += map[r][c];
		}
	}
	mlog("2", tot);
	return tot;
}
int popular3() {
	//x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
	int tot = 0;
	for (int r = x + d1; r <= N; ++r) {
		for (int c = 1; c <= y - d1 + d2; ++c) {
			tot += map[r][c];
		}
	}
	mlog("3", tot);
	return tot;
}
int popular4() {
	//x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
	int tot = 0;
	for (int r = x + d2 + 1; r <= N; ++r) {
		for (int c = y - d1 + d2; c <= N; ++c) {
			tot += map[r][c];
		}
	}
	mlog("4", tot);
	return tot;
}

int popular5_1() {
	int tot = 0;
	//(x, y), (x+1, y-1), ...,
	//마지막 미포 (x+d1, y-d1)
	for (int r = x; r < x + d1; ++r) {
		for (int c = y; c >= y + (r - x); --c) {
			tot += map[r][c];
		}
	}
	mlog("5-1", tot);
	return tot;
}
int popular5_2() {
	int tot = 0;
	//시작 미포함 (x, y),
	//(x+1, y+1), ..., (x+d2, y+d2)
	for (int r = x + 1; r <= x + d2; ++r) {
		for (int c = y + 1; c <= y + (r - x); ++c) {
			tot += map[r][c];
		}
	}
	mlog("5-2", tot);
	return tot;
}
int popular5_3() {
	int tot = 0;
	//(x+d1, y-d1), (x+d1+1, y-d1+1), ...
	//마지막 미포 (x+d1+d2, y-d1+d2)
	for (int r = x + d1; r < x + d1 + d2; ++r) {
		for (int c = y - d1; c <= (y - d1) + (r - x - d1); ++c) {
			tot += map[r][c];
		}
	}
	mlog("5-3", tot);
	return tot;
}
int popular5_4() {
	int tot = 0;
	//(x+d2, y+d2), (x+d2+1, y+d2-1), ...,
	//마지막 미포 (x+d2+d1, y+d2-d1)
	for (int r = x + d2; r < x + d2 + d1; ++r) {
		for (int c = y + d2; c <= (y + d2) + (r - x - d2); ++c) {
			tot += map[r][c];
		}
	}
	mlog("5-4", tot);
	return tot;
}

void countPopular() {
	int p5_1 = popular5_1();
	int p5_2 = popular5_2();
	int p5_3 = popular5_3();
	int p5_4 = popular5_4();

	maxp = popular1() - p5_1;
	minp = maxp;

	tmp = popular2() - p5_2;
	maxp = MAX(maxp, tmp);
	minp = MIN(minp, tmp);

	tmp = popular3() - p5_3;
	maxp = MAX(maxp, tmp);
	minp = MIN(minp, tmp);

	tmp = popular4() - p5_4;
	maxp = MAX(maxp, tmp);
	minp = MIN(minp, tmp);

	tmp = p5_1 + p5_2 + p5_3 + p5_4  ;
	maxp = MAX(maxp, tmp);
	minp = MIN(minp, tmp);

	res = MIN(res, maxp - minp);
	mlog("res", res);
	mlog("", 0);
}*/
//2020.10.13
//읽기(13) 17:29 17:42
//풀이(21) 17:42 18:03
//한글차트(8) 18:03 18:11
//차트() 
//코딩(129) 18:11 20:20
//디버깅() 
//합(171)

//풀긴했는데 자꾸 틀림, 이미 꼬인것 같음. 정답보기

//규칙성을 제대로 못찾아서 결국 못풀었음, 규칙성을 찾으려고 조금만 더 생각해봤으면 좋았을듯

//정답을 봤는데 나중에 다시 풀거나 생각해보기~


#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N, R, C, D, G;

vector<vector<pair<int, int>>> dragon;
//케이스마다 (r,c)의 배열

bool map[101][101] = { 0 };

pair<int, int> spos;//시작점
pair<int, int> epos;//기준점
int res = 0;
void count() {
	for (auto d : dragon) {
		for (auto a : d) {
			map[a.first][a.second] = true;
			//printf("(%d,%d) ", a.first, a.second);
		}
		//printf("\n");
	}

	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 10; ++j) {
			printf("%d", map[i][j]);
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) {
				++res;
			}
		}
		printf("\n");
	}
}

void printD() {
	for (auto d : dragon) {
		for (auto a : d) {
			printf("(%d,%d) ", a.first, a.second);
		}
		printf("\n");
	}
}

pair<int, int> firstLine() {
	int endR, endC;
	switch (D) {
	case 0:
		endR = R;
		endC = C + 1;
		break;
	case 1:
		endR = R - 1;
		endC = C;
		break;
	case 2:
		endR = R;
		endC = C - 1;
		break;
	case 3:
		endR = R + 1;
		endC = C;
		break;
	}
	return pair<int, int>(endR, endC);
}

pair<int, int> turn(pair<int, int> pos, bool rot) {
	pair<int, int> ret;
	//rot = true;

	//나-기, 음대칭
	ret.first = epos.first - pos.first; //기준 - 나
	ret.second = epos.second - pos.second; //기준 - 나

	if (!rot) {
		if (D % 2 == 0) {
			ret.first *= -1;
		}
		else {
			ret.second *= -1;
		}
	}
	else {
		if (D % 2 == 0) {
			ret.second *= -1;
		}
		else {
			ret.first *= -1;
		}
	}
	ret.first += epos.first;
	ret.second += epos.second;

	return ret;
}
void makeDragon() {
	vector<pair<int, int>> points;

	//0세대
	spos = pair<int, int>(R, C);
	epos = firstLine();
	points.push_back(spos);
	printf("(%d,%d)", points.back().first, points.back().second);
	points.push_back(epos);
	printf("(%d,%d)", points.back().first, points.back().second);
	printf("\n");
	points.push_back(turn(points[0], true));//점 돌려서 집어넣기
	printf("(%d,%d)\n", points.back().first, points.back().second);
	epos = points.back();
	for (int i = 1; i < G; ++i) {
		//뒤에서부터 읽음
		//뒤에서 첫번째는 기준점이니까 돌리지 않음

		for (int j = points.size() - 2; j >= 0; --j) {
			points.push_back(turn(points[j],false));//점 돌려서 집어넣기
			printf("(%d,%d)", points.back().first, points.back().second);
		}
		//시작점 새로운 끝점으로 바꿔주기
		epos = points.back();
		printf("\n");
	}


	dragon.push_back(points);
	printf("------------------------------\n");
}
int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d %d", &C, &R, &D, &G);
		makeDragon();
	}

	printD();
	count();
	printf("%d", res);
	return 0;
}
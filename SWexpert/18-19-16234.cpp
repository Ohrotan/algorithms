//2020.10.15
//읽기(6) 21:14 ~ 21:20
//풀이(18) 21:30 ~ 21:48
//코딩(37) 21:56 ~ 22:33

//답이 틀림
//디버깅(26) 22:50 ~ 23:16

//진짜 중요한거 배웠다!! for(auto item : vector)는 값을 변경할 때 쓰면 안된다.
//item이 본체가 아니라 카피본이라서 값 변경이 안된다
//합(87)
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
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

class Nation {
public:
	int num;//나라번호 = N*r + c
	int pop;//인구
	int r;//위치
	int c;
	int root;//수장국
	vector<int> children;//자식
	Nation(int _num, int _pop, int _r, int _c) :num(_num), pop(_pop), r(_r), c(_c), root(_num) {
	}
};

vector<Nation> nations;

int N, L, R;
int mr[4] = { 0,0,1,-1 };
int mc[4] = { 1,-1,0,0 };

void printMap() {
	for (int i = 0; i < N * N; ++i) {
		if (i % N == 0) nn()
		printf("%6d", nations[i].pop);
		
	}
	nn()
	line()
}

bool inMap(int r, int c) {
	if (r >= 0 && c >= 0 && r < N && c < N) {
		return true;
	}
	return false;
}

//나라번호
void makeFed(int a, int b) {
	int roota = nations[a].root;
	int rootb = nations[b].root;
	if (nations[roota].children.size() > nations[rootb].children.size()) {
		//a에다가 b를 붙임
		for (int num : nations[rootb].children) {
			nations[num].root = roota; //기존 자식 루트 바꿔줌
			nations[roota].children.push_back(num); //새로운 루트에 자식 추가
		}
		nations[roota].children.push_back(rootb); //루트비추가
		nations[rootb].root = roota; //루트비도 루트 바꿔줌
		nations[rootb].children.clear(); //루트비에 자식 0

	}
	else {
		//b에다가 a를 붙임
		for (int num : nations[roota].children) {
			nations[num].root = rootb; //기존 자식 루트 바꿔줌
			nations[rootb].children.push_back(num); //새로운 루트에 자식 추가
		}
		nations[rootb].children.push_back(roota);
		nations[roota].root = rootb; 
		nations[roota].children.clear(); 
	}
}

//국경개방
bool openBorder() {
	bool ret = false;
	for (int i = 0; i < N*N; ++i) {
		int r = nations[i].r;
		int c = nations[i].c;
		int nr, nc, nn;//비교할 나라의 위치, 번호
		for (int j = 0; j < 4; ++j) {
			nr = r + mr[j];
			nc = c + mc[j];
			if (!inMap(nr, nc)) {
				continue;
			}
			nn = nr * N + nc;

			//이미 연합
			if (nations[i].root == nations[nn].root) {
				continue;
			}

			//인구차가 조건에 맞으면
			int gap = abs(nations[i].pop - nations[nn].pop);
			if (gap >= L && gap <= R) {
				makeFed(i, nn);
				ret = true;
			}

		}
	}
	return ret;
}

void closeBorder() {
	for (int i = 0; i < N * N;++i) {
		nations[i].root = nations[i].num;
		nations[i].children.clear();
	}
}
void movePeople() {
	printMap();
	for (int i = 0; i < N*N; ++i) {
		//본인이 루트일 때만 인구이동
		if (nations[i].num == nations[i].root) {
			int sum = nations[i].pop;

			for (auto c : nations[i].children) {
				sum += nations[c].pop;
			}
			int npop = sum / (nations[i].children.size() + 1);

			for (auto c : nations[i].children) {
				nations[c].pop = npop;
			}
			nations[i].pop = npop;
		}
	}
	printMap();
	closeBorder();
}

int main(void) {
	input();
	int pop;
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &pop);
			nations.push_back(Nation(i * N + j, pop, i, j));
		}
	}
	int res = 0;
	while (openBorder()) {
		++res;
		movePeople();
	}
	printf("%d", res);

	return 0;
}
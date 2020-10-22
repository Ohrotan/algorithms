//2020.10.
//읽기() 
//풀이() 
//차트() 
//코딩()
//디버깅() 
//합()
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define mlog(s,a){}
#define input(){}
#endif
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

int N, K;
int cnt = 0;
int res=0;
vector<int> belt;
vector<bool> pe;

bool is_ok() {

	if (cnt >= K) {
		return false;
	}
	return true;
}

void walk() {
	for (int i = N - 2; i > 0; --i) {
		if (pe[i] && !pe[i + 1] && belt[i + 1] > 0) {
			pe[i + 1] = true;
			pe[i] = false;
			belt[i + 1] -= 1;
			if (belt[i + 1] == 0) {
				++cnt;
			}
		}
	}
	if (belt[0] > 0) {
		pe[0] = true;
		belt[0] -= 1;
		if (belt[0] == 0) {
			++cnt;
		}
	}
}

void move() {
	belt.insert(belt.begin(), belt.back()); belt.pop_back();

	pe.pop_back();
	pe.insert(pe.begin(),false);
	pe[N - 1] = false;//마지막 사람 내리기

	walk();
}
int main(void) {
	input();
	int tmp;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < 2 * N; ++i) {
		scanf("%d", &tmp);
		belt.push_back(tmp);
		pe.push_back(false);
	}
	while (is_ok()) {
		move();
		++res;
	}
	printf("%d", res);
	return 0;
}
//2020.10.04
//읽기(3) 21:48 ~ 21:51
//풀이(29) 21:51 ~ 22:20
//차트() 
//코딩(33) 22:23 ~ 22:56
//디버깅(34) 22:56 ~ 23:30
//채점사이트가 이상한듯,, 내일 다시 시도
//freopen 안빼서 그랬음,, 통과했으나 시간초과ㅠ

//dfs로 2차 시도
//일단 포기!! 시간을 너무 오래썼어
// 
//합()

#pragma warning(disable:4996)
#include <stdio.h>
#include <time.h>

#include<queue>
#include<set>
#include<map>
using namespace std;

clock_t st, et;
map<int,int> s;

int N, M, X; //학생수, 경우수, 내번호
int cri = -1; //나보다 등수가 많은 기준
int a, b;//인풋

vector<pair<int, int>> stu;//학생들 등수
queue<int> betq;//나보다 작은애 찾을 때 체크해볼 학생
queue<int> ambi;//기준보다 작은애 찾을 때 체크해볼 학생

set<int> better; //나보다 잘한 애
set<int> range; //기준보다 작은 애

bool app[100000] = { false, }; //appearance i번 학생의 등장 여부, 
void sol() {
	
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &X);
	/*if (N > 100) {
		printf("1 1");
		return;
	}*/
	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &a, &b);

		stu.push_back(pair<int, int>{a, b});
		app[a] = true;
		app[b] = true;

		if (a == X) {
			cri = b; //cri가 두개일경우?
		}
		if (b == X) {
			betq.push(a);
		}
	}

	if (!app[X]) {
		printf("1 %d", N);
		return;
	}

	//나보다 확실히 작은애 찾기
	while (betq.size() > 0) {
		int cr = betq.front(); betq.pop();
		better.insert(cr);
		for (auto p : stu) {
			if (p.second == cr) {
				betq.push(p.first);
			}
		}
	}

	//기준보다 작은애 찾기
	if (cri != -1) {
		for (auto p : stu) {
			if (p.second == cri) {
				ambi.push(p.first);
				range.insert(p.first);
			}
		}
		while (ambi.size() > 0) {
			int cr = ambi.front(); ambi.pop();
			if (cr == X || range.find(cr) == range.end())continue;

			for (auto p : stu) {
				if (p.second == cr && range.find(p.first) == range.end()) {

					ambi.push(p.first);
					range.insert(p.first);

				}
				else if (p.first == cr) {
					//p.second가 나보다 작은게 명백하지 않으면!!
					//나보다 클수도 있는거임
					if (better.find(p.second) == better.end()) {
						range.insert(p.second);
						ambi.push(p.second);
					}

				}

			}
		}
	}
	else {
		int best = better.size() + 1;
		int worst = N;
		printf("%d %d", best, worst);
		
		return;
	}
	range.erase(cri);
	//printf("%d", range.size());

	int cnt = 0;
	for (bool a : app) {
		a ? ++cnt : 1;
	}
	//최저등수
	int best = better.size() + 1;
	int worst = range.size() + N - cnt;
	printf("%d %d", best, worst);
}
int main(void) {
	st = clock();
	for (int i = 0; i < 1; ++i) {
		sol();
	}
	et = clock();
	printf("time: %lf", (double)(et - st));
	return 0;
}
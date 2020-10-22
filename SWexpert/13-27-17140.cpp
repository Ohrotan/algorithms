//2020.10.14
//읽기(8) 17:25 ~ 17:33
//풀이(6) 17:33 ~ 17:39
//차트() 
//코딩(43) 17:39 ~ 18:22
//디버깅(60) 2100 2120   2305 2345
//소팅,카피 얘네들이 계속 문제가 생김
//시험에서 클래스 쓰거나 그냥 벡터로 옮겨넣기 해서 소팅하자
//답이 틀림
//1100

//sort 람다식 기억하기
//sort 할때 뭐가 트루?

//이번문제에서 얻어갈 게 많다!!!
//단순 구현 문제였는데, 열과 행을 오가는 문제를 내가 잘 못푼다.
//원래 배열에서 계속 변경하려고 해서 널포인터 등 오류가 많았다.
//다른 사람거 보니까, 횟수 세는 배열 따로, 새로 집어넣는 배열 따로 
//다 따로 만들고 최대값이 100으로 배열을 고정해놔서 100넘는 경우는 고려하지 않는 조건도 쉽게 구현하고
//널포인터 등 런타임 에러가 안 나는 방향으로 코딩했다
//기죽지 말고 배워가면 된다.
//시험전까지 최대한 "다양한" 실수를 많이 하는 것이 목적이다.
//그런 의미에서 이번 문제는 소팅하는 방법, 배열 잘쓰는 방법을 배웠다.

//소팅! set은 중복없음, 중복되면 뒤에게 안들어감, 삽입할때 트리형태로 정렬삽입됨
//set을 소트하려면 set< MYCLASS, COMP> 형식으로 만들고, COMP 클래스 만들기
class comp {
public:
	bool operator()(int a, int b)const {
		return true;
	}
}

//배열 잘쓰는법! 정해진 칸이 있으면 배열로 만들기
//기존 배열을 연산을 통해 바꾸는 거라면, 새로운 배열 만들어서 옮겨넣기
//vector는 copy 말고 assign 쓰기
//횟수 셀때, 횟수 세는 배열 만들어서 횟수 세기 cnt[n]++;

//합(180)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;
class numcnt {
public:
	int num;
	int cnt;
	numcnt(int n, int c) :num(n), cnt(c) {}
};
class compSet {
public:
	bool operator() (numcnt a, numcnt b) const {
		if (a.cnt < b.cnt) {
			return true;
		}if (a.cnt == b.cnt) {
			if (a.num < b.num) {
				return true;
			}
		}
		return false;
	}
};
//0행 0열 안씀
int R, C, K;
int res;
int maxr = 4, maxc = 4;
vector<vector<int>> a(4); //배열
set<numcnt, compSet> numset; //숫자, 등장횟수

void printA() {
	for (int i = 1; i < a.size(); ++i) {
		for (int j = 1; j < a[i].size(); ++j) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void init() {
	for (int i = 1; i < a.size(); ++i) {
		for (int j = 1; j < a[i].size(); ++j) {
			a[i][j] = 0;
		}

	}
}


vector<int> sortNumset() {
	vector<int> ret;
	ret.push_back(0);//0행, 0열 안쓰기때문
	vector<numcnt> tmp;


	//sort(numset.begin(), numset.end());
	for (auto item : numset) {
		tmp.push_back(numcnt(item.num, item.cnt));
	}
	//sort(tmp.begin(), tmp.end());

	for (auto item : tmp) {
		ret.push_back(item.num);
		ret.push_back(item.cnt);
		// numset.erase(el);
	}


	return ret;
}

int cntR(int r, int num) {
	int cnt = 0;
	for (auto item : a[r]) {
		if (num == item) {
			++cnt;
		}
	}
	return cnt;
}
int cntC(int c, int num) {
	int cnt = 0;
	for (auto col : a) {
		if (col.size() <= c)continue;
		if (num == col[c]) {
			++cnt;
		}
	}
	return cnt;
}

void opC(int initialR) {
	for (int j = 1; j < a[1].size(); ++j) {
		//한 열마다 클리어
		numset.clear();
		for (int i = 1; i < initialR; ++i) {
			if (a[i][j] == 0) continue;
			int cnt = cntC(j, a[i][j]);
			numset.insert(numcnt(a[i][j], cnt));
		}//모든 숫자의 등장횟수 찾아서 저장함

		vector<int> newarr = sortNumset();
		maxc = maxc < newarr.size() ? newarr.size() : maxc;//최대 길이 저장


		//새로운 배열로 바꾸기
		for (int k = 1; k < max(a.size(), newarr.size()); ++k) {
			if (k > 100) {
				break;
			}
			if (a.size() <= k) {
				a.push_back(vector<int>(maxc));
			}
			if (k < newarr.size()) {
				a[k][j] = newarr[k];
			}
			else {
				a[k][j] = 0;
			}
		}
	}


}
void opR() {

	for (int i = 1; i < a.size(); ++i) {
		//한 행마다 클리어
		numset.clear();
		for (int j = 1; j < a[i].size(); ++j) {
			if (a[i][j] == 0) continue;
			int cnt = cntR(i, a[i][j]);
			numset.insert(numcnt(a[i][j], cnt));
		}//모든 숫자의 등장횟수 찾아서 저장함

		vector<int> newarr = sortNumset();
		maxc = maxc < newarr.size() ? newarr.size() : maxc;//최대 길이 저장
		if (newarr.size() > 101) { newarr.resize(101); }
		a[i] = newarr; //새로운 배열로 바꾸기
	}
}
bool sol() {
	if (a.size() > R && a[R].size() > C && a[R][C] == K) {
		return true;
	}
	//행이 열보다 수가 적으면
	maxc = 0;
	if (a.size() < a[1].size()) {
		opC(a.size());
	}
	else {
		opR();
	}
	//0으로 채우기
	for (int i = 1; i < a.size(); ++i) {
		while (a[i].size() < maxc) {
			a[i].push_back(0);
		}
	}
	//printA();
	//printf("-----------------\n");
	return false;
}

int main(void) {
	input();

	a[1].resize(4, 0);
	a[2].resize(4, 0);
	a[3].resize(4, 0);
	scanf("%d %d %d", &R, &C, &K);
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	int res = 0;
	//printA();
	while (!sol() && res <= 100) { ++res; }
	if (res > 100) {
		res = -1;
	}
	printf("%d", res);

	return 0;
}
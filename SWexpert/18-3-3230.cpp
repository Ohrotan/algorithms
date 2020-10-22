//2020.10.06
//읽기() 17:40
//풀이() 
//차트() 
//코딩() 15:15
//디버깅() 
//합()
//BFS 한참만에 풀었다..
//내가 속도도 느리고 메모리 사용도 제일 느리고 많은 수준이네..?

#define DEBUG 1 

#pragma warning(disable:4996)

#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

class Tunnel {
public:
	int r1;//방1
	int r2;//방2
	int d;//거리
	Tunnel(int r, int rr, int di) :r1(r), r2(rr), d(di) {}
	/*bool operator<(const Tunnel& t) {
		return d<t.d;
	}*/
};

int n, rb1, rb2;//방개수,로봇번호
int r1, r2, d;
map<int, vector<Tunnel>> tmap;// 방번호, 터널정보

bool vis[100000] = { false, };//방문했니
vector<Tunnel> history;//지나온 유의미한 길
queue<Tunnel> q;

int main(void) {
	input();
	scanf("%d %d %d", &n, &rb1, &rb2);
	if (n == 1 || rb1==rb2) {
		printf("0");
		return 0;
	}
	for (int i = 0; i < n - 1; ++i) {
		scanf("%d %d %d", &r1, &r2, &d);

		map<int, vector<Tunnel>>::iterator it = tmap.find(r1);
		if (it != tmap.end()) {
			it->second.push_back(Tunnel(r1, r2, d));
		}
		else {
			vector<Tunnel> vec{ Tunnel(r1, r2, d) };
			tmap.insert(make_pair(r1, vec));
		}

		it = tmap.find(r2);
		if (it != tmap.end()) {
			it->second.push_back(Tunnel(r2, r1, d));
		}
		else {
			vector<Tunnel> vec{ Tunnel(r2, r1, d) };
			tmap.insert(make_pair(r2, vec));
		}
	}


	q.push(Tunnel(0, rb1, 0)); //이전 위치, 현재 위치, 거리
	while (q.size() > 0) {
		bool flag = false;
		Tunnel t = q.front(); q.pop();
		int r2 = t.r2;
		vis[r2] = true;
		for (auto tu : tmap.find(r2)->second) {


			if (!vis[tu.r2]) {
				flag = true;
				q.push(Tunnel(r2, tu.r2, tu.d));

				if (tu.r2 == rb2) {
					history.push_back(t);
					history.push_back(q.back());
					flag = false;
					q = queue<Tunnel>();
					break;
				}
			}
		}
		if (flag) {
			history.push_back(t);
		}


	}


	reverse(history.begin(), history.end());
	Tunnel last = history.front();
	int longd = last.d;
	int res = last.d;
	log("last", last.r2);
	for (auto a : history) {
		if (a.r2 != last.r1) {
			continue;
		}
		if (a.d > longd) {
			longd = a.d;
		}
		res += a.d;
		last = a;

		//printf("pa:%3d, me:%3d, d:%3d, res:%d\n", a.r1, a.r2, a.d, res);
		//auto a = max_element(history.begin(),history.end());

	}
	log("longd", longd);
	printf("%d", res - longd);

	return 0;
}
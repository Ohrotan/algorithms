//2020.10.
//읽기() 
//풀이() 
//차트() 
//코딩()
//디버깅() 
//합()

#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include<list>
#include<map>
#include<queue>
#include <algorithm>
using namespace std;

int n, m;
int p, f, d;
//int por, fac, day; 


int por[10001] = { 0, }; //공항으로 지목받은 횟수
int fac[10001] = { 0, }; //
int res = 0;
class Road {
public:
	int p;
	int f;
	int d;

	Road(int p, int f, int d) {
		this->p = p;
		this->f = f;
		this->d = d;
	}
	bool operator==(Road& r) {
		if (p == r.p && f == r.f && d == r.d) {
			return true;
		}
		return false;
	}
};
list<Road> ro;
list<Road> remain;
map<int, vector<Road>> pmap;
map<int, vector<Road>> fmap;
queue<int> pq;
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &p, &f, &d);
		ro.push_back(Road(p, f, d));
		
		pmap.insert(make_pair(p, Road(p, f, d)));
		fmap.insert(make_pair(f, Road(p, f, d)));
		++(por[p]);
		++(fac[f]);
	}
	//갈 곳 없는 애 있으면 -1
	for (int i = 1; i <= n; ++i) {
		if (por[i] == 0 || fac[i] == 0) {
			printf("-1");
			return 0;
		}
	}
	pq.push(1);//1번공항으로 시작

	while (pq.size() > 0) {
		int p = pq.front(); pq.pop();
		Road r = pmap.find(p)->second;

	}

	////갈곳이 1개밖에 없는 애들 먼저 처리
	//list<Road> remain(ro);
	//for (auto r : ro) {
	//	if (por[r.p] == 1 || fac[r.f] == 1) {
	//		por[r.p] = -1;
	//		por[r.f] = -1;
	//		res = max(res, r.d);
	//		remain.remove(r);
	//	}
	//}
	//printf("%d", remain.size());
	////갈곳 여러군데인 애들  맵으로 처리
	//for (int i = 0; i <= remain.size(); ++i) {
	//	;
	//}


	return 0;
}
//2020.10.
//�б�() 
//Ǯ��() 
//��Ʈ() 
//�ڵ�()
//�����() 
//��()

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


int por[10001] = { 0, }; //�������� ������� Ƚ��
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
	//�� �� ���� �� ������ -1
	for (int i = 1; i <= n; ++i) {
		if (por[i] == 0 || fac[i] == 0) {
			printf("-1");
			return 0;
		}
	}
	pq.push(1);//1���������� ����

	while (pq.size() > 0) {
		int p = pq.front(); pq.pop();
		Road r = pmap.find(p)->second;

	}

	////������ 1���ۿ� ���� �ֵ� ���� ó��
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
	////���� ���������� �ֵ�  ������ ó��
	//for (int i = 0; i <= remain.size(); ++i) {
	//	;
	//}


	return 0;
}
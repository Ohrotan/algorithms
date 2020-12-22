//2020.09.22 09:00 ~ 9:45 (ns-chart)
//10:05 ~ 11:04 (coding)
#pragma warning(disable:4996)

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int TC = 0;
int tc = 0;
int v = 0; //정점개수
int e = 0; //간선수
int a = 0; //주어진 자식 정점1
int b = 0;//주어진 자식 정점2
int rel[10001] = { 0, };//간선관계 rel[자식]=부모
list<int> ap; //a의 조상 리스트, 시작은 a, 마지막은 b와 공통 조상 or 그 위 조상
list<int> bp;
queue<int> subtree;//서브트리 개수찾기 위한 큐

void initRel() {
	for (int i = 0; i <= v; ++i) {
		rel[i] = 0;
	}
}

int findParent() {
	list<int> list1 = ap;
	list<int> list2 = bp;
	list<int> tmp;
	int lastP = list1.back();
	while (1) {
		
		for (int i : list2) {
			if (i == lastP) {
				return i;
			}
		}

		tmp = list2;
		list2 = list1;
		list1 = tmp;

		lastP = rel[list1.back()];
		list1.push_back(lastP); //마지막의 부모 찾아서 넣기
	}
	return -1;
}

int countSubtree() {
	int cnt = 1;
	int node;
	while (!subtree.empty()) {
		node = subtree.front();
		subtree.pop();
		for (int i = 1; i <= v; ++i) {
			if (rel[i] == node) {
				subtree.push(i);
				++cnt;
			}
		}
	}
	return cnt;
}
int main(void) {
	int p, c = 0;//간선에서 부모 자식
	scanf("%d", &TC);
	for (tc = 1; tc <= TC; ++tc) {
		scanf("%d %d %d %d", &v, &e, &a, &b);
		ap.push_back(a);
		bp.push_back(b);

		for (int i = 0; i < e; ++i) {
			scanf("%d %d", &p, &c);
			rel[c] = p;
		}
		int result = findParent();
		subtree.push(result);
		int cnt = countSubtree();
		
		//데이터삭제
		initRel();
		ap.clear();
		bp.clear();
		printf("#%d %d %d\n",tc,result,cnt);
	}
	return 0;
}

//2020.09.22 09:00 ~ 9:45 (ns-chart)
//10:05 ~ 11:04 (coding)
#pragma warning(disable:4996)

#include<stdio.h>
#include<list>
#include<queue>
using namespace std;

int TC = 0;
int tc = 0;
int v = 0; //��������
int e = 0; //������
int a = 0; //�־��� �ڽ� ����1
int b = 0;//�־��� �ڽ� ����2
int rel[10001] = { 0, };//�������� rel[�ڽ�]=�θ�
list<int> ap; //a�� ���� ����Ʈ, ������ a, �������� b�� ���� ���� or �� �� ����
list<int> bp;
queue<int> subtree;//����Ʈ�� ����ã�� ���� ť

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
		list1.push_back(lastP); //�������� �θ� ã�Ƽ� �ֱ�
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
	int p, c = 0;//�������� �θ� �ڽ�
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
		
		//�����ͻ���
		initRel();
		ap.clear();
		bp.clear();
		printf("#%d %d %d\n",tc,result,cnt);
	}
	return 0;
}

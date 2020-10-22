//2020.10.14
//�б�(8) 17:25 ~ 17:33
//Ǯ��(6) 17:33 ~ 17:39
//��Ʈ() 
//�ڵ�(43) 17:39 ~ 18:22
//�����(60) 2100 2120   2305 2345
//����,ī�� ��׵��� ��� ������ ����
//���迡�� Ŭ���� ���ų� �׳� ���ͷ� �Űֱܳ� �ؼ� ��������
//���� Ʋ��
//1100

//sort ���ٽ� ����ϱ�
//sort �Ҷ� ���� Ʈ��?

//�̹��������� �� �� ����!!!
//�ܼ� ���� �������µ�, ���� ���� ������ ������ ���� �� ��Ǭ��.
//���� �迭���� ��� �����Ϸ��� �ؼ� �������� �� ������ ���Ҵ�.
//�ٸ� ����� ���ϱ�, Ƚ�� ���� �迭 ����, ���� ����ִ� �迭 ���� 
//�� ���� ����� �ִ밪�� 100���� �迭�� �����س��� 100�Ѵ� ���� ������� �ʴ� ���ǵ� ���� �����ϰ�
//�������� �� ��Ÿ�� ������ �� ���� �������� �ڵ��ߴ�
//������ ���� ������� �ȴ�.
//���������� �ִ��� "�پ���" �Ǽ��� ���� �ϴ� ���� �����̴�.
//�׷� �ǹ̿��� �̹� ������ �����ϴ� ���, �迭 �߾��� ����� �����.

//����! set�� �ߺ�����, �ߺ��Ǹ� �ڿ��� �ȵ�, �����Ҷ� Ʈ�����·� ���Ļ��Ե�
//set�� ��Ʈ�Ϸ��� set< MYCLASS, COMP> �������� �����, COMP Ŭ���� �����
class comp {
public:
	bool operator()(int a, int b)const {
		return true;
	}
}

//�迭 �߾��¹�! ������ ĭ�� ������ �迭�� �����
//���� �迭�� ������ ���� �ٲٴ� �Ŷ��, ���ο� �迭 ���� �Űֱܳ�
//vector�� copy ���� assign ����
//Ƚ�� ����, Ƚ�� ���� �迭 ���� Ƚ�� ���� cnt[n]++;

//��(180)
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
//0�� 0�� �Ⱦ�
int R, C, K;
int res;
int maxr = 4, maxc = 4;
vector<vector<int>> a(4); //�迭
set<numcnt, compSet> numset; //����, ����Ƚ��

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
	ret.push_back(0);//0��, 0�� �Ⱦ��⶧��
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
		//�� ������ Ŭ����
		numset.clear();
		for (int i = 1; i < initialR; ++i) {
			if (a[i][j] == 0) continue;
			int cnt = cntC(j, a[i][j]);
			numset.insert(numcnt(a[i][j], cnt));
		}//��� ������ ����Ƚ�� ã�Ƽ� ������

		vector<int> newarr = sortNumset();
		maxc = maxc < newarr.size() ? newarr.size() : maxc;//�ִ� ���� ����


		//���ο� �迭�� �ٲٱ�
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
		//�� �ึ�� Ŭ����
		numset.clear();
		for (int j = 1; j < a[i].size(); ++j) {
			if (a[i][j] == 0) continue;
			int cnt = cntR(i, a[i][j]);
			numset.insert(numcnt(a[i][j], cnt));
		}//��� ������ ����Ƚ�� ã�Ƽ� ������

		vector<int> newarr = sortNumset();
		maxc = maxc < newarr.size() ? newarr.size() : maxc;//�ִ� ���� ����
		if (newarr.size() > 101) { newarr.resize(101); }
		a[i] = newarr; //���ο� �迭�� �ٲٱ�
	}
}
bool sol() {
	if (a.size() > R && a[R].size() > C && a[R][C] == K) {
		return true;
	}
	//���� ������ ���� ������
	maxc = 0;
	if (a.size() < a[1].size()) {
		opC(a.size());
	}
	else {
		opR();
	}
	//0���� ä���
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
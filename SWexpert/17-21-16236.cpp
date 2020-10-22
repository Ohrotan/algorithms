//2020.10.15
//�б�(5) 1719 1724
//Ǯ��(15) 1724 1739
//��Ʈ() 
//�ڵ�(36) 1739 1815
//�����(45) 1815 1900
//0�� �κе� ����� ����ϰ� ����
//�켱���� �߸� ������
//��(141)

//�� �񽺿����� �´µ� �����ϴ� Ʋ��
//2�������(36) 1900 1936

//����� ���غ��ϱ� ���� �¾Ҵµ�, �ð��ʰ���
//dp �Ƚᵵ �Ǵ��� �˾Ҵµ�, ���� Ǯ������ DP ��ߵǴ��� ����ؾ߰ڴ�.
//3���ڵ�() 0924
//dp�� ���ʿ䰡 ������, ��ũũ�⸦ 9�� �ξ �ڱⰡ �ڱ⸦ ��� �Ծ ���� ���ѷ���
//pro���� step��ü���� ���۷����� ��������� ����
//�׷����� ���� Ʋ���� ��..?
//��.. notyet �迭�� true�� �ʱ�ȭ �Ƚ�Ų�� ������ ������ ����Ʈ�� �޶� ��� ���� Ʋ�ȴ� �Ŵ�..


//�׷�, ���縸ŭ ���� ����!
//1. �켱���� ���� �� ������ Ŭ���� ���� operator< �����
//2. ���ú������� ������ ������ �ʱ�ȭ�ϱ�
//3. ����� �� �ִ��� ���̽� ���� ���ϱ�
//��()

//priority q ã�ƺ���
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <queue>

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

class Step {
public:
	int pr;//����ĭ
	int pc;
	int r;//����ĭ
	int c;
	int cnt;//������� ���µ� �ɸ� �̵�Ƚ��
	Step(int _pr, int _pc, int _r, int _c, int _cnt) :pr(_pr), pc(_pc), r(_r), c(_c), cnt(_cnt) {}
	bool operator<(Step a)const {
		if (cnt < a.cnt) {
			return true;
		}
		else if (cnt == a.cnt) {
			if (r < a.r) {
				return true;
			}
			else if (r == a.r) {
				if (c < a.c) {
					return true;
				}
			}
		}
		return false;
	}
};


int N;
int map[20][20];

int sr, sc, shark;//��� ��ġ, ũ��
int cnt;//���� ����� ���� ��

int mr[4] = { -1,0,0,1 };//���¿���
int mc[4] = { 0,-1,1,0 };
int res = 0;

void printMap() {

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%d", map[i][j]);
		}
		nn()
	}
	mlog("time", res);
	mlog("cnt", cnt);
	mlog("shark", shark);
	line()
}

bool inborder(int r, int c) {
	if (r < N && c < N && c >= 0 && r >= 0) {
		return true;
	}
	return false;
}

bool eat(Step step) {
	if (map[step.r][step.c]!=0 && map[step.r][step.c] < shark) {
		++cnt;
		map[step.r][step.c] = 0;
		if (cnt == shark) {
			cnt = 0;
			++shark;
		}
		return true;
	}
	return false;
}

//�����̷��� ĭ
bool valid(int nr, int nc) {
	if (!inborder(nr, nc)) {
		return false;
	}
	if (map[nr][nc] > shark) {
		return false;
	}
	return true;
}

//�ǾհŰ� ť���� ���� �ֵ��߿��� �켱���� ������ ������ �ǵڷ� ����
void prio(vector<Step> &q) {
	bool flag = true;
	while (flag) {
		flag = false;
		Step f = q.front();
		for (int i = 1; i < q.size(); ++i) {
			//�̵�Ƚ���� ���ų� �۰�
			//r�� �۰�
			//r�� ���ٸ� c�� �����ְ�
			//�ִٸ� �Ǿ����� ������
			if (f.cnt > q[i].cnt) {
				q.insert(q.begin(), q[i]);
				q.erase(q.begin() + i + 1);
				flag = true;
				break;
			}
			else if (f.cnt==q[i].cnt && (f.r > q[i].r || (f.r == q[i].r && f.c > q[i].c))) {
				q.insert(q.begin(), q[i]);
				q.erase(q.begin()+i+1);
				flag = true;
				break;
			}
		}
	}
}

bool findFish() {
	int nr, nc;
	bool notyet[20][20];//true�� �湮 ���ߴٴ°�!!
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			notyet[i][j] = true;
		}
	}
	vector<Step> q;
	q.push_back(Step(sr, sc, sr, sc, 0));
	notyet[sr][sc] = false;

	while (q.size() > 0) {
		sort(q.begin(), q.end());
		Step now = q.front(); q.erase(q.begin());
		if (eat(now)) {
			map[sr][sc] = 0;//���� ����ڸ��� 0
			sr = now.r;
			sc = now.c;
			res += now.cnt;
			map[sr][sc] = 0;//���ο� ��� �ڸ�
			printMap();
			return true;
		}

		for (int i = 0; i < 4; ++i) {
			nr = now.r + mr[i];
			nc = now.c + mc[i];
			if (valid(nr, nc) && notyet[nr][nc]) {
				notyet[nr][nc] = false;
				q.push_back(Step(now.r, now.c, nr, nc, now.cnt + 1));
			}
		}
	}
	return false;
}

int main(void) {
	input();
	int tmp;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &tmp);
			map[i][j] = tmp;
			if (tmp == 9) {
				map[i][j] = 0;
				sr = i;
				sc = j;
				shark = 2;//ũ��
			}
		}

	}

	while (findFish());

	printf("%d", res);
	return 0;
}
//2020.10.13
//�б�(13) 17:29 17:42
//Ǯ��(21) 17:42 18:03
//�ѱ���Ʈ(8) 18:03 18:11
//��Ʈ() 
//�ڵ�(129) 18:11 20:20
//�����() 
//��(171)

//Ǯ���ߴµ� �ڲ� Ʋ��, �̹� ���ΰ� ����. ���亸��

//��Ģ���� ����� ��ã�Ƽ� �ᱹ ��Ǯ����, ��Ģ���� ã������ ���ݸ� �� �����غ����� ��������

//������ �ôµ� ���߿� �ٽ� Ǯ�ų� �����غ���~


#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N, R, C, D, G;

vector<vector<pair<int, int>>> dragon;
//���̽����� (r,c)�� �迭

bool map[101][101] = { 0 };

pair<int, int> spos;//������
pair<int, int> epos;//������
int res = 0;
void count() {
	for (auto d : dragon) {
		for (auto a : d) {
			map[a.first][a.second] = true;
			//printf("(%d,%d) ", a.first, a.second);
		}
		//printf("\n");
	}

	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 10; ++j) {
			printf("%d", map[i][j]);
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) {
				++res;
			}
		}
		printf("\n");
	}
}

void printD() {
	for (auto d : dragon) {
		for (auto a : d) {
			printf("(%d,%d) ", a.first, a.second);
		}
		printf("\n");
	}
}

pair<int, int> firstLine() {
	int endR, endC;
	switch (D) {
	case 0:
		endR = R;
		endC = C + 1;
		break;
	case 1:
		endR = R - 1;
		endC = C;
		break;
	case 2:
		endR = R;
		endC = C - 1;
		break;
	case 3:
		endR = R + 1;
		endC = C;
		break;
	}
	return pair<int, int>(endR, endC);
}

pair<int, int> turn(pair<int, int> pos, bool rot) {
	pair<int, int> ret;
	//rot = true;

	//��-��, ����Ī
	ret.first = epos.first - pos.first; //���� - ��
	ret.second = epos.second - pos.second; //���� - ��

	if (!rot) {
		if (D % 2 == 0) {
			ret.first *= -1;
		}
		else {
			ret.second *= -1;
		}
	}
	else {
		if (D % 2 == 0) {
			ret.second *= -1;
		}
		else {
			ret.first *= -1;
		}
	}
	ret.first += epos.first;
	ret.second += epos.second;

	return ret;
}
void makeDragon() {
	vector<pair<int, int>> points;

	//0����
	spos = pair<int, int>(R, C);
	epos = firstLine();
	points.push_back(spos);
	printf("(%d,%d)", points.back().first, points.back().second);
	points.push_back(epos);
	printf("(%d,%d)", points.back().first, points.back().second);
	printf("\n");
	points.push_back(turn(points[0], true));//�� ������ ����ֱ�
	printf("(%d,%d)\n", points.back().first, points.back().second);
	epos = points.back();
	for (int i = 1; i < G; ++i) {
		//�ڿ������� ����
		//�ڿ��� ù��°�� �������̴ϱ� ������ ����

		for (int j = points.size() - 2; j >= 0; --j) {
			points.push_back(turn(points[j],false));//�� ������ ����ֱ�
			printf("(%d,%d)", points.back().first, points.back().second);
		}
		//������ ���ο� �������� �ٲ��ֱ�
		epos = points.back();
		printf("\n");
	}


	dragon.push_back(points);
	printf("------------------------------\n");
}
int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d %d", &C, &R, &D, &G);
		makeDragon();
	}

	printD();
	count();
	printf("%d", res);
	return 0;
}
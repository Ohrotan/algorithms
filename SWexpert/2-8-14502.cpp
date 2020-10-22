//2020.10.10
//�б�(5) 20:12 ~ 20:17
//��Ʈ(26) 20:17 ~ 20:43 
//�ڵ�(60) 20:57 ~ 21:57 ��Ʈ��� �ڵ��� ���� �Ȱɷȴµ� ������� ������
//�����(20) 23:11 ~ 23:21
//nearWall���� k����ϴµ� i�� �߸�����
//mapPrint �ּ�ó���Ϸ��ٰ� ���� map = 2 �̰� �ּ�ó���ع�����
//�̰͵鶧���� ���� ����ߴ�
//�׷��� ó���� ��Ʈ�Ἥ �� ����ߴ�.
//�����δ� ��Ʈ�� �� �Ĳ��ϰ� ����. �׷��� ������ �ذ�� ��
//��(111)

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <array>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif

#define MAX(a,b) (a>b?a:b)

#include <queue>

using namespace std;

int N, M;
int safety;
int res = 0;

array<array<int, 8>, 8> map;
queue<int> rq; //���̷���ť row q
queue<int> cq; //���̷���ť col q

int dr[8] = { -1,1,0,0,-1,-1,1,1 }; //�����¿� �밢��
int dc[8] = { 0,0,-1,1,-1,1,-1,1 };

void mapPrint(array<array<int, 8>, 8> m) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%d", m[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
//���̷��� �۶߸��� �� �� ��������
int spread() {
	//���� ����
	queue<int> lrq(rq); //���̷���ť row q
	queue<int> lcq(cq); //���̷���ť col q
	array<array<int, 8>, 8> lmap(map);
	int safe = safety;

	//mapPrint(lmap);

	while (lrq.size() > 0) {
		int r = lrq.front(); lrq.pop();
		int c = lcq.front(); lcq.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
				if (lmap[nr][nc] == 0) {
					--safe;
					if (res >= safe) {
						//printf("--------end----------\n");
						//mapPrint(lmap);
						return safe; //�� ���� ���̻� �� �� ����
					}
					lmap[nr][nc] = 2;
					//mapPrint(lmap);
					lrq.push(nr);
					lcq.push(nc);
				}
			}
		}

	}
	//printf("--------end----------\n");
	//mapPrint(lmap);
	return safe;
}

//�����¿�밢���� ���� �ִ���
bool nearWall(int i, int j) {
	int ni, nj;
	for (int k = 0; k < 8; ++k) {
		ni = i + dr[k];
		nj = j + dc[k];

		//��輱�̸�
		if (ni < 0 || nj < 0 || ni == N || nj == M) {
			return true;
		}
		//�ֺ��� ������
		if (map[ni][nj] == 1) {
			return true;
		}
	}
	return false;
}

int main(void) {
	input();
	int tmp;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &tmp);
			if (tmp == 0) {
				++safety;
			}
			if (tmp == 2) {
				rq.push(i);
				cq.push(j);
			}
			map[i][j] = tmp;
		}
	}

	safety -= 3;//�� 3�� �����Ŵϱ�

	for (int k = 0; k < N * M; ++k) {
		int i1 = k / M;
		int j1 = k % M;
		if (map[i1][j1] == 0 && nearWall(i1, j1)) {
			map[i1][j1] = 1;

			for (int k2 = k + 1; k2 < N * M; ++k2) {
				int i2 = k2 / M;
				int j2 = k2 % M;
				if (map[i2][j2] == 0 && nearWall(i2, j2)) {
					map[i2][j2] = 1;

					for (int k3 = k2 + 1; k3 < N * M; ++k3) {
						int i3 = k3 / M;
						int j3 = k3 % M;
						if (map[i3][j3] == 0 && nearWall(i3, j3)) {
							map[i3][j3] = 1;

							res = MAX(res, spread());
							//mapPrint(map);

							map[i3][j3] = 0;
						}
					}

					map[i2][j2] = 0;
				}
			}
 
			map[i1][j1] = 0;
		}

	}

	printf("%d", res);
	return 0;
}
//2020.10.13
//�б�(10) 21:22 ~ 21:32
//Ǯ��() 
//��Ʈ() 
//�ڵ�(28) 21:32 ~ 22:00
//�����(17) 22:00 ~ 22:17
//��(55)

//������ ������.
//������ϴµ� �ð��� �ɷȴ�����
//r,c�� 0�� �����ϴ��� ���ϴ��� ���� ������ ��Ȯ�� �� ����
//������ ��, ����� ���� �� �� ��
//�Ѵ� ��Ȯ���� �ʴٴ� ���� �˾�����, �����Ƽ� �ϴ� �غ��� �ȵǸ� Ȯ���ؾ��� ��� �������� �ߴ�
//��Ȯ���� ���� ���� ���� ����, �׶� �ٷ� �̰� ��Ȯ���� Ȯ���غ���

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int N,M,r,c,d;

//��������� �������� �̵��ϴ� ��
int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

bool map[51][51] = { false };
bool clean[51][51] = { false };

void printMap() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <M; ++j) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
}
void printClean() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%d", clean[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(void) {
	input();

	int t,nr,nc;

	scanf("%d %d", &N,&M);
	scanf("%d %d %d", &r, &c, &d);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &t);
			map[i][j] = !t;

			//printf("%d", map[i][j]);
		}
	}
	while (1) {
		//printf("now: %d %d\n", r, c);
		if (map[r][c]&&!clean[r][c]) {
			clean[r][c] = true;
		}
		//����ĭ
		nr = r + dr[d];
		nc = c + dc[d];

		//���� �ְ�, ��û�Ҹ�
		if (map[nr][nc] && !clean[nr][nc])
		{
			d = (d+3)%4;//ȸ��
			r = nr, c = nc;//�̵�
			clean[nr][nc] = true;//û��
		}
		//����� ���̰ų� û���߰ų�
		else if ((!map[r+1][c]||clean[r+1][c])&&
			(!map[r - 1][c] || clean[r - 1][c])&&
			(!map[r][c+1] || clean[r ][c+1])&&
			(!map[r][c-1] || clean[r][c-1])) {
			//����
			nr = r + dr[(d+3)%4];
			nc = c + dc[(d+3)%4];
			if (!map[nr][nc]) {
				//�ڰ� ���̸�
				break;//����
			}
			//��ĭ ����
			r = nr;
			c = nc;
		}
		//���ʺ��� ���̰ų�, û���߰ų�
		else {
			d = (d + 3) % 4;//ȸ��
		}

		//printClean();
	}
	int res = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (clean[i][j]) ++res;
		}
	}
	//printMap();

	printf("%d", res);
	return 0;
}
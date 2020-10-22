//2020.10.09
//�б�(9) 21:18 ~ 21:27
//Ǯ��(4) 21:27 ~ 21:31
//��Ʈ() 
//�ڵ�(75) 21:31 ~ 22:46 �� dfs ��Ʈ��ŷ���� �Ϸ��� �ߴµ� �̰Ŵ� �� �ƴѰ� ���⵵ �ϰ�.. ���� �ٽ� �����غ���
//�����(60) �ᱹ ��Ʈ��ŷ���� Ǭ�� �¾ҳ�.. ��� ��� Ʋ�ȴ��� �� ����ϰ� ������ϴϱ� �����
//���̵� ��ƴٱ⺸�� �̰� ���� ������ ���� �ڵ尡 ������������, 
//������ ���� �ڵ尡 ������ٺ��ϱ� �Ǽ��� �������� Ǫ�µ� �����ɷȴ�
//������, ���� �ͼ������� �ǰ�, �Ǽ� ���ϰ� �Ĳ��� üũ�ϸ� ��
//��Ʈ �ۼ��ؼ� Ǯ���
//��(180)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <array>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int n;
vector<int> anshis;
vector<int> history;
array<int, 17> fx; //1�� ������� x��ǥ
array<int, 17> fy;
array<int, 17> fd; //������� ����

array<array<int, 4>, 4> map; //����� ��ġ��
array<array<int, 4>, 4> dir; //����� �����
array<int, 9> movex = { 0,-1,-1,0,1,1,1,0,-1 };
array<int, 9> movey = { 0,0,-1,-1,-1,0,1,1,1 };

int sx = -1; //��� ��ġ
int sy = -1; //��� ��ġ
int sd = 6; //��� ����

int res = 0; //���� ������ȣ ��

int answer =0;

void mapPrint() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == sx && j == sy) {
				printf("  S/%d ",sd);
			}
			else {
				printf("%3d/%d ", map[i][j], dir[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n");
}

void moveFish() {
	int x, y, d;
	int mx, my;
	for (int i = 1; i < 17; ++i) {
		if (fx[i] == -1) {
			//������� ���� �����
			continue;
		}
		//printf("%d�� ����� ��ġ �ٲ�\n",i);
		bool nowhere = false;
		x = fx[i];
		y = fy[i];
		d = fd[i];

		mx = x + movex[d];
		my = y + movey[d];

		int cnt = 1; //����Ⱑ ���� ã�� Ƚ��
		//�ٱ��̰ų� �� ������
		while (mx > 3 || mx < 0 || my>3 || my < 0 || (mx == sx && my == sy)) {
			//�ݽð�� ����
			if (cnt == 8) {
				//�� ã�ƺ��� �̵�����
				nowhere = true;
				break;
			}

			d = d == 8 ? 1 : d + 1;
			mx = x + movex[d];
			my = y + movey[d];
			++cnt;
		}
		if (nowhere) {
			continue; //����Ⱑ ���̻� ���ڸ� ��� ���� ��������� ��
		}
		fx[i] = mx;
		fy[i] = my;
		int other = map[mx][my];
		map[mx][my] = map[x][y];
		map[x][y] = other;
		fx[other] = x;
		fy[other] = y;


		fd[i] = d;
		dir[x][y] = dir[mx][my];
		dir[mx][my] = d;
		//��ȯ
		

	}
	//mapPrint();
	//printf("------fish moved---------\n");
}
void eat(int x, int y) {
	history.push_back(map[x][y]);
	res += map[x][y];
	sx = x;
	sy = y;
	sd = dir[x][y];

	fx[map[x][y]] = -1;
	fy[map[x][y]] = -1;
	fd[map[x][y]] = -1;
	map[x][y] = 0;
	dir[x][y] = 0;
	//mapPrint();
	
}

void eat() {
	int newx = sx + movex[sd];
	int newy = sy + movey[sd];

	//�� �̵��� �� ���� ��
	while (newx >= 0 && newy >= 0 && newx < 4 && newy < 4) {
		//���� ���� ���
		int lres = res;
		array<int, 17> lfx = fx; //1�� ������� x��ǥ
		array<int, 17> lfy = fy;
		array<int, 17> lfd = fd; //������� ����


		array<array<int, 4>, 4> lmap = map; //����� ��ġ��
		array<array<int, 4>, 4> ldir = dir; //����� �����
		int lsx = sx; //��� ��ġ
		int lsy = sy; //��� ��ġ
		int lsd = sd; //��� ����

		//���
		vector<int> lh(history);


		if (map[newx][newy] != 0) {

			res += map[newx][newy];
			eat(newx, newy);
			moveFish();
			eat();
		}
		if (answer < res) {
			answer = res;
			anshis = history;
		}
		//printf("-----------------back--------------\n");

		//����
		res = lres;
		fx = lfx;
		fy = lfy;
		fd = lfd;
		map = lmap;
		dir = ldir;
		sx = lsx;
		sy = lsy;
		sd = lsd;
		history = lh;
	/*	mapPrint();
		printf("-------------------���� ��---------------------\n");
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				printf("%3d/%d ", lmap[i][j], ldir[i][j]);
			}
			printf("\n");
		}
		printf("\n");*/


		newx += movex[sd];
		newy += movey[sd];
		while (newx >= 0 && newy >= 0 && newx < 4 && newy < 4&&map[newx][newy] == 0) {
			newx += movex[sd];
			newy += movey[sd];
		}
	}
}
int main(void) {
	input();
	for (int i = 0; i < 4; ++i) {
		scanf("%d %d %d %d %d %d %d %d", &map[i][0], &dir[i][0], &map[i][1],
			&dir[i][1], &map[i][2], &dir[i][2], &map[i][3], &dir[i][3]);
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int fish = map[i][j];
			fx[fish] = i;
			fy[fish] = j;
			fd[fish] = dir[i][j];
		}
	}

	//mapPrint();
	//�� ����
	eat(0, 0);
	moveFish();
	eat();
	//mapPrint();
	//printf("----------------------------------------\n");
	//printf("----------------------------------------\n");
	//mapPrint();
	answer = 0;
	for (auto h : anshis) {
		answer+= h;
	}
	printf("%d", answer);
	return 0;
}
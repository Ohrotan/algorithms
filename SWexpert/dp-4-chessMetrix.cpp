//2020.09.27 09:40 ~ �Ϸ�

#include<queue>

using namespace std;

int cr, cc; //current row, col
int mc[16] = { -2,-2,-1,-1,-1,-1,-1,0,0,1,1,1,1,1,2,2 }; //move col
int mr[16] = { -1,1,-2,-1,0,1,2,-1,1,-2,-1,0,1,2,-1,1 }; //move row
int nr, nc; //next row, col
int sr, sc, er, ec; //start, end

int num; //����ũ��
int run; //�̵��ؾ��� Ƚ��
long long cnt; //�̵� ���(����)

queue<int> rq, cq; //�湮�� ��ġ row, col
int board[5][5]; //�� �ڸ��� ������� �̵��� Ƚ��

void input() {
	num = 5;
	sr = 0;
	sc = 0;

	er = 4;
	ec = 3;

	run = 3;
}

void init() {
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			board[i][j] = 0;
		}
	}
}

void printB() {
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int main(void) {
	input();

	init();

	rq.push(sr);
	cq.push(sc);

	while (rq.size() > 0) {
		cr = rq.front(); rq.pop();
		cc = cq.front(); cq.pop();
		if (board[cr][cc] == run) {
			break; //while (rq.size() == 0) { rq.pop(); }
		}
		//16�� �̵��� �� �ִ� ����� ����
		for (int i = 0; i < 16; ++i) {
			nr = cr + mr[i];
			nc = cc + mc[i];

			if (nr<0 || nc<0 || nr>num - 1 || nc>num - 1) {
				continue;
			}

			if (board[cr][cc] == run - 1) {
				if (nc == ec && nr == er) {
					++cnt;
					continue;
				}
			}
			else {
				board[nr][nc] = board[cr][cc] + 1; 
				rq.push(nr);
				cq.push(nc);
				printB();
			}
			
		}
	}
	printf("end");
	printf("result: %ld", cnt);

	return 0;
}
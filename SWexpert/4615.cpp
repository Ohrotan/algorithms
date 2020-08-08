#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

int T; //test case
int N; //board number
int M; //turn num
const char B = '1'; //black
const char W = '2'; //white
const char E = '0'; //empty
char board[9][9] = { 0, };
int a, b; //point
char me = B; //player
char u = W; //other player
int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,-1},{0,-1},{1,0},{-1,-1} };
int whiteNum;
int blackNum;
vector<pair<int, int>> result;

int getNum() {
	int res = 0;
	int input = getchar();
	while (input <= '9' && input >= '0') {
		res = (res * 10) + (input - '0');
		input = getchar();
	}

	return res;
}
void initBoard() {
	memset(board, E, sizeof(char) * 81);
	board[N / 2][N / 2] = W;
	board[N / 2][N / 2 + 1] = B;
	board[N / 2 + 1][N / 2] = B;
	board[N / 2 + 1][N / 2 + 1] = W;
	whiteNum = 2;
	blackNum = 2;
}
void putStone() {
	
	if (me == B) {
		board[a][b] = B;
		u = W;
		++blackNum;
	}
	else {
		board[a][b] = W;
		u = B;
		++whiteNum;
	}
}
void turnStone() {
	if (me == B) {
		++blackNum;
		--whiteNum;
	}
	else {
		++whiteNum;
		--blackNum;
	}
}
void printBoard() {
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
int main(void) {
	int dx, dy = 0;
	T = getNum();

	for (int t = 0; t < T; ++t) {
		N = getchar() - '0'; getchar();
		M = getNum();
		initBoard();
		for (int m = 0; m < M; ++m) {
			a = getchar() - '0'; getchar();
			b = getchar() - '0'; getchar();
			me = getchar(); getchar();
			putStone();
			//printBoard();
			for (int i = 0; i < 8; ++i) {
				dx = a + dir[i][0];
				dy = b + dir[i][1];
				
				if (dx > N || dx<1 || dy > N || dy < 1) {
					continue;
				}
				//printf("dx:%d dy:%d\n", dx, dy);
				if (board[dx][dy] == u) {
					int j = 1;
					while (1) {

						dx = a + ((++j) * dir[i][0]);
						dy = b + j * dir[i][1];
						//printf("dx:%d dy:%d val:%c=%c j:%d\n", dx, dy,board[dx][dy],me,j);
						if (dx > N || dx<1 || dy > N || dy < 1 || board[dx][dy] == E) {
							break;
						}
						else if (board[dx][dy] == me) {
							while (j != 1) {
								dx = a + ((--j) * dir[i][0]);
								dy = b + j * dir[i][1];
								board[dx][dy] = me;
								turnStone();
							}
							break;
						}

					}
				}
			}

		}
		result.push_back(pair<int, int>(blackNum, whiteNum));
	}

	for (int i = 0; i < result.size(); ++i) {
		printf("#%d %d %d\n", i + 1, result.at(i).first, result.at(i).second);
	}

	return 0;
}

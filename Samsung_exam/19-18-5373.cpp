//2020.10.16
//읽기(5) 1233 1238
//풀이(11) 1238 1249
//차트() 
//코딩(132) 1400 1528, 1533 1617
//디버깅() 
//합(148)

//돌리는거 이런거 잘 못하는 구나
//무조건 그대로 하려고 하지말고, 돌리는거는 규칙을 찾아서 최대한 간단하게 만들어야함
//일일이 하다가 실수하기 쉬움
//하드코딩하면 디버깅이 불가능이다


//assign은 몇개를 어떤 밸류로 지정할수 있음, 기존거 무시하고 새로 엎어씌움
//enum 쓰는법
//반시계는 시계3번
//시뮬은 시간이 많으므로 구현이 쉬운방향

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define mlog(s,a){}
#define input(){}
#endif
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}

using namespace std;

int TC, tc, N;
char side, dir;
int s, d; //side, dir 숫자

vector<vector<vector<char>>> cube(6);
vector<vector<char>> now;
vector<vector<char>> up;
vector<vector<char>> fr;
vector<vector<char>> dn;
vector<vector<char>> bk;
vector<vector<char>> le;
vector<vector<char>> ri;

char col[6] = { 'w','r','y','o','g','b' };
//위앞아 뒤왼오
//w r y  o g  b

void init() {
	for (int c = 0; c < 6; ++c) {
		cube[c].resize(3);
		for (int i = 0; i < 3; ++i) {
			cube[c][i].resize(3);
			for (int j = 0; j < 3; ++j) {
				cube[c][i][j] = col[c];
			}
		}
	}
	up = cube[0];
	fr = cube[1];
	dn = cube[2];
	bk = cube[3];
	le = cube[4];
	ri = cube[5];
}

void toNum() {
	switch (side) {
	case 'U':
		s = 0;
		break;
	case 'F':
		s = 1;
		break;
	case 'D':
		s = 2;
		break;
	case 'B':
		s = 3;
		break;
	case 'L':
		s = 4;
		break;
	case 'R':
		s = 5;
		break;
	}
	return;
}

void turnSelf() {
	vector<char> tmp;

	//시계
	if (d > 0) {
		for (int j = 0; j < 3; ++j) {
			for (int i = 2; i >= 0; --i) {
				tmp.push_back(cube[s][i][j]);
			}
		}
	}
	else {
		for (int j = 2; j >= 0; --j) {
			for (int i = 0; i < 3; ++i) {
				tmp.push_back(cube[s][i][j]);
			}
		}
	}
	cube[s][0].assign(tmp.begin(), tmp.begin() + 3);
	cube[s][1].assign(tmp.begin() + 3, tmp.begin() + 6);
	cube[s][2].assign(tmp.begin() + 6, tmp.begin() + 9);
}
void turn() {
	vector<char> tmp;

	switch (side) {
	case 'U':
		//[0][j]
		//+: 35143
		if (d > 0) {
			//거꾸로 저장
			tmp.assign(cube[4][0].begin(), cube[4][0].end());
			cube[4][0].assign(cube[1][0].begin(), cube[1][0].end());
			cube[1][0].assign(cube[5][0].begin(), cube[5][0].end());
			cube[5][0].assign(cube[3][0].begin(), cube[3][0].end());
			cube[3][0].assign(tmp.begin(), tmp.end());
		}
		//-: 34153
		else {
			tmp.assign(cube[5][0].begin(), cube[5][0].end());
			cube[5][0].assign(cube[1][0].begin(), cube[1][0].end());
			cube[1][0].assign(cube[4][0].begin(), cube[4][0].end());
			cube[4][0].assign(cube[3][0].begin(), cube[3][0].end());
			cube[3][0].assign(tmp.begin(), tmp.end());
		}
		break;

	case 'D':
		// 
		//+: 15341
		if (d > 0) {
			//거꾸로 저장
			tmp.assign(cube[4][2].rbegin(), cube[4][2].rbegin()+3);

			cube[4][2].assign(cube[3][2].begin(), cube[3][2].end());
			cube[3][2].assign(cube[5][2].rbegin(), cube[5][2].rbegin() + 3);
			cube[5][2].assign(cube[1][2].begin(), cube[1][2].end());
			cube[1][2].assign(tmp.begin(), tmp.end());
		}
		//-: 14351
		else {
			tmp.assign(cube[5][2].begin(), cube[5][2].end());
			
			cube[5][2].assign(cube[3][2].rbegin(), cube[3][2].rbegin()+3);
			cube[3][2].assign(cube[4][2].begin(), cube[4][2].end());

			cube[4][2].assign(cube[1][2].rbegin(), cube[1][2].rbegin() + 3);
			
			cube[1][2].assign(tmp.begin(), tmp.end());
		}
		break;

	case 'L':
		//[i][0]
		//+:01230
		if (d > 0) {
			tmp.clear();
			tmp.push_back(cube[3][2][0]);
			tmp.push_back(cube[3][1][0]);
			tmp.push_back(cube[3][0][0]);

			cube[3][0][0] = cube[2][0][0];
			cube[3][1][0] = cube[2][1][0];
			cube[3][2][0] = cube[2][2][0];

			cube[2][0][0] = cube[1][0][0];
			cube[2][1][0] = cube[1][1][0];
			cube[2][2][0] = cube[1][2][0];

			cube[1][0][0] = cube[0][0][0];
			cube[1][1][0] = cube[0][1][0];
			cube[1][2][0] = cube[0][2][0];

			cube[0][0][0] = tmp[0];
			cube[0][1][0] = tmp[1];
			cube[0][2][0] = tmp[2];
		}
		//-: 03210
		else {
			tmp.clear();
			tmp.push_back(cube[1][0][0]);
			tmp.push_back(cube[1][1][0]);
			tmp.push_back(cube[1][2][0]);

			cube[1][0][0] = cube[2][0][0];
			cube[1][1][0] = cube[2][1][0];
			cube[1][2][0] = cube[2][2][0];

			cube[2][0][0] = cube[3][0][0];
			cube[2][1][0] = cube[3][1][0];
			cube[2][2][0] = cube[3][2][0];

			cube[3][0][0] = cube[0][0][0];
			cube[3][1][0] = cube[0][1][0];
			cube[3][2][0] = cube[0][2][0];

			cube[0][0][0] = tmp[0];
			cube[0][1][0] = tmp[1];
			cube[0][2][0] = tmp[2];
		}
		break;
	case 'R':
		//[i][2]
		//+:03210
		if (d > 0) {
			tmp.clear();
			tmp.push_back(cube[1][2][2]);
			tmp.push_back(cube[1][1][2]);
			tmp.push_back(cube[1][0][2]);

			cube[1][0][2] = cube[2][0][2];
			cube[1][1][2] = cube[2][1][2];
			cube[1][2][2] = cube[2][2][2];

			cube[2][0][2] = cube[3][0][2];
			cube[2][1][2] = cube[3][1][2];
			cube[2][2][2] = cube[3][2][2];

			cube[3][0][2] = cube[0][2][2];
			cube[3][1][2] = cube[0][1][2];
			cube[3][2][2] = cube[0][0][2];

			cube[0][0][2] = tmp[0];
			cube[0][1][2] = tmp[1];
			cube[0][2][2] = tmp[2];
			
		}
		//-: 01230
		else {
			tmp.clear();
			tmp.push_back(cube[3][0][2]);
			tmp.push_back(cube[3][1][2]);
			tmp.push_back(cube[3][2][2]);

			cube[3][0][2] = cube[2][0][2];
			cube[3][1][2] = cube[2][1][2];
			cube[3][2][2] = cube[2][2][2];

			cube[2][0][2] = cube[1][0][2];
			cube[2][1][2] = cube[1][1][2];
			cube[2][2][2] = cube[1][2][2];

			cube[1][0][2] = cube[0][0][2];
			cube[1][1][2] = cube[0][1][2];
			cube[1][2][2] = cube[0][2][2];

			cube[0][0][2] = tmp[0];
			cube[0][1][2] = tmp[1];
			cube[0][2][2] = tmp[2];
		}
		break;
	case 'F':
		//
		//+:05240
		if (d > 0) {
			tmp.clear();
			tmp.push_back(cube[4][0][0]);
			tmp.push_back(cube[4][1][0]);
			tmp.push_back(cube[4][2][0]);

			cube[4][0][0] = cube[2][2][0];
			cube[4][1][0] = cube[2][2][1];
			cube[4][2][0] = cube[2][2][2];

			cube[2][2][0] = cube[5][0][0];
			cube[2][2][1] = cube[5][1][0];
			cube[2][2][2] = cube[5][2][0];

			cube[5][0][0] = cube[0][2][0];
			cube[5][1][0] = cube[0][2][1];
			cube[5][2][0] = cube[0][2][2];

			cube[0][2][0] = tmp[0];
			cube[0][2][1] = tmp[1];
			cube[0][2][2] = tmp[2];

		}
		//-: 04250
		else {
			tmp.clear();
			tmp.push_back(cube[5][0][0]);
			tmp.push_back(cube[5][1][0]);
			tmp.push_back(cube[5][2][0]);

			cube[5][0][0] = cube[2][2][0];
			cube[5][1][0] = cube[2][2][1];
			cube[5][2][0] = cube[2][2][2];

			cube[2][2][0] = cube[4][0][0];
			cube[2][2][1] = cube[4][1][0];
			cube[2][2][2] = cube[4][2][0];

			cube[4][0][0] = cube[0][2][0];
			cube[4][1][0] = cube[0][2][1];
			cube[4][2][0] = cube[0][2][2];

			cube[0][2][0] = tmp[0];
			cube[0][2][1] = tmp[1];
			cube[0][2][2] = tmp[2];
		}
		break;
	case 'B':

		//+:04250
		if (d > 0) {
			tmp.clear();
			tmp.push_back(cube[5][0][2]);
			tmp.push_back(cube[5][1][2]);
			tmp.push_back(cube[5][2][2]);

			cube[5][0][2] = cube[2][0][0];
			cube[5][1][2] = cube[2][0][1];
			cube[5][2][2] = cube[2][0][2];

			cube[2][0][0] = cube[4][0][2];
			cube[2][0][1] = cube[4][1][2];
			cube[2][0][2] = cube[4][2][2];

			cube[4][0][2] = cube[0][0][0];
			cube[4][1][2] = cube[0][0][1];
			cube[4][2][2] = cube[0][0][2];

			cube[0][0][0] = tmp[0];
			cube[0][0][1] = tmp[1];
			cube[0][0][2] = tmp[2];
		}
		//-: 05240
		else {
			tmp.clear();
			tmp.push_back(cube[4][0][2]);
			tmp.push_back(cube[4][1][2]);
			tmp.push_back(cube[4][2][2]);

			cube[4][0][2] = cube[2][0][0];
			cube[4][1][2] = cube[2][0][1];
			cube[4][2][2] = cube[2][0][2];

			cube[2][0][0] = cube[5][0][2];
			cube[2][0][1] = cube[5][1][2];
			cube[2][0][2] = cube[5][2][2];

			cube[5][0][2] = cube[0][0][0];
			cube[5][1][2] = cube[0][0][1];
			cube[5][2][2] = cube[0][0][2];

			cube[0][0][0] = tmp[0];
			cube[0][0][1] = tmp[1];
			cube[0][0][2] = tmp[2];

		}
		break;
	}
	turnSelf();
}
void printUp() {
	for (int i = 0; i < 3; ++i) {

		for (int j = 0; j < 3; ++j) {
			printf("%c", cube[0][i][j]);
		}
		nn()
	}
	line()
}

int main(void) {
	input();
	scanf("%d", &TC);
	
	for (tc = 1; tc <= TC; ++tc) {
		scanf("%d", &N); getchar();
		init();
		for (int i = 0; i < N; ++i) {
			scanf("%c%c ", &side, &dir);
			toNum();
			d = dir == '+' ? 1 : -1; //시계, 반시계
			turn();
			
		}
		printUp();
	}
	return 0;
}
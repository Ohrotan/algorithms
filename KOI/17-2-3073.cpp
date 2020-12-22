//2020.10.06
//읽기(3) 20:57 ~ 21:00
//풀이(10) 21:00 ~ 21:10
//차트() 
//코딩(40) 21:20 ~ 22:00
//dfs로 한번에 통과,, 그러나 BFS도 생각해보자!!
//디버깅() 
//합(53)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include<queue>

#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

class Room {
public:
	int a;//A방 배정 개수
	int b;
	int c;
	int n; //배정 안 된 학생수
	Room(int nn, int aa = -1, int bb = -1, int cc = -1) :n(nn), a(aa), b(bb), c(cc) {}
};

int n, A, B, C; //A방의 정원(A<B<C)

queue<Room> q;
int res = 0;

void dfs(char type, int n) {
	int i = 0;
	switch (type) {
	case 'A':
		if (n % A == 0) {
			res = 1;
			break;
		}
		while (res == 0 && A * i < n) {
			dfs('B', (n % A) + A * i++);
		}
		break;
	case 'B':
		if (n % B == 0) {
			res = 1;
			break;
		}
		while (res == 0 && B * i < n) {
			dfs('C', (n % B) + B * i++);
		}
		break;
	case 'C':
		if (n % C == 0) {
			res = 1;
		}
	}
}

int main(void) {
	input();
	scanf("%d %d %d %d", &A, &B, &C, &n);
	dfs('A', n);
	printf("%d",res);
	return 0;
	q.push(Room(n));
	while (q.size() > 0) {
		Room r = q.front(); q.pop();

		while (1) {
			if (r.b == -1 && n - A > 0) {
				q.push(Room(n - A, r.a + 1));
			}
		}
	}


	return 0;
}
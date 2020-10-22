//2020.10.15
//읽기(5) 1719 1724
//풀이(15) 1724 1739
//차트() 
//코딩(36) 1739 1815
//디버깅(45) 1815 1900
//0인 부분도 물고기 취급하고 먹음
//우선순위 잘못 지정함
//합(141)

//엥 비스에서는 맞는데 제출하니 틀림
//2차디버깅(36) 1900 1936

//정답과 비교해보니까 답은 맞았는데, 시간초과됨
//dp 안써도 되는줄 알았는데, 문제 풀기전에 DP 써야되는지 계산해야겠다.
//3차코딩() 0924
//dp는 쓸필요가 없었고, 샤크크기를 9로 두어서 자기가 자기를 계속 먹어서 생긴 무한루프
//pro보다 step자체에서 오퍼레이터 만들었더니 맞음
//그런데도 답이 틀린건 왜..?
//하.. notyet 배열을 true로 초기화 안시킨것 때문에 서버의 디폴트랑 달라서 계속 답이 틀렸던 거다..


//그래, 힘든만큼 배운게 많다!
//1. 우선순위 따질 때 무조건 클래스 만들어서 operator< 만들기
//2. 로컬변수쓰면 무조건 무조건 초기화하기
//3. 경우의 수 최대인 케이스 만들어서 비교하기
//합()

//priority q 찾아보기
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
	int pr;//직전칸
	int pc;
	int r;//현재칸
	int c;
	int cnt;//여기까지 오는데 걸린 이동횟수
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

int sr, sc, shark;//상어 위치, 크기
int cnt;//지금 물고기 먹은 수

int mr[4] = { -1,0,0,1 };//상좌우하
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

//움직이려는 칸
bool valid(int nr, int nc) {
	if (!inborder(nr, nc)) {
		return false;
	}
	if (map[nr][nc] > shark) {
		return false;
	}
	return true;
}

//맨앞거가 큐에서 남은 애들중에서 우선순위 빠른게 있으면 맨뒤로 보냄
void prio(vector<Step> &q) {
	bool flag = true;
	while (flag) {
		flag = false;
		Step f = q.front();
		for (int i = 1; i < q.size(); ++i) {
			//이동횟수가 같거나 작고
			//r이 작고
			//r이 같다면 c가 작은애가
			//있다면 맨앞으로 꺼내기
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
	bool notyet[20][20];//true면 방문 안했다는거!!
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
			map[sr][sc] = 0;//원래 상어자리는 0
			sr = now.r;
			sc = now.c;
			res += now.cnt;
			map[sr][sc] = 0;//새로운 상어 자리
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
				shark = 2;//크기
			}
		}

	}

	while (findFish());

	printf("%d", res);
	return 0;
}
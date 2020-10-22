//2020.10.13
//읽기(6) 14:38 ~ 14:44
//풀이(15) 14:45 ~ 15:00 
//코딩(45) 15:00 ~ 15:45
//디버깅(75) 15:45 ~ 17:00
//합(141)
//미친.. 복붙하다가 right에 left 잘못 넣은거랑
//오른쪽으로 밀면서 마지막꺼를 삭제를 안했던거
//이거 두개때문에 1시간넘게 눈이 빠져라 코드봤네..

//그래, 실수는 할 수 있어!! 근데 답이 맞는지 테스트 케이스 꼼꼼하게 직접 체크해보자
//그랬다면 남의 코드 안보고도 금방 발견했을거야
//시험장에서는 정답코드랑 비교도 못하고, 테스트케이스가 맞았다고 나왔으면, 이대로 제출을 해버렸을거야
//단계 하나하나 제대로 넘어간 게 맞는지 일일이 확인해보자
//이게 중요!!!!

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include<iostream>
#include<cstring>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

vector<vector<int>> wheel(5); //0번 바퀴안씀
vector<int> rotation(5, 0); // rotation[1] = 1 , 1번바퀴를 시계방향회전
int k;
int res;

void wheelPrint() {
	for (int i = 1; i < 5; ++i) {
		for (int j = 0; j < 8; ++j) {
			printf("%1d", wheel[i][j]);
		}
		printf("\n");
	}
}

void leftwheel(int num, int dir) {
	rotation[num] = dir;
	if (num > 1) {
		if (wheel[num][6] != wheel[num - 1][2]) {
			leftwheel(num - 1, -dir); //극이 다르면 왼쪽 바퀴도 굴리기
		}
	}
}

void rightwheel(int num, int dir) {
	rotation[num] = dir;
	if (num < 4) {
		if (wheel[num][2] != wheel[num + 1][6]) {
			rightwheel(num + 1, -dir); //극이 다르면 오른쪽 바퀴도 굴리기
		}
	}
}
void rotate() {
	for (int i = 1; i < 5; ++i) {
		if (rotation[i] == 1) {
			wheel[i].insert(wheel[i].begin(), wheel[i].back());
            wheel[i].erase(wheel[i].begin() + 8);
		}
		else if (rotation[i] == -1) {
			wheel[i].push_back(wheel[i].front());
			wheel[i].erase(wheel[i].begin());
		}
	}
	rotation.clear();
	rotation.resize(5, 0);
}




struct TOP {
    int topni;
    bool getUP() {
        return topni & 1;
    }
    bool getRIGHT() {
        return topni & (1 << 2);
    }
    bool getLEFT() {
        return topni & (1 << 6);
    }

    void rotate(int dir) {
        if (dir == 1) {
            bool temp = topni & 0b10000000;
            topni <<= 1;
            topni |= temp;
            topni &= 0xff;
        }
        else if (dir == -1) {
            bool temp = topni & 1;
            topni >>= 1;
            topni |= (temp << 7);
        }
    }
    void set(int v) {
        for (int i = 0; i < 8; i++) {
            topni <<= 1;
            topni += v % 10;
            v /= 10;
        }
    }
}tops[5];

int flag[5];

int main2() {
    freopen("input.txt", "r", stdin);
    for (int i = 1; i <= 4; i++) {
        int n;
        cin >> n;
        tops[i].set(n);
    }
  
    int m;
    cin >> m;
    while (m--) {
        memset(flag, 0, sizeof(flag));

        int n, r;
        cin >> n >> r;
        flag[n] = r;

        for (int i = n - 1; i >= 1; i--) {
            if (tops[i + 1].getLEFT() ^ tops[i].getRIGHT()) { flag[i] = -flag[i + 1]; }
            else break;
        }

        for (int i = n + 1; i <= 4; i++) {
            if (tops[i - 1].getRIGHT() ^ tops[i].getLEFT()) flag[i] = -flag[i - 1];
            else break;
        }
        for (int i = 1; i <= 4; i++) {
            tops[i].rotate(flag[i]);
        }
    }


    int res = 0;
    for (int i = 1; i <= 4; i++) {
        res += (tops[i].getUP() << (i - 1));
    }
    cout << "co: " << res << endl;;
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < 8; ++j) {

            cout << tops[i].getUP();
            tops[i].topni >>= 1;

        }
        cout << endl;
    }
    return 0;
}
int main3(void) {
    int wheelNum, dir;
    char buf[10];
    input();
    wheel[1].resize(8, 0);
    wheel[2].resize(8, 0);
    wheel[3].resize(8, 0);
    wheel[4].resize(8, 0);
    for (int i = 1; i <= 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            scanf("%1d", &wheel[i][j]);
        }
    }
    scanf("%d", &k);
    //wheelPrint();
    for (int i = 0; i < k; ++i) {
        scanf("%d %d", &wheelNum, &dir);
        leftwheel(wheelNum, dir);
        rightwheel(wheelNum, dir);
        rotate();
        //printf("--------after----------\n");
        //wheelPrint();
    }
    res = (wheel[1][0]) + 2 * (wheel[2][0]) + 4 * (wheel[3][0]) + 8 * (wheel[4][0]);
    wheelPrint();
    printf("me: %d\n", res);
    main2();
    //wheelPrint();
    return 0;
}
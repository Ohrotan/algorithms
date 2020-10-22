//2020.10.13
//�б�(6) 14:38 ~ 14:44
//Ǯ��(15) 14:45 ~ 15:00 
//�ڵ�(45) 15:00 ~ 15:45
//�����(75) 15:45 ~ 17:00
//��(141)
//��ģ.. �����ϴٰ� right�� left �߸� �����Ŷ�
//���������� �и鼭 ���������� ������ ���ߴ���
//�̰� �ΰ������� 1�ð��Ѱ� ���� ������ �ڵ�ó�..

//�׷�, �Ǽ��� �� �� �־�!! �ٵ� ���� �´��� �׽�Ʈ ���̽� �Ĳ��ϰ� ���� üũ�غ���
//�׷��ٸ� ���� �ڵ� �Ⱥ��� �ݹ� �߰������ž�
//�����忡���� �����ڵ�� �񱳵� ���ϰ�, �׽�Ʈ���̽��� �¾Ҵٰ� ��������, �̴�� ������ �ع������ž�
//�ܰ� �ϳ��ϳ� ����� �Ѿ �� �´��� ������ Ȯ���غ���
//�̰� �߿�!!!!

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

vector<vector<int>> wheel(5); //0�� �����Ⱦ�
vector<int> rotation(5, 0); // rotation[1] = 1 , 1�������� �ð����ȸ��
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
			leftwheel(num - 1, -dir); //���� �ٸ��� ���� ������ ������
		}
	}
}

void rightwheel(int num, int dir) {
	rotation[num] = dir;
	if (num < 4) {
		if (wheel[num][2] != wheel[num + 1][6]) {
			rightwheel(num + 1, -dir); //���� �ٸ��� ������ ������ ������
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
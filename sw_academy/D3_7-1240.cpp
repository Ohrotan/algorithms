// 2020.09.23 09:33 ~ 10:10,10:30 ~ 10:45
// 10:45 ~ 12:20 또 초기화문제 때문에 시간 많이 날림!!!
#pragma warning(disable:4996)


#include <cstdio>

using namespace std;
int tc, TC = 0;
int row, col = 0;
char buf[101];
int code[8] = { 0, };
int cnt = 7; //번호의 자리수
bool reading = false;
int bit = 1;
int MAX = 0b1000000;
int bitCnt = 0; // 비트 자리수
int sum = 0; //각 자리수 합
int num[10] = { 0b0001101,0b0011001,
0b0010011,0b0111101,0b0100011,0b0110001
,0b0101111,0b0111011,0b0110111,0b0001011 };

void decode()
{
	sum = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (code[i] == num[j]) {
				code[i] = j;
				sum += j;
				// printf("%d",j);
				break;
			}
		}
	}
}

int checkSum() {
	int check = 0;
	check = (code[0] + code[2] + code[4] + code[6]) * 3;
	check += code[1] + code[3] + code[5] + code[7];
	// printf(" check: %d",check);
	if (check % 10 == 0) {
		return sum;
	}
	else {
		return 0;
	}
}
void init() {
	//buf init
	for (char c : buf) {
		c = '0';
	}
	for (int i = 0; i < 8; ++i) {
		code[i] = 0;

	}
	cnt = 7;
	bit = 1;
}
int main(void) {
	scanf("%d", &TC);
	for (tc = 1; tc <= TC; ++tc) {
		scanf("%d %d", &row, &col);
		// printf(" r:%d, c:%d ",row,col);
		getchar();
		init();

		for (int i = 0; i < row; ++i) {
			gets_s(buf);
			if (reading) {
				continue;
			}
			for (int j = col - 1; j >= 0; --j) {
				if (reading) {
					if (bit == MAX) {
						if (cnt == 0) { //모든 숫자 다읽음
							break;
						}
						--cnt; bit = 1; //다음 자리수
					}
					else {
						bit = bit << 1;
					}
				}
				if (buf[j] == '1') {
					reading = true;
					code[cnt] += bit;
					//printf("code[%d] = %d, bit = %d",cnt,code[cnt],bit);
				}
			}
		}
		reading = false;
		decode();
		//printf(" sum: %d ",sum);
		printf("#%d %d\n", tc, checkSum());
	}
	return 0;
}
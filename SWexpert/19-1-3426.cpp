//2020.10.04 
//읽기(2) 11:48 ~ 11:50
//풀이(40) 11:50 ~ 12:29
//차트() 
//코딩(55) 12:30 ~ 12:45, 17:28 ~ 18:10
//규칙 제대로 못찾겠어서 전체탐색..
//전체탐색으로 5분만에 성공.,
//합(100)

#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
using namespace std;

int input; //입력받은 수
int num[6] = { 0, }; //자리수별로 input을 재입력
int n = 1; //자리수

int ca[6] = { 0, }; //자리수별 경우의 수 ca[0] = 3 

int com(int n, int k) {
	int sum = 1;
	for (int i = 1; i <= k; ++i) {
		sum = sum * n-- / i;
	}
	return sum;
}

void count(int N) {
	int res = 0;
	for (int i = 1; i <= N; ++i) {
		int tmp = i / 100000;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
		tmp = (i % 100000)/ 10000;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
		tmp = (i % 10000) / 1000;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
		tmp = (i % 1000) / 100;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
		tmp = (i % 100) / 10;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
		tmp = i % 10;
		if (tmp != 0 && tmp % 3 == 0) {
			++res;
			//printf("%3d ", i);
		}
	}
	printf("%d\n", res);
}

int main(void) {
	scanf("%d", &input);
	count(input);
	return 0;
	//자리수별로 input을 재입력
	while (input > 9) {
		num[n] = input / 10;
		++n;
		input %= 10;
	}
	num[n] = input;
	
	/*for (int i = 1; i <= n; ++i) {
		printf("%d ", num[i]);
	}*/
	//end

	int sum = 0;
	for (int i = 1; i <= 6; ++i) {
		sum = 0;
		for (int k = 1; k <= i; ++k) {
			sum += pow(3, k) * pow(7, i - k) * k * com(i, k);
		}
		ca[i] = sum;
		printf("%d\n", sum);
	}

	//첫번째 자리 경우의 수
	sum = ca[n - 1] * num[1]; //첫번째 자리수에서 숫자 1이 낮은 경우 예) 53일 때, 1x부터 4x인 경우의 수 구함
	for (int i = 1; i <= n; ++i) {

		if (num[i] > 3) {
			sum += 10;
			if (num[i] > 6) {
				sum += 10;
			}
		}
		if (num[i] % 3 == 0) {
			sum += num[i + 1] + 1;
		}
	}


	//printf("res: %d\n", sum);

	return 0;
}
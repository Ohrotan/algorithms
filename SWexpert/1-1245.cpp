//2020.09.18 21:30 ~ 12:30, + 45분
#pragma warning(disable:4996)
#include <stdio.h>

using namespace std;
double x[10] = { 0, }; //좌표
double m[10] = { 0, }; //무게
int tc, n;
double gap = 0.000000000001;// 0.000000000001; // 1e-12
int main(void) {
	scanf("%d",&tc);
	for (int i = 1; i <= tc; ++i) {
		scanf("%d", &n);
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &x[j]);
		}
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &m[j]);
		}
		printf("#%d", i);
		
		double tmp = 0;
		double left = 0;
		double right = 0;
		double lowerB = 0;
		double upperB = 0;
		
		for (int k = 1; k < n; ++k) {
			lowerB = x[k - 1];
			upperB = x[k];
			tmp = (lowerB + upperB) / (double)2;
			while (1) {
				left = right = 0;
				for (int a = 0; a < n; ++a) {
					if (a < k) {
						left += m[a] / ((x[a] - tmp) * (x[a] - tmp));
					}
					else {
						right += m[a] / ((x[a] - tmp) * (x[a] - tmp));
					}
				}

				if (left > right) {
					lowerB = tmp;
					tmp = (tmp + upperB) / (double)2;//증가
					if (tmp - lowerB < gap) { break; }
				}
				else {
					upperB = tmp;
					tmp = (tmp + lowerB) / (double)2;//tmp 감소
					if (upperB - tmp < gap) { break; }
				}
			}
			printf(" %.10f",tmp);
		}
		printf("\n");
	}
	return 0;
}

/*
#include<stdio.h>
int T, N;
double arr[12]; //x좌표
double weight[12];
double X, left, mid, right;
void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%lf", &arr[i]);
	}
	for (int i = 0; i < N; i++)
	{
		scanf("%lf", &weight[i]);
	}
}

void simul() {
	double sum1 = 0, sum2 = 0;
	for (int i = 0; i < N - 1; i++) {
		sum1 = sum2 = 0;
		left = arr[i], right = arr[i + 1];
		for (int k = 0; k < 50; k++) {
			mid = (left + right) / 2.0;
			sum1 = sum2 = 0;

			for (int j = 0; j <= i; j++) sum1 += weight[j] / ((mid - arr[j]) * (mid - arr[j]));
			for (int j = i + 1; j < N; j++) sum2 += weight[j] / ((mid - arr[j]) * (mid - arr[j]));

			if (sum1 < sum2) right = mid;
			else if (sum1 > sum2) left = mid;
			else {
				X = mid;
				break;
			}
		}
		printf(" %.10f", mid);
	}
}

int main() {
	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {
		input();

		printf("#%d", t);
		simul();
		puts(" ");
	}
	return 0;
*/
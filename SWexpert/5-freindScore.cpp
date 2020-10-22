//2020.09.26 16:00 ~ 16:35
#include<time.h>

#include<string>
#include<vector>
#include<algorithm>

using namespace std;
clock_t start, endt;
vector<int> myF;
int allF[50] = { 0, };
int N;
vector<string> input;
int maxCnt, cnt = 0;

void init() {
	for (int i = 0; i < N; ++i) {
		allF[i] = 0;
	}
	myF.clear();
	cnt = 0;
}

void mySol() {
	for (int i = 0; i < N; ++i) {
		init();
		for (int j = 0; j < N; ++j) {
			if (input[i][j] == 'Y') {
				myF.push_back(j);
				allF[j] = 1;
			}
		}

		for (int j = 0; j < myF.size(); ++j) {
			int jj = myF.at(j);
			for (int k = 0; k < N; ++k) {
				if (input[jj][k] == 'Y') {
					allF[k] = 1;
				}
			}
		}

		for (int j = 0; j < N; ++j) {
			if (allF[j] == 1) {
				++cnt;
				allF[j] = 0;
			}
		}
		maxCnt = max(cnt - 1, maxCnt); //나 자신은 뺌
	}
}

void bookSol() {
	for (int i = 0; i < N; ++i) {
		int cnt = 0;
		for (int j = 0; j < N; ++j) {
			if (i == j)continue;

			if (input[i][j] == 'Y') {
				++cnt;
			}
			else {
				for (int k = 0; k < N; ++k) {
					if (input[j][k] == 'Y' && input[k][i] == 'Y') {
						++cnt;
						break;
					}
				}
			}
		}
		maxCnt = max(maxCnt, cnt);
	}
}
int main(void) {
	start = clock();
	N = 10;
	input.push_back("NNNNYNNNNN");
	input.push_back("NNNNYNYYNN");
	input.push_back("NNNYYYNNNN");
	input.push_back("NNYNNNNNNN");
	input.push_back("YYYNNNNNNY");

	input.push_back("NNYNNNNNYN");
	input.push_back("NYNNNNNYNN");
	input.push_back("NYNNNNYNNN");
	input.push_back("NNNNNYNNNN");
	input.push_back("NNNNYNNNNN");

	//-----------data-------
	//내방식은 30 ~ 33
	//book은 55 ~ 61
	for (int tt = 0; tt < 1000; ++tt)
	{
		bookSol();
	}
	printf("max: %d", maxCnt);
	endt = clock();
	printf("time: %f", (double)(endt - start));
	return 0;
}

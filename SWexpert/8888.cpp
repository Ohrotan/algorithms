#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int T;
int n, t, p;
int applicant[2000] = { 0, };
int myrank = 1;
int score[2000] = { 0, };
bool grade[2000][2000];
vector<pair<int, int>> res;



//�� ����� ���� Ǭ ����
int probNum(int num) {
	int result = 0;
	for (int i = 0; i < t; i++) {
		if (grade[num][i]) ++result;
	}
	return result;
}

int main(void) {

	T = getchar() - '0';	getchar();
	for (int i = 0; i < T; i++) {
		myrank = 1;

		n = getchar() - '0'; 	getchar();
		t = getchar() - '0'; 	getchar();
		p = getchar() - '0';	getchar();

		//start - �� ������ ���� �Է�

		//score = (int*)malloc(t + 1);
		//memset(score, 0, sizeof(int*) * (t + 1));


		//grade = (bool**)malloc(n + 1);

		for (int j = 1; j <= n; ++j) {
			//grade[j] = (bool*)malloc(t + 1);
			for (int k = 1; k <= t; ++k) {
				grade[j][k] = getchar() - '0'; getchar();
				if (!grade[j][k]) {
					//������ �� Ǯ������, ������ �ø���.
					score[k]++;
				}
			}
		}
		//end - �� ������ ���� �Է�

		//start - �����ں� ���� ���

		//applicant = (int*)malloc(t + 1);
		int sum = 0;

		for (int j = 1; j <= n; ++j) {

			for (int k = 1; k <= t; ++k) {
				//cout << "grade:" << grade[j][k] << ", score:" << score[k] << endl;
				sum += grade[j][k] * score[k];
			}
			applicant[j] = sum;
			sum = 0;

		}
		//end - �����ں� ���� ���

		int myProbNum = probNum(p);

		for (int i = 1; i <= n; ++i) {
			if (i == p)continue;
			if (applicant[i] > applicant[p]) {
				++myrank;
			}
			else if (applicant[i] == applicant[p]) {
				if (probNum(i) > myProbNum) {
					++myrank;
				}
				else if (probNum(i) == myProbNum && i < p) {
					++myrank;
				}
			}
			//cout << i + 1 << "�� ����: " << applicant[i] << endl;
		}
		res.push_back(pair<int, int>(applicant[p], myrank));
		memset(applicant, 0, sizeof(int) * 2000);
		memset(score, 0, sizeof(int) * 2000);
		memset(grade, 0, sizeof(int) * 2000*2000);
	}
	for (int i = 1; i <= T; ++i) {
		cout << "#" << i << " " << res.at(i - 1).first << " " << res.at(i - 1).second << endl;
	}

	return 0;
}
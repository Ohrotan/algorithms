#pragma warning (disable:4996)
#include<cstring>
#include <cstdio>
using namespace std;
int T;
int n, t, p;
const int MAX = 2001;
//int applicant[2001] = { 0, }; //사람별 총득점
int myrank = 1; // p번의 순위
//int score[2001] = { 0, }; //사람별 총득점
int grade[2001][2002]; //[사람번호][문제번호] pass fail
int sum;
char buf[4002];


int main(void) {
	scanf("%d", &T);
	//T = getNum();
	for (int tc = 1; tc <= T; ++tc) {
		myrank = 1;
		scanf("%d %d %d", &n, &t, &p);
		for (int k = 1; k <= t; ++k)
			grade[0][k] = n;//모든 배점을 참가자수로 초기화
		getchar();

		//start - 각 문제별 배점 입력
		for (int j = 1; j <= n; ++j) {
			gets_s(buf);
			int prob = 0;
			for (int k = 1; k <= t; ++k) {
				if (buf[2 * (k - 1)] == '1') {
					--grade[0][k]; //푼 사람이 있으니 배점낮추기
					grade[j][++prob] = k; //j 참가자가 푼 문제번호를 1부터 순서대로 기록
				}
			}
			grade[j][0] = prob;//j 참가자가 푼 문제개수
		}
		//end - 각 문제별 배점 입력


		//start - 지원자별 점수 계산
		for (int j = 1; j <= n; ++j) {
			sum = 0;
			for (int k = 1; k <= grade[j][0]; ++k) {
				if (p == j) printf("grade[j][k]: %d, grade[0][grade[j][k]]: %d\n", grade[j][k], grade[0][grade[j][k]]);
				sum += grade[0][grade[j][k]];
			}
			grade[j][MAX] = sum; //j참가자의 총점
			if (p == j) {
				printf("grade[0][2]: %d", grade[0][2]);
			}
		}
		//end - 지원자별 점수 계산


		//start - 지원자 rank
		for (int i = 1; i <= n; ++i) {
			if (i == p)continue;
			if (grade[i][MAX] > grade[p][MAX]) {
				++myrank;
			}
			else if (grade[i][MAX] == grade[p][MAX]) {
				if (grade[i][0] > grade[p][0]) {
					++myrank;
				}
				else if (grade[i][0] == grade[p][0] && i < p) {
					++myrank;
				}
			}
			//cout << i + 1 << "번 점수: " << applicant[i] << endl;
		}
		//end - 지원자 rank

		printf("#%d %d %d\n", tc, grade[p][MAX], myrank);
		//cout << "#" << i+1 << " " << applicant[p] << " " << myrank << endl;
		//cout << res.at(0).first << endl;
		//cout << "3번의 배점:" << score[3] << ", 총 득점: " << res.at(res.size() - 1).first << endl;

		//memset(applicant, 0, sizeof(int) * (n + 1));
		//memset(score, 0, sizeof(int) * (t + 1));
		memset(grade, 0, sizeof(int) * 2001 * 2002);

	}
	
	return 0;
}
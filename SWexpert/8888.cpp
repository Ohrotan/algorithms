#pragma warning (disable:4996)
#include<cstring>
#include <cstdio>
using namespace std;
int T;
int n, t, p;
const int MAX = 2001;
//int applicant[2001] = { 0, }; //����� �ѵ���
int myrank = 1; // p���� ����
//int score[2001] = { 0, }; //����� �ѵ���
int grade[2001][2002]; //[�����ȣ][������ȣ] pass fail
int sum;
char buf[4002];


int main(void) {
	scanf("%d", &T);
	//T = getNum();
	for (int tc = 1; tc <= T; ++tc) {
		myrank = 1;
		scanf("%d %d %d", &n, &t, &p);
		for (int k = 1; k <= t; ++k)
			grade[0][k] = n;//��� ������ �����ڼ��� �ʱ�ȭ
		getchar();

		//start - �� ������ ���� �Է�
		for (int j = 1; j <= n; ++j) {
			gets_s(buf);
			int prob = 0;
			for (int k = 1; k <= t; ++k) {
				if (buf[2 * (k - 1)] == '1') {
					--grade[0][k]; //Ǭ ����� ������ �������߱�
					grade[j][++prob] = k; //j �����ڰ� Ǭ ������ȣ�� 1���� ������� ���
				}
			}
			grade[j][0] = prob;//j �����ڰ� Ǭ ��������
		}
		//end - �� ������ ���� �Է�


		//start - �����ں� ���� ���
		for (int j = 1; j <= n; ++j) {
			sum = 0;
			for (int k = 1; k <= grade[j][0]; ++k) {
				if (p == j) printf("grade[j][k]: %d, grade[0][grade[j][k]]: %d\n", grade[j][k], grade[0][grade[j][k]]);
				sum += grade[0][grade[j][k]];
			}
			grade[j][MAX] = sum; //j�������� ����
			if (p == j) {
				printf("grade[0][2]: %d", grade[0][2]);
			}
		}
		//end - �����ں� ���� ���


		//start - ������ rank
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
			//cout << i + 1 << "�� ����: " << applicant[i] << endl;
		}
		//end - ������ rank

		printf("#%d %d %d\n", tc, grade[p][MAX], myrank);
		//cout << "#" << i+1 << " " << applicant[p] << " " << myrank << endl;
		//cout << res.at(0).first << endl;
		//cout << "3���� ����:" << score[3] << ", �� ����: " << res.at(res.size() - 1).first << endl;

		//memset(applicant, 0, sizeof(int) * (n + 1));
		//memset(score, 0, sizeof(int) * (t + 1));
		memset(grade, 0, sizeof(int) * 2001 * 2002);

	}
	
	return 0;
}
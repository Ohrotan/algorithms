//2020.09.27 19:36 ~ 20:10

#include<vector>
#include<algorithm>
using namespace std;

vector<int> don; //�� ������ ��ξ�
vector<int> res; //res[i] i��ȣ�� ������� ���� ���� ��ξ� ����

void init() {
	res.clear();
	for (int i = 0; i < don.size(); ++i) {
		res.push_back(0);
	}
}
int main(void) {
	don = { 94, 40, 49, 65, 21, 21, 106, 80, 92, 81, 679, 4, 61,
  6, 237, 12, 72, 74, 29, 95, 265, 35, 47, 1, 61, 397,
  52, 72, 37, 51, 1, 81, 45, 435, 7, 36, 57, 86, 81, 72 };
	init();
	int result = 0;

	
	//ù��°�� ������� ��
	for (int i = 0; i < don.size(); ++i) {
		if (i < 2) {
			res[i] = don[i];
		}
		else if (i == 2) {
			res[i] = res[0] + don[i];
		}
		else if (i == don.size() - 1) {
			res[i] = 0;
		}
		else {
			res[i] = max(res[i-2],res[i-3])+don[i];
		}
		result = max(result, res[i]);
	}


	init();
	//ù��°�� ��� ������ ��
	for (int i = 1; i < don.size(); ++i) {
		if (i < 3) {
			res[i] = don[i];
		}
		else {
			res[i] = max(res[i - 2], res[i - 3]) + don[i];
		}
		result = max(result, res[i]);
	}

	printf("res: %d", result);
	return 0;
}
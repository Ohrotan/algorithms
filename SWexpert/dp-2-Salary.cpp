//2020.09.27 18:55 ~ 19:10
#include<string>
#include<vector>

using namespace std;

vector<string> rel;//관계
vector<int> sal;//급여
int num;//직원수
void input() {
	rel =
	{ "NYNNYN",
	 "NNNNNN",
	 "NNNNNN",
	 "NNYNNN",
	 "NNNNNN",
	 "NNNYYN" };

	//Returns: 8

}

void init() {
	sal.clear();
	for (int i = 0; i < num; ++i) {
		sal.push_back(0);
	}
}
int getSal(int p) {
	if (sal[p] != 0) {
		return sal[p];
	}
	for (int j = 0; j < num; ++j) {
		if (rel[p][j] == 'Y') {
			sal[p] += getSal(j);
		}
	}
	if (sal[p] == 0) {
		sal[p] = 1;
	}
	return sal[p];

}

int main(void) {
	input();
	num = rel.size();
	int res = 0;
	
	init();
	for (int i = 0; i < num; ++i) {
		res += getSal(i);
	}
	printf("res: %d", res);
	return 0;
}
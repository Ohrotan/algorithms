//2020.10.05
//�б�(4) 16:48 16:52
//Ǯ��(3) 16:52 16:55
//��Ʈ() 
//�ڵ�(26) 16:55 17:21
//�����() 
//��(33)

#pragma warning(disable:4996)

#include <stdio.h>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

int n;//�� ����
map<int, vector<int>> points;
vector<int> colors;
int res = 0;

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	int pos, col;

	//���򺰷� �з�
	for (int i = 0; i < n; ++i) {
		scanf("%d %d",&pos,&col);
		if (points.find(col) != points.end()) {
			points.find(col)->second.push_back(pos);
		}
		else {
			vector<int> val = {pos};
			points.insert(make_pair(col,val));
			colors.push_back(col);
		}
	}
	

	
	for (int i = 0; i < colors.size(); ++i) {
		int col = colors[i];
		sort(points[col].begin(), points[col].end());//��ġ������ ����
		int len = points[col].size();
		res += points[col][1] - points[col][0];//ù��° ���� ������ �ι�° ���� ��
		for (int j = 1; j < len -1; ++j) {
			//�� ���ʰ� ������ �� ª�� �Ÿ��� ����
			res += min(points[col][j] - points[col][j - 1], points[col][j + 1] - points[col][j]);
		}
		res += points[col][len -1] - points[col][len -2];//������ ���� ������ �ڿ��� �ι�° ���� ��
	}
	
	printf("%d",res);
	

	return 0;
}
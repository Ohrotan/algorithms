//2020.10.05
//읽기(4) 16:48 16:52
//풀이(3) 16:52 16:55
//차트() 
//코딩(26) 16:55 17:21
//디버깅() 
//합(33)

#pragma warning(disable:4996)

#include <stdio.h>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

int n;//점 개수
map<int, vector<int>> points;
vector<int> colors;
int res = 0;

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	int pos, col;

	//색깔별로 분류
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
		sort(points[col].begin(), points[col].end());//위치순으로 정렬
		int len = points[col].size();
		res += points[col][1] - points[col][0];//첫번째 점은 무조건 두번째 점만 감
		for (int j = 1; j < len -1; ++j) {
			//내 왼쪽과 오른쪽 중 짧은 거리를 더함
			res += min(points[col][j] - points[col][j - 1], points[col][j + 1] - points[col][j]);
		}
		res += points[col][len -1] - points[col][len -2];//마지막 점은 무조건 뒤에서 두번째 점만 감
	}
	
	printf("%d",res);
	

	return 0;
}
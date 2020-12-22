#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int t = 0;//����ð�
int W;//�ٸ��� �ߵ�� ����
int sum = 0;//���� �ٸ��� Ʈ������
queue<int> running; //�ٸ� ���� �ִ� Ʈ���� ��ġ�� ����
vector<int> truck; //Ʈ���� ���Ե�

bool move() {
	++t;
	sum -= running.front();
	running.pop();
	if (truck.size() > 0) {
		if (truck.front() + sum <= W) {
			sum += truck.front();
			running.push(truck.front());
			truck.erase(truck.begin());
		}
		else {
			running.push(0);
		}
	}
	else if(sum==0){
		return false;
	}
	return true;
	
}


int solution(int bridge_length, int weight, vector<int> truck_weights) {
	W = weight;
	truck = truck_weights;
	t = 0;
	sum = 0;
	while (bridge_length-- > 0) {
		running.push(0);
	}
	while (move());
	cout << t << endl;
	return t;

}
void solution2() {
	//solution(10, 15, vector<int>{7, 2, 1, 3, 8, 2, 4, 1, 6, 4, 3});
	//solution(100, 100, vector<int>{10,10,10,10,10,10,10,10,10,10});
	solution(5, 5, { 2, 2, 2, 2, 1, 1, 1, 1, 1 });//19
}
//2020.10.08
//�б�(5) 15:10 ~15:15
//Ǯ��(18) 15:16 ~ 15:34 
//��Ʈ() 
//�ڵ�(69) 15:34 ~ 15:50, 16:37 ~ 17:30
//memoization ����,,

//dfs + memoization
//���� ���ش� �ȵ�..
//���ݸ� �� �����غ��� Ǯ �� ������!
//���� �����ɰž�
//����(55) 17:30 ~ 18:25
//��(147)

#define DEBUG 1 
#define MIN(a,b) { a < b ? a : b}
#pragma warning(disable:4996)
#include <stdio.h>
#include <queue>

#if DEBUG
#define mylog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define mylog(s,a){}
#define input(){}
#endif


#include <stdlib.h> 
#include <iostream> 
#include <vector> 

using namespace std;

vector<bool> day; //�ȵǴ� �� false
int total_day, absent_day;
int cost[101][101];
int cnt = 0;
int count_mem = 0;

int find_cost(int start_day, int num_coupon) {
	
	int min_cost = 987654321;

	//���� ��¥�� ��ü ������ �Ѿ�� ��!
	if (start_day > total_day) {
		return 0;
	}

	//���� ��¥�� �� �Ǵ� ���̸�
	if (day[start_day] == false)
	{
		//���� ������ ������ �Ǵ� ��¥ �ִ� �� ã�ƺ�
		for (int i = start_day + 1; i <= total_day; ++i)
		{
			if (day[i])
			{
				//�Ǵ� �� ã���� �ٽ� find_cost �θ���
				return cost[start_day][num_coupon] = find_cost(i, num_coupon);
			}
		}
		//���������� ������ �Ǵ³��� ������ �ݾ� 0 ��ȯ
		return cost[start_day][num_coupon] = 0;
	}

	//���� �Ǵ� ���̰�
	//�����Ͽ� ���� ������ �� �ݾ��� ������ �� ������
	if (cost[start_day][num_coupon] == 0)
	{

		//������ ������ 1�� ������ ���̰�
		//�������� �Ǵ� ���̰�
		//�� �������� �Ǵ� ���̸�
		//�׳� �Ѿ
		//������ 3�ϱ��� �̵��̴ϱ�~~
		if (start_day <= total_day - 2 && day[start_day + 1] && day[start_day + 2]) {
		}
		//������ ������ ���� or ���������̰ų�
		//����, ����, �� �������� �Ǵ� ���� �ƴϸ�
		else {
			//1�ϱ� ������ ���� �ݾ��� �̴ϸ� ����
			min_cost = MIN(min_cost,find_cost(start_day + 1, num_coupon) + 10000);
		}

		//������ 5�����̰�
		//5�� ���� �Ǵ³��̸�
		//�׳� �Ѿ
		//������ 5�ϱ��� �̵��̴ϱ�~~
		if (start_day <= total_day - 5 && day[start_day + 1]
			&& day[start_day + 2] && day[start_day + 3] && day[start_day + 4])
		{
		}
		//5�ϵ� �ȳ��Ұų�,
		//5�� �� �Ϸ�� �ȵǴ� �� ������
		else {
			//3�ϱ� ������ ���� �ݾװ� �̴ϸ� ��
			min_cost = MIN(min_cost, find_cost(start_day + 3, num_coupon + 1) + 25000);
		}

		//5�ϱ� ������ ���� �ݾװ� �̴ϸ� ��
		min_cost = MIN(min_cost, find_cost(start_day + 5, num_coupon + 2) + 37000);

		//���� ���簡�� ������ 3�� �̻��̸�
		if (num_coupon >= 3) {
			//������ ����ó���� �Ŷ� �̴ϸ� ���غ�
			min_cost = MIN(min_cost, find_cost(start_day + 1, num_coupon - 3));
		}
		//���� ã�� �ݾ� ����
		cost[start_day][num_coupon] = min_cost;

	}

	//�ݾ� ��ȯ
	return cost[start_day][num_coupon];

}

int main()
{
	input();
	int tmp;
	int answer;
	scanf("%d %d\n", &total_day, &absent_day);
	day.resize(total_day + 1, true);

	for (int i = 0; i < absent_day; i++) {
		scanf("%d ", &tmp);
		day[tmp] = false; //�ȵǴ� ��
	}
	answer = find_cost(1, 0); //�����ϰ� ���� ��������
	printf("%d", answer);
	return 0;
}

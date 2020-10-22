//2020.10.08
//읽기(5) 15:10 ~15:15
//풀이(18) 15:16 ~ 15:34 
//차트() 
//코딩(69) 15:34 ~ 15:50, 16:37 ~ 17:30
//memoization 포기,,

//dfs + memoization
//완전 이해는 안됨..
//조금만 더 생각해보면 풀 수 있을것!
//점점 적응될거야
//정답(55) 17:30 ~ 18:25
//합(147)

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

vector<bool> day; //안되는 날 false
int total_day, absent_day;
int cost[101][101];
int cnt = 0;
int count_mem = 0;

int find_cost(int start_day, int num_coupon) {
	
	int min_cost = 987654321;

	//현재 날짜가 전체 방학일 넘어가면 끝!
	if (start_day > total_day) {
		return 0;
	}

	//현재 날짜가 안 되는 날이면
	if (day[start_day] == false)
	{
		//다음 날부터 끝까지 되는 날짜 있는 지 찾아봄
		for (int i = start_day + 1; i <= total_day; ++i)
		{
			if (day[i])
			{
				//되는 날 찾으면 다시 find_cost 부르기
				return cost[start_day][num_coupon] = find_cost(i, num_coupon);
			}
		}
		//다음날부터 끝까지 되는날이 없으면 금액 0 반환
		return cost[start_day][num_coupon] = 0;
	}

	//현재 되는 날이고
	//현재일에 현재 쿠폰일 때 금액이 산정된 적 없으면
	if (cost[start_day][num_coupon] == 0)
	{

		//오늘이 끝나기 1일 전보다 앞이고
		//다음날이 되는 날이고
		//그 다음날도 되는 날이면
		//그냥 넘어감
		//무조건 3일권이 이득이니까~~
		if (start_day <= total_day - 2 && day[start_day + 1] && day[start_day + 2]) {
		}
		//오늘이 마지막 전날 or 마지막날이거나
		//오늘, 내일, 모레 연속으로 되는 날이 아니면
		else {
			//1일권 끊었을 때의 금액을 미니멈 지정
			min_cost = MIN(min_cost,find_cost(start_day + 1, num_coupon) + 10000);
		}

		//끝나기 5일전이고
		//5일 연속 되는날이면
		//그냥 넘어감
		//무조건 5일권이 이득이니까~~
		if (start_day <= total_day - 5 && day[start_day + 1]
			&& day[start_day + 2] && day[start_day + 3] && day[start_day + 4])
		{
		}
		//5일도 안남았거나,
		//5일 중 하루라도 안되는 날 있으면
		else {
			//3일권 끊었을 때의 금액과 미니멈 비교
			min_cost = MIN(min_cost, find_cost(start_day + 3, num_coupon + 1) + 25000);
		}

		//5일권 끊었을 때의 금액과 미니멈 비교
		min_cost = MIN(min_cost, find_cost(start_day + 5, num_coupon + 2) + 37000);

		//만약 현재가진 쿠폰이 3장 이상이면
		if (num_coupon >= 3) {
			//오늘을 쿠폰처리한 거랑 미니멈 비교해봄
			min_cost = MIN(min_cost, find_cost(start_day + 1, num_coupon - 3));
		}
		//실컷 찾은 금액 저장
		cost[start_day][num_coupon] = min_cost;

	}

	//금액 반환
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
		day[tmp] = false; //안되는 날
	}
	answer = find_cost(1, 0); //시작일과 누적 쿠폰개수
	printf("%d", answer);
	return 0;
}

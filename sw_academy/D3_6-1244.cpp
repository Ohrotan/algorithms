//2020.09.19 11:15 ~ 12:31 예외부분
#pragma warning(disable:4996)

#include <stdio.h>

using namespace std;

int TC;
int cards[6] = { 0, }; //카드배열
int input; //
int num = -1; //카드개수
int cnt; //교환횟수

int curId = 0; //현재 교환하려는 카드인덱스
int maxId = -1; //최대값의 카드인덱스
int max = -1; //최대값
bool flag = 0;
void swap() {
    //최대값이 여러개 && 교환횟수>=최대값수
    int maxCnt = 0;
    for (int i = 0; i <= num; ++i) {
        if (max == cards[i]) {
            ++maxCnt;
        }
    }
    int min = 10;
    //최대값이 두개 이상이고 나머지 숫자배열에 따라 달리 처리해야함
//그냥 가장 마지막 최대값과 자리바꾸면 안됨
// 나: 32881 -> 82831 -> 88231
//정답: 32881 - 38821 -> 88321
    if (maxCnt > 1) {

        for (int c = 0; c < maxCnt;++c) {
            //새로운 최소값 찾기
            min = 10;
            for (int i = 0; i < cnt && i < maxCnt; ++i) {
                if (cards[i] < min) {
                    curId = i;
                    min = cards[i];
                }
            }

            if (cards[curId] < max) { //현재자리와 최고값 교환
                cards[maxId] = cards[curId];
                cards[curId] = max;
                --cnt;
                if (cnt == 0) {
                    return;
                }
            }

            //새로운 최대값 찾기
            max = 0;
            for (int i = curId + 1; i <= num; ++i) {
                if (cards[i] >= max) {
                    max = cards[i];
                    maxId = i;
                }
            }

        }
    }
    else {

        curId = 0;
        while (1) {

            if (cards[curId] < max) { //현재자리와 최고값 교환
                cards[maxId] = cards[curId];
                cards[curId] = max;
                --cnt;
                
            }

            ++curId;
            if (cnt == 0 || curId == num) {
                break;
            }

            //새로운 최대값 찾기
            max = 0;
            for (int i = curId + 1; i <= num; ++i) {
                if (cards[i] >= max) {
                    max = cards[i];
                    maxId = i;
                }
            }

        }
    }


	if (cnt > 0) {
		for (int i = 0; i <= num; ++i) {
			for (int j = i + 1; j <= num; ++j) {
				if (cards[i] == cards[j]) {
					return;//같은 값끼리 남은 횟수 교환하면 되므로 현재가 최대값
				}
			}
		}

		//같은 값이 없고 교환횟수는 남았으므로 가장 작은 값끼리 교환
		if (cnt % 2 == 1) {
			max = cards[num];
            cards[num] = cards[num - 1];
			cards[num - 1] = max;
		
			return;
		}
	}
}
int main(void) {
	scanf("%d", &TC);
	getchar();
	for (int tc = 1; tc <= TC; ++tc) {
		num = -1;
		max = -1;
		while (1) {
			input = getchar();
			if (input != ' ') {
				cards[++num] = input-'0';
				if (cards[num] >= max) {
					max = cards[num];
					maxId = num;
				}
			}
			else {
				input = getchar();
				cnt = input - '0';
				input = getchar();
				if (input >= '0' && input<='9') {
					cnt = cnt * 10 + input-'0';
				}
				
				break;
			}
		}
		swap();
		printf("#%d ", tc);
		for (int i = 0; i <= num; ++i) {
			printf("%d", cards[i]);
		}
		printf("\n");

	}
}

/*
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;

priority_queue<int > pq;

int T;

bool compare(int a,int b)
{
    if(a>b)
        return true;
    else
        return false;
}

int main()
{
    scanf("%d",&T);

    for(int tc=1;tc<=T;tc++)
    {
        int arr;
        int aa[7]={0,};
        int bb[7]={0,};
        int N;
        scanf("%d %d",&arr,&N);
        int a=arr;
        int cnt=0;
        int MAX=0;
        while(a>0)
        {
            bb[cnt]=(a%10);
            MAX=max(MAX,a%10);
            cnt++;
            a=a/10;
        }
        sort(bb,bb+cnt,compare);

        a=arr;
        int cc=cnt;
        for(int i=cnt-1;i>=0;i--)
        {
            aa[i]=a%10;
            a=a/10;
        }
        int ccc=0;
        int r=N;
        for(int i=0;i<N;i++)
        {
                int flag2=0;
            if(i>5)
            {
                for(int j=0;j<cnt;j++)
                {
                    if(aa[j]==aa[j+1])
                    {
                        flag2=1;
                    }
                }
                if(flag2==0)
                {
                    int eee;
                    eee=aa[cnt-1];
                    aa[cnt-1]=aa[cnt-2];
                    aa[cnt-2]=eee;
                }
                continue;
            }
            int x=bb[i];
            int flag=0;
            for(int j=cnt-1;j>=0;j--)
            {
                int temp;
                if(x==aa[j])
                {
                    int w=j;
                    for(int k=1;k<r;k++)
                    {
                        if(x==aa[j-k])
                            w--;
                    }
                    for(int k=0;k<=w-1;k++)
                    {
                        if(aa[w]>aa[k])
                        {
                            temp=x;
                        aa[w]=aa[k];
                        aa[k]=x;
                        r--;
                        flag=1;
                        break;
                        }
                    }
                if(flag==0)
                    {
                        ++N;
                    }

                break;
                }

            }

        }

        printf("#%d ",tc);
        for(int i=0;i<cnt;i++)
            printf("%d",aa[i]);
        printf("\n");
    }
}
*/
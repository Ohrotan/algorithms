//2020.09.19 11:15 ~ 12:31 ���ܺκ�
#pragma warning(disable:4996)

#include <stdio.h>

using namespace std;

int TC;
int cards[6] = { 0, }; //ī��迭
int input; //
int num = -1; //ī�尳��
int cnt; //��ȯȽ��

int curId = 0; //���� ��ȯ�Ϸ��� ī���ε���
int maxId = -1; //�ִ밪�� ī���ε���
int max = -1; //�ִ밪
bool flag = 0;
void swap() {
    //�ִ밪�� ������ && ��ȯȽ��>=�ִ밪��
    int maxCnt = 0;
    for (int i = 0; i <= num; ++i) {
        if (max == cards[i]) {
            ++maxCnt;
        }
    }
    int min = 10;
    //�ִ밪�� �ΰ� �̻��̰� ������ ���ڹ迭�� ���� �޸� ó���ؾ���
//�׳� ���� ������ �ִ밪�� �ڸ��ٲٸ� �ȵ�
// ��: 32881 -> 82831 -> 88231
//����: 32881 - 38821 -> 88321
    if (maxCnt > 1) {

        for (int c = 0; c < maxCnt;++c) {
            //���ο� �ּҰ� ã��
            min = 10;
            for (int i = 0; i < cnt && i < maxCnt; ++i) {
                if (cards[i] < min) {
                    curId = i;
                    min = cards[i];
                }
            }

            if (cards[curId] < max) { //�����ڸ��� �ְ� ��ȯ
                cards[maxId] = cards[curId];
                cards[curId] = max;
                --cnt;
                if (cnt == 0) {
                    return;
                }
            }

            //���ο� �ִ밪 ã��
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

            if (cards[curId] < max) { //�����ڸ��� �ְ� ��ȯ
                cards[maxId] = cards[curId];
                cards[curId] = max;
                --cnt;
                
            }

            ++curId;
            if (cnt == 0 || curId == num) {
                break;
            }

            //���ο� �ִ밪 ã��
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
					return;//���� ������ ���� Ƚ�� ��ȯ�ϸ� �ǹǷ� ���簡 �ִ밪
				}
			}
		}

		//���� ���� ���� ��ȯȽ���� �������Ƿ� ���� ���� ������ ��ȯ
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
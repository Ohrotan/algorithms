//2020.10.03
//읽기(2) 23:22 ~ 23:24
//풀이(20) 23:24 ~ 23:44
//못풀것 같아서 정답코드 가져옴!
//정답() 10:40
//합()
#pragma warning(disable:4996)
#include <stdio.h>
#define m 1000000000

int dp[101][10][1 << 10];


int main(void)
{
    int full = (1 << 10) - 1; // 11 1111 1111
    for (int i = 1; i <= 9; i++)
    {
        dp[1][i][1 << i] = 1;
    }

    for (int i = 2; i <= 100; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= full; k++)
            {
                if (j == 0)
                {
                    dp[i][0][k | (1 << j)] = (dp[i][0][k | (1 << j)] + dp[i - 1][1][k]) % m;
                }
                else if (j == 9)
                {
                    dp[i][9][k | (1 << j)] = (dp[i][9][k | (1 << j)] + dp[i - 1][8][k]) % m;
                }
                else
                {
                    dp[i][j][k | (1 << j)] = (dp[i][j][k | (1 << j)] + dp[i - 1][j - 1][k] + dp[i - 1][j + 1][k]) % m;
                }
                if (i == 11)
                    k>1000&&dp[i][j][k] != 0 ? printf("(%d)%d ", k, dp[i][j][k]) : printf("");
            }
            printf("\n");
        }
        //printf("----------------------------------------");
    }
    int T;
    scanf("%d", &T);
    for (int ab = 1; ab <= T; ab++)
    {
        int N;
        scanf("%d", &N);
        int sum = 0;
        for (int j = 0; j <= 9; j++)
            sum = (sum + dp[N][j][full]) % m;
        printf("#%d %d\n", ab, sum);
    }
}

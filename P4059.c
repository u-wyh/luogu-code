#include<stdio.h>
#include<string.h>
#include<limits.h>  // Ϊ��ʹ��INT_MIN

#define max(x,y) ((x)>(y)?(x):(y))
#define MAX(x,y,z) (max(max((x),(y)),(z)))

char s1[3001], s2[3001];
int P[5][5];
int f[3001][3001][4];

// f[i][0]��ʾs1,s2��������ĸ��β�����Ž�
// f[i][1]��ʾs1�Կո��β,s2����ĸ��β�����Ž�
// f[i][2]��ʾs1����ĸ��β,s2�Կո��β�����Ž�

int n, m, A, B;

int work(char ch)
{
    switch(ch)
    {
        case 'A': return 1;
        case 'T': return 2;
        case 'G': return 3;
        case 'C': return 4;
    }
    return 0;  // Ĭ�Ϸ���0����Ȼ�����֧ʵ���ϲ��ᱻִ�У������������ǺϷ��ģ�
}

int main()
{
    freopen("dnaseq.in", "r", stdin);
    freopen("dnaseq.out", "w", stdout);

    scanf("%s", s1 + 1);
    n = strlen(s1 + 1);
    scanf("%s", s2 + 1);
    m = strlen(s2 + 1);

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            scanf("%d", &P[i][j]);

    scanf("%d %d", &A, &B);

    // ��ʼ��f����Ϊһ����С��ֵ��ע�⣺������INT_MIN�ľ���ֵ����Ϊmemset�ǰ��ֽ����õģ�
    memset(f, 0x80, sizeof(f));  // 0x80��-128���㹻С��������INT_MIN

    f[0][0][0] = 0;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            if (i + j == 0) continue;

            int t1 = work(s1[i]), t2 = work(s2[j]);

            if (i != 0 && j != 0)
                f[i][j][0] = P[t1][t2] + MAX(f[i-1][j-1][0], f[i-1][j-1][1], f[i-1][j-1][2]);

            if (j != 0)
                f[i][j][1] = MAX(f[i][j-1][0] - A, f[i][j-1][1] - B, f[i][j-1][2] - A);

            if (i != 0)
                f[i][j][2] = MAX(f[i-1][j][0] - A, f[i-1][j][1] - A, f[i-1][j][2] - B);
        }

    printf("%d\n", MAX(f[n][m][0], f[n][m][1], f[n][m][2]));

    return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define maxn 60

int a[maxn][maxn];
int F[2 * maxn][maxn][maxn];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // ��ʼ��F����Ϊ-1
    memset(F, -1, sizeof(F));
    // ��ʼ�����Ͻǵ�
    F[2][1][1] = 0;

    // ��̬�滮���F����
    for (int k = 3; k < m + n; k++) {
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int s = F[k][i][j];
                if (F[k - 1][i][j] > s) s = F[k - 1][i][j];
                if (F[k - 1][i - 1][j] > s) s = F[k - 1][i - 1][j];
                if (F[k - 1][i][j - 1] > s) s = F[k - 1][i][j - 1];
                if (F[k - 1][i - 1][j - 1] > s) s = F[k - 1][i - 1][j - 1];
                if (s == -1) continue; // ���s��Ȼ��-1��˵�����ܵ���õ�
                F[k][i][j] = s + a[k - i][i] + a[k - j][j];
            }
        }
    }

    // ������½ǵĽ�����������ǿɴ�ģ�ʵ�ʿ�����Ҫ��飩
    printf("%d\n", F[m + n - 1][n - 1][n]);

    return 0;
}

#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 51

static int dp[Max][Max];

int min(int a, int b) {
    return a < b ? a : b;
}

int compute(char *s, int n) {
    // ��ʼ������Ϊ1��2���Ӵ���dpֵ
    for (int i = 0; i < n - 1; i++) {
        dp[i][i] = 1;
        dp[i][i + 1] = (s[i] == s[i + 1]) ? 1 : 2;
    }

    // ���dp����
    for (int len = 3; len <= n; len++) { // �ӳ���Ϊ3���Ӵ���ʼ����
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i][j - 1]; // ���������ͬ����̳���벿�ֵĽ��
            } else {
                dp[i][j] = INT_MAX; // ��ʼ��Ϊ���ֵ����������Сֵ
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    char s[Max];
    fgets(s, Max, stdin);
    // ȥ��fgets��ȡ�Ļ��з�
    s[strcspn(s, "\n")] = 0;
    int n = strlen(s);
    printf("%d\n", compute(s, n));
    return 0;
}

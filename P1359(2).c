#include<stdio.h>
#include<limits.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int nums[n][n];  // ����Ϊ n x n ��С
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &nums[i][j]);  // ֱ�Ӷ�ȡ�� nums[i][j]
        }
    }
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    dp[n-1] = 0;  // ���һ��վ�㵽��������Ϊ 0
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            dp[i] = min(dp[i], dp[j] + nums[i][j]);  // ʹ����ȷ������
        }
    }
    printf("%d\n", dp[0]);
    return 0;
}

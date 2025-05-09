#include<stdio.h>
#include<limits.h> // ���ڶ���INT_MAX

int n, k, x, dp[4009];

int min(int a,int b)
{
    return a<b?a:b;
}

int main() {
    scanf("%d %d %d", &n, &k, &x);
    for (int i = 0; i <= 4000; i++) {
        dp[i] = INT_MAX; // ��ʼ��Ϊ����󣬱�ʾ���ɴ�
    }
    dp[x] = 0; // ��ʼ״̬��һ������������

    while (n--) {
        int id, a;
        scanf("%d %d", &id, &a);
        int m = 4000;
        if (id == 2)
            m = 1899; // ��������ı���������

        // �������
        for (int i = a + 1; i <= m; i++) {
            int now = i - (i - a + 3) / 4; // ��������ķ���
            if (now <= 4000 && dp[i] != INT_MAX) { // ȷ��now�ڷ�Χ����dp[i]��Ч
                dp[now] = (dp[now] < dp[i] + 1) ? dp[now] : dp[i] + 1; // ���Ը���
            }
        }

        // �������
        for (int i = min(m, a - 1); i >= 0; i--) {
            int now = i + (a - i) / 4;
            if (now <= 4000 && dp[i] != INT_MAX) { // ȷ��now�ڷ�Χ����dp[i]��Ч
                dp[now] = (dp[now] < dp[i] + 1) ? dp[now] : dp[i] + 1; // ���Ը���
            }
        }
    }

    // ���Ҵ�
    for (int i = 4000; i >= 0; i--) {
        if (dp[i] <= k) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}


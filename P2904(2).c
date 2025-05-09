#include<stdio.h>
#include<limits.h> // ����INT_MAX

#define MAX_N 10010

int f[MAX_N];
int sum[MAX_N];
int w[MAX_N];
int m, n;

int main() {
    scanf("%d %d", &n, &m);
    int inf = INT_MAX; // ʹ��INT_MAX��Ϊ���޴�
    for (int i = 1; i <= n; i++) {
        f[i] = inf; // ��ʼ��f[i]Ϊ���޴�
        scanf("%d", &w[i]);
        if (i > 1) {
            sum[i] = sum[i - 1] + w[i]; // ����ǰ׺�ͣ�ע��i>1ʱ�ſ�ʼ�ۼ�
        } else {
            sum[i] = w[i]; // ��һ��Ԫ�ص�ǰ׺�;���������
        }
    }
    for (int i = 1; i <= n; i++) {
        sum[i] += 2 * m; // ÿ��Ԫ�ؼ���2*m
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (f[j - i] != inf) { // ȷ��f[j-i]�������޴�Ž��и���
                f[j] = (f[j] < f[j - i] + sum[i]) ? f[j] : f[j - i] + sum[i]; // ����f[j]
            }
        }
    }

    if (f[n] == inf) {
        printf("No solution\n"); // ���û���ҵ����н�
    } else {
        printf("%d\n", f[n] - m); // ����⣬��ȥm��Ϊ����Ҫ������
    }

    return 0;
}

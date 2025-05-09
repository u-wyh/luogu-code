#include <stdio.h>
#include <limits.h> // ����INT_MAX

#define MAX_N 1000005

int min(int a,int b)
{
    return a<b?a:b;
}

int n;
int a[MAX_N];
int f[MAX_N + 1]; // ע���������1����ΪҪ����f[n+1]

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        f[i] = INT_MAX; // ע���ʼ��
    }
    f[n + 1] = INT_MAX; // ͬ����ʼ��f[n+1]

    for (int i = 1; i <= n + 1; i++) { // ѭ����n+1
        // ע������i��1��ʼ����������a[i]ֻ���嵽n������a[i]��i=n+1ʱδ���壬��f[i]�ļ��㲻��Ҫa[n+1]
        f[i] = INT_MIN; // ������Ӧ��ʹ��һ���ܴ������Ϊ��ʼֵ��������Ϊ�˼��߼�������Ϊ��Сֵ
        if (i >= 1) f[i] = min(f[i], f[i - 1]);
        if (i >= 2) f[i] = min(f[i], f[i - 2]);
        if (i >= 3) f[i] = min(f[i], f[i - 3]);
        if (i <= n) f[i] += a[i]; // ֻ��i<=nʱ��a[i]����Ϊa[n+1]δ����
    }

    // ����⣬ע��f[n+1]������Ȼ��INT_MAX����ʾ�޷������δ����
    if (f[n + 1] == INT_MAX) {
        printf("Unreachable\n"); // ��������ʾ�޷������ֵ
    } else {
        printf("%d\n", f[n + 1]);
    }

    return 0; // �������
}

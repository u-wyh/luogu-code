#include <stdio.h>

long long ans;
int p[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int s = 0, v = a;
    while (v) {
        v /= 10;
        s++; // ����λ��
    }

    for (int i = a; i < b; i++) { // ö��n
        int n = i;
        int m = (n % 10) * p[s - 1] + n / 10; // �����ļ���m
        while (n != m) { // ��n == m����mö�����
            if (n < m && m <= b) { // ������������ans++
                ans++;
            }
            m = (m % 10) * p[s - 1] + m / 10; // ö��m
        }
    }

    printf("%lld\n", ans);
    return 0;
}

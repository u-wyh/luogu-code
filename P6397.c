#include <stdio.h>
#define ll long long

double d[100005];
double k;
int n;

int check(double x) {
    double maxx = d[1] + x; // 1����ʹ��������λ��
    for (int i = 2; i <= n; i++) {
        if (d[i] - x - maxx > k) return 0; // ��i����ʹ����£�����У����޷���������
        maxx += k; // ��������ʹi����ʹ�ߵ�����i-1����ʹk��λ��
        if (d[i] + x < maxx) maxx = d[i] + x; // ����þ�ʱ�䶼�߲����������maxxΪi����ʹ�ļ���λ��
    }
    return 1;
}

int main() {
    scanf("%lf%d", &k, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &d[i]);
    double l = 0, r = d[n], ans = 0;
    while (r - l >= 0.000001) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            ans = mid;
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.3lf\n", ans);
    return 0;
}

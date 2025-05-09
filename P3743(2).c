#include <stdio.h>

int n; // �豸����
double p; // ������ĳ���ٶ�
double a[200000], b[200000];
double lbound = 0, rbound = 1e10;
double sum = 0; // ��Ҫ�������ܺͣ���֤��ʱ���������豸�����������ٶ��ܺͣ�-1����ʱ��

int check(double ans) { // ��֤��
    double q = p * ans; // ���������ṩ������
    sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] * ans <= b[i]) { // ���豸���е���������ʹ��ʱ����Ҫ������
            continue; // ���Ը��豸
        }
        sum += (a[i] * ans - b[i]); // �����ó������磬ʹ�豸���е���������ʹ��ʱ����Ҫ������������¼��Ҫ��������
    }
    return sum <= q; // ���Ƚ���Ҫ�������ܺͺͳ��������ṩ��������
}

int main() {
    scanf("%d %lf", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &a[i], &b[i]);
        sum += a[i];
    }
    if (sum <= p) { // �������豸�����������ٶ��ܺͻ���С�ڳ�����ĳ���ٶȣ����-1��
        printf("%.6f\n", -1.0);
        return 0;
    }
    while (rbound - lbound > 1e-6) {
        double mid = (lbound + rbound) / 2;
        if (check(mid)) {
            lbound = mid;
        } else {
            rbound = mid;
        }
    }
    printf("%.6f\n", lbound);
    return 0;
}

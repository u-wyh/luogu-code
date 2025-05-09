#include<stdio.h>

double a, b, c, d;

double fc(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    double l, r, m, x1, x2;
    int s = 0, i;

    // ����
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

    for (i = -100; i < 100; i++) {
        l = i;
        r = i + 1;
        x1 = fc(l);
        x2 = fc(r);

        // �ж���˵㣬�����ֱ�����
        if (x1 == 0.0) {
            printf("%.2lf ", l);
            s++;
        }

        // �������и�
        if (x1 * x2 < 0.0) {
            while (r - l >= 0.001) {
                m = (l + r) / 2;
                if (fc(m) * fc(r) <= 0.0) {
                    l = m;
                } else {
                    r = m;
                }
            }
            // ע�⣺����Ӧ���������ȷ�ĸ���λ�ã���l��(l+r)/2
            printf("%.2lf ", l); // ����ʹ�� (l + r) / 2 ����ȡ����ȷ��ֵ
            s++;
        }

        // �ҵ��������˳�
        if (s == 3) {
            break;
        }
    }

    return 0;
}

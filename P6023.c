#include <stdio.h>
#include <stdlib.h>

long long n, m, k; // ע�⣺��Ϊ���ݷǳ�������ÿһ�����ݶ��ÿ�long long����Ȼ�����
long long a, b, s;
long long c[99999999]; // �۲����ݷ�Χ������RE�Ϳ��������
long long maxn = 0; // ������¼���ֵ

int main() {
    scanf("%lld %lld %lld", &n, &m, &k); // �����������
    for (int i = 0; i < k; i++) { // �ֱ�����ÿһ��������ʩ��ע�������0��ʼ��
        scanf("%lld %lld", &a, &b);
        if (n - b > 0) { // �ж��Ƿ����õ�����
            if (a <= m) { // ȷ��a����Ч������
                c[a - 1] += (n - b); // �洢��һ����û��֣�C���������0��ʼ
            }
        }
    }
    for (int i = 0; i < m; i++) { // ע����Ҫ����������m�ڲ���
        if (c[i] > maxn) { // ����m��֮�п����õ���������
            maxn = c[i];
        }
    }
    printf("%lld\n", maxn); // ���
    return 0; // ��ϰ��
}

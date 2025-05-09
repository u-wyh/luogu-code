#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define MAXK 105

int n, k;
double a[MAXN], f[MAXN][MAXK]; // a[i]��ʾ��i�����ʵĳ���
double s[MAXN]; // s��ǰ׺������

int main() {
    scanf("%d%d", &n, &k);
    double ave = 0.0; // ��¼ƽ����
    for (int i = 1; i <= n; i++) {
        char str[25];
        scanf("%s", str); // ���뵥�ʣ�ȫ��x��
        a[i] = strlen(str); // ��¼���ʳ���
        ave += a[i]; // �ۼ���������ƽ����
        s[i] = (i > 0) ? s[i-1] + a[i] : a[i]; // ����ǰ׺�ͣ�ע��i=1ʱ�����⴦��
    }
    ave /= k; // ���ƽ����

    // ��ʼ����̬�滮����
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            f[i][j] = INT_MAX; // ��ʼ�������ֵ
        }
        f[i][1] = (s[i] - ave * i) * (s[i] - ave * i) / i; // �ֳ�һ�ε���Сֱֵ�Ӽ��������
    }

    // ��̬�滮���
    for (int j = 2; j <= k; j++) { // �ֳ�һ�β��ô����ˣ�ֱ�Ӵӷֳ����ο�ʼ����
        for (int i = j; i <= n; i++) { // ǰ��i�������Ҳֻ�ֳܷ�i��
            for (int l = 1; l < i; l++) { // ö�ٷָ��
                f[i][j] = fmin(f[i][j], f[l][j-1] + (s[i] - s[l] - ave * (i - l)) * (s[i] - s[l] - ave * (i - l)) / (i - l));
            }
        }
    }

    printf("%.1lf\n", f[n][k]); // �������

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int M = 10005;
int f[101][11][11][11];
// f[i][j][k][m] ��ʾǰi����Ʒ����ǰ������A j����B k����C m��
int n;
char obje[101]; // ����Ʒ

int main() {
    memset(f, 63, sizeof(f)); // ��Ϊinf
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) cin >> obje[i];
    f[0][0][0][0] = 0; // ��ֵ

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 10; ++j) {
            for (int k = 0; k <= 10; ++k) {
                for (int p = 0; p <= 10; ++p) {
                    if (j + k + p > 10) continue; // ������Ʒ���ܳ���10�������򲻴���

                    // ����״̬ת�ƣ������(ֻװ)��ע��j,k,p�ô���
                    if (obje[i] == 'A' && j)
                        f[i][j][k][p] = f[i - 1][j - 1][k][p];
                    if (obje[i] == 'B' && k)
                        f[i][j][k][p] = f[i - 1][j][k - 1][p];
                    if (obje[i] == 'C' && p)
                        f[i][j][k][p] = f[i - 1][j][k][p - 1];

                    // ����ж����ת��
                    f[i][0][k][p] = min(f[i][0][k][p], f[i][j][k][p] + 1);
                    f[i][j][0][p] = min(f[i][j][0][p], f[i][j][k][p] + 1);
                    f[i][j][k][0] = min(f[i][j][k][0], f[i][j][k][p] + 1);
                }
            }
        }
    }

    printf("%d\n", f[n][0][0][0]); // ��̬
    return 0;
}


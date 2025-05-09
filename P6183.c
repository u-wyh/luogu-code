#include <stdio.h>

#define MAX_N 70000
#define MAX_COLUMNS 20

int n, mapp[MAX_N][MAX_COLUMNS], num = 2;

int main() {
    mapp[1][1] = 0;  // ���� n=1 ʱ�Ĵ𰸡�
    mapp[2][1] = 1;

    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {  // ����ÿһ�� i ��Ҫ�õ� i-1 ʱ�Ĵ�
        num *= 2;  // ������Ҫ��� 2 �� n �����д�

        // ��ת�ϰ벿�ֵ��°벿��
        for (int j = 1; j <= num / 2; j++) {
            for (int k = 1; k < i; k++) {
                mapp[num / 2 + j][k] = mapp[num / 2 - j + 1][k];
            }
        }

        // �趨��벿��ĩβΪ 1��ǰ�벿��ĩβΪ 0
        for (int j = 1; j <= num; j++) {
            if (j > num / 2) {
                mapp[j][i] = 1;
            } else {
                mapp[j][i] = 0;
            }
        }
    }

    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= n; j++) {
            if (mapp[i][j]) {
                printf("X");  // ������ת���� O �� X��
            } else {
                printf("O");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        printf("O");
    }
    printf("\n");

    return 0;
}

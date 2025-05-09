#include <stdio.h>
#include <stdbool.h> // ���벼������֧��

#define MAX_N 1000
#define MAX_M 1000

int ans[MAX_N]; // �洢�������
int a[MAX_N];   // ţÿ����Ҫ��ÿ��ά��������С��
int b[MAX_M][MAX_N]; // ÿ�����ϰ����ĸ���ά���������Ķ���
int c[MAX_N];  // ����������ѡ������ϱ��
int n, m, minn = 100000000;

// �ж��Ƿ�����ά��������
bool pd(int x) {
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= x; j++) {
            sum += b[c[j]][i];
        }
        if (sum < a[i]) return false;
    }
    return true;
}

// ��������
void search(int t, int s) {
    if (t > m) {
        if (pd(s)) {
            if (s < minn) {
                minn = s;
                for (int i = 1; i <= minn; i++) {
                    ans[i] = c[i];
                }
            }
        }
        return;
    }
    c[s + 1] = t;
    search(t + 1, s + 1);
    c[s + 1] = 0; // ע�⣺��C�У�����Ԫ��δ��ʼ��ʱ��ֵ�ǲ�ȷ���ģ���������ʽ��Ϊ0�������Ļ��ݲ���
    search(t + 1, s);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    search(1, 0);
    printf("%d ", minn);
    for (int i = 1; i <= minn; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}

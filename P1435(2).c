#include <stdio.h>
#include <string.h>
#include <limits.h> // ����INT_MAX

#define MAX_LEN 1200

int f[2][MAX_LEN];
char s[MAX_LEN];

// �Զ����min��������ΪC��׼����û��ֱ�ӷ������������н�Сֵ�ĺ���
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%s", s + 1); // ��s[1]��ʼ�����ַ�����s[0]δʹ��
    int len = strlen(s + 1);
    int now = 0;

    // ��ʼ��f���飬������������Ӵ��ĳ�ʼ��С�������Ϊ�ǳ��������INT_MAX��
    // ����f[0][0]Ϊ0�����ַ�������Ҫ���룩
    for (int i = 0; i <= len; i++) {
        f[0][i] = INT_MAX;
    }
    f[0][0] = 0;

    // ��̬�滮����
    for (int i = len - 1; i >= 1; i--) {
        for (int j = i + 1; j <= len; j++) {
            if (s[i] == s[j]) {
                f[now ^ 1][j] = f[now][j - 1];
            } else {
                f[now ^ 1][j] = min(f[now][j], f[now ^ 1][j - 1]) + 1;
            }
        }
        now ^= 1;
    }

    // ��������ע�����洢��f[now][len]��
    printf("%d\n", f[now][len]);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ����max��min����
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int f(char *a, int n, int x) {
    int s = 0;
    char a1 = a[x];
    char b2 = a[x + 1];
    int i;

    // ��ǰ��
    for (i = x; i >= 0 && (a[i] == a1 || a[i] == 'w'); i--) {
        s++;
    }

    // ����
    for (i = x + 1; i < n && (a[i] == b2 || a[i] == 'w'); i++) {
        s++;
    }

    return s;
}

int main() {
    int ans = -1, n;
    char a[3000]; // ���������ַ������Ȳ�����1000��Ϊ�˴���ѭ�����ƣ����������ռ�

    scanf("%d%s", &n, a);
    int len = strlen(a);
    // �����ַ����Դ���ѭ��
    char temp[3000 * 3 + 1]; // +1 for the null terminator
    strcpy(temp, a);
    strcat(temp, a);
    strcat(temp, a);

    // �����м����һ��
    for (int i = len; i < 2 * len; i++) {
        if (temp[i] == temp[i + 1]) {
            continue;
        }

        if (temp[i] == 'w') {
            temp[i] = 'r';
            ans = max(ans, f(temp, 3 * len, i));
            temp[i] = 'b';
            ans = max(ans, f(temp, 3 * len, i));
            temp[i] = 'w';
        }

        ans = max(ans, f(temp, 3 * len, i));
    }

    ans = min(ans, n); // �Ҳ���ܱ��ܳ���
    if (ans == -1) {
        ans = n; // ������������ض���һ·continue������
    }

    printf("%d\n", ans);
    return 0;
}

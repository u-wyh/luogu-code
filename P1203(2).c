#include<string.h>
#include<stdio.h>
#include<stdlib.h>

// ����max��min����
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    char s[700], c;
    int a = 0, b = 0, w = 0, ans = 0;

    scanf("%d%s", &n, s);

    // �����ַ����Դ���ѭ��
    char temp[700 * 2];
    memcpy(temp, s, n);
    memcpy(temp + n, s, n);

    // ��ʼ��cΪ��һ���ַ�
    c = s[0];

    // �����������ȵ��ַ���
    for (int i = 0; i < n * 2; i++) {
        if (temp[i] == 'w') {
            b++;
            w++;
        } else if (temp[i] == c) {
            b++;
            w = 0;
        } else {
            ans = max(ans, a + b);
            a = b - w;
            b = w + 1;
            w = 0;
            c = temp[i];
        }
    }

    // ���һ�θ���ans
    ans = max(ans, a + b);

    // ����������������n
    printf("%d\n", min(ans, n));

    return 0;
}

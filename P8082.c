#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

char s[MAXN];
int st[MAXN], top = 0;

int main() {
    int n, k;
    scanf("%d%d%s", &n, &k, s + 1); // ע��s+1����Ϊ����������1��ʼ��ȡ

    for (int i = 1; i <= n; i++) {
        int x = s[i] - '0'; // ���ַ�ת��Ϊ����
        while (k && top && st[top] < x) {
            k--;
            st[top--] = 0; // ��������
        }
        st[++top] = x; // �������
    }

    // ����ջ������������ʣ���k����
    for (int i = 1; i <= top - k; i++) {
        printf("%d", st[i]);
    }
    return 0;
}

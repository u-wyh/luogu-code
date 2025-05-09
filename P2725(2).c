#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VALUE 2000000
#define LL unsigned long long

int k, n, i, j, s, a; // k: �ܹ����ĵ���Ʊ��
int f[MAX_VALUE + 1]; // f[i]��ʾ������ֵΪi������Ҫ����Ʊ��

// �Զ���min����
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d", &k, &n);
    for (i = 0; i <= MAX_VALUE; i++) {
        f[i] = MAX_VALUE + 1; // ���Ϊ���ɴ�
    }
    f[0] = 0; // ����ֵ����0����Ʊ���Թ���0

    for (i = 1; i <= n; i++) {
        scanf("%d", &a); // ������Ʊ��ֵ
        for (j = a; j <= MAX_VALUE; j++) {
            if (f[j - a] + 1 <= k) { // �õ���Ʊ��Ŀ�ڷ�Χ��
                f[j] = min(f[j], f[j - a] + 1); // ȡ��С��
            }
        }
    }

    s = 0;
    for (i = 1; i <= MAX_VALUE; i++) { // �Ҵ�1��ʼ��������ȡ�ļ��ϵ����һ��
        if (f[i] == MAX_VALUE + 1) { // �ղ�����
            s = i - 1; // ��¼
            break; // �˳�
        }
    }

    printf("%d\n", s); // ���
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 1000005

char s[L];
int l, f[L], Ans = 0, id = 0;

int main() {
    scanf("%s", s + 1); // ���룬�±��1��ʼ
    l = strlen(s + 1); // �±��1��ʼ���ַ�������
    for (int i = 2; i <= l; ++i) { // s[1]��Ȼ�޷�ƥ�䣬���Դ�2��ʼ
        if (s[i] == '(' || s[i] == '[') continue; // �����
        else if ((s[i] == ')' && s[i - f[i - 1] - 1] == '(') ||
                 (s[i] == ']' && s[i - f[i - 1] - 1] == '[')) {
            f[i] = f[i - 1] + 2 + (i - f[i - 1] > 2 ? f[i - f[i - 1] - 2] : 0);
            // ע�⴦��i-f[i-1]-2����Խ������
            if (f[i] > Ans) {
                Ans = f[i];
                id = i; // Ans��¼�����ƥ�䣬id��¼�����ƥ����±�
            }
        }
    }
    for (int i = id - Ans + 1; i <= id; ++i) {
        printf("%c", s[i]);
    }
    putchar('\n');
    return 0;
}

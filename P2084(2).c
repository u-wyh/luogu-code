#include <stdio.h>
#include <string.h>

int m;
char c[1001];

int main()
{
    scanf("%d ", &m); // ע�⣺������һ���ո���%d���棬���ᵼ��scanf��ȡ�������������Ŀհ��ַ�
    // ʹ��fgets����gets��ע��fgets���ȡ���з�������������Ҫȷ����Ҫ��������߽�
    fgets(c, sizeof(c), stdin);
    // ȥ��fgets��ȡ�Ļ��з���������ڣ�
    c[strcspn(c, "\n")] = 0;

    int len = strlen(c);
    for (int i = 0; i < len; i++)
    {
        if (i != 0 && c[i] != '0')
            printf("+");
        if (c[i] == '0')
            continue;
        printf("%c*%d^%d", c[i], m, len - i - 1);
    }
    printf("\n"); // ��������һ�����з��Ա��������ʽ��һ���ԣ���ѡ��
    return 0;
}

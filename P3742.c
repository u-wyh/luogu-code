#include<stdio.h>
#include<string.h>

int main()
{
    int n;
    scanf("%d", &n);
    char s1[n+1], s2[n+1], s3[n+1];  // ��1�Դ洢�ַ���������'\0'
    scanf("%s", s1);
    scanf("%s", s2);

    int lessThan = 0;  // ���ڱ���Ƿ���s1�����ַ�С��s2�еĶ�Ӧ�ַ�

    for(int i = 0; i < n; i++)  // ��ȷ��ѭ���߽�
    {
        if(s1[i] < s2[i])
        {
            printf("-1\n");
            lessThan = 1;
            break;  // һ������С�ڵ���������˳�ѭ��
        }
        s3[i] = s2[i];  // ����s2��s3
    }

    if (!lessThan) {
        s3[n] = '\0';  // ȷ��s3��null�ַ���β
        puts(s3);
    }

    return 0;
}

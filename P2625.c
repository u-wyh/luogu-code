#include<stdio.h>
#include<string.h>

struct travel
{
    char str[20];
    int nums;  // ע����������˷ֺ�
};

int main()
{
    int n;
    scanf("%d", &n);
    getchar();  // ��ȡ������֮ǰ�Ļ��з�
    struct travel t[n+1];

    for(int i = 1; i <= n; i++)
    {
        fgets(t[i].str, 20, stdin);
        while (getchar() == '\0')
        scanf("%d", &t[i].nums);
    }

    // ʾ������ӡ��ȡ������
    for(int i = 1; i <= n; i++)
    {
        printf("%s %d\n", t[i].str, t[i].nums);
    }

    return 0;
}
/*#include<stdio.h>
#include<math.h>
#include<string.h>

struct travel
{
    char str[20];
    int nums;
};
int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    struct travel t[n+1];
    for(int i=1;i<=n;i++)
    {
        fgets(t[i].str,20,stdin);
        scanf("%d",t[i].nums);
    }
    return 0;
}*/

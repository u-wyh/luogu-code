#include<stdio.h>
#include<stdlib.h>
#define MAXN 205

// �ȽϺ���������qsort
int cmp(const void *x, const void *y) {
    return (*(int *)y - *(int *)x);
}

int main() {
    int m, s, c, ans;
    int a[MAXN], C[MAXN],b[MAXN],min=s,max=0;
    scanf("%d %d %d", &m, &s, &c);
    for(int i=1;i<=s;i++)
    {
        a[i]=0;
        C[i]=0;
        b[i]=0;
    }
    int k;
    for (int i = 1; i <= c; i++) {
        min=min<k?min:k;
        max=min>k?max:k;
        scanf("%d",&k);
        a[k]=1;
    }
    ans=s;

    if (m >= c) { // ���ľ��������ţ����ÿֻţ������һ��ľ��
        printf("%d\n", c);
        return 0;
    }
    C[0]=0;
    for(int i=min;i<=max;i++)
    {
        if(a[i]==1)
        {
            C[i]=0;
            b[i-1]=C[i-1];
        }
        else
            C[i]=1+C[i-1];
    }

    qsort(b + 1, s, sizeof(int), cmp); // �Ծ����������

    // ��ȥ������ľ������ֱ������m��ľ��
    for (int i = 1; i <= m -1; i++) {
        ans  -= b[i];
    }

    printf("%d\n", ans);

    return 0;
}

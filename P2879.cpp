#include<bits/stdc++.h>

using namespace std;

struct node {
    int first;
    int second;
}h[10005];
int kdl[10005][10005];//�������ȥ��
int n, f[10005], hest, r, t, a, b, c, d;

int main()
{
    scanf("%d%d%d%d", &n, &t, &hest, &r);
    for (int i = 1; i <= n; i++) {
        f[i] = hest;
    }
    for (int i = 1; i <= r; i++) {
        scanf("%d%d", &a, &b);
        h[i].first = min(a, b);
        h[i].second = max(a, b);//���������С�ĸ���first����ĸ���second
        if (kdl[a][b] == 1)
            continue;
        kdl[a][b] = 1;//����Ѿ����һ�ξ�������û����ͱ�ǲ�����
        for(int j=h[i].first+1;j<h[i].second;j++)
            f[j]--;
    }//���м�����ţ�ĸ߶ȼ�һ
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i]);
    return 0;
}

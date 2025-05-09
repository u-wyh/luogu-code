#include<stdio.h>

int change(int n){
    int ans=0;
    while(n){
        ans+=n%10;
        n/=10;
    }
    return ans;
}

int euler(int n) {
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0��ʾ������1��ʾ����
    int prime[n / 2 + 1];
    int cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }

        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            visit[i * prime[j]] = 1; // ���Ϊ����
            if (i % prime[j] == 0) {
                break; // ÿ������ֻ������С��������ɸȥһ��
            }
        }
    }
    int ans=0;
    for(int i=0;i<cnt;i++){
        if(!visit[change(prime[i])])
            ans++;
    }

    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",euler(b)-euler(a-1));
    }
    return 0;
}

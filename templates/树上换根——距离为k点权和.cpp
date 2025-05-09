// ÿ���ڵ����k���ڵ�Ȩֵ��(�ݹ��)
// ����һ��n���������ÿ�����е�Ȩ
// ����ÿ���ڵ�ľ��벻����k�Ľڵ�������ɸ�
// ����Щ�ڵ�Ȩֵ�����������Ǹõ㲻��������k�ĵ�Ȩ��
// ��ӡÿ���ڵ㲻��������k�ĵ�Ȩ��
// ע��k������
// �������� : https://www.luogu.com.cn/problem/P3047
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code05_SumOfNearby2�ļ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXK = 25;

int n,k;
int arr[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sum[MAXN][MAXK];
// sum[u][i] : ��uΪͷ�������ڣ�����Ϊi�Ľڵ�Ȩֵ��
int dp[MAXN][MAXK];
// dp[u][i] : ��u�������������ϣ�����Ϊi�Ľڵ�Ȩֵ��

void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            for(int j=1;j<=k;j++){
                sum[u][j]+=sum[v][j-1];
            }
        }
    }
}

void dfs2(int u,int f){
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp[v][0] = sum[v][0];
            dp[v][1] = sum[v][1] + dp[u][0];
            for (int i = 2; i <= k; i++) {
                dp[v][i] = sum[v][i] + dp[u][i - 1] - sum[v][i - 2];
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        cin>>sum[i][0];
    }
    dfs1(1,0);
    for(int i=0;i<=k;i++){
        dp[1][i]=sum[1][i];
    }
    dfs2(1,0);
    for (int i = 1, ans; i <= n; i++) {
        ans = 0;
        for (int j = 0; j <= k; j++) {
            ans += dp[i][j];
        }
        cout<<ans<<endl;
    }
    return 0;
}

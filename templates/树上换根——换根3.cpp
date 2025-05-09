// ��ת��·�������ٵ��׶�
// ����һ��n������������Ǹ�����ÿ���߶��������
// ��Ҫѡ��ĳ������Ϊ�׶���Ҫ���׶�һ������ȥ���κ�һ������
// ����һ����������Ҫ��תһЩ�ߵķ�����������������뷭ת��·������������
// ��ӡ���ٷ�ת������·�Ϳ���ӵ���׶�
// ��������ɵ����׶�ʱ����ת��·�������������ٵģ���ô��ӡ��Щ��
// �������� : https://www.luogu.com.cn/problem/CF219D
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int dp[MAXN];

void dfs1(int u,int f){
    dp[u]=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            dp[u]+=dp[v];
            if(weight[i]==0){
                dp[u]++;
            }
        }
    }
    //cout<<u<<"    "<<dp[u]<<endl;
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            if(weight[i]==0){
                dp[v]=dp[u]-1;
            }else{
                dp[v]=dp[u]+1;
            }
            dfs2(v,u);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=1;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=0;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dfs2(1,0);
    int ans[MAXN],minans=INT_MAX,k=1;
    for(int i=1;i<=n;i++){
        if(dp[i]<minans){
            minans=dp[i];
            k=1;
            ans[k++]=i;
        }else if(dp[i]==minans){
            ans[k++]=i;
        }
    }
    cout<<minans<<endl;
    for(int i=1;i<k;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}

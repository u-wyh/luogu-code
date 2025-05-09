// Ⱦɫ���������
// ����һ��n�����������ʼʱ���нڵ�ȫ�ǰ׵�
// ��һ�β����������ѡ�������Ⱦ��
// �Ժ�ÿ�β���������ѡ���Ѿ�Ⱦ�ڵĵ�����ڵ����Ⱦ�ڣ�һֱ�����еĵ㶼��Ⱦ��
// ÿ�ζ���ã���ǰ��Ⱦɫ��İ�ɫ��ͨ���С����Ϊ����
// ���ؿɻ�õ���������
// �������� : https://www.luogu.com.cn/problem/CF1187E
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];//�Ըýڵ�Ϊͷ����������С
long long dp[MAXN];

// dp[i]���³�
// �ڵ�i��Ϊ�Լ������������Ⱦ�ĵ㣬Ⱦ�������������Ƕ���
void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]+=sz[v];//��С����������С֮�ͼ���1������
            dp[u]+=dp[v];
        }
    }
    dp[u]+=sz[u];
}
//����sz������Ϣ  ���������������ֻ��Ҫ�õ�����dp[1]����

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp[v]=dp[u]+n-sz[v]-sz[v];
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
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dfs2(1,0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout<<ans;
    return 0;
}

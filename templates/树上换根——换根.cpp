// �����Ⱥ�(�ݹ��)
// ����һ��n����������ҵ�һ���ڵ㣬ʹ��������ڵ�Ϊ��ʱ���������нڵ�����֮�����
// ����ж���ڵ�����Ҫ�󣬷��ؽڵ�����С��
// �������� : https://www.luogu.com.cn/problem/P3478
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code01_MaximizeSumOfDeeps2�ļ�

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];//�Ըýڵ�Ϊͷ����������С
long long sum[MAXN];//���������Ľڵ㵽�õ�ľ����ܺ�
long long dp[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
    sz[u]=1;
    sum[u]=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]+=sz[v];//��С����������С֮�ͼ���1������
            sum[u]+=(sum[v]+sz[v]);//�������ǿ������Ϊ��Ȩ��1
        }
    }
}
//����sz  sum������Ϣ

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp[v]=dp[u]-sz[v]+(n-sz[v]);
            dfs2(v,u);
            //�����v�ڵ�  Ȼ��ſ������±���
        }
    }
}
//ʵ�ֻ�������

int main()
{
    n=read();
    for(int i=1,u,v;i<n;i++){
        u=read(),v=read();

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dp[1]=sum[1];
    //һ��ʼֻ��dp[1]��Ч  ��Ϊ����������Ϊ���ڵ���1
    dfs2(1,0);
    long long maxans=LLONG_MIN;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(dp[i]>maxans){
            ans=i;
            maxans=dp[i];
        }
    }
    cout<<ans;
    return 0;
}

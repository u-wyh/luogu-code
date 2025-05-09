#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 3e6+5;

int n;
char s[MAXN];

int cnt;
int tree[MAXM][26];
int en[MAXM];

int dp[MAXM];// dp[u] ��ʾ�Խڵ� u Ϊ�������������ֵ
//ʵ���� �������ڵ�en[u]==0 ��ôdpʵ���ϼ�ʹ0
int ans;

//������ǰ׺��
void insert(char *s){
    int u=0;
    int len=strlen(s+1);
    for(int i=len;i>=1;i--){
        //�������
        int path=s[i]-'a';
        if(!tree[u][path]){
            tree[u][path]=++cnt;
        }
        u=tree[u][path];
    }
    en[u]++;
}

//dp[u]ʵ���ϱ�ʾ����u�����Ϊһ���ӿ�  �������Ƕ���
//������Ӧ���������һ������maxx1  Ȼ�����������Ч���ӽڵ����-1������ļ�һ��maxx1ռ��1�����ӣ�
//Ȼ�����1 ��ʾ���λ���Լ�ҲҪ��
//Ϊʲô������maxx2  ��Ϊ����֮��u�����м�λ�� ���ܳ�Ϊ�ӿ���
//���Ǽ���������Ч����  ��Ӱ���������Ϊ�ӿ�
void dfs(int u){
    int sz=0;
    int maxx1=0,maxx2=0;
    for(int i=0;i<26;i++){
        int v=tree[u][i];
        if(v){
            dfs(v);
        }
        sz+=en[v];
        if(maxx1<dp[v]){
            maxx2=maxx1;
            maxx1=dp[v];
        }
        else if(maxx2<dp[v]){
            maxx2=dp[v];
        }
    }
    if(en[u]){
        dp[u]=maxx1+max(sz,1);//��øĳ�dp[u]=maxx1+1+max(sz-1,0);
    }
    ans=max(ans,maxx1+maxx2+en[u]+max(sz-2,0));
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        insert(s);
    }
    dfs(0);
    cout<<ans<<endl;
    return 0;
}

//P5852
//�������ʵ�ر��  ���set  ��ʵ�е㱩������ζ
//����ά��һ��set  ��¼ӵ��ÿһ����ɫ�Ľڵ���  ��ʾ�����������нڵ㶼�������ɫ
//ÿ���¼���ɫʱ  ���Ƚ������ɫ���Լ��������ڵ�ȫ��ɾȥ  Ȼ��������
//������������д����������ɫ�ļ���  ��ô�Ͳ��ü�����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfn[MAXN];//dfn��
int rk[MAXN];//dfn���Ӧ��ԭ�����
int low[MAXN];//��ʾ������ڵ�Ϊͷ������dfn������Ƕ���
int dfncnt;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int f){
    dfn[u]=++dfncnt;
    rk[dfncnt]=u;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    low[u]=dfncnt;
}

struct node{
    long long tree[MAXN];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int val){
        while(x<=n){
            tree[x]+=val;
            x+=lowbit(x);
        }
    }
    long long sum(int x){
        long long ans=0;
        while(x){
            ans+=tree[x];
            x-=lowbit(x);
        }
        return ans;
    }
}a,b;
//a��״����ά�ֵ����������iΪ�׵��������ж�������ɫ�Ǵ�ҹ���ӵ�е�
//b��״����ά�ֵ������ͷ�����һ����ɫ ��ô�������ϻ����Ӷ���Ч��

// ά��ÿ����ɫ�� dfn�򼯺�
set<int> st[MAXN];

void update(int x,int val){
    a.add(dfn[x],val);
    a.add(low[x]+1,-val);//��ʾֻ���������������d����ɫ  �����ڲ��
    b.add(dfn[x],(low[x]-dfn[x]+1)*val);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v),addedge(v,u);//����
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int op,u;
        op=read(),u=read();
        if(op==1){
            int v=read();
            auto it = st[v].upper_bound(dfn[u]);
            // ����Ƿ��������Ѿ���Ⱦɫ
            if (it != st[v].begin() && low[rk[*prev(it)]] >= low[u])
                continue;
            // ɾ���������Ѿ���Ⱦɫ�Ľڵ�
            while (it != st[v].end() && (*it) <= low[u]) {
                update(rk[*it], -1); // ����֮ǰ�ĸ���
                st[v].erase(it++);
            }
            st[v].insert(dfn[u]); // ���뵱ǰ�ڵ�
            update(u, 1); // ������״����
        }
        else{
            //ans���ȼ���������������нڵ㶼�е���ɫ
            //b.sum(x)���������dfn���С��x�Ľڵ����еĹ���
            //b.sum(low[u]) - b.sum(dfn[u])  ��þ�����������Ͻڵ��������Ĳ���ͷ������е���ɫ
            long long ans=(low[u] - dfn[u] + 1) * a.sum(dfn[u]) + b.sum(low[u]) - b.sum(dfn[u]);
            cout<<ans<<endl;
        }
    }
    return 0;
}

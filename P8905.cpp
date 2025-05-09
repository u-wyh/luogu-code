#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;
long long ans=0;

int in[MAXN];//�������¿�ʼ�ӵ�ʱ�Ķ���
bool vis[MAXN];//��ʾ�Ƿ��Ѿ������¼���
int degree[MAXN];//�����ʼ�����

int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int fa[MAXN];
int sz[MAXN];

set<pair<int,int>>s;//ʵ���϶�Ҳ����  ���ǹ���ʵ�ֽ�Ϊ�鷳
stack<int>st;//��ʾ����˳��

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
        degree[u]++,degree[v]++;
    }
    for(int i=1;i<=n;i++){
        s.insert({degree[i],i});
    }
    while(!s.empty()){
        int u=(*s.begin()).second;
        s.erase(s.begin());
        st.push(u);
        in[u]=degree[u];
        //��ʾ����ڵ��Ѿ���ɾ��  ��û��ɾ���ĵ�  ������㱻���¼����ʱ�� Ҳһ������
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            if(in[v]){
                //�������0  һ�����Ѿ���ɾ��
                continue;
            }
            s.erase(s.lower_bound({degree[v],v}));//����Ԫ��
            degree[v]--;//��Ϊu����ڵ㱻���� ���Զ�����һ  ��Ϊ���¼���v��ʱ��  uһ��û����ͼ��
            s.insert({degree[v],v});
        }
    }
    for(int i=1;i<=n;i++){
        int u=st.top();
        vis[u]=true;
        st.pop();
        for(int j=head[u];j;j=Next[j]){
            int v=to[j];
            if(vis[v]){
                //��ʾ������Ѿ�����
                un(u,v);
            }
        }
        //��ʱ��in[u]һ���Ƕ���С��  ��Ϊ��Ŀǰ���¼���ĵ㶼���ڵ�ʱ��  ɾ���Ľڵ���u  ˵��u�Ķ���һ������С��
        ans=max(ans,(long long)sz[find(u)]*in[u]);
        //cout<<in[i]<<' ';
    }
    cout<<ans<<endl;
    return 0;
}

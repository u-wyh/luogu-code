#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e5+5;
const int MOD = 1e9;

int n,m;
//�����׼����  �����������ɾ����  ���鼯(�����ϸ������ϵģ�  ��������ͼ
//��2����1��·�ϣ���ͼ��  ���о����ĵ�����ͼ��һ���ǿ��Ե���2
//����Щ��ĸ�������Ϊ1
//�������еĵ����  ���val��Ϊ0  ��ôһ����1���Ե����
//������վ������ɾ����Ĳ�Ϊ0�Ľڵ�  ������1  ��ô����inf
int in[MAXN];
int val[MAXN];//ֻ�нڵ�1Ҫ��ʼ��Ϊ1
int fa[MAXN];//Ҳ���ó�ʼ�� ��������ֻ��Ҫ����Ҫ�ĵ�����Ϊ1  ʣ��ľͲ��ù���
bool vis[MAXN];//��ֹdfs������ʱ��ѭ��

int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int headr[MAXN];
int Nextr[MAXM<<1];
int tor[MAXM<<1];
int cntr=1;

queue<int>q;

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

void addedger(int u,int v){
    Nextr[cntr]=headr[u];
    tor[cntr]=v;
    headr[u]=cntr++;
}

void dfs(int u){
    vis[u]=true;//��ֹ������ѭ��
    for(int i=headr[u];i;i=Nextr[i]){
        int v=tor[i];
        if(!vis[v]){
            fa[v]=1;
            dfs(v);
        }
    }
}

bool ok[MAXN];//����1���Ե���ĵ�
bool visit[MAXN];

void dfs1(int u){
    visit[u]=true;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(!visit[v]){
            ok[v]=true;
            dfs1(v);
        }
    }
}

int main()
{
    cin>>n>>m;
    val[1]=1;
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedger(v,u);
        in[v]++;
    }
    ok[1]=1;
    dfs1(1);
    for(int i=1;i<=n;i++){
        if(!ok[i]){
            for(int j=head[i];j;j=Next[j]){
                int v=to[j];
                in[v]--;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(!ok[u]){
            continue;
        }
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            val[v]+=val[u];
            val[v]%=MOD;
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    fa[2]=1;
    dfs(2);
    for(int i=1;i<=n;i++){
        if(in[i]&&val[i]&&fa[i]){
            //��ʾ�ڻ��ϵĵ�  1���Ե���ĵ�  ���Ե���2�ĵ�
            //�ⲻ����inf��������  Ϊʲô������
            cout<<"inf"<<endl;
            return 0;
        }
    }
    cout<<val[2]<<endl;
    return 0;
}
/*
5 5
1 4
4 2
3 5
5 3
3 4
*/

//P9233
//�����Ŀ��ÿ���������һ�������ѯ
//���Ǽ�¼����ÿ����ɫ��Ƶ�Ĵ�Ƶ
//��Ϊ�����Ҫ�����������ɫ�Ĵ�Ƶ��ͬ
//����������Ӧ������������ʽ�ϲ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int dfn[MAXN],id[MAXN];//dfn��  �Լ�dfn��Ӧ��ԭ�������
int dfncnt;
int sz[MAXN];
struct node{
    int l,r;
}q[MAXN];//�ĳ�n�������ѯ
int qcnt;//��¼�����ѯ���
int n,m;
int cnt[MAXN];//ͳ��Ԫ�س��ָ���
int tot[MAXN];//ͳ�Ƴ��ִ�����ͬ�ĸ���
int ans;//��¼���ִ����Ĳ�ͬ�������м���
int val[MAXN];
int pos[MAXN];

int head[MAXN];
int to[MAXN];
int Next[MAXN];
int tcnt=1;

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
    Next[tcnt]=head[u];
    to[tcnt]=v;
    head[u]=tcnt++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    id[dfncnt]=u;
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        dfs(v);
        sz[u]+=sz[v];
    }
    q[++qcnt]={dfn[u],dfn[u]+sz[u]-1};
}

//��ż�������Ż�
inline bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

void add(int x){
    if(cnt[val[x]]){
        //��ʾ��ǰ����
        tot[cnt[val[x]]]--;//��ô��������ִ�����ͬ��Ԫ�ظ�������һ��
        if(tot[cnt[val[x]]]==0){
            ans--;
            //�������0  ��ô�������һ��
        }
    }
    cnt[val[x]]++;//���ִ�����һ
    tot[cnt[val[x]]]++;//������ִ�����Ԫ�ظ�����һ
    if(tot[cnt[val[x]]]==1){
        ans++;
        //��ʾ��ǰû��������ִ��� ���ڳ�����
    }
}

void sub(int x){
    tot[cnt[val[x]]]--;//��ǰ�϶���  Ҫ��Ȼ������뵽�������
    if(tot[cnt[val[x]]]==0){
        ans--;
        //������ִ�����û����
    }
    cnt[val[x]]--;
    if(cnt[val[x]]!=0){
        //���ִ�����0�Ļ�  ����ͳ��
        tot[cnt[val[x]]]++;
        if(tot[cnt[val[x]]]==1){
            ans++;
        }
    }
}

int main()
{
    n=read();
    int size=sqrt(n);
    for(int i=1;i<=n;i++){
        pos[i]=i/size;
        val[i]=read();
        int u=read();
        addedge(u,i);
    }
    dfs(1);
    sort(q+1,q+n+1,cmp);
    int l=1,r=0,res=0;
    for(int i=1;i<=n;i++){
        while (l > q[i].l) add(id[--l]);
		while (r < q[i].r) add(id[++r]);
		while (l < q[i].l) sub(id[l++]);
		while (r > q[i].r) sub(id[r--]);
		res += (ans == 1);
    }
    cout<<res<<endl;
    return 0;
}

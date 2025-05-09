//P1751
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 1005;
const int MAXT = 505;

int n,m,tt;

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];

int pos[MAXM];//ÿ��̰�Գ�����λ��
int nums[MAXN];//ÿ���ڵ���Ϊ����̰�Գ棬0��ʾû��̰�Գ�
int arr[MAXT];//ÿһ��ʳ����ֵĵط�
int eat[MAXM];//ÿ��̰�Գ�Ե�ʳ����

//������������dfs�������õ��ı���
int t[MAXN];   // ռ��ÿ���ڵ��ʱ��
int o[MAXN];   // ÿ���ڵ㱻ռ�ݵ�̰�Գ���

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

void dfs(int u,int fa){
    if(nums[u]){
        //�������ڵ㱾�����г���
        //��ô��������ʹ�г���Ҳ��������  ��Ϊ���Ǿ���Զ
        t[u]=0,o[u]=nums[u];

        pos[nums[u]]=u;//��ʵ�������Ҳ��Ӱ��  ��ǰҲ�����ֵ
        return ;
    }
    //��������������ڵ�û�г��� ��ô��Ȼ����һ�����Ӿ�������
    //����һ�����  ��������������û�г���  ��ô����t o�������mp mt
    int mp=1e9,mt=1e9;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);//ȥ���ӽڵ�ͳ����Ϣ
        if(o[v]==1e9){
            continue;//˵���������û�г���
        }
        if((t[v] + 1) < mt || ((t[v] + 1) == mt && o[v] < mp)){
            mt = t[v] + 1;
            mp = o[v];
        }
    }
    t[u] = mt;
    o[u] = mp;//�������������û�г���  ��ô��ֵ����1e9
    if(mp!=1e9){
        //������ֵ��1e9  ��ô˵���������û�г���
        //����pos��ʱ������  ���������ӻ����Լ���������  ��ô��������Ľڵ㸲��
        //�����ʵ���Ǹ���
        nums[pos[mp]]=0;
        pos[mp]=u;
        nums[u]=mp;//����b p����
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }

    m=read();
    for(int i=1;i<=m;i++){
        int u;
        u=read();
        pos[i]=u,nums[u]=i;//�޸���Ӧ��Ϣ
    }

    tt=read();
    for(int i=1;i<=tt;i++){
        arr[i]=read();
    }

    for(int i=1;i<=tt;i++){
        //ÿ�β�ѯ  ���൱�ڻ���
        memset(t, 0, sizeof(t));
        memset(o, 0, sizeof(o));
        dfs(arr[i], 0);
        eat[o[arr[i]]]++;
    }

    for(int i=1;i<=m;i++){
        cout<<pos[i]<<' '<<eat[i]<<endl;
    }
    return 0;
}
/*
9
1 2 2 3 3 4 1 5 5 6 5 7 7 8 7 9
4
2 4 5 9
3
1 3 6
*/

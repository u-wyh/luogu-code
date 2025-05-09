//P5782
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;

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

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            //��ʾ����ڵ�û�б����ʹ�
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //��ʾ��������ǻ����� һ����ͬһ�����ϵ�
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //�����нڵ㰴����ɫ����  �������
        while(st[top]!=x){
            //����ͬһ��ǿ��ͨ����
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a,b,x,y;
        a=read(),x=read(),b=read(),y=read();//aΪx  ����  bΪy
        //���� 1~n��ȡ0  n+1~2*n��ȡ1
        if(x==1&&y==1){
            //���߱���������һ����1
            addedge(a,b+n);//��ôaȡ0  ���Եó�bһ����1
            addedge(b,a+n);
        }
        else if(x==0&&y==1){
            //a��0  ����  b��1
            addedge(a+n,b+n);//��ôaȡ1  bһ������1  ��Ϊa������ȡ0��Ҫ��
            addedge(b,a);
        }
        else if(x==1&&y==0){
            addedge(b+n,a+n);
            addedge(a,b);
        }
        else{
            addedge(a+n,b);
            addedge(b+n,a);
        }
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]==col[i+n]){
            //������Ҫ�� ֱ���˳�
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }
    cout<<"POSSIBLE"<<endl;
    //��������
    //Ҫʹ�õ���������   ����ʵ��������Ҳ����Ϊ�˷�ֹ���� a->b->a'  ��a->a' ���ֿ��ܻᵼ�´������
    //��������ѡ�������������  �������ں����  a'һ���޷��Ƶ���a�����a'�����������Ļ���
    //��Ϊ�����޷�ָ��ǰ��  ���򲻾�����һ������������  ���������Ǵ����
    //�����������  ��ʵ��ɫ����Ǿ���С��  ��Ϊtarjan��ʱ��  �Ƚ�β������Щ���ַ��ʵ�  Ȼ��������������
    //������Ȼ���е�ʱ��  ѡ���С����ɫ����ǶԵ�  ���������ŵ�
    for(int i=1;i<=n;i++){
        if(col[i]>col[i+n])
            printf("1 ");
        else
            printf("0 ");
    }
    return 0;
}

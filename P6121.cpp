#include<iostream>
#include<cstdio>
using namespace std;
struct _edge{
    int from;
    int to;
    int next;
}e[400010];
int tot,head[200010],k;
bool vis[200010];                        //�ж�ũ���Ƿ���
inline void add_edge(int from,int to){   //��ʽǰ���Ǵ�ͼ
    e[++tot].from=from;
    e[tot].to=to;
    e[tot].next=head[from];
    head[from]=tot;
}
int n,m,u,v,t[200010],ans[200010],f[200010];
inline int _find(int x){            //��ѯ+·��ѹ��
    while(x!=f[x]) x=f[x]=f[f[x]];
    return x;
}
inline void init(){                 //���鼯��ʼ��
    for(register int i=1;i<=n;i++)
        f[i]=i;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);              //����ͼ˫����
        add_edge(v,u);
    }
    for(register int i=1;i<=n;i++)
        scanf("%d",&t[i]);          //ũ���ص�ʱ�䣬���ſ����ǿ���ʱ��
    init();                         //�����˺��������ǵ���
    vis[t[n]]=1;                    //t_nʱ����ũ�� t[n]�����
    ans[n]=1;                       //ֻ����һ��ʱͼ�ض�����ͨ��
    for(register int i=n-1;i>=1;i--) //�����ѣ���i ʱ�̿���ũ��t[i]
    {
        vis[t[i]]=1;                //���
        for(register int j=head[t[i]];j;j=e[j].next)
        {
            if(vis[e[j].to]==1)      //����ñ��յ�ũ��Ҳ���ˣ�ִ���������
            {
                int fx=_find(t[i]),fy=_find(e[j].to);//���鼯��ѯ
                if(fx!=fy)     //����ͬһ�����ϵĻ�
                {
                    ++k;       //�ϲ����� +1
                    f[fx]=fy;  //�ϲ���������
                }
            }
        }
        if(k==n-i) ans[i]=1;   //��ǰ����n-��i-1����ũ�����ж��Ƿ���ͨ�������
        else ans[i]=0;
    }
    for(register int i=1;i<=n;i++)
    {
        if(ans[i]==1) printf("YES\n");  //��ӡ��
        else printf("NO\n");
    }
    return 0;
}

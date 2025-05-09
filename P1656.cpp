#include <bits/stdc++.h>
using namespace std;

int maps[151][151];//�ڽӾ��󣬼��׶�
struct Edge {
    int x,y;
} E[5001];//���Ǵ�𰸵ģ����ڽӱ�棬Ӧ�ò��ý���
int dfn[151],low[151],n,m,id,cnt,f[151];
/*
��Щ����ĺ��壺
dfn:{�±꣺����     �ڴ��ֵ�������������ʱ�ڼ�������}
low:{�±꣺����     �ڴ��ֵ���������ͨ���������ﵽ���dfnֵ��С�ĵ��dfn}
f:{�±꣺����       �ڴ��ֵ������������һ����}
�����ĺ��壺n:������        m:�߸���       id:����dfn���      cnt:�����ڽӱ��ͼ
*/
bool cmp(Edge a,Edge b) {
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}//����ĿҪ�󣬱�Ҫ����

void addEdge(int x,int y) {
    E[++cnt].x=x;
    E[cnt].y=y;
}//addedge�����������ڽӱ�

void tarjan(int x) {
    int c=0,y;
    dfn[x]=low[x]=++id;
    for(int i=1; i<=n; i++) {
        if(!maps[x][i])continue;//����Ҫ�б�
        y=i;//�������
        if(dfn[y]&&y!=f[x])
            low[x]=min(low[x],dfn[y]);//��������ְ֣���߾�û�����ˣ��ú����
        if(!dfn[y]) {//����ҵ����Ȼ���ʲô����
            f[y]=x;//�������Ⱦ��ϰְ�
            tarjan(y);//dfs����
            low[x]=min(low[x],low[y]);//����ʱ���Űְָ���low
            if(low[y]>dfn[x])
                addEdge(x,y);//�Ǹ�ߣ��ͼ����
        }
    }
}//tarjan���֣�֤��������
int main() {
    int x,y;
    cin>>n>>m;
    for(register int i=1; i<=m; i++) {
        cin>>x>>y;
        maps[x][y]=maps[y][x]=1;//���
    }
    for(register int i=1; i<=n; i++) {
        if(!dfn[i])
            tarjan(i);//tarjan
    }
    sort(E+1,E+cnt+1,cmp);//sort�󷨺�
    for(register int i=1; i<=cnt; i++) {
        cout<<min(E[i].x,E[i].y)<<' '<<max(E[i].x,E[i].y)<<endl;//���
    }
    return 0;//��������ˣ�֤����ʼ��
}

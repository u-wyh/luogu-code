//ʹ������dp
// ����ֱ��ģ��(����dp)
// ����һ��������Ȩ����Ϊ������ֱ������
// �������� : https://www.luogu.com.cn/problem/U81904
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����е�����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

// ֱ���Ŀ�ʼ��
int start;
// ֱ���Ľ�����
int en;
// ֱ������
int diameter;

// dist[u] : ��u��ʼ���������ߣ����߳��������룬���Բ�ѡ�κα�
int dist[MAXN];
// ans[u] : ·�����������u������£����·����
int ans[MAXN];
//�����������������  distֻ����һ����  ans����ʹ������
//dist���Ѿ����ʹ�������Ŀǰ���ֵ
//distһ��ʼ��0 ��ʾʲô����ѡ  ansҲ��
//dist[u]����dist[v]+weight[i]����Ϊ���ֵ
//ansͨ��dist[u]+dist[v]+weight[i]����Ϊ���ֵ
//��ʾ��ǰ������dist[u]  ����Ŀǰ�����ߵ�����weight[i]   ���Ϻ��ӽڵ�����ֵ  �����ܷ�������ֵ
//ʵ����ans[u]�������Ϊ��uΪ�׵����������γɵ����ֱ��

void dp(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dp(to[i],u);
        }
    }
    //ʵ������һ��dfs
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            ans[u]=max(ans[u],dist[u]+dist[to[i]]+weight[i]);
            dist[u]=max(dist[u],dist[to[i]]+weight[i]);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    dp(1,0);
    for(int i=1;i<=n;i++){
        diameter=max(diameter,ans[i]);
    }
    cout<<diameter<<endl;
    return 0;
}



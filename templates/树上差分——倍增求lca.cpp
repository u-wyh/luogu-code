// ��С�����еļ۸��ܺ�(����������lca)
// ��n���ڵ��γ�һ������ÿ���ڵ����е�Ȩ���ٸ����ܶ�·��
// ÿ��·���п�ʼ��ͽ����㣬·�����۾��Ǵӿ�ʼ�㵽������ĵ�Ȩ��
// ����·���Ĵ����ܺ;������еļ۸��ܺ�
// �����ѡ���ĳЩ��ĵ�Ȩ����һ�룬���������еļ۸��ܺ�
// ����Ҫ��ѡ��ĵ㲻������
// �������еļ۸��ܺ��������Ƕ���
// �������� : https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 100;
const int LIMIT = 6;

//�ֱ��ʾ�ж��ٸ���  �Ͷ���������·��
int n,m;
//��ʾÿһ����ĵ�Ȩ
int price[MAXN];

//��ʽǰ���ǽ�ͼ
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

//�����㷨
int deep[MAXN],stjump[MAXN][LIMIT];
int power;
//��¼�����õ�Ĵ���  һ��ʼȫ����0
int num[MAXN];
//��ʾ������·��˳��
int trip[MAXM][2];
int no,yes;
//no yes��ʾ�ڲ�Ҫ��ǰͷ���  ���� Ҫ��ǰͷ���  ��С����
//��ʵ��������������  ��Ȼ�ռ��˷�  û��Ҫ

void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs1(to[e], u);
        }
        //���µݹ�
    }
}
//��������������ǽ���deep  st����Ϣ
//Ϊ�˷��������ѯlca

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs2(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            num[u]+=num[v];
        }
    }
}
//�����޸ĺ����Ϣ(������Ϣ)

void dp(int u,int f){
    int n=price[u]*num[u];//��ǰ�ڵ㲻�Ż�  ����ڵ��ϵĻ���
    int y=num[u]*(price[u]/2);//��ǰ�ڵ��Ż�  ����ڵ��ϵĻ���
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp(v,u);//���µݹ�
            n+=min(no,yes);
            y+=no;
        }
    }
    no=n;
    yes=y;
}
//����dp

int main()
{
    cin>>n>>m;
    power=log2(n);
    for(int i=1;i<=n;i++){
        cin>>price[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs1(1,0);
    //��ɲ����Ϣ׼��
    for(int i=1;i<=m;i++){
        cin>>trip[i][0]>>trip[i][1];
        int u,v;
        u=trip[i][0];
        v=trip[i][1];
        int lcafather,Lca;
        Lca=lca(u,v);
        lcafather=stjump[Lca][0];
        num[u]++;
        num[v]++;
        num[Lca]--;
        num[lcafather]--;
    }
    //���������Ϣ
    dfs2(1,0);
    dp(1,0);
    cout<<min(no,yes);
    return 0;
}


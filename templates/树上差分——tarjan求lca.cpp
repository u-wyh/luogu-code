// ������¼�(�ݹ��)
// ��n���ڵ��γ�һ����
// ����һ���ɵ�����ɵ����飬��ʾ��������Ҫȥ���ĵص�
// ����ÿ�ߵ�һ���ڵ㶼������һ���ǹ������������ֹͣǰ��
// �����������һ���ص�ʱ����Ҫ���ǹ�
// ��ӡÿ���ڵ�������׼�������ǹ�������������������������Ľڵ�
// �������� : https://www.luogu.com.cn/problem/P3258
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code02_SquirrelHome2�ļ�
//������кܶ��lca��Ҫ��ѯ ��ô����ֱ�ӽ���Щlca�����  ��tarjan�㷨
//ʹ�õ�ʱ�����ֱ����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tcnt=1;
//��ͼ����ʽǰ����

int headQuery[MAXN];
int queryNext[MAXN << 1];
int queryTo[MAXN << 1];
// ����ı�ţ�һ���д𰸿���֪����д����
int queryIndex[MAXN << 1];
int qcnt=1;
//�������ʽǰ����   ����һ������ı������  �������

// unionfind������tarjan�㷨ר�õĲ��鼯�ṹ
int unionfind[MAXN];
// father���鲻�������鼯�����Ǽ�¼ÿ���ڵ�ĸ��׽ڵ�
int father[MAXN];
// ans������tarjan�㷨������������¼ÿ���������˵����͹�������
int ans[MAXN];
int travel[MAXN];
//��ʾһ�ξ����ĵص�
bool visited[MAXN];
int num[MAXN];
//��ʾ����Ҫ����Ķ���

void build(){
    for(int i=1;i<=n;i++){
        unionfind[i]=i;
    }
}
//���鼯��ʼ��

int find(int i) {
    if (i != unionfind[i]) {
        unionfind[i] = find(unionfind[i]);
    }
    return unionfind[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            tarjan(v, u);//���µݹ�  ֱ��Ҷ�ڵ�
        }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            //���˵�������ڵ��Ѿ������ʹ�  �ſ��Խ��д���д
            ans[queryIndex[e]] = find(v);
            //��д�Ĵ�������ڵ����ڲ��鼯��ͷ���
        }
    }
    unionfind[u] = f;
    father[u] = f;
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            num[u]+=num[v];
        }
    }
}

void compute() {
    tarjan(1, 0);
    for (int i = 1, u, v, lca, lcafather; i < n; i++) {
        u = travel[i];
        v = travel[i + 1];
        lca = ans[i];
        lcafather = father[lca];
        num[u]++;
        num[v]++;
        num[lca]--;
        num[lcafather]--;
    }
    //Ŀǰʵ����������ˡ���֡�  ��Ҫ���һ��
    dfs(1, 0);
    for (int i = 2; i <= n; i++) {
        num[travel[i]]--;
    }
}

int main()
{
    cin>>n;
    build();
    for(int i=1;i<=n;i++){
        cin>>travel[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[tcnt]=head[u];
        to[tcnt]=v;
        head[u]=tcnt++;

        Next[tcnt]=head[v];
        to[tcnt]=u;
        head[v]=tcnt++;

    }
    for(int i=1;i<n;i++){
        int u,v;
        u=travel[i];
        v=travel[i+1];

        queryNext[qcnt] = headQuery[u];
		queryTo[qcnt] = v;
		queryIndex[qcnt] = i;
		headQuery[u] = qcnt++;

        queryNext[qcnt] = headQuery[v];
		queryTo[qcnt] = u;
		queryIndex[qcnt] = i;
		headQuery[v] = qcnt++;
    }
    compute();
    for(int i=1;i<=n;i++){
        cout<<num[i]<<endl;
    }
    return 0;
}


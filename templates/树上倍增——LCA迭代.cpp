#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int LIMIT = 20;

int n,m,root;
int log_2[MAXN];
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];
struct node{
    int u,f,e;
};
stack<node>st;
// ջ����������Ϣ
// u : ��ǰ����ĵ�
// f : ��ǰ��u�ĸ��ڵ�
// e : �������ű���
// ���e==-1����ʾ֮ǰû�д����u���κα�
// ���e==0����ʾu�ı߶��Ѿ���������

void build(){
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
    }
}

void dfs(){
    st.push({root,0,-1});
    while (!st.empty()) {
        node cur=st.top();
        st.pop();
        if (cur.e == -1) {
            //˵�����ǵ�һ�η���  ��ôֱ�Ӿ�Ҫ������deep  stjump
            deep[cur.u] = deep[cur.f] + 1;
            stjump[cur.u][0] = cur.f;
            for (int p = 1; p <= log_2[n]; p++) {
                stjump[cur.u][p] = stjump[stjump[cur.u][p - 1]][p - 1];
            }
            cur.e = head[cur.u];
        } else {
            //������һ����
            cur.e = Next[cur.e];
        }
        if (cur.e != 0) {
            //˵�����б�
            st.push({cur.u, cur.f, cur.e});
            if (to[cur.e] != cur.f) {
                st.push({to[cur.e], cur.u, -1});
                //�����ӽڵ�
            }
        }
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = log_2[n]; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = log_2[n]; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0]==0?root:stjump[a][0];
}

int main()
{
    cin>>n>>m>>root;
    build();
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
    //����
    dfs();
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    return 0;
}

// ��Щ����Ը��������
// ����һ��n�����������������ɾ��һ���ߣ�Ȼ��������һ����
// ͨ�����ַ�ʽ�����úܶ��������
// ��ӡ�����ܱ�����ĵĵ�
// �������� : https://www.luogu.com.cn/problem/CF708C
// �������� : https://codeforces.com/problemset/problem/708/C
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

// size[i]: i�ڲ�������������С
int sz[MAXN];
// maxsub[i]: i�ڲ��������������i�ڵ���ĸ�����ӵ�У���¼�ڵ���
int maxsub[MAXN];
// inner1[i]: i�ڲ���<=n/2�ҵ�һ��������Ƕ�󣬼�¼��С
int inner1[MAXN];
// inner2[i]: i�ڲ���<=n/2�ҵڶ���������Ƕ�󣬼�¼��С
int inner2[MAXN];
// ע��: inner1[i]��inner2[i]�������������һ��Ҫ����i�Ĳ�ͬ����

// choose[i]: inner1[i]���������������i�ڵ���ĸ�����ӵ�У���¼�ڵ���
int choose[MAXN];
// outer[i]: i�ⲿ��<=n/2�ҵ�һ��������Ƕ�󣬼�¼��С
int outer[MAXN];

void dfs1(int u, int f) {
    sz[u] = 1;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[maxsub[u]] < sz[v]) {
                maxsub[u] = v;
            }
            int innerSize = sz[v] <= n / 2 ? sz[v] : inner1[v];
            if (inner1[u] < innerSize) {
                choose[u] = v;
                inner2[u] = inner1[u];
                inner1[u] = innerSize;
            } else if (inner2[u] < innerSize) {
                inner2[u] = innerSize;
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (n - sz[v] <= n / 2) {
                outer[v] = n - sz[v];
            } else if (choose[u] != v) {
                outer[v] = max(outer[u], inner1[u]);
            } else {
                outer[v] = max(outer[u], inner2[u]);
            }
            dfs2(v, u);
        }
    }
}

bool check(int u) {
    if (sz[maxsub[u]] > n / 2) {
        //��������д��ڴ���n/2������  ���ȿ���ȷ���������ĸ�������������  һ��С��n/2
        //��ô����Ҫ���ľ������̶ȵ�����������������С  ����ʹ�����
        //ֻ���Զϵ�һ����  ��ô�ϵ������߻�ӵ�u��  ��������Ҫ������ҪС��n/2
        //�����inner1�Ķ���
        return sz[maxsub[u]] - inner1[maxsub[u]] <= n / 2;
    }
    if (n - sz[u] > n / 2) {
        //����ͬ��
        return n - sz[u] - outer[u] <= n / 2;
    }
    //��������  ˵������û�д���n/2������  �������������
    return true;
}

int main()
{
    cin>>n;
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
    dfs2(1,0);
    for (int i = 1; i <= n; i++) {
        cout<<(check(i) ? "1 " : "0 ");
    }
    return 0;
}


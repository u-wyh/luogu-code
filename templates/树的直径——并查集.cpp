// �칫԰
// һ��n���ڵ㣬���1~n����m�������ӣ���Ȩ����1
// ���нڵ�����γɶ����ͨ����ÿ����ͨ����֤�����ṹ
// ���������͵Ĳ���
// ���� 1 x   : ����x��������Զ�ĵ�ľ���
// ���� 2 x y : ���x��y�Ѿ���ͨ����ô����
//              �������ͨ����ôִ����ͨ��������x��y���Ե�������ͨ����
//              ����Ҫ��֤��ͨ�ɵĴ������ֱ��������С
// �������� : https://www.luogu.com.cn/problem/P2195
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n,m,q;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

// ���鼯��Ҫ
int father[MAXN];
// ����dp��Ҫ
// dist[u] : ��u��ʼ���������ߣ����߳��������룬���Բ�ѡ�κα�
int dist[MAXN];
// diameter[i] : ���i�Ǽ��ϵ�ͷ�ڵ㣬diameter[i]��ʾ�������ϵ�ֱ������
//               ���i�����Ǽ��ϵ�ͷ�ڵ㣬diameter[i]��ֵû����
// ���鼯 + ���ϴ��ǩ���ɣ�����Ŀ�����056������057
int diameter[MAXN];

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// ����dp�ķ�ʽ��ֱ������
void dp(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
        }
    }
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            diameter[u] = max(diameter[u], max(diameter[v], dist[u] + dist[v] + 1));
            dist[u] = max(dist[u], dist[v] + 1);
        }
    }
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

        u = find(u);
        v = find(v);
        //�����Ա�Ϊ���Լ��ϵĴ����
        father[u] = v;
        //�ϲ���ͬ����  ��������ͬ��ǩ
    }
    for (int i = 1; i <= n; i++) {
        if (i == father[i]) {
            dp(i, 0);
        }
        //����������Ǵ���� ˵����һ���µļ���
    }
    for (int i = 1, op, x, y; i <= q; i++) {
        cin>>op;
        if (op == 1) {
            cin>>x;
            x=find(x);
            cout<<diameter[x];
        } else {
            cin>>x>>y;
            x = find(x);
            y = find(y);
            if (x != y) {
                father[x] = y;
                diameter[y] = max((diameter[x] + 1) / 2 + (diameter[y] + 1) / 2 + 1,max(diameter[x], diameter[y]));
            }
        }
    }
    return 0;
}

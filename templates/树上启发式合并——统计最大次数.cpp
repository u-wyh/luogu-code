// ������ɫ�ۼӺͣ�C++��
// һ����n���ڵ㣬���1~n������n-1���ߣ����нڵ�����һ������1�Žڵ�Ϊ��ͷ
// ÿ���ڵ����һ����ɫֵ��������ɫ�ۼӺͶ�������
// ��xΪͷ�������ϣ�������ɫ������࣬������ɫ����������ɫ��������ɫ���ܲ�ֹһ��
// ����������ɫ��ֵ�ۼ�������ÿ��������ɫֻ�ۼ�һ�Σ����Ǹ�������������ɫ�ۼӺ�
// ��ӡ1~nÿ���ڵ�Ϊͷ��������������ɫ�ۼӺ�
// 1 <= n����ɫֵ <= 10^5
// �������� : https://www.luogu.com.cn/problem/CF600E
// �������� : https://codeforces.com/problemset/problem/600/E
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n;
int color[MAXN];//�ڵ���ɫ��Ϣ

//��ʽǰ���ǽ�ͼ
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt = 0;

//�����ʷ�
int fa[MAXN];
int siz[MAXN];
int son[MAXN];

//��ʾ��ͬ��ɫ���ֵĴ���
int colorCnt[MAXN];
//��ʾĿǰ���ֵĴ���������ɫ�����˶��ٴ�
int maxCnt[MAXN];
//��¼��ǰ�ڵ�Ĵ�
long long ans[MAXN];

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

//�����ʷ� ͳ���ض�����Ϣ
void dfs1(int u, int f) {
    fa[u] = f;
    siz[u] = 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            siz[u] += siz[v];
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

void effect(int u, int h) {
    //���������һ������h ��ʾ�ռ�������ϢҪ���ݸ�h�ڵ�
    colorCnt[color[u]]++;
    if (colorCnt[color[u]] == maxCnt[h]) {
        //������ִ����������� ��ô���ۼ�
        ans[h] += color[u];
    } else if (colorCnt[color[u]] > maxCnt[h]) {
        //������ִ������� ��ô���´�
        maxCnt[h] = colorCnt[color[u]];
        ans[h] = color[u];
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            effect(v, h);
        }
    }
}

//ȡ������ӵ�Ӱ��
void cancle(int u) {
    colorCnt[color[u]] = 0;
    maxCnt[u] = 0;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            cancle(v);
        }
    }
}

void dfs2(int u, int keep) {
    //��ȥ�����
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, 0);
        }
    }
    //��ȥ�ض���
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    //����ǰ�ڵ�Ĺ���
    //���ȼ̳��ض��ӵ���Ϣ
    maxCnt[u] = maxCnt[son[u]];
    ans[u] = ans[son[u]];
    colorCnt[color[u]]++;//�ýڵ����ɫ������һ
    //����������ɫ
    if (colorCnt[color[u]] == maxCnt[u]) {
        ans[u] += color[u];
    } else if (colorCnt[color[u]] > maxCnt[u]) {
        maxCnt[u] = colorCnt[color[u]];
        ans[u] = color[u];
    }
    //�����������Ϣ
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            effect(v, u);//����ط�Ҫע���һ������u
        }
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}

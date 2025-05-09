// �ɳ������鼯ģ���⣬C++��
// һ����n���㣬ÿ����������С��ÿ�����������С��ı��
// һ����n-1������ߣ����нڵ�����һ����
// ��i�ŵ㣬2 <= i <= n����������������Ĵ𰸲���ӡ
// ��1�ŵ㵽i�ŵ�����·���ϣ�ÿ����ֻ����һ��С��������ü�����Ų�ͬ��С��
// 1 <= n <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/AT_abc302_h
// �������� : https://atcoder.jp/contests/abc302/tasks/abc302_h
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�����֮����Ҫʹ�ÿɳ������鼯  ����Ϊ��Ҫ���ݲ���
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

//��ʾÿ���ڵ��ϵ�����С��ı��
int arr[MAXN][2];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt;

//��ʾ������Ϣ
int father[MAXN];
//��ʾ�����С
int siz[MAXN];
//��ʾ��������еı���
int edgeCnt[MAXN];

//�����������ջ�Ĺ���
int rollback[MAXN][2];
int opsize = 0;//��ʾջ�Ĵ�С

int ans[MAXN];
int ball = 0;

void addEdge(int u, int v) {
	nxt[++cnt] = head[u];
	to[cnt] = v;
    head[u] = cnt;
}

int find(int i) {
	while(i != father[i]) {
		i = father[i];//ע������û�б�ƽ��
	}
	return i;
}

void Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    edgeCnt[fx] += edgeCnt[fy] + 1;//��������в���
    //����ջ��  ���㷵��
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    //����һ������
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
    edgeCnt[fx] -= edgeCnt[fy] + 1;
}

void dfs(int u, int fa) {
    int fx = find(arr[u][0]);
    int fy = find(arr[u][1]);
    bool added = false;
    bool unioned = false;
    if (fx == fy) {
        //��ͬһ��������  ����������� ��ô����������Լ�һ
        if (edgeCnt[fx] < siz[fx]) {
            ball++;
            added = true;//����
        }
        edgeCnt[fx]++;
    } else {
        if (edgeCnt[fx] < siz[fx]|| edgeCnt[fy] < siz[fy]) {
            //����һ��С�����ڼ��ϵı������� ��ô����������Լ�һ
            ball++;
            added = true;
        }
        Union(fx, fy);
        unioned = true;
    }
    ans[u] = ball;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        //���µݹ�
        if (to[e] != fa) {
            dfs(to[e], u);
        }
    }

    //���ݲ���  ��ʾ�����㲻����
    if (added) {
        ball--;
    }
    if (unioned) {
        undo();
    } else {
        //��ʹû�кϲ����� �������Ǽ���һ  Ҫ����ȥ
        edgeCnt[fx]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
        edgeCnt[i] = 0;
    }
    dfs(1, 0);
    for (int i = 2; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << ans[n] << "\n";
    return 0;
}
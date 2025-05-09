// ��ͬ����������C++��
// һ����n���ڵ㣬���1~n������ÿ���ڵ�����ֺ͸��׽ڵ���
// ������string���ͣ�������׽ڵ���Ϊ0��˵����ǰ�ڵ���ĳ������ͷ�ڵ�
// ע�⣬n���ڵ���ɵ���ɭ�ֽṹ�����������ɿ���
// һ����m����ѯ��ÿ����ѯ x k����������
// ��xΪͷ�������ϣ���x����Ϊk�����нڵ��У���ӡ��ͬ���ֵ�����
// 1 <= n��m <= 10^5
// �������� : https://www.luogu.com.cn/problem/CF246E
// �������� : https://codeforces.com/problemset/problem/246/E
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;

unordered_map<string, int> nameId;
bool root[MAXN];//�ж�����ڵ��ǲ���ͷ���
int id[MAXN];//����ڵ���ı�����ת�����������ֱ��

// ��ʽǰ���ǽ�ͼ����
int headg[MAXN];
int nextg[MAXN];
int tog[MAXN];
int cntg;

// �����б�
int headq[MAXN];
int nextq[MAXN];
int ansiq[MAXN];
int kq[MAXN];
int cntq;

// �����ʷ�
int fa[MAXN];
int siz[MAXN];
int dep[MAXN];
int son[MAXN];

// ��������ʽ�ϲ�
vector<unordered_set<int>> depSet;//��ʾ�ڲ���Ϊi�Ĳ�ͬ���ֵĸ��� set�Զ�ȥ����
int ans[MAXN];

//����һ������ �������ֵı��
//���֮ǰ�Ѿ������������ ��ôֱ�ӷ��ر�ż���
//��������� ��ô�¼����ȥ  �����ر��
int getNameId(const string &name) {
    if (nameId.find(name) != nameId.end()) {
        return nameId[name];
    }
    int newId = nameId.size() + 1;
    nameId[name] = newId;
    return newId;
}

//��deep�� ����һ��id
void addId(int deep, int id) {
    depSet[deep].insert(id);
}

//��deep�� ɾ��һ��id
void removeId(int deep, int id) {
    depSet[deep].erase(id);
}

//ͳ��deep���ȥ�غ�Ĵ�
int sizeOfDeep(int deep) {
    if (deep > n) {
        return 0;
    }
    return (int)depSet[deep].size();
}

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addQuestion(int u, int ansi, int k) {
    nextq[++cntq] = headq[u];
    ansiq[cntq] = ansi;
    kq[cntq] = k;
    headq[u] = cntq;
}

//�����ʷ�  ͳ��sz  dep son����Ϣ
void dfs1(int u, int f) {
    fa[u] = f;
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        dfs1(tog[e], u);
    }
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

void effect(int u) {
    addId(dep[u], id[u]);
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        effect(tog[e]);
    }
}

void cancle(int u) {
    removeId(dep[u], id[u]);
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        cancle(tog[e]);
    }
}

void dfs2(int u, int keep) {
    //��ȥ�����
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }
    //��ȥ�ض���
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    //��������ڵ�Ĺ���
    addId(dep[u], id[u]);
    //���������
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            effect(v);
        }
    }
    for (int i = headq[u]; i > 0; i = nextq[i]) {
    	ans[ansiq[i]] = sizeOfDeep(dep[u] + kq[i]);//ͳ�������ȵĽڵ����
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string name;
    int father;
    for (int i = 1; i <= n; i++) {
        cin >> name >> father;
        id[i] = getNameId(name);
        if (father == 0) {
        	root[i] = true;//��ʾ��ͷ���
        } else {
            addEdge(father, i);//��������
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            //��ÿ������ͷ��㿪ʼ�����ʷ�
            dfs1(i, 0);
        }
    }
    depSet.resize(n + 1);
    cin >> m;
    for (int i = 1, node, k; i <= m; i++) {
        cin >> node >> k;
        addQuestion(node, i, k);//���⽨ͼ
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            //�����
            dfs2(i, 0);
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}

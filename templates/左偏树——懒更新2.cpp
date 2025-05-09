// ���ֵĲ�����C++��
// ���1~n���ڵ㣬ÿ���ڵ���������Լ���Ȩֵ��ʵ������7�ֲ���������һ������m��
// U x y  : x���ڵļ��Ϻ�y���ڵļ��Ϻϲ�
// A1 x v : x�ڵ��Ȩֵ����v
// A2 x v : x���ڵļ������нڵ��Ȩֵ����v
// A3 v   : ���нڵ��Ȩֵ����v
// F1 x   : ��ӡx�ڵ��Ȩֵ
// F2 x   : ��ӡx���ڵļ����У�Ȩֵ���Ľڵ��Ȩֵ
// F3     : ��ӡ���нڵ��У�Ȩֵ���Ľڵ��Ȩֵ
// 1 <= n��m <= 3 * 10^5��Ȩֵ���ᳬ��int���͵ķ�Χ
// �������� : https://www.luogu.com.cn/problem/P3273
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300001;
int n, m;
// ��ƫ����Ҫ
int num[MAXN];
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// ���鼯��·����Ϣ
int fa[MAXN];
// ���ϵĴ�С��Ϣ
int siz[MAXN];
// ��������������Ӧ�üӶ���ֵ
int add[MAXN];
// ׼����һ��ջ���õ�����ʽʵ��������������õݹ鷽ʽ
int sta[MAXN];
// ���м���ͷ�ڵ��ֵ��������������ͷ�ڵ������
multiset<int> heads;
int addAll = 0;

// ���Ϊh�Ľڵ㲻������ƫ����ͷ����ͷ�ڵ��������ɾ��һ��h�ڵ��ֵ
void minusHead(int h) {
    if (h != 0) {
        //������ʵֵ��Ŀǰֵ  ����  ����Ϣ��ֵ
        heads.erase(heads.find(num[h] + add[h]));
    }
}

// ���Ϊh�Ľڵ㵱ǰ����ƫ����ͷ����ͷ�ڵ������������һ��h�ڵ��ֵ
void addHead(int h) {
    if (h != 0) {
        heads.insert(num[h] + add[h]);
    }
}

void prepare() {
    dist[0] = -1;
    heads.clear();
    for (int i = 1; i <= n; i++) {
        up[i] = ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
        siz[i] = 1;
        add[i] = 0;
        addHead(i);//�Լ�һ���ڵ���һ������  ֱ�Ӽӵ��������
    }
    addAll = 0;
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);
    return fa[i];
}

int merge(int i, int j) {
    if (i == 0 || j == 0) return i + j;
    if (num[i] < num[j]) {
        swap(i, j);
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;
    if (dist[ls[i]] < dist[rs[i]]) {
        swap(ls[i], rs[i]);
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = i;
    fa[rs[i]] = i;
    return i;
}

// �ڵ�i��������ƫ��������ڵ㣬ɾ���ڵ�i��������������ͷ�ڵ���
int remove(int i) {
    int h = find(i);
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    int s = merge(ls[i], rs[i]);
    int f = up[i];
    fa[i] = s;
    up[s] = f;
    if (h != i) {
        fa[s] = h;
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        for (int d = dist[s]; dist[f] > d + 1; f = up[f], d++) {
            dist[f] = d + 1;
            if (dist[ls[f]] < dist[rs[f]]) {
                swap(ls[f], rs[f]);
            }
        }
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;
    return fa[s];
}

// ��iΪͷ����ƫ���������˸������ƫ��  һ����С�����ӵ������  ����ʽ�ϲ�
// i�ı�ǩ��Ϣȡ������iΪͷ�����������нڵ��ֵ����v
// ���õݹ�ʵ��������������ױ�ջ�������õ���ʵ���������
void down(int i, int v) {
    if (i != 0) {
        add[i] = 0;
        int size = 0;
        sta[++size] = i;
        while (size > 0) {
            i = sta[size--];
            num[i] += v;
            if (rs[i] != 0) sta[++size] = rs[i];
            if (ls[i] != 0) sta[++size] = ls[i];
        }
    }
}

// U x y  : x���ڵļ��Ϻ�y���ڵļ��Ϻϲ�
void u(int i, int j) {
    int l = find(i);
    int r = find(j);
    if (l == r) return;
    int lsize = siz[l];
    minusHead(l);
    int rsize = siz[r];
    minusHead(r);
    //�Ƚ��������ϵĴ�С  �����������ɾ������ͷ���
    int addTag;//���ڼ�¼�ϲ�֮��ļ�������Ҫ���϶��ٲ�����ʵֵ
    if (lsize <= rsize) {
        down(l, add[l] - add[r]);
        addTag = add[r];
    } else {
        down(r, add[r] - add[l]);
        addTag = add[l];
    }
    //����С�����ϲ����ϴ����
    int h = merge(l, r);
    siz[h] = lsize + rsize;
    add[h] = addTag;
    addHead(h);
    //���ϲ����ͷ�����뵽�������
}

// A1 x v : x�ڵ��Ȩֵ����v
void a1(int i, int v) {
    int h = find(i);
    //hΪi���ڼ���ͷ���  ���������ɾ��
    minusHead(h);
    int l = remove(i);
    //lΪi���ڼ���ɾ��i֮���ͷ���
    if (l != 0) {
        //�������Ԫ��
        siz[l] = siz[h] - 1;
        add[l] = add[h];
        addHead(l);
    }
    num[i] = num[i] + add[h] + v;//��i�ڵ����Ϣ����
    fa[i] = i;//�Լ���Ϊһ������
    siz[i] = 1;
    add[i] = 0;
    addHead(i);
    u(l, i);//����ǰ�ڵ���뵽ԭ���ļ�����
}

void a2(int i, int v) {
    int h = find(i);
    minusHead(h);
    add[h] += v;
    addHead(h);
}

void a3(int v) {
    addAll += v;
}

// F1 x   : ��ӡx�ڵ��Ȩֵ
int f1(int i) {
    return num[i] + add[find(i)] + addAll;
    //����Ȩֵ���ڱ���ֵ  ���ϼ��Ϲ�ͬ�ӵ�ֵ  ��������Ԫ�ض�Ҫ�ӵ�ֵ
}

// F2 x   : ��ӡx���ڵļ����У�Ȩֵ���Ľڵ��Ȩֵ
int f2(int i) {
    int h = find(i);
    return num[h] + add[h] + addAll;
}

int f3() {
    return (*heads.rbegin()) + addAll;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> num[i];
    prepare();
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string op;
        cin >> op;
        if (op == "F3") {
            cout << f3() << "\n";
        } else {
            int x; cin >> x;
            if (op == "U") {
                int y; cin >> y;
                u(x, y);
            } else if (op == "A1") {
                int y; cin >> y;
                a1(x, y);
            } else if (op == "A2") {
                int y; cin >> y;
                a2(x, y);
            } else if (op == "A3") {
                a3(x);
            } else if (op == "F1") {
                cout << f1(x) << "\n";
            } else {
                cout << f2(x) << "\n";
            }
        }
    }
    return 0;
}

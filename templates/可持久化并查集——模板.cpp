// �ɳ־û����鼯ģ���⣬C++��
// ���ִ�1��n��һ��ʼÿ���������ڵļ���ֻ���Լ�
// ʵ���������ֲ�������i�������������������ֵ�״����Ϊi�汾������һ������m��
// ���� 1 x y : �����ϸ��������ɵİ汾����x�ļ�����y�ļ��Ϻϲ������ɵ�ǰ�İ汾
// ���� 2 x   : ������x�Ű汾��״�������ɵ�ǰ�İ汾
// ���� 3 x y : �����ϸ��������ɵİ汾�����ɵ�ǰ�İ汾����ѯx��y�Ƿ�����һ������
// 1 <= n <= 10^5
// 1 <= m <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/P3402
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 200001;
const int MAXT = 8000001;

int n, m;
// rootfa[i] = j����ʾfather���飬i�汾��ͷ�ڵ���Ϊj
int rootfa[MAXM];
// rootsiz[i] = j����ʾsiz���飬i�汾��ͷ�ڵ���Ϊj
int rootsiz[MAXM];

// �ɳ־û�father����Ϳɳ־û�siz���飬����һ��ls��rs��val
// ��Ϊ�ɳ־û�ʱ������Ľڵ��Ų�ͬ�����Կ��Թ���
//��������� �����Ҫ����ϵͳҲ���ǲ���
//����siz�����fa����  ���Ƕ��õ���cnt���
//����ϵͳ����һ��sz����
int ls[MAXT];
int rs[MAXT];
int val[MAXT];//��ʵ��fa  sz����϶�Ϊһ
int cnt = 0;

// �����ɳ־û���father����
int buildfa(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        val[rt] = l;//��ʼ��fa��Ϣ���Լ�
    } else {
        int mid = (l + r) / 2;
        ls[rt] = buildfa(l, mid);
        rs[rt] = buildfa(mid + 1, r);
    }
    return rt;
}

// �����ɳ־û���siz����
int buildsiz(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        val[rt] = 1;//��ʼʱ sz������1
    } else {
        int mid = (l + r) / 2;
        ls[rt] = buildsiz(l, mid);
        rs[rt] = buildsiz(mid + 1, r);
    }
    return rt;
}

// ���Խ���157����Ŀ1���޸�������һ��λ�õ�ֵ�������°汾������
// ���i���ڿɳ־û�father����Ľڵ㣬��ô�޸ĵľ���father����
// ���i���ڿɳ־û�siz����Ľڵ㣬��ô�޸ĵľ���siz����
int update(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    if (l == r) {
        val[rt] = jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// ���Խ���157����Ŀ1����ѯ������һ��λ�õ�ֵ
// ���i���ڿɳ־û�father����Ľڵ㣬��ô��ѯ�ľ���father����
// ���i���ڿɳ־û�siz����Ľڵ㣬��ô��ѯ�ľ���siz����
int query(int jobi, int l, int r, int i) {
    if (l == r) {
        return val[i];
    }
    int mid = (l + r) / 2;
    if (jobi <= mid) {
        return query(jobi, l, mid, ls[i]);
    } else {
        return query(jobi, mid + 1, r, rs[i]);
    }
}

// ����v�汾����ѯx�ļ���ͷ�ڵ㣬������ƽ��
int find(int x, int v) {
    int fa = query(x, 1, n, rootfa[v]);
    while(x != fa) {
        //��������ڵ�����ĸ��׽ڵ�һ�� ˵���Ǵ���ڵ�
        x = fa;
        fa = query(x, 1, n, rootfa[v]);
    }
    return x;
}

// v�汾�Ѿ�������v-1�汾���ϲ�x���ڵļ��Ϻ�y���ڵļ��ϣ�ȥ����v�汾
void Union(int x, int y, int v) {
    int fx = find(x, v);
    int fy = find(y, v);
    if (fx != fy) {
        int xsiz = query(fx, 1, n, rootsiz[v]);
        int ysiz = query(fy, 1, n, rootsiz[v]);
        if (xsiz >= ysiz) {
            rootfa[v] = update(fy, fx, 1, n, rootfa[v]);
            rootsiz[v] = update(fx, xsiz + ysiz, 1, n, rootsiz[v]);
        } else {
            rootfa[v] = update(fx, fy, 1, n, rootfa[v]);
            rootsiz[v] = update(fy, xsiz + ysiz, 1, n, rootsiz[v]);
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    rootfa[0] = buildfa(1, n);
    rootsiz[0] = buildsiz(1, n);
    for (int v = 1, op, x, y; v <= m; v++) {
        cin >> op;
        rootfa[v] = rootfa[v - 1];
        rootsiz[v] = rootsiz[v - 1];//�ȼ̳���һ���汾����Ϣ
        if (op == 1) {
            cin >> x >> y;
            Union(x, y, v);
        } else if (op == 2) {
            cin >> x;
            rootfa[v] = rootfa[x];
            rootsiz[v] = rootsiz[x];
        } else {
            cin >> x >> y;
            if (find(x, v) == find(y, v)) {
                cout << 1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    return 0;
}
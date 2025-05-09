// ��ƫ��ģ����1��C++��
// ���θ���n���Ǹ����֣���ʾ��n��С���ѣ�ÿ����ֻ��һ����
// ʵ���������ֲ���������һ������m��
// 1 x y : ��x���������ڵĶѺ͵�y���������ڵĶѺϲ�
//         ������������Ѿ���һ���ѻ���ĳ�������Ѿ�ɾ���������кϲ�
// 2 x   : ��ӡ��x���������ڶѵ���Сֵ�������ڶ���ɾ�������Сֵ
//         �����x�������Ѿ���ɾ����Ҳ�����Ҳ������ڵĶѣ���ӡ-1
//         ���ж����Сֵ������ɾ�����С��
// 1 <= n, m <= 10^5
// �������� : https://www.luogu.com.cn/problem/P3377
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// ���鼯��Ҫfather���飬��������ҵ�����ͷ
// father[i]������i�����ϵĸ��׽ڵ�
// father�ǲ��鼯�Ҵ���ڵ��·����Ϣ
// ��Ҫ��֤�����鼯���Ϸ��Ĵ���ڵ� = ����ͷ�ڵ�
int fa[MAXN];

//Ԥ����
void prepare() {
    dist[0] = -1;
    for(int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);//��ƽ������
    return fa[i];
}

//����i �� jΪͷ�����ϲ�  ������ͷ�����
int merge(int i, int j) {
    if (i == 0 || j == 0) {
        //�����˿սڵ� ��ô���Էǿ���Ϊͷ���
        return i + j;
    }
    if (num[i] > num[j] || (num[i] == num[j] && i > j)) {
        //˭С˭��ͷ ��������Ŀ�涨  һ�㶼������涨
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);//���Ҷ��Ӻ������ϲ�
    //���dist��û������ �Ƿ���Ҫ����
    if (dist[ls[i]] < dist[rs[i]]) {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

// �ڵ�iһ������ƫ����ͷ������ƫ����ɾ���ڵ�i������������ͷ�ڵ���
int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    // ���鼯��·��ѹ��������i�·���ĳ���ڵ�x��������father[x] = i
    // ����Ҫɾ��i�ˣ�����x���ϻ��Ҳ�����ȷ��ͷ�ڵ�
    // Ϊ���κνڵ����϶����ҵ���ȷ��ͷ������Ҫ���������
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    prepare();
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (num[x] != -1 && num[y] != -1) {
                //��ʾ�������ֶ�û�б�ɾ��
                int l = find(x);
                int r = find(y);
                if (l != r) {
                    //��ʾ�������ֲ���һ������
                    merge(l, r);
                }
            }
        } else {
            int x;
            cin >> x;
            if (num[x] == -1) {
                //������ֲ�����
                cout << -1 << "\n";
            } else {
                int ans = find(x);
                cout << num[ans] << "\n";
                //������Сֵ
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}

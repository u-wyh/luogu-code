// �����ߣ�ɾ�������Žڵ㣬C++��
// ����t��w��k����ʾһ����t���ˣ�������ʽ��Ϊw��������ֵ��Ϊk��w��k�����Ժ����
// ÿ���˶�����n��m����ʾ����һ����n�����£���m������
// ����˵�n�����£�������Ӧ��n�����ֵ��Ȼ�����m������������������
// 2 a   : ��a�����µ����ֵ���0
// 3 a b : ��a���������ڵļ����У�������ֵ�Ĵ��£����ֵ����b
//         ������ٺ����ֵ��ɸ�������Ϊ������µ����ֵ��Ϊ0
//         ��������У��������¶����������ֵ��ȡ��Ž�С�Ĵ���
// 4 a b : ��a���������ڵļ������b���������ڵļ��Ϻϲ�
// һ�����¼��ϵ����ֵ = ��������е�������ֵ��ֻȡһ��
// һ���˵����ֵ = ��������д��¼��ϵ����ֵ�ۼ�����
// Ȼ�����������ʽw����ÿ���˵����ֵ����������Ȼ���ӡ����˵��³�
// ���w==1��������
// ���w==2���˵����ֵ -= ���¼��ϵ����ֵ�е����ֵ
// ���w==3���˵����ֵ += ���¼��ϵ����ֵ�е����ֵ
// ���һ���˵����ֵ == 0����ӡ"Gensokyo 0"
// ���һ���˵����ֵ  > k����ӡ"Hell "��Ȼ���ӡ���ֵ
// ���һ���˵����ֵ <= k����ӡ"Heaven "��Ȼ���ӡ���ֵ
// һ����t���ˣ��������ջ���t�δ�ӡ
// 1 <= t <= 30
// 1 <= n <= 2 * 10^6
// �������ֵ���ܴܺ����뱣֤ÿ���˵����ֵ��long���Ͳ����
// �������� : https://www.luogu.com.cn/problem/P4971
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000001;
int t, w, n, m;
long long k;
long long num[MAXN];
// up[i]��ʾ�ڵ�i����ƫ���ṹ�ϵĸ��׽ڵ�
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// father[i]��ʾ���鼯��ڵ�i��·����Ϣ
int fa[MAXN];

void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= n; i++) {
        up[i] = ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    return fa[i] == i ? i : (fa[i] = find(fa[i]));
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    int tmp;
    if (num[i] < num[j] || (num[i] == num[j] && i > j)) {
        tmp = i; i = j; j = tmp;
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;//����ĵط�  ���ǽ��Ҷ��ӵĸ��׽ڵ����
    if (dist[ls[i]] < dist[rs[i]]) {
        tmp = ls[i]; ls[i] = rs[i]; rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

// �ڵ�i��������ƫ��������ڵ㣬ɾ���ڵ�i��������������ͷ�ڵ���
int remove(int i) {
    int h = find(i);//�ҵ��������ͷ���
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];//�������������ӵĸ�����ʱ��Ϊ�Լ�
    int s = merge(ls[i], rs[i]);//���������Ӻϲ�  �����½ڵ�
    int f = up[i];//f��i�ڵ����һ��ڵ�
    fa[i] = s;//�൱��ɾ��ͷ������
    up[s] = f;//�����дһ��  ���������ӵĺϲ���ڵ�s�ĸ��׸�Ϊf
    if (h != i) {
        fa[s] = h;//���鼯�ı�ƽ������
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        //��������
        for (int d = dist[s], tmp; dist[f] > d + 1; f = up[f], d++) {
            dist[f] = d + 1;
            if (dist[ls[f]] < dist[rs[f]]) {
                tmp = ls[f]; ls[f] = rs[f]; rs[f] = tmp;
            }
        }
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;//������ڵ����Ϣ����
    return fa[s];
}

void reduce(int i, long long v) {
    int h = remove(i);//���������ȫ�Ƴ�
    num[i] = max(num[i] - v, 0LL);//����������Ȩֵ
    fa[h] = fa[i] = merge(h, i);//����������¼�������
}

long long compute() {
    long long ans = 0;
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            ans += num[i];
            if (num[i] > mx) mx = num[i];
        }
    }
    if (w == 2) {
        ans -= mx;
    } else if (w == 3) {
        ans += mx;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t >> w >> k;
    for(int i = 1; i <= t; i++) {
        cin >> n >> m;
        prepare();
        for (int j = 1; j <= n; j++) {
            cin >> num[j];
        }
        for (int j = 1, op, a, b; j <= m; j++) {
            cin >> op >> a;
            if (op == 2) {
                reduce(a, num[a]);
            } else if (op == 3) {
                cin >> b;
                reduce(find(a), b);
            } else {
                cin >> b;
                int l = find(a);
                int r = find(b);
                if (l != r) {
                    merge(l, r);
                }
            }
        }
        long long ans = compute();
        if (ans == 0) {
            cout << "Gensokyo " << ans << endl;
        } else if (ans > k) {
            cout << "Hell " << ans << endl;
        } else {
            cout << "Heaven " << ans << endl;
        }
    }
    return 0;
}

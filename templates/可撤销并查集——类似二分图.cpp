// �Ž���C++��
// һ����n���ˣ�ÿ���˸�����ţ�һ����m���ߣ���������֮����ì��
// һ����k��С�飬�����е���û�ˣ���������Ȼ����
// ������a����b�����������һ��ȥ�Ž�����a����b�������ˣ��������´���
// ������������ֳ��������ţ�ÿ�˶�Ҫ�μӻ��֣�����ÿ�����ŵ��ڲ�������ì��
// ��ô��a����b�ͽ���һ��"�Ϸ����"��ע�⣬��b����a�Ͳ����ظ�������
// һ����k���飬����ѡ�����������ܶ࣬����һ���ж��ٸ�"�Ϸ����"
// 1 <= n��m��k <= 5 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF1444C
// �������� : https://codeforces.com/problemset/problem/1444/C
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int n, m, k;
// ÿ���ڵ�����
int team[MAXN];
// ÿ�����������˵�
int edge[MAXN][2];

// �����˵�Ϊ��ͬ��ıߣ�u��uteam��v��vteam
struct CrossEdge {
    int u, uteam, v, vteam;
};
bool CrossEdgeCmp(CrossEdge x, CrossEdge y) {
    if(x.uteam != y.uteam) {
    	return x.uteam < y.uteam;
    } else {
    	return x.vteam < y.vteam;
    }
}
CrossEdge crossEdge[MAXN];
int cnt = 0;

// conflict[i] = true����ʾi�����Լ�ȥ���ֶ���ͼ����Ȼ�г�ͻ
// conflict[i] = false����ʾi�����Լ�ȥ���ֶ���ͼ��û�г�ͻ
bool conflict[MAXN];

// �ɳ������鼯
int father[MAXN << 1];
int siz[MAXN << 1];
int rollback[MAXN << 1][2];
int opsize;

int find(int i) {
    while (i != father[i]) {
        i = father[i];
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
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
}

void filter() {
    for (int i = 1; i <= 2 * n; ++i) {
        //�൱�ڼ�һ��  1 <-> 1'
        father[i] = i;
        siz[i] = 1;
    }
    for (int i = 1, u, v; i <= m; i++) {
        u = edge[i][0];
        v = edge[i][1];
        if (team[u] < team[v]) {
            //��������ߵ������㲻��һ����
            //��ôͳ���ڲ�ͬ��ı߼�
            crossEdge[++cnt].u = u;
            crossEdge[cnt].uteam = team[u];
            crossEdge[cnt].v = v;
            crossEdge[cnt].vteam = team[v];
        } else if (team[u] > team[v]) {
            crossEdge[++cnt].u = v;
            crossEdge[cnt].uteam = team[v];
            crossEdge[cnt].v = u;
            crossEdge[cnt].vteam = team[u];
        } else {
            //�����ж�������ܷ��Ϊ����ѡ�����
            if (conflict[team[u]]) {
                continue;
            }
            if (find(u) == find(v)) {
                k--;
                conflict[team[u]] = true;
                //��ʾ�����ͻ����ì�� ֱ�Ӳ��ÿ���
            } else {
                //�����൱��������
            	Union(u, v + n);
            	Union(v, u + n);
            }
        }
    }
}

long long compute() {
    sort(crossEdge + 1, crossEdge + cnt + 1, CrossEdgeCmp);
    //���ս�С���Ǹ��ڵ����켯������
    long long ans = (long long)k * (k - 1) / 2;//ȫ������ж���
    int u, uteam, v, vteam, unionCnt;
    for (int l = 1, r = 1; l <= cnt; l = ++r) {
        uteam = crossEdge[l].uteam;
        vteam = crossEdge[l].vteam;
        while (r + 1 <= cnt && crossEdge[r + 1].uteam == uteam && crossEdge[r + 1].vteam == vteam) {
            //�����������ڽ����ͬ�ı߻���Ϊһ����
            r++;
        }
        if (conflict[uteam] || conflict[vteam]) {
            //��������������ǲ��Ϸ���  ֱ����̭
            //�Դ�Ҳ������Ӱ�� ��Ϊһ��ʼ��k�ͼ�����
            continue;
        }
        unionCnt = 0;
        for (int i = l; i <= r; i++) {
            u = crossEdge[i].u;
            v = crossEdge[i].v;
            if (find(u) == find(v)) {
                //������Ϸ�
                ans--;
                break;
            } else {
            	Union(u, v + n);
            	Union(v, u + n);
                unionCnt += 2;//ע������������
            }
        }
        for (int i = 1; i <= unionCnt; i++) {
            undo();
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> team[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> edge[i][0] >> edge[i][1];
    }
    filter();
    cout << compute() << "\n";
    return 0;
}
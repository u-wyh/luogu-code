#include <bits/stdc++.h>
#define MAXN 500010
using namespace std;

int n, m, p, t, tote;
int dist[MAXN], ans[MAXN];
//dist��ʾ�����������˳�ʱ��
//ans��ʵ��һ����¼���� �������ڸ�����¼�𰸵�  ����¼���������߶�Ӧ������distֵ

struct Bus {
    int x, t, idx, dist;
} b[MAXN];

void build(int x, int t, int idx, int dist) {
    b[++tote] = {x, t, idx, dist};
}

// ����ʱ����ͬʱ���˳�ʱ��Խ����Խǰ�档
// ����ʱ�䲻ͬʱ������ʱ�������Խ���档
bool cmp(const Bus &x, const Bus &y) {
    return (x.t == y.t) ? (x.dist > y.dist) : (x.t < y.t);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m >> p >> t;
    
    for (int i = 1, s, t, a, b, c, d; i <= m; i++) {
        cin >> s >> t >> a >> b >> c >> d;
        build(s, a, i, 0);
        build(t, d, i, c - b);
    }
    
    build(n + 1, t, 0, -0x3f3f3f3f);
    sort(b + 1, b + tote + 1, cmp);
    
    memset(dist, 250, sizeof(dist));
    dist[1] = 0;
    
    for (int i = 1; i <= tote; i++) {
        if (b[i].x == n + 1) {
            break;
        }
        if (!b[i].dist) {
            ans[b[i].idx] = dist[b[i].x];
        } else {
            dist[b[i].x] = max(dist[b[i].x], ans[b[i].idx] + b[i].dist);
			//����ʽ��֤��һ��·�����һ�����յ�֮ǰ�����ʹ�
        }
		// ������ö��ÿ���㣬��Ϊ����򽫶�Ӧ�� ans ��Ϊ���õ�� dist ֵ��
		// ��Ϊ�յ㣬���øõ�� ans+ ���õ��ǰ೵����������ʱ��ֵ���� bdist?�����¸õ�� dist ֵ�� 
		// ������ p ��ʱ distp? ֵС������� ?1������������� t?distp?��
    }
    
    (dist[p] < 0) ? cout << "-1" : cout << t - dist[p];
    return 0;
}
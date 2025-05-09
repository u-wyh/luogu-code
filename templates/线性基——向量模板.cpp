// װ������
// һ����n����Ʒ��ÿ����Ʒ����m������ֵ
// ���涨��ʲô�ǲ���Ҫ����Ʒ������Ѿ�ѡ����k����Ʒ����ʱ����һ����ǰ��Ʒ
// ������Ѿ�ѡ�����Ʒ����һ����˵�ϵ������������ֵ��ӣ����ܵõ���ǰ��Ʒ
// ��ô��˵��ǰ��Ʒ�ǲ���Ҫ�ģ��������������
// a = { 4, 6, 2 }, b = { 2, 8, 4 }, c = { 6, 19, 9 }
// a * 0.5 + b * 2 = c����ôc��Ʒ�ǲ���Ҫ��
// ÿ����Ʒ���м۸�����ϣ��������Ĺ�����Ʒ�������ܳ��ֲ���Ҫ����Ʒ
// ����������򼸼���Ʒ�����ٵĻ���
// 1 <= n��m <= 500
// 0 <= ����ֵ <= 1000
// �������� : https://www.luogu.com.cn/problem/P3265
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 502;
const int MAXM = 502;
const double sml = 1e-5;

double mat[MAXN][MAXM + 1];
int basis[MAXN];
int n, m;
int cnt, cost;

//�������Ի�ģ��
bool insert(int i) {
    for (int j = 1; j <= m; j++) {
        if (fabs(mat[i][j]) >= sml) {
            if (basis[j] == 0) {
                basis[j] = i;
                return true;
            }
            double rate = mat[i][j] / mat[basis[j]][j];
            for (int k = j; k <= m; k++) {
                mat[i][k] -= rate * mat[basis[j]][k];
            }
        }
    }
    return false;
}

void compute() {
    cnt = cost = 0;//��¼��
    vector<pair<double, int>> prices;
    for (int i = 1; i <= n; i++) {
        prices.emplace_back(mat[i][m + 1], i);
    }
    sort(prices.begin(), prices.end());
    //���ݼ۸�����  �۸�С������

    for (const auto& p : prices) {
        int i = p.second;
        if (insert(i)) {
            //��������Ʒ���Բ��� ��ô�Ͳ���
            cnt++;
            cost += static_cast<int>(mat[i][m + 1]);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> mat[i][m + 1]; // price
    }
    compute();
    cout << cnt << " " << cost << endl;
    return 0;
}

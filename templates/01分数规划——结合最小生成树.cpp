// ���ű���������
// һ����n����ׯ��ÿ����ׯ��(x, y, z)��ʾ
// ����(x,y)�����ׯ�ڶ�ά��ͼ�е�λ�ã�z�����亣�θ߶�
// ����������ׯ֮��ľ�����Ƕ�ά��ͼ�е�ŷʽ����
// ����������ׯ֮�����·���Ѿ��Ǻ��β�ֵ�ľ���ֵ
// ����������д�ׯ��ͨ������ϣ����·�����������٣�ͬʱϣ����
// �ܻ��� / �ܾ��룬�����ֵ����С��������С�ı�ֵ�Ƕ��٣��������С�����3λ���ಿ������
// 2 <= n <= 10^3
// 0 <= x��y <= 10^4
// 0 <= z <= 10^7
// �������� : http://poj.org/problem?id=2728
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const double sml = 1e-6;

int x[MAXN];
int y[MAXN];
int z[MAXN];
double dist[MAXN][MAXN];
double cost[MAXN][MAXN];
bool visit[MAXN];
double value[MAXN];
int n;

// �ڽӾ���ṹ�µ�prim�㷨���ӽڵ�1�����õ���С��������Ȩֵ��
double prim(double x) {
    // ����ֵ����Ȩ������ͳ�ƾ���
    // ����ֻ�ͱ�Ȩ�йأ�ԭʼ��dist��cost����Ҫ
    // ��1�ŵ���������µ����е�ľ��룬Ҳ����value����
    for (int i = 1; i <= n; i++) {
        visit[i] = false;
        value[i] = cost[1][i] - x * dist[1][i];
    }
    visit[1] = true;
    double sum = 0;
    // ��С������һ����n-1���ߣ�����һ����n-1�ֽ�����ÿ�ν����µĵ������С�������ĵ㼯
    for (int i = 1; i <= n - 1; i++) {
        // ��û�н����ĵ��У��ҵ�����С�������ĵ㼯����ĵ㣬���н���
        double minDist = INT_MAX;
        int next = 0;
        for (int j = 1; j <= n; j++) {
            if (!visit[j] && value[j] < minDist) {
                minDist = value[j];
                next = j;
            }
        }
        // ��С�ı߽�����С�������ı߼��������ĵ������С�������ĵ㼯
        sum += minDist;
        visit[next] = true;
        // �鿴�µĽ������ܲ�������������ľ���
        for (int j = 1; j <= n; j++) {
            if (!visit[j] && value[j] > cost[next][j] - x * dist[next][j]) {
                value[j] = cost[next][j] - x * dist[next][j];
            }
        }
    }
    // ������С��������Ȩֵ��
    return sum;
}

int main()
{
    cin>>n;
    while (n != 0) {
        for (int i = 1; i <= n; i++) {
            cin>>x[i]>>y[i]>>z[i];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                    cost[i][j] = abs(z[i] - z[j]);
                }
            }
        }
        double l = 0, r = 100, x, ans = 0;
        while (l < r && r - l >= sml) {
            x = (l + r) / 2;
            // �����С��������Ȩֵ <= 0����꣬��������Ѱ��С��ֵ
            // �����С��������Ȩֵ > 0������꣬�Ҳ������Ѱ�����ֵ
            if (prim(x) <= 0) {
                ans = x;
                r = x - sml;
            } else {
                l = x + sml;
            }
        }
        printf("%.3f\n", ans);
        cin>>n;
    }
    return 0;
}

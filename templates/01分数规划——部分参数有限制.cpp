// ţȺ�Ĳ���չʾ
// һ����nֻţ��ÿֻţ�������Ͳ�����������ֵ
// Ҫ��һ��Ҫѡ����ֻţ��ʹ��������������w������ѡ����ţ��ϣ����
// ���յĺ� / �����ĺͣ������ֵ������
// ���ظñ�ֵ * 1000�����������С����������
// 1 <= n <= 250
// 1 <= w <= 1000
// 1 <= ţ������ <= 10^6
// 1 <= ţ�Ĳ��� <= 10^3
// �������� : https://www.luogu.com.cn/problem/P4377
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 251;
const int MAXW = 1001;
// �㹻С������Ч��
const double NA = -1e9;
// ��С����
const double sml = 1e-6;

// ����
int weight[MAXN];
// ����
int talent[MAXN];
// (���� - x * ����)�Ľ���
double value[MAXN];
// dp[i][j] : 1...i��ţ����ѡ������������j������£����Ľ����
// �ر�ģ�dp[i][w]��ʾ1...i��ţ����ѡ������������1��2��3...����������У����Ľ����
//������������w��  ȫ���㵽w���������ȥ
// Ϊ�˽�ʡʱ��Ϳռ�ѡ����ô���壬ͬʱ���ռ�ѹ��
double dp[MAXW];
int n, w;

bool check(double x) {
    for (int i = 1; i <= n; i++) {
        value[i] = (double) talent[i] - x * weight[i];
    }
    dp[0] = 0;
    for(int i=1;i<=w;i++){
        dp[i]=NA;
    }
    for (int i = 1; i <= n; i++) {
        //��ʾ��iͷţ
        for (int p = w, j; p >= 0; p--) {
            //�Ӻ���ǰ��  ��ֹ���ǵ��³���
            j = (int) (p + weight[i]);
            if (j >= w) {
                dp[w] = max(dp[w], dp[p] + value[i]);
            } else {
                dp[j] = max(dp[j], dp[p] + value[i]);
            }
        }
    }
    return dp[w] >= 0;
}

int main()
{
    cin>>n>>w;
    for(int i=1;i<=n;i++){
        cin>>weight[i]>>talent[i];
    }
    double l = 0, r = 0, x;
    for (int i = 1; i <= n; i++) {
        r += talent[i];
    }
    //cout<<r<<endl;
    double ans = 0;
    while (l < r && r - l >= sml) {
        //cout<<r<<endl;
        x = (l + r) / 2;
        if (check(x)) {
            ans = x;
            l = x + sml;
        } else {
            r = x - sml;
        }
    }
    cout<<((int) (ans * 1000))<<endl;
    return 0;
}

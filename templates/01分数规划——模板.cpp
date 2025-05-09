// 01�����滮ģ����
// ����n�����ݣ�ÿ��������(a, b)����ֵ����Ϊ���������Ҷ��ǷǸ���
// ��������k�����ݣ�ϣ����ʣ����������������a�ĺ� / ����b�ĺͣ������ֵ������
// ���ʣ����������b�ĺ�Ϊ0����Ϊ������
// ��󣬽��ñ�ֵ * 100��С��������������������������
// 1 <= n <= 100
// 0 <= a��b <= 10^9
// �������� : https://www.luogu.com.cn/problem/P10505
// �������� : http://poj.org/problem?id=2976
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const double sml = 1e-6;

struct node {
    double x,y,r;
}arr[MAXN];
int n,k;

bool cmp(node a,node b){
    return a.r>b.r;
}

bool check(double x) {
    // x�̶�������£��õ��������ݵĽ���
    for (int i = 1; i <= n; i++) {
        arr[i].r = arr[i].x - x * arr[i].y;
    }
    // ����Ӵ�С����
    sort(arr + 1, arr + n + 1, cmp);
    // ���k��������ۼӺ�
    double sum = 0;
    for (int i = 1; i <= k; i++) {
        sum += arr[i].r;
    }
    return sum >= 0;
}

int main()
{
    cin>>n>>k;
    while((n+k)!=0){
        k = n - k;
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].x;
        }
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].y;
        }
        double l = 0, r = 0, x;
        for (int i = 1; i <= n; i++) {
            r += arr[i].x;
        }
        double ans = 0;
        while (l < r && r - l >= sml) {
            x = (l + r) / 2;
            if (check(x)) {
                ans = x;
                l = x + sml;
            } else {
                r = x - sml;
            }
        }
        cout<<((int) (100 * (ans + 0.005)))<<endl;
        cin>>n>>k;
    }
    return 0;
}

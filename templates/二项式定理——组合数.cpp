// ���������
// ��Ϲ�ʽc(i, j)����ʾ��i����Ʒ��ѡ��j����Ʒ�ķ�����
// �������ֵ��k������������ô��(i, j)��һ���Ϸ���
// ���������һ������n��m����i��j���㣺0 <= i <= n��0 <= j <= min(i, m)
// �����ж��ٺϷ���
// һ����t����ԣ����в��Ե�k��Ϊͬһ��ֵ
// ÿ����Ը���n��m����ӡÿ����ԵĴ�
// 1 <= t <= 10^4
// 2 <= k <= 21
// 0 <= n��m <= 2000
// �������� : https://www.luogu.com.cn/problem/P2822
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXV = 2000;
const int MAXN = 2002;

int c[MAXN][MAXN];
int f[MAXN][MAXN];
int sum[MAXN][MAXN];
int t, k, n, m;

void build() {
    for (int i = 0; i <= MAXV; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;//�������ʽ���
        }
    }
    for (int i = 1; i <= MAXV; i++) {
        for (int j = 1; j <= i; j++) {
            f[i][j] = c[i][j] % k == 0 ? 1 : 0;
        }
    }
    for (int i = 2; i <= MAXV; i++) {
        for (int j = 1; j <= i; j++) {
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + f[i][j];
        }
        sum[i][i + 1] = sum[i][i];
    }
}

int main()
{
    cin>>t>>k;
    build();
    for(int i=1;i<=t;i++){
        cin>>n>>m;
        if (m > n) {
            cout<<sum[n][n]<<endl;
        } else {
            cout<<sum[n][m]<<endl;
        }
    }
    return 0;
}

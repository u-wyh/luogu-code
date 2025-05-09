// ��С�ƶ��ܾ���
// ���й����ͻ����˶��ֲ���x����
// ��������Ϊn�Ķ�ά����factory��factory[i][0]Ϊi�Ź�����λ�ã�factory[i][1]Ϊ����
// ��������Ϊm��һά����robot��robot[j]Ϊ��j�������˵�λ��
// ÿ���������ڵ�λ�ö���ͬ��ÿ�����������ڵ�λ�ö���ͬ�������˵������ľ���Ϊλ�ò�ľ���ֵ
// ���л����˶��ǻ��ģ����ǻ����˿���ȥ���κι��������������ǲ��ܳ���ĳ������������
// �������ݱ�֤���л����˶����Ա�ά�ޣ��������л������ƶ�����С�ܾ���
// 1 <= n��m <= 100
// -10^9 <= factory[i][0]��robot[j] <= +10^9
// 0 <= factory[i][1] <= m
// �������� : https://leetcode.cn/problems/minimum-total-distance-traveled/
#include<bits/stdc++.h>
using namespace std;
const long NA = LONG_MAX;
const int MAXN = 101;
const int MAXM = 101;

int n, m;
// �����±��1��ʼ��fac[i][0]��ʾλ�ã�fac[i][1]��ʾ����
struct node{
    int pos,cap;
}fac[MAXN];
// �������±��1��ʼ��rob[i]��ʾλ��
int rob[MAXM];
// dp[i][j] : 1...i����ȥ����1...j�Ż����ˣ�����ܾ����Ƕ���
long dp[MAXN][MAXM];
// ǰ׺������
long sum[MAXM];
// ��������
int q[MAXM];
int l, r;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

// i�Ź�����j�Ż����˵ľ���
long dist(int i, int j) {
    return abs((long) fac[i].pos - rob[j]);
}

// i�Ź�����j�Ż����˿�ʼ�����ָ��
// ��Ŀ��У�����ָ���ֵ
// ��������У�����NA
long value(int i, int j) {
    if (dp[i - 1][j - 1] == NA) {
        return NA;
    }
    return dp[i - 1][j - 1] - sum[j - 1];
}

void build() {
    // �����ͻ����˶���������λ������
    sort(fac+1,fac+n+1,cmp);
    sort(rob+1,rob+m+1);
    // dp��ʼ��
    for (int j = 1; j <= m; j++) {
        dp[0][j] = NA;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>fac[i].pos>>fac[i].cap;
    }
    for(int i=1;i<=m;i++){
        cin>>rob[i];
    }
    build();
    for (int i = 1, cap; i <= n; i++) {
        // i�Ź���������
        cap = fac[i].cap;
        // sum[j]��ʾ
        // 1�Ż�����ȥ��i�Ź����ľ���
        // 2�Ż�����ȥ��i�Ź����ľ���
        // ...
        // j�Ż�����ȥ��i�Ź����ľ���
        // ����ȫ��������Ҳ����ǰ׺�͵ĸ���
        for (int j = 1; j <= m; j++) {
            sum[j] = sum[j - 1] + dist(i, j);
        }
        l = r = 0;
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (value(i, j) != NA) {
                while (l < r && value(i, q[r - 1]) >= value(i, j)) {
                    r--;
                }
                q[r++] = j;
            }
            if (l < r && q[l] == j - cap) {
                l++;
            }
            if (l < r) {
                dp[i][j] = min(dp[i][j], value(i, q[l]) + sum[j]);
            }
        }
    }
    cout<<dp[n][m];
    return 0;
}

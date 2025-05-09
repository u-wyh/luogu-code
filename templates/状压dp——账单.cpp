// �����˵�ƽ��
// ����һ����ʾ���׵����� transactions
// ���� transactions[i] = [fromi, toi, amounti]
// ��ʾ ID = fromi ���˸� ID = toi ���˹��� amounti
// ������㲢���ػ�������ծ�����С���ױ���
// �������� : https://leetcode.cn/problems/optimal-account-balancing/
#include<bits/stdc++.h>
using namespace std;

int n;
int tran[100][3];
int help[100];
int debt[100];
int cnt=0;

int f(int status, int sum, int* dp) {
    if (dp[status] != -1) {
        return dp[status];
    }
    int ans = 0;
    if ((status & (status - 1)) != 0) { // �����в�ֻһ��Ԫ��
        if (sum == 0) {
            for (int i = 0; i < n; i++) {
                if ((status & (1 << i)) != 0) {
                    // �ҵ��κ�һ��Ԫ�أ�ȥ�����Ԫ��
                    // ʣ�µļ��Ͻ��г��ԣ�����ֵ + 1
                    ans = f( status ^ (1 << i), sum - debt[i], dp) + 1;
                    // Ȼ����Ҫ�ٳ�����һ��Ԫ���ˣ���Ϊ��һ����һ����
                    // ����ֱ��break
                    break;
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                if ((status & (1 << i)) != 0) {
                    ans = max(ans, f( status ^ (1 << i), sum - debt[i], dp));
                }
            }
        }
    }
    dp[status] = ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>tran[i][0]>>tran[i][1]>>tran[i][2];
    }
    for(int i=1;i<=n;i++){
        help[tran[i][0]]+=tran[i][2];
        help[tran[i][1]]-=tran[i][2];
    }
    for (int num : help) {
        if (num != 0) {
            cnt++;
        }
    }
    int index = 0;
    for (int num : help) {
        if (num != 0) {
            debt[index++] = num;
        }
    }
    n=index;
    int dp[1 << n];
    memset(dp, -1, sizeof(dp));
    cout<< n - f((1 << n) - 1, 0, dp);
    return 0;
}

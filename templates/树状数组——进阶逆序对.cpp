//P4280
//��������״�����Ѷ��Ǻܴ��
//������������ û��ȷ����λ�����������һ���ǵ���������
//��Ϊ�����ǰ����ں����  ��ô����һ��λ�ÿ϶��������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 105;

int n, m;
int a[MAXN];
vector<int> lis[2]; 
// ʹ��vector����̬���������С����������
//lis[0][i]��ʾǰ��������д���i�ĸ���
//lis[1][i]��ʾ�����������С��i�ĸ���
long long ans;

int main() {
    scanf("%d%d", &n, &m);
    lis[1].resize(m + 1, 0); // ��ʼ��lis[1]Ϊ��СΪm+1�����飬����Ԫ��Ϊ0

    // ��ȡ���벢ͳ��ÿ�����ֳ��ֵĴ���������-1��
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            lis[1][a[i]]++;
        }
    }

    // �ۼ�lis[1]���飬�����������ǰ׺��
    for (int i = 1; i <= m; ++i) {
        lis[1][i] += lis[1][i - 1];
        //��ʱ��ʾ����С�ڵ���i�Ĵ���
    }

    // ��ʼ��lis[0]����
    lis[0].resize(m + 1, 0);

    // ����ÿ��λ��
    for (int i = 1; i <= n; ++i) {
        int ct=0;
        if (a[i] == -1) {
            int c = 0, d = 0,  mx = INT_MAX; // ʹ��INT_MAX����0x7fffffff

            // �ҵ����ŵ����ֵ
            for (int j = ct; j <= m; ++j) {
                int current_sum = lis[0][j + 1] + lis[1][j - 1];
                if (current_sum < mx) {
                    mx = current_sum;
                    ct = j;
                }
            }
            a[i] = ct; // ���-1λ�õ�����ֵ
        } else {
            // �����ǰλ�ò���-1�������lis[1]���飨������ʹ�õ����֣�
            for (int j = a[i]; j <= m; ++j) {
                lis[1][j]--;
            }
        }

        // ���´𰸲�����lis[0]���飨��¼��ǰλ��֮ǰ��LIS���ȣ�
        ans += lis[0][a[i] + 1];
        for (int j = 1; j <= a[i]; ++j) {
            lis[0][j]++;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
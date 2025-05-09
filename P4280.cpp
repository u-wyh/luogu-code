#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 105;

int n, m;
int a[MAXN];
int lis[2][MAXM];
long long ans;

int main() {
    scanf("%d%d", &n, &m);
    
    // ���벢ͳ�Ƴ�ʼ��׺��
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            ++lis[1][a[i]];
        }
    }
    
    // �����׺��
    for (int i = 1; i <= m; ++i) {
        lis[1][i] += lis[1][i - 1];//���ڵ�0��λ�ö��� �����ʾС�ڵ���i��Ԫ�ظ���
    }
    
    // ����ÿ��Ԫ��
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) {
            // Ѱ�����ŵ����ֵ
            int ct = 0, mx = 0x7fffffff;
            for (int j = 1; j <= m; ++j) {
                int current = lis[0][j + 1] + lis[1][j - 1];
                if (current < mx) {
                    mx = current;
                    ct = j;
                }
            }
            a[i] = ct;
        } else {
            // ���º�׺��
            for (int j = a[i]; j <= m; ++j) {
                --lis[1][j];//��ʾ����ʣ�µ�λ�ö���  ����С�ڵ���j�ĸ�������һ
            }
        }
        
        // ͳ������Բ�����ǰ׺��
        ans += lis[0][a[i] + 1];//ͳ��ǰ������Լ���Ԫ�صĸ���
        for (int j = 1; j <= a[i]; ++j) {
            ++lis[0][j];//��ʾ���ں����Ԫ�ض��� ������������j  ��ô����������ָ�����һ
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}
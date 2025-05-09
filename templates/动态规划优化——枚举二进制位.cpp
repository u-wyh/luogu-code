// ����������Ϊ0���������
// ����һ������Ϊn������arr�����������ѡ���������������
// ����Ҫ���������ڵ�������&�Ľ��������0�������������в��ǺϷ���
// ������Ϸ������еĳ���
// 1 <= n <= 10^5
// 0 <= arr[i] <= 10^9
// �������� : https://www.luogu.com.cn/problem/P4310
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;

int n;
int pre[32];
int arr[100005];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for (int i = 0, num, cur; i < n; i++) {
        num = arr[i];
        cur = 1;
        for (int j = 0; j < 31; j++) {
            if (((num >> j) & 1) == 1) {
                cur = max(cur, pre[j] + 1);
            }
        }
        for (int j = 0; j < 31; j++) {
            if (((num >> j) & 1) == 1) {
                pre[j] = max(pre[j], cur);
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < 31; j++) {
        ans = max(ans, pre[j]);
    }
    cout<<ans;
    return 0;
}

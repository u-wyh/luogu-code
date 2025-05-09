// ��ʦ������
// ��Ŀ���Լ�Ϊ���µ�����
// ����һ������Ϊn������arr���±��0��ʼ
// �κ�һ���������ָ��Ϊ���������ۼӺ� * ����������Сֵ
// ����arr������������ָ����ۼӺͣ��𰸶� 1000000007 ȡģ
// 1 <= n <= 10^5
// 1 <= arr[i] <= 10^9
// �������� : https://leetcode.cn/problems/sum-of-total-strength-of-wizards/
#include<iostream>
using namespace std;
const int MOD = 1e9+7;

int n;
int st[100005];
int arr[100005];
int sumsum[100005];

int sum(int l, int m, int r) {
    long left = sumsum[r - 1];
    if (m - 1 >= 0) {
        left = (left - sumsum[m - 1] + MOD) % MOD;
    }
    left = (left * (m - l)) % MOD;
    long right = 0;
    if (m - 1 >= 0) {
        right = (right + sumsum[m - 1]) % MOD;
    }
    if (l - 1 >= 0) {
        right = (right - sumsum[l - 1] + MOD) % MOD;
    }
    right = (right * (r - m)) % MOD;
    return (int) (((left - right + MOD) % MOD * arr[m]) % MOD);
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int pre = arr[0] % MOD;
    sumsum[0] = pre;
    for (int i = 1; i < n; i++) {
        pre = (pre + arr[i]) % MOD;
        sumsum[i] = (sumsum[i - 1] + pre) % MOD;
    }
    int size = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (size > 0 && arr[st[size - 1]] >= arr[i]) {
            int m = st[--size];
            int l = size > 0 ? st[size - 1] : -1;
            ans = (ans + sum(l, m, i)) % MOD;
        }
        st[size++] = i;
    }
    while (size > 0) {
        int m = st[--size];
        int l = size > 0 ? st[size - 1] : -1;
        ans = (ans + sum(l, m, n)) % MOD;
    }
    cout<<ans;
    return 0;
}

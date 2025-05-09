// ��������1�ķǸ�����
// ����һ��������n������ͳ����[0, n]��Χ�ķǸ�������
// �ж��ٸ������Ķ����Ʊ�ʾ�в�����������1
// �������� : https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
#include<bits/stdc++.h>
using namespace std;

int n;
int cnt[31];

// cnt[len] : �����������lenλ�����ж�����״̬�в�����������1��״̬�ж��ٸ�����������
// ��num��������ʽ�ĸ�λ��ʼ����ǰ������iλ��֮ǰ��λ��ȫ��numһ��
// ����<=num�Ҳ�����������1��״̬�ж��ٸ�
int f(int num, int i) {
    if (i == -1) {
        return 1; // num����Ϸ�
    }
    int ans = 0;
    if ((num & (1 << i)) != 0) {
        ans += cnt[i];
        if ((num & (1 << (i + 1))) != 0) {
            // ���num������״̬��ǰһλ��1����ǰλҲ��1
            // ���ǰ׺���ֺ�numһ��������һ�����Ϸ���
            // ������ǰ����
            return ans;
        }
    }
    // ֮ǰ�ĸ�λ��numһ�����ҺϷ�������ȥi-1λ�ݹ�
    ans += f(num, i - 1);
    return ans;
}

int main()
{
    cin>>n;
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    cout<<f(n, 30);
    return 0;
}

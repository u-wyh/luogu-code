// �����������
// ����һ������Ϊn��ֻ��Сд��ĸ��ɵ��ַ���s������һ���Ǹ�����k
// �ַ���s�������ɺܶ������У�����������������еĶ���
// ���������������ڵ������ַ�������ĸ����λ�εĲ�ֵ����ֵ<=k
// ���������������
// 1 <= n <= 10^5
// 0 <= k <= 25
// sֻ��Сд��ĸ���
// �������� : https://leetcode.cn/problems/longest-ideal-subsequence/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// �߶����ڵ�����������26����ĸ�㹻��
const int MAXN = (26 + 1) * 4;

int maxTree[MAXN];
int n = 26;

// ���¸��ڵ�ֵ
void up(int i) {
    maxTree[i] = max(maxTree[i << 1], maxTree[i << 1 | 1]);
}

// �������
void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r && jobi == l) {
        maxTree[i] = jobv;
    } else {
        int m = (l + r) >> 1;
        if (jobi <= m) {
            update(jobi, jobv, l, m, i << 1);
        } else {
            update(jobi, jobv, m + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// ��ѯ�������ֵ
int queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return maxTree[i];
    }
    int m = (l + r) >> 1;
    int ans = INT_MIN;
    if (jobl <= m) {
        ans = max(ans, queryMax(jobl, jobr, l, m, i << 1));
    }
    if (jobr > m) {
        ans = max(ans, queryMax(jobl, jobr, m + 1, r, i << 1 | 1));
    }
    return ans;
}

int longestIdealString(string s, int k) {
    fill(maxTree,maxTree+MAXN, 0);
    int ans = 0;
    for (char cha : s) {
        int v = cha - 'a' + 1;
        int p = queryMax(max(v - k, 1), min(v + k, n), 1, n, 1) + 1;
        ans = max(ans, p);
        update(v, p, 1, n, 1);
    }
    return ans;
}

int main() {
    string s;
    int k;
    cout << "Enter the string: ";
    cin >> s;
    cout << "Enter the value of k: ";
    cin >> k;

    int result = longestIdealString(s, k);
    cout << "The length of the longest ideal string is: " << result << endl;

    return 0;
}

// ͳ���ж��ٸ���ͬ���ַ���
// �������� : https://www.luogu.com.cn/problem/P3370
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
const int BASE = 499;

vector<long long> nums(MAXN);
int n;

int v(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 11;
    } else {
        return c - 'a' + 37;
    }
}

long long value(const string& s) {
    long long ans = 0;
    for (size_t i = 0; i < s.length(); i++) {
        ans = ans * BASE + v(s[i]);
    }
    return ans;
}

//long long value(const string& s) {
//    long long ans = v(s[0]);//����һ��ʼ��������Ϊ0  �����0��ʼ
//    for (size_t i = 1; i < s.length(); i++) {
//        ans = ans * BASE + v(s[i]);
//    }
//    return ans;
//}

// ���� + ��д + Сд
// '0' -> 1
// '1' -> 2
// ...
// '9' -> 10
// 'A' -> 11
// 'B' -> 12
// ...
// 'Z' -> 36
// 'a' -> 37
// ...
// 'z' -> 62

int cnt() {
    sort(nums.begin(), nums.begin() + n);
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i - 1]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        nums[i] = value(line);
    }
    cout << cnt() << endl;
    return 0;
}

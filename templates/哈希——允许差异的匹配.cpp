// ����ƥ�䶨����ƥ���Ӵ�������
// ������Ϊn���ַ���s���Լ�����Ϊm���ַ���p������һ������k
// s'��sƥ��Ķ���Ϊ��s'��s������ͬ���������k��λ���ַ���ͬ
// Ҫ������ַ���s���ж����Ӵ����ַ���pƥ��
// �������� : https://www.luogu.com.cn/problem/P3763
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 100001;
const int base = 499;

vector<long long> pow(MAXN), hashs(MAXN), hashp(MAXN);//hashs hsahp�ֱ���s p �Ĺ�ϣ����

void build(const string& s, const string& p) {
    pow[0] = 1;
    for (int j = 1; j < MAXN; j++) {
        pow[j] = pow[j - 1] * base;
    }

    int n = s.size(), m = p.size();
    hashs[0] = s[0] - 'a' + 1;
    for (int j = 1; j < n; j++) {
        hashs[j] = hashs[j - 1] * base + s[j] - 'a' + 1;
    }

    hashp[0] = p[0] - 'a' + 1;
    for (int j = 1; j < m; j++) {
        hashp[j] = hashp[j - 1] * base + p[j] - 'a' + 1;
    }
}

long long hash1(const vector<long long>& hash, int l, int r) {
    long long ans = hash[r];
    if (l > 0) ans -= hash[l - 1] * pow[r - l + 1];
    return ans;
}

bool same(int l1, int l2, int len) {
    return hash1(hashs, l1, l1 + len - 1) == hash1(hashp, l2, l2 + len - 1);
}

//���s�д�l1 �� r1  ��   p �� l2��m-1  (m-1-l2)==(r1-l1)  �������ַ����Ĳ����Ƿ�С��k
bool check(const string& s, const string& p, int l1, int r1, int k) {
    int l2 = 0, diff = 0;
    while (l1 <= r1 && diff <= k) {
        int left = 1, right = r1 - l1 + 1, len = 0;
        //ÿ�ζ���ö����һ����ͬ���ַ����ֵ�λ��
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (same(l1, l2, mid)) {
                len = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (l1 + len <= r1) {
            diff++;
        }
        l1 += len + 1;
        l2 += len + 1;
    }
    return diff <= k;
}

int compute(const string& s, const string& p, int k) {
    //��ʾ���s��  �ж��ٸ���  p ���ڲ���С�� k �����Ӵ�
    int n = s.size(), m = p.size();
    if (n < m)
        return 0;
    build(s, p);//��ɹ�ϣ����
    int ans = 0;
    for (int i = 0; i <= n - m; i++) {
        if (check(s, p, i, i + m - 1, k)) {
            ans++;
        }
    }
    return ans;
}

int main() {
    int n;
    string s, p;
    cin >> n ;
    int k=3;
    for (int i = 0; i < n; i++) {
        cin >> s >> p;
        cout << compute(s, p, k) << endl;
    }
    return 0;
}

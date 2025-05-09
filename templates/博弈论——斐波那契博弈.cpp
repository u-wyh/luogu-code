// 쳲���������(Fibonacci Game + Zeckendorf����)
// һ����nöʯ�ӣ���λ��Ҷ������¹��������Ϸ��
// ���ֺ�������ȡʯ�ӣ������ڵ�һ�ֿ���ȡ�������ʯ��
// ��������ÿһ�ֵ�ǰ���������Ҫȡ��һ��ʯ�ӣ����ȡ����һ��ȡ��������2��
// ��Ȼ�����ȡ�ߵ��������벻����Ŀǰ����ʣ���ʯ��������˫���������Ų���ȡʯ��
// ��Ҳ�������ˣ����ݹ�������һ�����ʤ������������֪��
// ��һ���Լ�ȡ�����ټ���ʯ�ӾͿ��Ա�֤��ʤ��
// �������� : https://www.luogu.com.cn/problem/P6487
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include <iostream>
#include <vector>
using namespace std;

const long long MAXN = 1000000000000000LL;
const int MAXM = 101;

vector<long long> f(MAXM);
int size;

void build() {
    f[0] = 1;
    f[1] = 2;
    size = 1;
    while (f[size] <= MAXN) {
        f[size + 1] = f[size] + f[size - 1];
        size++;
    }
}

long long bs(long long n) {
    int l = 0;
    int r = size;
    int m;
    long long ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (f[m] <= n) {
            ans = f[m];
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

long long compute(long long n) {
    long long ans = -1, find;
    while (n != 1 && n != 2) {
        find = bs(n);
        if (n == find) {
            ans = find;
            break;
        } else {
            n -= find;
        }
    }
    if (ans != -1) {
        return ans;
    } else {
        return n;
    }
}

int main() {
    build();
    long long n;
    while (cin >> n) {
        cout << compute(n) << endl;
    }
    return 0;
}

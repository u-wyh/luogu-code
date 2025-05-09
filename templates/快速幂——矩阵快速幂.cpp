// ��쳲��������е�n��
// �������� : https://leetcode.cn/problems/fibonacci-number/
// ������Ե�������̫С�����Ҳ�ǣ��ȡģ������
// ���Ծ�������ݿ���������
#include <iostream>
#include <vector>

using namespace std;

// ʱ�临�Ӷ�O(n)����ͨ�ⷨ
int fib1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int lastLast = 0, last = 1;
    for (int i = 2, cur; i <= n; i++) {
        cur = lastLast + last;
        lastLast = last;
        last = cur;
    }
    return last;
}

// �������
// a������һ��Ҫ����b������
vector<vector<int>> multiply(vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    return ans;
}

// ���������
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//��λ���� �൱�ڳ˷��������е�1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//ÿ�ζ��Ǳ���
    }
    return ans;
}

// ʱ�临�Ӷ�O(logn)����������ݵĽⷨ
int fib2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // �����ʼ�����ת�ƾ���
    vector<vector<int>> start = { {1, 0} };
    vector<vector<int>> base = {
        {1, 1},
        {1, 0}
    };

    // ������������
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    return ans[0][0];
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    cout << "Fibonacci number (O(n)): " << fib1(n) << endl;
    cout << "Fibonacci number (O(logn)): " << fib2(n) << endl;

    return 0;
}

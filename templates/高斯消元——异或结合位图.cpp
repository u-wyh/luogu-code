// ����ǧ���
// һ����n�ֳ��ӣ����1~n��������Ϊ������Ϊ�����ǳ棬ż����Ϊ�ǵ����
// һ����m�������ȵĲ�����¼����¼���1~m
// ��������һ��������¼Ϊ��011 1����ʾ1�ų�û���룬2�š�3�ų�����ˣ�������Ϊ����
// ������¼��֤����������ì�ܵ���������ǿ���������Ĳ������
// Ҳ��ӵ�дӵ�1�ŵ���k�Ų�����¼�͹��ˣ�k+1~m�Ų�����¼�л���û�ж���Ӱ��������
// ��ӡ���k�����Ҵ�ӡÿ�ֳ��ӵ��������ǳ滹�ǵ����
// ���ʹ�����еĲ����������Ȼ�޷�ȷ��ÿ�ֳ��ӵ����ԣ���ӡ"Cannot Determine"
// 1 <= n <= 1000
// 1 <= m <= 2000
// �������� : https://www.luogu.com.cn/problem/P2447
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>

using namespace std;

const int BIT = 64;
const int MAXN = 2002;
const int MAXM = (MAXN / BIT) + 1;

long long mat[MAXN][MAXM];
int n, m, s;
int need;

// ��˹��Ԫ�����򷽳���
void gauss(int n) {
    need = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (mat[j - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT))) {
                swap(mat[i - 1], mat[j - 1]);
                need = max(need, j);
                break;
            }
        }
        // һ��û��Ψһ�⣬���Խ�����
        if (!(mat[i - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT)))) {
            return;
        }
        for (int j = 1; j <= n; ++j) {
            if (i != j && (mat[j - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT)))) {
                for (int k = 0; k < MAXM; ++k) {
                    mat[j - 1][k] ^= mat[i - 1][k];
                }
            }
        }
    }
}

// ����row�У�col�е�״̬Ϊv
void set(int row, int col, int v) {
    if (v == 0) {
        mat[row - 1][col / BIT] &= ~(1LL << (col % BIT));
    } else {
        mat[row - 1][col / BIT] |= 1LL << (col % BIT);
    }
}

// ��ȡrow�У�col�е�״̬
int get(int row, int col) {
    return (mat[row - 1][col / BIT] >> (col % BIT)) & 1;
}

// ��������
void swap(long long* a, long long* b) {
    long long tmp[MAXM];
    for (int i = 0; i < MAXM; ++i) {
        tmp[i] = a[i];
        a[i] = b[i];
        b[i] = tmp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    s = max(n, m);
    for (int i = 1; i <= m; ++i) {
        string line;
        cin >> line;
        for (int j = 1; j <= n; ++j) {
            set(i, j, line[j - 1] - '0');
        }
        int val;
        cin >> val;
        set(i, s + 1, val);
    }

    gauss(s);
    bool sign = true;
    for (int i = 1; i <= n; ++i) {
        if (!get(i, i)) {
            sign = false;
            break;
        }
    }

    if (!sign) {
        cout << "Cannot Determine" << endl;
    } else {
        cout << need << endl;
        for (int i = 1; i <= n; ++i) {
            if (get(i, s + 1)) {
                cout << "?y7M#" << endl;
            } else {
                cout << "Earth" << endl;
            }
        }
    }

    return 0;
}

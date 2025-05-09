#include <stdio.h>
#include <ctype.h>
#include <limits.h> // ����INT_MAX

#define mid ((l + r + 1) / 2) // ע�������Ϊ��������

// �������
long long read() {
    long long s = 0, f = 1;
    char ch;
    while (!isdigit(ch = getchar()))
        if (ch == '-')
            f = -f;
    for (s = ch - '0'; isdigit(ch = getchar()); s = s * 10 + (ch - '0'));
    return s * f;
}

const int N = 55, inf = INT_MAX; // ʹ��INT_MAX��Ϊ�Ͻ�
int n, m, l, r;
int c[55];

// �жϺ���
int judge(int std) {
    int tmp = 0, rest = std;
    for (int i = 1; i <= n; i++) {
        if (c[i] >= std)
            continue;
        tmp += (std - c[i]);
        rest -= (std - c[i]);
        if (tmp > m || rest < 0)
            return 0;
    }
    return 1;
}

int main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
        c[i] = read();
    l = 1, r = inf;
    while (l < r) { // ����������Ŀ
        if (judge(mid))
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}

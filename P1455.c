#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // ����isalnum

int read() // ���
{
    int num = 0, f = 1;
    char ch = getchar();

    while (!isalnum(ch)) {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (isalnum(ch)) {
        num = num * 10 + (ch - '0');
        ch = getchar();
    }
    return num * f;
}

int father[10001]; // ���鼯����

int find(int x) // ���鼯����
{
    if (father[x] == x) {
        return x;
    }
    return father[x] = find(father[x]);
}

int c[10001], d[10001], f[100001]; // DP���飬ע��f����Ĵ�С������Ҫ������֧�ָ����w

int main()
{
    int n = read(), m = read(), w = read();
    for (int i = 1; i <= n; i++) { // ��ʼ�����鼯
        father[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        c[i] = read();
        d[i] = read();
    }

    int x, y;
    for (int i = 1; i <= m; i++) { // ���鼯
        x = read();
        y = read();
        father[find(x)] = find(y);
    }

    for (int i = 1; i <= n; i++) { // ��ͬ���ϵ��ƶ�ļ�Ǯ���ֵ������һ���ƶ���
        if (father[i] != i) {
            d[find(i)] += d[i];
            d[i] = 0;
            c[find(i)] += c[i];
            c[i] = 0;
        }
    }

    for (int i = 1; i <= n; i++) { // DP
        for (int v = w; v >= c[i]; v--) {
            f[v] = (f[v] > f[v - c[i]] + d[i]) ? f[v] : (f[v - c[i]] + d[i]);
        }
    }
    printf("%d\n", f[w]);
    return 0;
}

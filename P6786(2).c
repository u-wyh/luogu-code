#include <stdio.h>
#include <stdlib.h>

#define MAXN 500050

typedef long long LL;

LL N, a[MAXN], x[MAXN], t[MAXN], f[MAXN], cnt = 0, Ans = 0;

int compare(const void *a, const void *b) {
    return (*(LL *)a - *(LL *)b);
}

void Init() {
    scanf("%lld", &N);
    for (int i = 0; i < N; ++i) scanf("%lld", &a[i]);
    qsort(a, N, sizeof(LL), compare); // ʹ��qsort��������

    for (int i = 0; i < N; ++i) {
        if (i == 0 || a[i] != a[i - 1]) {
            x[cnt] = a[i];
            t[cnt] = 1;
            ++cnt;
        } else {
            ++t[cnt - 1];
        }
    }

    for (int i = 0; i < cnt; ++i) {
        f[i] = x[i] * t[i];
        if (f[i] > Ans) Ans = f[i]; // �������ֵ
    }
}

void Solve() {
    for (int i = 1; i < cnt; ++i) {
        if (x[i] % 3 != 0) continue; // �������������������
        LL val = x[i] / 3 * 2;
        // ʹ�ö��ֲ��ң�����ֱ��ʹ�ü�ѭ���������Ϊ����������
        int pos = 0;
        while (pos < i && x[pos] < val) ++pos;
        if (pos < i && x[pos] == val) {
            f[i] += f[pos]; // ����fֵ
            if (f[i] > Ans) Ans = f[i]; // ȡ���ֵ
        }
    }
}

void Print() {
    printf("%lld\n", Ans);
}

int main() {
    Init();
    Solve();
    Print();
    return 0;
}

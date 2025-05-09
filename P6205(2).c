#include <stdio.h>
#include <string.h>

#define rei int
#define FOR(i, l, r) for(rei i = l; i <= r; ++i)

typedef __int128 ll;

ll f[1001];
int n, m;

void print(ll x) { // ��д
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[50]; // �������ֲ��ᳬ��49λ��ʵ����__int128��ʮ���Ʊ�ʾ���ܸ�����������Ϊ�˼򻯣�
    int pos = 0;
    while (x > 0) {
        buf[pos++] = (x % 10) + '0';
        x /= 10;
    }
    for (int i = pos - 1; i >= 0; --i) {
        putchar(buf[i]);
    }
    putchar('\n');
}

int main() {
    scanf("%d%d", &m, &n);
    memset(f, 0, sizeof(f)); // ��ʼ��f����Ϊ0
    f[0] = 1;
    FOR(i, 1, n) // ���ѭ��ö����Ʒ���ڲ�ѭ��ö��Ǯ��
        FOR(j, i, m)
            f[j] += f[j - i];
    print(f[m]);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ll long long

// �Զ���Ķ��뺯����ģ��C++��read
ll read() {
    ll x = 0, y = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') y = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * y;
}

int main() {
    int n, l, r;
    char s[1000007]; // �����ַ�����󳤶�Ϊ1000006����Ϊ���һ���ַ���'\0'��
    bool fuck[1000007] = {0}; // ʹ��bool����������Ѿ����'a'��λ��

    n = read();
    l = read();
    r = read();

    // ��l��rת��Ϊ���ַ���ĩβ��ʼ���������
    l = n - l;
    r = n - r;

    // ��ȡ�ַ���
    scanf("%s", s);

    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (flag == l) break;
        if (s[i] != 'a') {
            s[i] = 'a';
            flag++;
        } else {
            fuck[i] = true;
        }
    }

    // �������Ҫ�����'a'����'b'���ﵽr
    if (flag < r) {
        for (int i = n - 1; i >= 0; i--) {
            if (fuck[i]) { // ֻ�޸���Щ֮ǰ�Ѿ���'a'��λ��
                s[i] = 'b';
                flag++;
                if (flag == r) break;
            }
        }
    }

    // ������
    printf("%s\n", s);

    return 0;
}

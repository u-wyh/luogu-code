#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n, k;
char s[200005];

bool check(int x) {
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            p = i; // �ҵ���һ��'1'
            break;
        }
    }
    int cnt = 0; // ��¼����
    while (p <= n) {
        p += x;
        cnt++;
        if (p > n) break; // ���Ʊ߽�
        while (s[p] == '0') p++; // �����'0'�����踲��
    }
    if (cnt <= k) return true; // ��������
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s + 1); // ��s[1]��ʼ�����ַ�����s[0]δʹ��
        int l = 1; // ��˵���Ϊ1
        int r = n / k + 1; // ����ÿ���ζ������ܶ�

        while (l < r) { // ���ִ�
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }
    return 0;
}

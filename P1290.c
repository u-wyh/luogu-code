#include <stdio.h>

int m, n, q;

// ��ǰ������Ϊp, pΪ0ʱ����Stan����, pΪ1ʱ����Ollie������
int find(int x, int y, int p) {
    if (x == y) return p; // ����ʤ��
    if (y / x >= 2) return p; // ����ʤ��
    else return find(y - x, x, p ^ 1); // ����һ��״̬����
}

int main() {
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &m, &n);
        if (m > n) {
            int temp = m;
            m = n;
            n = temp;
        }
        if (find(m, n, 0) == 0) {
            printf("Stan wins\n"); // �������0, ʤ��ΪStan
        } else {
            printf("Ollie wins\n"); // ��֮��ΪOllie
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h> // ����stdlib.h��ʹ��malloc��free

const int mod = 1e9 + 7;
const int N = 1e7;

int main() {
    int *f = (int*)malloc(N * sizeof(int)); // ��̬�����ڴ�
    if (f == NULL) { // ����ڴ��Ƿ�ɹ�����
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // ��ʼ�������ǰ����Ԫ��
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    f[3] = 5;

    int n;
    scanf("%d", &n);

    // ����f[n]
    for (int i = 4; i <= n; ++i) {
        f[i] = (2 * f[i - 1] % mod + f[i - 3] % mod) % mod;
    }

    printf("%d\n", f[n]);

    // �ͷ��ڴ�
    free(f);

    return 0;
}

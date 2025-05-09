#include <stdio.h>
#include <stdlib.h>

#define int long long
#define N 1000000 + 100000

// �ȽϺ���������qsort
int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y - x); // ע�����ﷵ��y-x��ʵ�ֽ�������
}

int main() {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    int a[N], b[N];
    int ans = 0, kk = 0;

    // ��ȡ����a�����
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        ans += a[i];
    }

    // ��ȡ����b�����
    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
        ans += b[i];
    }

    // ������a�������򣨽���
    qsort(a, n, sizeof(int), compare);

    // �ҳ�����������Ԫ������������ans
    int minn = (n < m) ? n : m;
    for (int i = 0; i < minn; i++) {
        if (a[i] > k) {
            ans += a[i];
            kk++;
        }
    }

    // ʣ�µ�Ԫ�ض���k����
    ans += k * (minn - kk);

    // ������
    printf("%lld\n", ans);

    // main����Ӧ����int���ͣ�����ͨ������0��ʾ�ɹ�
    return 0;
}

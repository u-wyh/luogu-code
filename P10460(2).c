#include <stdio.h>

typedef struct {
    int st;
    int en;
    int dis;
} defender;

defender arr[200005];

int main() {
    int t, n, s, e, d;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) { // ע��C����������������0��ʼ
        scanf("%d", &n);
        int m = 0;
        for (int j = 0; j < n; j++) { // ͬ��ע������
            scanf("%d%d%d", &s, &e, &d);
            arr[j].st = s;
            arr[j].en = e;
            arr[j].dis = d;
            for (int k = s; k <= e; k += d) {
                m ^= k; // ʹ���������������ǡ����ڵ�����
            }
        }
        if (m == 0) {
            printf("There's no weakness.\n");
            continue;
        }
        int num = 0;
        for (int j = 0; j < n; j++) { // ���m�Ƿ���ĳ�������d�ı�����
            if (m <= arr[j].en && m >= arr[j].st && (m - arr[j].st) % arr[j].dis == 0) {
                num++;
            }
        }
        printf("%d %d\n", m, num);
    }
    return 0;
}

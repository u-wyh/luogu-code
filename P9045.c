#include <stdio.h>
#include <stdbool.h> // ���벼������֧��

#define MAX_N 500001
bool book[MAX_N]; // ֻ��Ҫ�������ݾͿ��ԣ���bool��ʡ�ռ�
long long ans;
int a, n, k, d;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (book[a] == 0) {
            book[a] = 1;
            ans += i - d - 1;
            d++;
        }
        if (d == k) { // ��֭�Ѿ����ֵ�Ʒ�����Ѿ�������Ҫ��ֱ��������۲�����ѭ���Ϳ�����
            printf("%lld\n", ans);
            return 0;
        }
    }
    printf("-1\n"); // ���û���ҵ�k����ͬ��Ʒ�ƣ������-1
    return 0;
}

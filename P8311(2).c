#include <stdio.h>
#include <limits.h> // ����INT_MAX���Զ��������������ֱ������һ������

#define ll long long

int main() {
    ll a, b, ans = 0, min = 1000000005; // ����long long�����ڣ��������Ц������ȷʵ��Ҫע�����ݷ�Χ��

    // ʹ��scanf��ȡa
    scanf("%lld", &a);

    // ����a�Ƿ�Ϊ1
    if (a == 1) {
        printf("0\n"); // ע��C����printf�����Զ����У���Ҫ�ֶ����\n
    } else {
        for (int i = 1; i <= a; i++) {
            // ʹ��scanf��ȡb
            scanf("%lld", &b);
            // �ۼ��ܺ�
            ans += b;
            // ������Сֵ
            if (b <= min) {
                min = b;
            }
        }
        // ���㲢������
        // ע�⣺�������a����Ϊ0�����������д��������Կ���ֱ�ӽ�������
        printf("%lld\n", a * min - min * 2 + ans);
    }

    return 0;
}

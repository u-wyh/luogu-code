#include <stdio.h>

int main() {
    long long x, y, ans = 0, temp;
    scanf("%lld %lld", &x, &y);

    while (x && y) { // ���x��y����Ϊ0�������ѭ��
        // ����x��y��ֵ
        temp = x;
        x = y;
        y = temp;

        // ���㲢�ۼӵ�ǰ����ֲ���������������
        ans += 4 * y * (x / y);

        // ����x��ֵΪx����y������
        x %= y;
    }

    // ������
    printf("%lld\n", ans);

    return 0;
}

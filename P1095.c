#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int m, s, t, now = 0;
    scanf("%d %d %d", &m, &s, &t);
    int s1 = 0, s2 = 0; // ����ܲ����ߵľ��������˸���ߵľ���
    for (int i = 1; i <= t; i++) { // һ����ʱ��ȥ��
        s1 += 17; // ���ֺ��ܲ���������
        if (m >= 10) {
            s2 += 60;
            m -= 10; // �ܹ�������϶�Ҫ���ֵ�
        } else {
            m += 4; // û����һ�غϾ���������
        }
        if (s2 > s1) {
            s1 = s2; // ���ֵĿ��˾Ͱ��ܲ����滻�����ֵ�
        }
        if (s1 >= s) { // �ܳ�ȥ�˾������ǰʱ��
            printf("Yes\n%d\n", i);
            return 0;
        }
    }
    printf("No\n%d\n", s1); // ʱ�䶼�����˻�û�ܳ�ȥ�������No����s1��ֵ
    return 0;
}

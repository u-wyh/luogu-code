#include <stdio.h>

int minx = 2147483647, flag, ans; // ������Сֵ����־��������С·��
int a[5][11], b[5][11], c[5]; // 3������

int main() { // ���̻�����ʼ
    for (int i = 0; i < 5; i++) {
        c[i] = 1; // ע�⣬��ֵΪ1
        for (int j = 1; j < 11; j++) {
            scanf("%d", &a[i][j]); // ����
            b[i][j] = a[i][j] - a[i][j - 1]; // ����
        }
    }

    for (int i = 0; i < 20; i++) {
        minx = 2147483647; // ÿ�θ��³�ʼֵ
        for (int j = 0; j < 5; j++) {
            if (b[j][c[j] + 1] < minx && c[j] + 1 <= 10) { // �����Ŀǰ��СֵС����û�г���10km
                flag = j; // ��־
                minx = b[j][c[j] + 1]; // ��Сֵ����
            }
        }
        c[flag]++; // ����
    }

    ans = 0; // ��ʼ��ans
    for (int i = 0; i < 5; i++) {
        ans += a[i][c[i]]; // �������Ž�
    }

    printf("%d\n%d %d %d %d %d\n", ans, c[0], c[1], c[2], c[3], c[4]); // �������
    return 0; // ���̻�������
}

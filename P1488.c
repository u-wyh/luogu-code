#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int a[3];
} tri;

tri h[50000 + 5];
bool point[50000 + 5];

int main() {
    int n;
    scanf("%d", &n);

    // ��ȡ�����ζ��㣬ע�����һ�������β���Ҫ��ȡ
    for (int i = 0; i < n - 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &h[i].a[j]);
        }
    }

    // ��ʼ����һ�������εĶ���Ϊ�ѷ���
    for (int j = 0; j < 3; ++j) {
        point[h[0].a[j]] = true;
    }

    short ans = 0;

    // ����ÿ�������Σ����˵�һ����
    for (int i = 1; i < n - 2; ++i) {
        int _ans = 0;

        // ͳ�Ƶ�ǰ���������ж��ٸ������ѱ�����
        for (int j = 0; j < 3; ++j) {
            if (point[h[i].a[j]]) {
                _ans++;
            }
        }

        // ��������������ѱ����ʣ������Ӵ𰸼���
        if (_ans == 2) {
            ++ans;
        }
    }

    // ������ĿҪ��������
    if (ans == 1) {
        printf("JMcat Win\n");
    } else if (ans == 2) {
        if (n % 2) {
            printf("PZ Win\n");
        } else {
            printf("JMcat Win\n");
        }
    } else {
        if (n % 2) {
            printf("PZ Win\n");
        } else {
            printf("JMcat Win\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BAMBOO 200005

typedef long long LL;

LL data[MAX_BAMBOO]; // �洢���ӵĸ߶�
int p[MAX_BAMBOO] = {0}; // �洢���ӻ��ܱ������Ĵ���

int main() {
    int n;
    int Max = 0; // ��ߵ�����Ҫ��������
    LL cnt = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &data[i]);
        LL t = data[i];
        while (t > 1) { // ע�⣬t �� 1 ��ʼ�����ٱ���������Ϊ��Ŀ�е� while ѭ�������� t-1
            p[i]++;
            t = (LL)sqrt((double)(t / 2 + 1)); // ע������ת���;�������
        }
        if (p[i] > Max) {
            Max = p[i];
        }
    }

    for (int i = Max; i > 0; i--) {
        for (int j = 0; j < n - 1; j++) { // ע�� j < n - 1 �Ա�������Խ��
            if (p[j] == i) {
                if (data[j] != data[j + 1]) { // �������߶Ȳ�һ����ʱ��ż���
                    cnt++;
                }
                p[j]--; // ��������һ�Σ��ɿ���������һ
                data[j] = (LL)sqrt((double)(data[j] / 2 + 1)); // �������ˣ��ù�ʽ���㱻������ĸ߶�
            }
        }
    }

    printf("%lld\n", cnt);
    return 0;
}

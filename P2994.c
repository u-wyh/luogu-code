#include <stdio.h>
#include <stdlib.h>

#define maxn 1005

long long int a[maxn], b[maxn], c, d; // ��ţλ�ú���λλ��
int flag[maxn]; // �����ţ�Ƿ�����λ
int pos; // ��¼����λ����ţ���

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &a[i], &b[i]);
    }
    for (int j = 1; j <= m; j++) {
        scanf("%lld %lld", &c, &d);
        long long int dis = 0; // ���㵱ǰ��ţ����λ�ľ���
        long long int mindis = 1e15; // ��¼��ǰ��С��ţ�����Ӿ���
        for (int i = 1; i <= n; i++) {
            if (flag[i] == 1) continue; // ������λ��ֱ������
            dis = (a[i] - c) * (a[i] - c) + (b[i] - d) * (b[i] - d); // �������
            if (dis < mindis) { // ���ˢ������С��¼
                mindis = dis;
                pos = i;
            }
        }
        flag[pos] = 1; // ��ǣ�������λ
    }
    if (n == m) { // ����û����ţ����λ
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) { // ����������
        if (flag[i]) continue;
        printf("%d\n", i);
    }
    return 0;
}

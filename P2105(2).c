#include <stdio.h>
#include <string.h>

#define MAXN 501
#define MAXK 20001

int x[MAXN], y[MAXN], n, m, k;
int flag[MAXK], vis[MAXK], sum, ans;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &x[i], &y[i]);
        vis[x[i]] = 1; // ����й�������
    }

    memset(flag, 0, sizeof(flag)); // ��ʼ��flag����
    ans = 0;

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue; // �����ǰ���й�����������

        sum = m; // ��ʼ����ǰ�еĿ�������Ϊm

        for (int j = 1; j <= k; j++) {
            if (flag[y[j]] != i) sum--; // ��ȥ��ǰ�������Ƶ���
            flag[y[j]] = i; // ����б���ǰ�й�������

            if (x[j] < i) { // ��ǰ�����ڵ�ǰ���Ϸ�
                if (y[j] + i - x[j] >= 1 && y[j] + i - x[j] <= m) {
                    // ���·���Խ���
                    if (flag[y[j] + i - x[j]] != i) sum--;
                    flag[y[j] + i - x[j]] = i;
                }
                if (y[j] - i + x[j] >= 1 && y[j] - i + x[j] <= m) {
                    // ���·���Խ���
                    if (flag[y[j] - i + x[j]] != i) sum--;
                    flag[y[j] - i + x[j]] = i;
                }
            } else { // ��ǰ�����ڵ�ǰ���·�
                if (y[j] + (x[j] - i) >= 1 && y[j] + (x[j] - i) <= m) {
                    // ���·���Խ���
                    if (flag[y[j] + (x[j] - i)] != i) sum--;
                    flag[y[j] + (x[j] - i)] = i;
                }
                if (y[j] - (x[j] - i) >= 1 && y[j] - (x[j] - i) <= m) {
                    // ���·���Խ���
                    if (flag[y[j] - (x[j] - i)] != i) sum--;
                    flag[y[j] - (x[j] - i)] = i;
                }
            }
        }

        ans += sum; // �ۼӵ�ǰ�еĿ�������
    }

    printf("%d\n", ans);
    return 0;
}

#include <stdio.h>

int s[11000];
int ans = 0;  // ��ʼ��ansΪ0

int main() {
    int n, m;
    scanf("%d %d", &n, &m);  // ��ȡѧ������n��ˮ��ͷ����m

    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);  // ��ȡÿ��ѧ���Ľ�ˮ��
    }

    int t = m + 1;  // t������¼��һ��ѧ���ı��

    while (t <= n + m) {
        for (int i = 1; i <= m; i++) {  // ö��m��ˮ��ͷ
            s[i]--;
            if (s[i] == 0) {
                // ������ѧ����ˮ�����ˣ�ģ�⻻��һ��ѧ�������ˮ��ͷ
                if (t <= n) {  // ȷ��tû�г���ѧ������
                    s[i] = s[t];
                    t++;
                }
            }
        }
        ans++;  // ģ���1���ӵĽ�ˮʱ�䣬ans��һ
    }

    printf("%d\n", ans);  // ������

    return 0;
}

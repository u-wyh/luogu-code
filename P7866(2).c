#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_num(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return p - '0';
    }
}

int n, ans;
int color_count[14][4]; // ������4�ֻ�ɫ����¼ÿ�����͵�ÿ�ֻ�ɫ����
int cnt[14]; // �洢ÿ���Ƶ�����������ӻ�ɫ

int main() {
    // freopen("xinxin.in", "r", stdin);
    // freopen("xinxin.out", "w", stdout);
    char a, b;
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    memset(color_count, 0, sizeof(color_count));

    for (int i = 0; i < n; i++) {
        scanf(" %c%c", &a, &b);
        int t = change_num(b);
        cnt[t]++; // ���Ƶ����������

        // ����'S', 'H', 'D', 'C' �ֱ�������ֻ�ɫ
        switch (a) {
            case 'S': color_count[t][0]++; break;
            case 'H': color_count[t][1]++; break;
            case 'D': color_count[t][2]++; break;
            case 'C': color_count[t][3]++; break;
        }
    }

    for (int i = 1; i <= 13; i++) {
        if (cnt[i] == 5) ans++; // 5��1��
        else if (cnt[i] >= 6) ans += 2; // 6,7,8��2��
        else if (cnt[i] >= 3 && cnt[i] <= 4) {
            int unique_colors = 0;
            for (int j = 0; j < 4; j++) {
                if (color_count[i][j] > 0) unique_colors++;
            }
            // �����3,4�ţ����ܻ�ɫ��
            // ���3���ƹ���3����ͬ�Ļ�ɫ �� 4���ƹ��в�ͬ��4����ɫ���϶�������ɡ�С�꿡�
            if (unique_colors == cnt[i]) ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}

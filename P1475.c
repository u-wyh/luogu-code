#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMPANIES 102

int a[MAX_COMPANIES][MAX_COMPANIES]; // a[i][j]��ʾ��˾iӵ�й�˾j�ٷ�֮a[i][j]�Ĺɷ�
int cnt[MAX_COMPANIES]; // cnt[i]��ʾ��ǰ�׶��й�˾xӵ�й�˾i�ۼ��аٷ�֮cnt[i]�Ĺɷ�
int m;
int f[MAX_COMPANIES]; // f[i]��ʾ��ǰ�׶��е�i����˾�Ƿ�������
int own[MAX_COMPANIES]; // own[i]��ʾ��ǰ�׶��й�˾x�Ƿ��ܿ��ƹ�˾i

void EMILY(int x) {
    if (f[x]) // �߽������������ǰ��˾�ѱ�����������ֱ�ӷ���
        return;
    f[x] = 1; // ���Ϊ������
    for (int i = m; i > 0; i--) // ö�����й�˾
    {
        cnt[i] += a[x][i]; // ���ϵ�ǰ��˾�Ĺɷݰٷֵ�
        if (cnt[i] > 50) { // ��������
            own[i] = 1; // ����Ϊ�ܹ�����
            EMILY(i); // �ݹ�
        }
    }
}

int main() {

    int i, j, u, v, w, n;

    // ��ʼ��mΪ0
    m = 0;

    for (scanf("%d", &n); n; n--) {
        scanf("%d%d%d", &u, &v, &w);
        a[u][v] = w; // ��˾uӵ�й�˾v�ٷ�֮w�Ĺɷ�
        m = (m > u) ? m : u;
        m = (m > v) ? m : v;
    }

    for (i = 1; i <= m; i++) {
        memset(f, 0, sizeof(f)); // �ѱ������ȫ�����
        memset(own, 0, sizeof(own)); // ���������ȫ����Ϊ0
        memset(cnt, 0, sizeof(cnt)); // ���ۼưٷֵ�ȫ������
        EMILY(i); // �ӵ�i����˾��ʼ����
        for (j = 1; j <= m; j++)
            if (own[j] && i != j) // �����˾j���ڹ�˾i��i������j
                printf("%d %d\n", i, j); // �����˾i���ƹ�˾j
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

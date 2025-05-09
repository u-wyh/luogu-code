#include <stdio.h>
#include <string.h>

#define MAXN 1010

int n, ans, ans1;
int fx[4] = {-1, 0, 1, 0};
int fy[4] = {0, 1, 0, -1}; // ��������
char d[MAXN][MAXN], f[MAXN][MAXN];

void dfs(int x, int y) { // ����û���м�����½
    d[x][y] = '.';
    for (int i = 0; i < 4; i++) {
        int xt = x + fx[i], yt = y + fy[i];
        if (d[xt][yt] != '.' && xt > 0 && xt <= n && yt > 0 && yt <= n)
            dfs(xt, yt);
    }
}

void df(int x, int y) { // ����ûǰ�м�����½
    f[x][y] = '.';
    for (int i = 0; i < 4; i++) {
        int xt = x + fx[i], yt = y + fy[i];
        if (f[xt][yt] == '#' && xt > 0 && xt <= n && yt > 0 && yt <= n)
            df(xt, yt);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf(" %c", &d[i][j]); // ע��%cǰ�Ŀո�������֮ǰ�Ļ��з�
            f[i][j] = d[i][j];
        }
        getchar(); // ��ȡ���������з�
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == '#' && (d[i-1][j] == '.' || d[i+1][j] == '.' || d[i][j-1] == '.' || d[i][j+1] == '.'))
                d[i][j] = '-';
        }
    }

    ans1 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (f[i][j] == '#') {
                ans1++;
                df(i, j);
            }
        }
    }

    ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == '#') {
                ans++;
                dfs(i, j);
            }
        }
    }

    printf("%d\n", ans1 - ans);
    return 0;
}

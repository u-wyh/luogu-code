#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Ϊ��ʹ��bool����

#define MAX_N 200
#define MAX_LINE_LENGTH 10000 // ����ÿ�г��Ȳ�����10000

int cx[4] = {-1, 1, 0, 0};
int cy[4] = {0, 0, -1, 1}; // �������飬�ϡ��¡�����

int a[MAX_N][MAX_N]; // ԭʼ���ݣ���Ȼ��a������f[i][j]�߼�������
int m[MAX_N]; // �洢ÿ�еĳ���
int n; // ��ͼ������
int h = 0; // ���������

void dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m[x] || a[x][y] == 0) return; // �߽��������ѷ��ʹ�
    a[x][y] = 0; // ���Ϊ�ѷ���
    for (int i = 0; i < 4; i++) {
        dfs(x + cx[i], y + cy[i]); // �ݹ�������������
    }
}

int main() {
    char buffer[MAX_LINE_LENGTH + 1]; // ��ȡ�еĻ�����
    scanf("%d", &n); // ����n
    getchar(); // ������β�Ļ��з�

    for (int i = 1; i <= n; i++) {
        fgets(buffer, sizeof(buffer), stdin); // ��ȡһ��
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[--len] = '\0'; // ȥ���ַ���ĩβ�Ļ��з�
        m[i] = len; // �洢ÿ�еĳ���

        for (int j = 0; j < len; j++) {
            if (buffer[j] >= 'a' && buffer[j] <= 'z') {
                a[i][j + 1] = 1; // ע�⣬C���������0��ʼ��������Ϊ�˷�����⣬����ʹ��1��ʼ������
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m[i]; j++) {
            if (a[i][j] == 1) {
                dfs(i, j); // �����ǰλ����½�أ���ʼ����
                h++; // ÿ�ҵ�һ�����죬����������1
            }
        }
    }

    printf("%d\n", h); // �����������
    return 0;
}

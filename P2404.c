#include <stdio.h>

int n, p[11] = {1}, cnt = 1, m;

void print(int aa) { // �������
    for (int i = 1; i < aa; i++) {
        printf("%d+", p[i]);
    }
    printf("%d\n", p[aa]);
}

void dfs(int a) { // ͨ��DFS�õ����У�a�ǵ�ǰ�����
    for (int i = p[a - 1]; i <= m; i++) { // ��ǰһ��������һ������ʼ����
        if (i == n) continue; // ��ֹ���һ�����n�����������Ϊ�˱��ⲻ��Ҫ����������Ϊn������Ϊ��ֵ�һ���֣�����n������ǲ�ֵ�һ������
        p[a] = i;
        m -= i;
        if (m == 0) {
            print(a); // m����ʱ���÷�����������ϣ��������
        } else {
            dfs(a + 1); // �����������
        }
        m += i; // ����
    }
}

int main() {
    scanf("%d", &n);
    m = n;
    dfs(1);
    return 0;
}

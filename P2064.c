#include <stdio.h>
#include <math.h>

#define INF 0x7fffffff

int n, ans = INF;

// �������������������
void dfs(int dep, int num);

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= (int)sqrt(n); i++) {
        // ����һ���ǳɶԳ��֣���������ö�ٵ�aʵ������i��n/i
        if (n % i == 0) {
            if (n / i != i) dfs(0, i);  // n/(n/i)=i
            if (i != 1 && i != n) dfs(0, n / i);  // �����ظ���n��������
        }
    }
    if (ans != INF) printf("%d\n", ans);  // �ж��ܷ񵽴�
    else printf("-1\n");
    return 0;
}

// �������������������
void dfs(int dep, int num) {
    if (num == 0) {
        // �߽�����
        if (dep < ans) ans = dep;  // ������С���
        return;
    }
    num--;  // ��ʽ�������1����
    for (int i = 2; i <= 9; i++) {  // ö��k
        if (num % i == 0) {  // �ж�����
            dfs(dep + 1, num / i);
        }
    }
}

// E&D��Ϸ
// ��������2n��ʯ�ӣ����Ϊ1��2��3...2n
// ����1��2Ϊһ�飻3��4Ϊһ�飻5��6Ϊһ��...2n-1��2nΪһ��
// ÿ����Խ��зָ������
// ��ȡһ��ʯ�ӣ��������ߣ�Ȼ��ָ�ͬһ�����һ��ʯ��
// ����ȡ�����ɸ�ʯ�ӷ��ڱ����ߵ�λ�ã�����µ�һ��
// ������ɺ�����ÿ�ѵ�ʯ�������뱣֤����0
// ��Ȼ�����ָ��һ�ѵ�ʯ��������ҪΪ2
// �������������зָ����������ֵ�ĳ�˽��в���ʱ�����жѵ�ʯ������Ϊ1���д����������
// ���������ܲ��ܻ�ʤ
// �������� : https://www.luogu.com.cn/problem/P2148
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int lowZero(int status) {
    int ans = 0;
    while (status > 0) {
        if ((status & 1) == 0) {
            break;
        }
        status >>= 1;
        ans++;
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int sg = 0;
        for (int j = 1, a, b; j <= n; j += 2) {
            scanf("%d%d", &a, &b);
            sg ^= lowZero((a - 1) | (b - 1));
        }
        if (sg != 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}

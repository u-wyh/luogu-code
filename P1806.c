/*
    ��δ����˼·����˵����ţ��
    ans[j]�Ӵ�С������    ans[j] += ans[j - i];
    ʲô��˼�أ�   ���һ����iȦ    �ܹ�����jȦ
    ans[j-i]��ÿһȦ�����ᳬ��i  Ϊʲô��   ��Ϊi��1��ʼ����
*/
#include <stdio.h>

long long n, ans[501];

int main() {
    scanf("%lld", &n);
    ans[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            ans[j] += ans[j - i];
        }
    }
    //printf("%lld\n", ans[n]-1);
    for(int i=1;i<=n;i++)
        printf("%10d",ans[i]-1);

    return 0;
}

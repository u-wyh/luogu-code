// ����ǰ׺�Ϻ���ں�
// ��n�����n���ڣ�Ҫ���2n���ȵ����У���֤����ǰ׺�ϣ�������� >= �ڵ�����
// �����ж��������з������𰸶� 100 ȡģ
// 1 <= n <= 100
// �������� : https://www.luogu.com.cn/problem/P1722
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 100;
const int MAXN = 1000001;

// ��ʽ4
long long compute4(int n) {
    long long f[n + 1];
    for(int i=0;i<=n;i++){
        f[i]=0;
    }
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int l = 0, r = i - 1; l < i; l++, r--) {
            f[i] = (f[i] + f[l] * f[r] % MOD) % MOD;
        }
    }
    return f[n];
}

int main()
{
    int n;
    cin>>n;
    cout<<compute4(n)<<endl;

    return 0;
}


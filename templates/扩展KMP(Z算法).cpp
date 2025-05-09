// ��չKMPģ�棬�ֳ�Z�㷨��Z����
// ���������ַ���a��b�������������
// b��bÿһ����׺���������ǰ׺���ȣ�z����
// b��aÿһ����׺���������ǰ׺���ȣ�e����
// �����Ҫ��������������������������Ȩֵ����
// ����һ������x��iλ�õ�Ȩֵ����Ϊ : (i * (x[i] + 1))
// ����ȨֵΪ����λ��Ȩֵ������
// �������� : https://www.luogu.com.cn/problem/P5410
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20000001;

int z[MAXN];
int e[MAXN];
char a[MAXN];
char b[MAXN];
int n,m;

void zArray(char* s, int n) {
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}
//���˵�в����Ļ�ֱ�Ӿ���ģ��

long eor(int* arr, int n) {
    long ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= (long) (i + 1) * (arr[i] + 1);
    }
    return ans;
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    scanf("%s",b);
    m=strlen(b);
    zArray(b,m);
    eArray(a,b,n,m);
    cout<<eor(z,m)<<endl;
    cout<<eor(e,n)<<endl;
    return 0;
}

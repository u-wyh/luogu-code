// īī�ĵ�ʽ(����תȦ��)
// һ����n��������ÿ��������ѡ������������������Ǹ���
// ��ôһ����ĳЩ��ֵ��������Щ�����ۼӵõ�
// ������[l...r]��Χ�ϣ��ж��ٸ����ܱ��ۼӵõ�
// 0 <= n <= 12
// 0 <= ��ֵ��Χ <= 5 * 10^5
// 1 <= l <= r <= 10^12
// �������� : https://www.luogu.com.cn/problem/P2371
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//֮����Ҫת��Ȧ  ����Ϊÿ�ο�ʼתȦ��ʱ��  ��㲻һ������С��
//������Ҫ�ڶ�Ȧ������
//����תȦ��������������ʱ�临�Ӷȸ��ȶ�  ��dj�㷨��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int v[MAXN];
long dist[MAXN];
int n, x;
long l, r;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

long compute() {
    sort(v + 1, v + n + 1);
    int sz = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] != 0) {
            //ͳ�����з�0������  �൱�ڽ�0�Ƶ�ǰ��
            v[++sz] = v[i];
        }
    }
    //ȥ����Ч����
    if (sz == 0) {
        //���ȫ����0  ��ô��û��Ҫ����
        return 0;
    }
    x = v[1];
    for(int i=0;i<x;i++){
        dist[i]=LONG_MAX;//���е�ľ��붼�����ֵ
    }
    dist[0] = 0;//0�ľ�����0
    for (int i = 2, d; i <= sz; i++) { // ���ֻ�׼��֮������������������·
        d = gcd(v[i], x); // �����Լ��  �õ����ĸ���
        for (int j = 0; j < d; j++) { // j��ÿ���ӻ������
            for (int cur = j, Next, circle = 0; circle < 2; circle += cur == j ? 1 : 0) {
                //��Ҫת��Ȧ  circle += cur == j ? 1 : 0�ж��Ƿ�ص���� ��Ȧ����һ
                Next = (cur + v[i]) % x;//��ʾҪȥ����һ����
                if (dist[cur] != LONG_MAX) {
                    dist[Next] = min(dist[Next], dist[cur] + v[i]);
                }
                cur = Next;//�任��ǰ��
            }
        }
    }
    long ans = 0;
    //Ȼ��ͳ��С��r  ��  С��l�ĸ���  �õ���
    for (int i = 0; i < x; i++) {
        if (r >= dist[i]) {
            ans += max((long)0, (r - dist[i]) / x + 1);
        }
        if (l >= dist[i]) {
            ans -= max((long)0, (l - dist[i]) / x + 1);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>l>>r;
    l--;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    cout<<compute();
    return 0;
}

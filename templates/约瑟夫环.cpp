// Լɪ������
// һ����1~n��Щ�㣬�����β��ӵĻ�
// ��1�ŵ������1��ʼ�������ĸ��ڵ㱨������k����ɾ���ýڵ�
// Ȼ����һ���ڵ������1��ʼ���±��������ջ��ϻ�ʣ��һ���ڵ�
// ���ظýڵ�ı��
// 1 <= n, k <= 10^6
// �������� : https://www.luogu.com.cn/problem/P8671
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    int ans = 1;
    for (int c = 2; c <= n; c++) {
        ans = (ans + k - 1) % c + 1;
    }
    cout<<ans;
    return 0;
}

// �����ӷŽ�������
// ����һ������Ϊn������weights������һ����k��
// ����weights[i]�ǵ�i�����ӵ�����
// ���㰴�����¹������е����ӷŽ�k������
// 1��û�б����ǿյ�
// 2�������i�����Ӻ͵�j��������ͬһ���������ôi��j�������Ӷ�Ҫ�����������
// һ�������������i��j���������ӣ���������ļ۸���weights[i]+weights[j]
// һ�����ӷ��䷽���ķ�����������k�������ļ۸�֮��
// �뷵�����з��䷽���У�����������С�����Ĳ�ֵΪ����
// 1 <= n, k <= 10^5
// �������� : https://leetcode.cn/problems/put-marbles-in-bags/
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    int weight[n];
    for(int i=0;i<n;i++){
        cin>>weight[i];
    }
    int sum[n-1];
    for(int i=1;i<n;i++){
        sum[i-1]=weight[i]+weight[i-1];
    }
    sort(sum,sum+n-1);
    int small = 0;
	int big = 0;
	for (int i = 0, j = n - 2, p = 1; p < k; i++, j--, p++) {
        small += sum[i];
        big += sum[j];
    }
	cout<<(big - small);
    return 0;
}

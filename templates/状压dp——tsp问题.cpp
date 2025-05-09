// �ۻ�Ա������ - TSP����
// ĳ����n����ׯ(1<=n<=20)����һ���ۻ�Ա����Ҫ��������ׯȥ�ۻ�
// ����ׯ֮���·��s(1<=s<=1000)����֪��
// ��A�嵽B���·�̣���B��A��·��಻ͬ(�����Ȩͼ)
// Ϊ�����Ч�ʣ������̵������ÿ����ׯһ�Σ�Ȼ�󷵻��̵����ڵĴ壬
// �����̵����ڵĴ�ׯΪ1
// ����֪��ѡ��ʲô����·�߲���ʹ���ߵ�·�����
// �������ѡ��һ����̵�·
// �������� : https://www.luogu.com.cn/problem/P1171
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

int n;
int graph[20][20];
int dp[1<<20][20];
//int ans=INT_MAX;

int f(int s, int i) {
    if (s == (1 << n) - 1) {
        // n : 000011111
        return graph[i][0];
    }
    if (dp[s][i] != -1) {
        return dp[s][i];
    }
    int ans = INT_MAX;
    for (int j = 0; j < n; j++) {
        // 0...n-1��Щ�壬�������ǲ�����һ����ŵ�
        if ((s & (1 << j)) == 0) {
            ans = min(ans, graph[i][j] + f(s | (1 << j), j));
        }
    }
    dp[s][i] = ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>graph[i][j];
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=-1;
        }
    }
    cout<<f(1,0);
    return 0;
}

// ժӣ��
// ����һ��n*n�������ξ���grid��ÿ������ֵֻ������-1��0��1
// -1��ʾ���Ӳ����ߡ�0��ʾ���ӿ����ߵ���û��ӣ�ҡ�1��ʾ���ӿ���������һ��ӣ��
// ���Ŀ���Ǵ����Ͻ��ߵ����½ǣ�ÿһ��ֻ�� ���� ���� ����
// Ȼ������½��߻����Ͻǣ�ÿһ��ֻ�� ���� ���� ����
// ��������У��뾡����Ļ��ӣ�ң�������ӣ�ҵĸ��ӣ�ֻ�ܼ�һ��
// ��������ܻ�ö���ӣ�ң����������ͨ·����0
// �������� : https://leetcode.cn/problems/cherry-pickup/
// ����ֻ��������˼·
// ����Ȥͬѧ�Լ��ĳ��ϸ�λ�������Ķ�̬�滮
// ����Ȥͬѧ�Լ��ĳ��ռ�ѹ���汾�Ķ�̬�滮
// ֮ǰ�Ŀδ����漰�����ﲻ��׸��
#include<iostream>
#include<cmath>
using namespace std;

int n;
int grid[50][50];
int dp[50][50][50];

int f(int a,int b,int c){
    int d=a+b-c;
    if(grid[a][b]==-1||grid[c][d]==-1||a==n||b==n||c==n||d==n){
        return -1;
    }
    if(a==n-1&&b==n-1){
        return grid[a][b];
    }
    if (dp[a][b][c] != -2) {
        return dp[a][b][c];
    }
    int get = a == c && b == d ? grid[a][b] : (grid[a][b] + grid[c][d]);
    int next = f(a + 1, b, c + 1);
    next = max(next, f(a + 1, b, c));
    next = max(next, f(a, b + 1, c + 1));
    next = max(next, f(a, b + 1, c));
    int ans = -1;
    if (next != -1) {
        ans = get + next;
    }
    dp[a][b][c] = ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                dp[i][j][k] = -2;
            }
        }
    }
    int ans = f(0, 0, 0);
    ans=ans == -1 ? 0 : ans;
    cout<<ans;
    return 0;
}

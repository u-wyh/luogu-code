// ���Ļ��ַ���
// ������m�ֳ�n�ݣ���ÿ�ݲ���Ϊ�գ�����������������ͬ(������˳��)
// ���磬m=7��n=3����ô(1, 1, 5) (1, 5, 1) (5, 1, 1)��Ϊ��ͬһ�ַ���
// �����ж����ֲ�ͬ�Ļ��ַ���
// �������� : https://www.luogu.com.cn/problem/P1025
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 201;
const int MAXK = 7;

int dp[MAXN][MAXK];
int n,k;

int f(int n,int k){
    if(n==0){
        return 1;
    }
    if(k==0){
        return 0;
    }
    if(dp[n][k]!=-1){
        return dp[n][k];
    }
    int ans;
    if(k>n){
        //���ӱ�ƻ����  ��ôע����һ�����ֻ����n�������ж���
        ans=f(n,n);
    }
    else{
        ans=f(n,k-1)+f(n-k,k);//�ֱ��ʾ  ��ʹ����������  ��  һ��ʹ���������ӣ�ÿ������������һ����
    }
    dp[n][k]=ans;
    return ans;
}

int main()
{
    cin>>n>>k;
    if(n<k)
        cout<<0<<endl;
    else if(n==k)
        cout<<1<<endl;
    else{
        n-=k;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=k;j++){
                dp[i][j]=-1;
            }
        }
        cout<<f(n,k)<<endl;
    }
    return 0;
}

// �����ֲ�ͬ��ɫΪ����Ϳɫ
// ������������m��n����ʾm*n����������ÿ����Ԫ���ʼ�ǰ�ɫ
// �����ú졢�̡���������ɫΪÿ����Ԫ��Ϳɫ�����е�Ԫ����Ҫ��Ϳɫ
// Ҫ�����ڵ�Ԫ�����ɫһ��Ҫ��ͬ
// ��������Ϳɫ�ķ��������𰸶� 1000000007 ȡģ
// 1 <= m <= 5
// 1 <= n <= 1000
// �������� : https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/
// ����Ȥ��ͬѧ�����Լ���һ�¿ռ�ѹ���İ汾
//����ʵ���е���������dp
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN = 1001;
const int MAXM = 5;
const int MAXS = pow(3, MAXM);
const int MOD = 1000000007;

int n,m;//��ʾ��n��m��
int maxs;
int first[MAXS];
int size;
int dp[MAXN][MAXM][MAXS];

// s��ʾ��ǰ״̬������3���������
// ��ǰ������j�Ÿ�3��j�η���bit
// ����s��j�Ÿ��ֵ
int get(int s, int bit) {
	return (s / bit) % 3;
}

// s��ʾ��ǰ״̬������3���������
// ��ǰ������j�Ÿ�3��j�η���bit
// ��s��j�Ÿ��ֵ���ó�v��������״̬
int set(int s, int bit, int v) {
	return s - get(s, bit) * bit + v * bit;
}

// ȡ�����е�һ�е���Ч״̬   ��Ϊ��һ��û���Ϸ�  �����ر���
void dfs(int j, int s, int bit) {
    if (j == m) {
        //��ʾһ����Ч�ĵ�һ��״̬
        first[size++] = s;
    } else {
        int left = j == 0 ? -1 : get(s, bit / 3);
        if (left != 0) {
            dfs(j + 1, set(s, bit, 0), bit * 3);
        }
        if (left != 1) {
            dfs(j + 1, set(s, bit, 1), bit * 3);
        }
        if (left != 2) {
            dfs(j + 1, set(s, bit, 2), bit * 3);
        }
    }
}

int f(int i,int j,int s,int bit){
    //�����s��ʵ��һ�еĺ��沿�ֺ���һ��ǰ�沿��ƴ�ӵ�״̬ �е�������dp����˼
    if(i==n){
        return 1;
    }
    if(j==m){
        return f(i+1,0,s,1);
    }
    if(dp[i][j][s]!=-1){
        return dp[i][j][s];
    }
    int left=j==0?-1:get(s,bit/3);
    int up=get(s,bit);
    int ans = 0;
    if (up != 0 && left != 0) {
        ans = (ans + f(i, j + 1, set(s, bit, 0), bit * 3)) % MOD;
    }
    if (up != 1 && left != 1) {
        ans = (ans + f(i, j + 1, set(s, bit, 1), bit * 3)) % MOD;
    }
    if (up != 2 && left != 2) {
        ans = (ans + f(i, j + 1, set(s, bit, 2), bit * 3)) % MOD;
    }
    dp[i][j][s] = ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    if(m>n){
        n^=m;
        m^=n;
        n^=m;
    }
    maxs=pow(3,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int s=0;s<maxs;s++){
                dp[i][j][s]=-1;
            }
        }
    }
    dfs(0,0,1);//��ɵ�һ��������Ч״̬��ͳ��
    int ans=0;
    for (int i = 0; i < size; i++) {
        ans = (ans + f(1, 0, first[i], 1)) % MOD;
    }
    cout<<ans<<endl;
    return 0;
}

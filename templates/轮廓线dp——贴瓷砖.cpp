// ����ש�ķ�����(������dp)
// ������������n��m����ʾn��m�еĿհ�����
// �����޶��1*2���Ĵ�ש��Ŀ������˿�Ϸ���������еĿհ�����
// �����ж����������ķ���
// 1 <= n, m <= 11
// �������� : http://poj.org/problem?id=2411
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<iostream>
using namespace std;

long dp[11][11][1<<11];
int n, m;

// ������������ȡ״̬s�е�jλ��״̬
int get(int s, int j) {
    return (s >> j) & 1;
}

// ��������������״̬s�е�jλ��״̬Ϊv���������µ�״̬
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

long f(int i,int j,int s){
    if(i==n){
        return 1;
    }
    if(j==m){
        return f(i+1,0,s);
    }
    if(dp[i][j][s]!=-1){
        return dp[i][j][s];
    }
    long ans=0;
    if(get(s,j)==1){
        ans+=f(i,j+1,set(s,j,0));
    }
    else{
        if (i + 1 < n) { // ��ǰ���Ű�ש
            ans = f(i, j + 1, set(s, j, 1));
        }
        if (j + 1 < m && get(s, j + 1) == 0) { // ��ǰ���Ű�ש
            ans += f(i, j + 2, s);
        }
    }
    dp[i][j][s]=ans;
    return ans;
}

int main()
{
    while(true){
        cin>>n>>m;
        if(n+m==0)
            break;
        for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int s = 0; s < (1<<m); s++) {
					dp[i][j][s] = -1;
				}
			}
		}
		cout<<f(0, 0, 0)<<endl;
    }
    return 0;
}

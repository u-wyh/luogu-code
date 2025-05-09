// ����ש�ķ�����(������dp+�ռ�ѹ��)
// ������������n��m����ʾn��m�еĿհ�����
// �����޶��1*2���Ĵ�ש��Ŀ������˿�Ϸ���������еĿհ�����
// �����ж����������ķ���
// 1 <= n, m <= 11
// �������� : http://poj.org/problem?id=2411
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<iostream>
using namespace std;

long dp[12][1<<11];
long prepare[1<<11];
int n, m;

// ������������ȡ״̬s�е�jλ��״̬
int get(int s, int j) {
    return (s >> j) & 1;
}

// ��������������״̬s�е�jλ��״̬Ϊv���������µ�״̬
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

int main()
{
    while(true){
        cin>>n>>m;
        if(n+m==0)
            break;
        for(int i=0;i<(1<<n);i++){
            prepare[i]=1;
        }
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<(1<<m);j++){
                //��ʱ����ǵ�m��  Ҳ���Ǽӳ�������һ��
                dp[m][j]=prepare[j];
            }

            for(int j=m-1;j>=0;j--){
                for(int s=0;s<(1<<m);s++){
                    long ans=0;
                    if(get(s,j)==1){
                        ans+=dp[j+1][set(s,j,0)];
                    }
                    else{
                        if (i + 1 < n) { // ��ǰ���Ű�ש
                            ans = dp[j + 1][set(s, j, 1)];
                        }
                        if (j + 1 < m && get(s, j + 1) == 0) { // ��ǰ���Ű�ש
                            ans += dp[j + 2][ s];
                        }
                    }
                    dp[j][s]=ans;
                }
            }

            for(int j=0;j<(1<<m);j++){
                prepare[j]=dp[0][j];
                //���ű�ĵ�һ��Ҳ����һ�ű�����һ��
            }
        }
        cout<<dp[0][0]<<endl;
    }
    return 0;
}

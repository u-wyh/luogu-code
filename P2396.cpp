#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m;
int dis[1<<24];//��ʾ��״̬i�£��ߵ��ĸ�λ��
bool ok[1<<24];//��ʾ��״̬i�£��ߵ���λ���Ƿ���Ч
int bad[2];//��ʾ��������
int dp[1<<24];//��ʾ��i��������ж����ַ���

int main()
{
    //cout<<change(16)<<' '<<change(64)<<' '<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>dis[1<<i];
    }
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>bad[i];
    }
    //������������

    dis[0]=0;
    for(int s=1;s<(1<<n); s++){
        int j=s&-s,k=s;
        dis[s]=dis[s^j]+dis[j];//�Ӽ����Լ��Ĳ���  ����һ����ֻ�������ұߵ��Ǹ�1
		ok[s]=true;
		for(int i=0;i<m;i++){
            if(dis[s]==bad[i]){
                ok[s]=false;
                break;
            }
		}
	}
	//���dis  ok����ĳ�ʼ��

	dp[0]=1;
	for(int s=1;s<(1<<n);s++){
        int k=s;
        while(k&&ok[s]){
            int j = k & -k; //j�ǵ�ǰ�ҵ���lowbit
            dp[s] = (dp[s] + dp[s ^ j])%MOD;
            k ^= j; //k��ȥ�����"1"�������´�lowbit���ҵ���һ��"1"
        }
	}
	cout<<dp[(1<<n)-1]<<endl;
    return 0;
}

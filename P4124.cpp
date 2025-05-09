#include<bits/stdc++.h>
using namespace std;

long long dp[11][10][10][2][2][2][2];
//���ǵڼ�λ  ǰ��λ��ǰһλ�Ƕ���  �Ƿ��Ѿ�������һ������  �Ƿ�ֵ֤��Ҫ���С   ��û��4 �� 8
//������Щ���ֱ���Ϸ�  ����ͷһ��������0
int num[12];

long long compute(int pos,int a,int b,bool c,bool free,bool four,bool eight){
    /*
    pos��ʾ��ǰ�����ڶ���λ
    a��ʾǰ��λ b��ʾǰһλ c��ʾ�Ƿ�������λһ����
    free��ʾ�Ƿ��������ѡ��
    four��ʾ��û��4  eight��ʾ��û��8
    */
    if(four&&eight){
        return 0;
    }
    if(dp[pos][a][b][c][free][four][eight]){
        return dp[pos][a][b][c][free][four][eight];
    }
    if(pos==0){
        //����0λ��  ˵��ȫ������ ��һ���Ƿ�������һ����  �����4��8  ��ôһ���޷���������
        return c;
    }
    long long ans=0;
    int limit=free?9:num[pos];
    for(int i=0;i<=limit;i++){
        ans+=compute(pos-1,b,i,c||(a==i&&a==b),free||(i<limit),four||(i==4),eight||(i==8));
    }
    dp[pos][a][b][c][free][four][eight]=ans;
    return ans;
}

long long calc(long long x){
    if(x<1e10){
        return 0;
    }
    memset(dp,0,sizeof(dp));
    int len;
    for(len=0;x;x/=10){
        num[++len]=x%10;
    }
    long long ans=0;
    for(int i=1;i<=num[len];i++){
        //��11λ����  һ��������0
        ans+=compute(10,0,i,0,i<num[len],i==4,i==8);
    }
    return ans;
}

int main()
{
    long long l,r;
    cin>>l>>r;
    cout<<(calc(r)-calc(l-1));
    return 0;
}

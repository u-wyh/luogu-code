// ����Ӯ��
// ������������n��m
// ������ҿ��������ӹ����������г�ȡ��1��n�����������Żأ�
// ��ȡ���������ۼ�������������Ҷ��㣩
// ˭���Լ��Ļغ����ۼӺ� >= m��˭��ʤ
// ���ȳ��ֵ��������Ӯ�򷵻�true�����򷵻�false
// ������λ�����Ϸʱ����������������ȫ��Ϊ�Լ�����
// �������� : https://leetcode.cn/problems/can-i-win/
#include<bits/stdc++.h>
using namespace std;

int n,m;
int dp[1<<21];//��ʾ��i��״̬�� �������ֿɲ�����Ӯ

// ���1~7��Χ�����ֶ���ѡ����ôstatus��״̬Ϊ��
// 1 1 1 1 1 1 1 1
// 7 6 5 4 3 2 1 0
// 0λ��������
// ���1~7��Χ�����֣�4��2�Ѿ�ѡ�˲�����ѡ����ôstatus��״̬Ϊ��
// 1 1 1 0 1 0 1 1
// 7 6 5 4 3 2 1 0
// 0λ��������
// f�ĺ��� :
// ���ַ�Χ1~n����ǰ�����֣����status����������״̬
// ���ۼӺͻ�ʣrest�������
// ���ص�ǰ�������ܲ���Ӯ����Ӯ����true������Ӯ����false
bool f(int status, int rest) {
    if(rest<=0)
        return false;
    if(dp[status]!=0)
        return dp[status]==1;
    bool ans=false;
    for(int i=1;i<=n;i++){
        if(status&(1<<i)!=0&&!f(status^(1<<i),rest-i)){
            //��ʾ��ǰ����ζ�����ֿ���ѡ ����ѡ��֮���״��ʹ�� ���ĺ����䣨����һ�ֵ����֣�
            ans=true;
            break;
        }
    }
    dp[status]=ans?1:-1;
    return ans;
}

bool canIWin() {
    if (m == 0) {
        // ������Ŀ�涨
        return true;
    }
    if (n * (n + 1) / 2 < m) {
        // ���1~n����ȫ������
        // �ۼӺͺ���n * (n+1) / 2����С��m
        // ��ô������Ӯ�ң�Ҳ����ζ�����ֲ����ʤ
        return false;
    }
    // dp[status] == 0 ����û���
    // dp[status] == 1 ���������true
    // dp[status] == -1 ���������false
    return f((1<<(n+1))-1,m);
}

int main()
{
    cin>>n>>m;
    if(canIWin()){
        cout<<"yes"<<endl;
    }
    else
        cout<<"no"<<endl;
    return 0;
}

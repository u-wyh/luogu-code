// ���������������ۼӺ�Ϊ����ֵ��������鳤��
// ����һ����������arr, ����Ԫ�ؿ������ɸ�����0
// ����һ������aim
// ��arr�������������ۼӺ�Ϊaim��������鳤��
// �������� : https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,aim;
int nums[MAXN];
int sum[MAXN];
map<int ,int >M;
int ans=0;

int main()
{
    cin>>n>>aim;
    M[0]=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
        if(M.find(sum[i])==M.end()){
            M[sum[i]]=i;
        }
        if(M.find(aim-sum[i])!=M.end()){
            ans=max(ans,i-M[aim-sum[i]]);
        }
    }
    cout<<ans;
    return 0;
}

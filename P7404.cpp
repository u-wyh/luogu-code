#include<bits/stdc++.h>
using namespace std;

int n;
int nums[200005],d[200005];
long long x[200005],y[200005];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        d[i]=nums[i]-nums[i-1];
    }
    for(int i=1;i<n;i++){
        if(d[i]<=0)
            x[i]=x[i-1]+1-d[i];
        else
            x[i]=x[i-1];
    }
    for(int i=n-1;i>=0;i--){
        if(d[i]>=0)
            y[i]=y[i+1]+d[i]+1;
        else
            y[i]=y[i+1];
    }
    long long  ans=1e15;
    for(int i=0;i<n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    //�������L��R����  ����d[L]++  d[R+1]--�������ǲ�����һ��һ��
    //����ֻ�ں�һ���ӻ��߼�   �����ȡ���ֵ  �������һ������ʱ��˳��ʵ�ֵڶ���Ŀ��
    return 0;
}

//P5911
//�����Ĺؼ���ö�����е��Ӽ�
#include<bits/stdc++.h>
using namespace std;
#define int long long

int weight,n;
struct node{
    int t,w;
}nums[16];
int f[1<<16];
int t[1<<16];//��ʾ��������״̬ ʱ���Ƕ���
int w[1<<16];//��ʾ��������״̬ �����Ƕ���

signed main()
{
    cin>>weight>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].t>>nums[i].w;
    }
    for(int s=0;s<(1<<n);s++){
        //ö���Ӽ�
        for(int i=0;i<n;i++){
            if(s&(1<<i)){
                //��ʾ���״̬���������
                t[s]=max(t[s],nums[i].t);
                w[s]+=nums[i].w;
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        f[i]=INT_MAX;
    }
    f[0]=0;
    for(int s=1;s<(1<<n);s++){
        for(int s1=s;;s1=s&(s1-1)){
            //�������Ա�֤s1һ����s���Ӽ�
            int s2=s^s1;//��ʾ����s�����һ��
            if(w[s2]<=weight){
                f[s]=min(f[s],f[s1]+t[s2]);
            }
            if(s1==0){
                //���ﲻ�ܷ���ѭ������Ϊ�ж�����
                //��Ϊ�������һ�ξ���ȫ����ȥ��
                break;
            }
        }
        //cout<<f[s]<<endl;
    }
    cout<<f[(1<<n)-1];
    return 0;
}

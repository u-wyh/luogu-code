#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005],r=0,ans;
int st[100005];

int main()
{
    cin>>n;
    ans=n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            if(nums[st[r-1]]==nums[i]){
                ans--;
            }
            r--;
        }
        st[r++]=i;
    }
    //�����������˼����һ��ʼ��������Ϊÿһλ�ö�������������
    //Ȼ�����ǿ����Ż�
    //����������ȸߵ�����  �����м�ֻ�б��Լ��ߵ�  �������������  ֻ��һ��ת��
    //��ô���Լ���һ��
    //��������������
    cout<<ans;
    return 0;
}

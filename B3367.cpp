#include<bits/stdc++.h>
using namespace std;

int n,k;
unsigned long long a[100005],q[100005];

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>a[i];
    int h=0,t=0;
    for(int i=0;i<n;i++){
        while(h<t&&q[h]+k<=i){
            h++;
        }
        while(h<t&&a[q[t-1]]<a[i]){
            t--;
        }//h<t  ��֤����������Ѿ��ǿյ�  ��ô����t--
        q[t]=i;
        t++;
        if(i>=k-1)
            cout<<t-h<<endl;
    }
    return 0;
}
//����Ҳ�����Ƚ���һ��k-1�Ļ�������  Ȼ���ڼ����k������  �жϲ�������ֵ
//ע������ĵ���ѹ��������Ǹ���h t�ı仯�����е�   ��ʵ�ϱ���������������������������   ֻ�ǲ��ᱻ������


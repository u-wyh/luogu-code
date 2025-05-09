//P2215
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m,k;
int arr[MAXN];
int dp[MAXN];//��ʾ�����Ե�ǰԪ����Ϊ��ʼ  ����������г���
int en[MAXN];//ends[i]��ʾ����  ����Ϊi  �ĵ���������  ��ͷ  ����Ƕ���
int len=0;//��ʾends���鳤��

void compute(){
    int u=1;
    while(dp[u]<k){
        u++;
    }
    int maxlen=k;
    int last=INT_MIN;
    for(int i=1;i<=k;i++){
        while(dp[u]<k-i+1||arr[u]<=last){
            u++;
        }
        cout<<arr[u]<<' ';
        last=arr[u];
        u++;
    }
    cout<<endl;
}

//�ҵ���һ��С�ڵ���val��Ԫ�ص��±�
int bs(int val){
    int l=1,r=len,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(en[mid]<=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=n;i>=1;i--){
        int sub=bs(arr[i]);
        if(sub==-1){
            //˵����ʱû�б���С��Ԫ��
            en[++len]=arr[i];//������ĩβ����һ��Ԫ��
            dp[i]=len;
        }
        else{
            en[sub]=arr[i];//��ԭ����Ԫ���滻
            dp[i]=sub;
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>k;
        if(k>len){
            cout<<"Impossible"<<endl;
        }
        else{
            compute();
        }
    }
    return 0;
}


#include<bits/stdc++.h>
using namespace std;
#define MAXN 200010

int n,m,x,y,mid;
int l[MAXN],r[MAXN];
int w[MAXN],v[MAXN];
long long sw[MAXN],sv[MAXN];
long long W,S,sum;

int main()
{
    cin>>n>>m>>S;
    W=S;//���׼�Ĳ�ֵ
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];
        y=max(y,w[i]);//��ʼ����߱�׼  ����Ʒ����Ƕ���
    }
    x=1,y+=1;//x,y�������жϱ�׼�ı仯��Χ
    //y+=1�ǿ������S=0�Ļ���ô�������еĶ���ѡ����õ�   �����еĲ�Ʒ�����ϸ�
    for(int i=1;i<=m;i++)
        cin>>l[i]>>r[i];
    while(x<y){
        memset(sw,0,sizeof(sw));
        memset(sv,0,sizeof(sv));
        mid=(x+y)>>1;
        sum=0;//sum��ʾ�����б�׼��ָ���Ƕ���
        for(int i=1;i<=n;i++){
            if(w[i]>=mid){
                sw[i]=sw[i-1]+1;
                sv[i]=sv[i-1]+v[i];
            }else{
                sw[i]=sw[i-1];
                sv[i]=sv[i-1];
            }
        }
        for(int i=1;i<=m;i++){
            sum+=(sw[r[i]]-sw[l[i]-1])*(sv[r[i]]-sv[l[i]-1]);
        }
        if(sum==S){
            W=0;
            break;
        }
        W=min(W,abs(sum-S));
        if(sum<=S){
            y=mid;
        }else{
            x=mid+1;
        }
    }
    cout<<W;
    return 0;
}

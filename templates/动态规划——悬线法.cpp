//P1169
//left[i][j]:�����(i,j)(i,j)�ܵ��������λ��
//right[i][j]:�����(i,j)(i,j)�ܵ��������λ��
//up[i][j]:�����(i,j)(i,j)������չ�����.
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n,m;
int nums[MAXN][MAXN];
int lef[MAXN][MAXN];
int righ[MAXN][MAXN];
int up[MAXN][MAXN];
int ans1=0,ans2=0;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            lef[i][j]=righ[i][j]=j;
            up[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(nums[i][j]!=nums[i][j-1]){
                lef[i][j]=lef[i][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=2;j--){
            if(nums[i][j]!=nums[i][j-1]){
                righ[i][j-1]=righ[i][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
            if(i>1&&nums[i][j]!=nums[i-1][j]){
                lef[i][j]=max(lef[i][j],lef[i-1][j]);
                righ[i][j]=min(righ[i][j],righ[i-1][j]);//�������Եõ��������խ�����
                up[i][j]=up[i-1][j]+1;//���򳤶�
            }
            int a=righ[i][j]-lef[i][j]+1;	//���򳤶�
            int b=min(a,up[i][j]);
            ans1=max(ans1,b*b);//������
            ans2=max(ans2,a*up[i][j]);//������
            //��������������ʵ���϶�����i��j��Ϊ���µ��������
        }
    }
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
int n,i,a[6][6],b[30],vis[30],sum;//vis�������ڱ��
void dfs(int x,int y,int z){
    if (y>n){
        if (z!=sum) return;
        x++,y=1,z=0;
    }
    if (x>n){
        for (int i=1;i<=n;i++){
            for (int j=1;j<n;j++) printf("%d ",a[i][j]);
            printf("%d\n",a[i][n]);
        }
        exit(0);//�Ż�3
    }
    for (int i=1;i<=n*n;i++)
        if (!vis[i]){//�Ż�2
            if (y==n && z+b[i]!=sum) continue;
            if (x==n){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][y];
                if (s+b[i]!=sum) continue;
            }
            if (x==n && y==1){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][n-j+1];
                if (s+b[i]!=sum) continue;
            }
            if (x==n && y==n){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][j];
                if (s+b[i]!=sum) continue;
            }
            a[x][y]=b[i];
            vis[i]=1;
            dfs(x,y+1,z+b[i]);
            vis[i]=0;
        }
}
int main(){
    cin>>n;
    for (i=1;i<=n*n;i++) scanf("%d",&b[i]),sum+=b[i];//�Ż�1
    sum/=n;
    cout<<sum<<endl;
    sort(b+1,b+n*n+1);//��b�����С����������һ�β��ҵ��Ľ����Ϊ�ֵ�����С��
    dfs(1,1,0);
}

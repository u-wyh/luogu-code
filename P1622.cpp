#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000];
int f[1000][1000];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+m+1); //��������Ĳ���ת��״̬
    a[0]=0;a[m+1]=n+1; //����0��n+1���η����ˣ���������״̬ת��
    for(int l=1;l<=m;l++)  //ö�����䳤��
        for(int i=1;i+l-1<=m;i++) //������˵�λ��
        {
            int j=i+l-1;  //�����Ҷ˵�λ��
            f[i][j]=999999999;
            for(int k=i;k<=j;k++)  //ö�ٷֽ��
                f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+a[j+1]-a[i-1]-1-1); //״̬ת��
        }
    printf("%d",f[1][m]);
}

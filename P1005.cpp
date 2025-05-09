#include<bits/stdc++.h>
using namespace std;

int n,m,lc;
char ch[100];
int d[100];
int a[100][100][100];
int er[81][100];
int A[100];
int B[100];
int ans[200];
int f[81][81][100];

inline void Add(int *b,int *c){
    memset(d,0,sizeof(d));
    d[0]=max(b[0],c[0])+1;
    for (int I=1;I<=d[0];I++){
        d[I]+=b[I]+c[I];
        d[I+1]+=(d[I]/10);
        d[I]%=10;
    }
    while (d[d[0]]==0) d[0]--;//ȥ��0
    for (int I=0;I<=d[0];I++) b[I]=d[I];
    return;
}

inline void CF(int *b,int *c){
    memset(d,0,sizeof(d));//���
    d[0]=b[0]+c[0];
    for (int k=1;k<=b[0];k++)//��
        for (int l=1;l<=c[0];l++){
            d[k+l-1]+=b[k]*c[l];
        }
    for (int k=1;k<=d[0];k++){
        d[k+1]+=d[k]/10;
        d[k]%=10;
    }
    while (d[d[0]]==0) d[0]--;//ȥ��ǰ���0
    for (int k=0;k<=d[0];k++) b[k]=d[k];
}

inline bool Max(int *b,int *c){
    while (b[b[0]]==0&&b[0]>0) b[0]--;
    while (c[c[0]]==0&&c[0]>0) c[0]--;
    if (b[0]>c[0]) return true;
    if (c[0]>b[0]) return false;
    for (int i=b[0];i>=1;i--)
        if (b[i]>c[i]) return true; else
        if (b[i]<c[i]) return false;
    return false;
}

bool flag;

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            scanf("%s",ch+1);//����
            lc=strlen(ch+1);
            a[i][j][0]=0;
            for (int k=lc;k>=1;k--){
                a[i][j][++a[i][j][0]]=ch[k]-'0';
            }
        }
    er[0][0]=1;er[0][1]=1;
    for (int i=1;i<=m;i++){
        for (int j=0;j<=er[i-1][0];j++){
            er[i][j]=er[i-1][j];
        }
        Add(er[i],er[i-1]);
    }
    for (int k=1;k<=n;k++)//��
    {
        memset(f,0,sizeof(f));
        for (int i=1;i<=m;i++)
        {//f[i][i]=a[k][i]*2^m;
            Add(f[i][i],a[k][i]);
            CF(f[i][i],er[m]);
        }
        for (int l=1;l<m;l++)
        {
            for (int i=1,j=i+l;j<=m;i++,j=i+l)
            {//�����dpת�ƵĹ���
                memset(A,0,sizeof(A));
                Add(A,a[k][i]);
                CF(A,er[m+i-j]);
                Add(A,f[i+1][j]);
                memset(B,0,sizeof(B));
                Add(B,a[k][j]);
                CF(B,er[m+i-j]);
                Add(B,f[i][j-1]);
                flag=Max(A,B);
                if (flag)
                {
                    for (int l=0;l<=A[0];l++)
                        f[i][j][l]=A[l];
                } else
                {
                    for (int l=0;l<=B[0];l++)
                        f[i][j][l]=B[l];
                }
            }
        }
        Add(ans,f[1][m]);
    }
    while (ans[ans[0]]==0&&ans[0]>0) ans[0]--;//ȥ��0
    if (ans[0]==0) ans[0]++;//����0
    for (int i=ans[0];i>=1;i--)//�������
        printf("%d",ans[i]);
    return 0;
}

//3423
//ʹ�õ��������Ż����ر�������
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 20005;
const int MAXN = 205;

int n,m;
int val[MAXN];
int num[MAXN];
int q[MAXN];

int f[MAXM];
int g[MAXM];

int d[MAXM][MAXN];
int d1[MAXM][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        num[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        f[i]=500;
    }
    f[0]=0;
    for(int i=1;i<=n;i++){
        //ö�ٻ�������
        for(int j=0;j<=m;j++){
            g[j]=f[j];//ÿ��f��仯  �ȿ���һ��
        }
        for(int j=1;j<=m;j++){
            for(int k=1;k<=n;k++){
                d1[j][k]=d[j][k];
            }
        }
        for(int j=0;j<val[i];j++){
            //��ֳ�val[i]����  ����%val[i]��������
            int head=0,tail=0;
            for(int k=j;k<=m;k+=val[i]){//������±�  ʵ�����ǿռ䣨���������г�����ģ�ͣ�
                //��ÿ������е�������
                while(head<tail&&q[head]<(k-num[i]*val[i])){
                    //����ÿ������ƶ�һ��λ��  ʵ�������ÿ��ֻ���Ƴ�һ�� ��if���Ҳ����
                    //(k-num[i]*val[i])  ��ʾ��߽� ��Ϊ���ѡnum[i]��  ÿ����֮�����val[i]
                    //Ŀǰ��Ҫ��Ļ���Ϊk��ʱ��  ���ļ�ֵ
                    head++;
                }
                while(head<tail&&g[k]<=(g[q[tail-1]]+(k-q[tail-1])/val[i])){
                    //ʵ������g[k]+(x-k)/v*w  <= g[q[tail-1]]+(x-q[tail-1])/v*w
                    //�����Ǽ��� ����x��k��q[tail-1]�Ĳ�ֵһ������Լ��v  ��Ϊ����һ����
                    //����Ĵ�����w=1
                    tail--;
                }
                q[tail++]=k;
                f[k]=min(g[k],g[q[head]]+(k-q[head])/val[i]);
                if(f[k]==g[q[head]]+(k-q[head])/val[i]){
                    for(int u=1;u<=i;u++){
                        d[k][u]=d1[q[head]][u];
                    }
                    d[k][i]+=(k-q[head])/val[i];
                }
            }
        }
//        cout<<i<<": ";
//        for(int j=0;j<=m;j++){
//            cout<<f[j]<<' ';
//        }
//        cout<<endl;
//        cout<<f[m]<<endl;
//        for(int j=1;j<=m;j++){
//            cout<<j<<": ";
//            for(int k=1;k<=n;k++){
//                cout<<d[j][k]<<' ';
//            }
//            cout<<endl;
//        }
    }
    cout<<f[m]<<endl;
    for(int i=1;i<=n;i++){
        cout<<d[m][i]<<' ';
    }
    return 0;
}

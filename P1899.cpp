#include<bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAXP = 5005;
const int MAXN = 1005;

int n,p,m=1;//m��ʾ������Чħ����Ʒ�ĸ���
int a[MAXN],b[MAXN];
int f[MAXP];//��ʾΪ�˴չ�i��Ǯ  ����Ҫ�˷Ѷ��ٱ������е�����
int v;//��ʾĿǰ������
int sv;//sv������Ϊ������  ��ʾ��������һ��ͼ�������

signed main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x;
        if(getchar()==' '){
            cin>>y;
            if(x>=y-p){
                //��ʾ������Ч��ħ����Ʒ
                v+=x;
            }
            else{
                a[m]=x,b[m++]=y;
            }
        }
        else
            v+=x;
    }
    for(int i=v+1;i<=p;i++){
        f[i]=INF;
    }
    sv=v;
    for(int i=1;i<=m;i++){
        v+=b[i]-p,sv+=a[i];
    }
    //��ʱ��v����������
    for(int i=1;i<=m;i++){
        for(int j=p;j>=a[i];j--){
            f[j]=min(f[j],f[j-a[i]]+b[i]-p-a[i]);
            //��ʾһ��ħ����Ʒֱ������ ��ɵ�������ʧ
        }
    }
    cout<<(sv<=p?sv:v-f[p])<<endl;
    return 0;
}

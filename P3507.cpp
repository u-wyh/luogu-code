#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
//f[i]��ʾ����ȡ��ǰi���������ּ�ȥ���ֵ����ֵ��
//���������ֺ�������Եģ���Ϊ�����ǵ���ģ���ʵ��ȡ������ȫ�෴�ģ�
//��ʵ�����Ǵ������1~i����������µ����Ž⣬A�ȴ�i��ʼ�����ȡ������˵�������ּ��������ֵ��
long long f[MAXN];

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
        arr[i]=read();
    }
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;i++){
        f[i]=max(f[i-1],arr[i]-f[i-1]);
        //���ֿ����õ�i  ���߶���һ����i-1
    }
    cout<<f[n]<<endl;
    return 0;
}

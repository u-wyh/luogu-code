#include<bits/stdc++.h>
using namespace std;

int n;
int h[1000005],m[1000005],st[1000005];
int r=0,ans=0;

inline int read(){
    int a=0,f=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {a=a*10+c-'0'; c=getchar();}
    return a*f;
}

//ʹ�õ���ջ����
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        h[i]=read(),m[i]=read();

    for(int i=1;i<=n;i++){
        while(r>0&&h[st[r-1]]>h[i]){
            r--;
            ans=max(ans,m[i]+((r>0)?m[st[r-1]]:0));
            //�������ջ�������������������ݴ�  ���������С
            //��ô��һ����Ŀǰջ�������С  ��ô�������ϵ����ݲ����㣺
            //��Ϊ���������ݱȼ�����������ݴ����Լ��������������ݾ���������������ұ������
        }
        st[r++]=i;
    }

    for(int i=1;i<r;i++){
        ans=max(ans,m[st[i-1]]);
    }
    cout<<ans;
    return 0;
}

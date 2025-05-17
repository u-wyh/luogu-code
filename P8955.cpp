#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,q,p;

int tree[MAXN];

int q[MAXN];

int ans[MAXN];

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

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
}

int main()
{
    n=read(),q=read(),p=read();

    return 0;
}
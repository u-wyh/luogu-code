#include<bits/stdc++.h>
using namespace std;
char ch;
long long l[1020],r[1020],h[1020],k[1020],n,m,top;
int d[1020][1020];
long long ans;
void ddzl(){//����ջ��ǰ��Ĵ�����ע��
    top=0;
    for(int i=m;i>=1;i--){
        while(top!=0&&h[i]<=h[k[top]]) l[k[top]]=i,top--;
        top++;
        k[top]=i;
    }
    while(top) l[k[top]]=0,top--;
}
void ddzr(){//ͬ��
    top=0;
    for(int i=1;i<=m;i++){
        while(top!=0&&h[i]<h[k[top]]) r[k[top]]=i,top--;
        top++;
        k[top]=i;
    }
    while(top) r[k[top]]=m+1,top--;
}
void work(){
    ddzl();
    ddzr();//���ε���ջԤ����l��r
    for(int i=1;i<=m;i++){
        ans+=(i-l[i])*(r[i]-i)*h[i];//ͳ��
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){//����
        for(int j=1;j<=m;j++){
            cin>>ch;
            if(ch=='*') d[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){h[j]++;if(d[i][j]) h[j]=0;}//Ԥ����h
        work();//ͳ�Ƶ�ǰ��
    }
    cout<<ans;//���
}

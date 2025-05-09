//P2391
//���������˲��鼯��˼��
//fa�����¼���ǽڵ�i֮���һ������Ⱦɫ�Ľڵ��λ��
//���ں�������ɫ�Ḳ��֮ǰ����ɫ
//�����������Ҫ����ö��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,p,q;
int fa[MAXN];
int col[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    cin>>n>>m>>p>>q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=m;i>=1;i--){
        //����ö��
        int l=(i*p+q)%n+1;
        int r=(i*q+p)%n+1;
        if(l>r){
            swap(l,r);
        }
        for(int j=find(r);j>=l;j=find(j-1)){
            //��ʾ����ڵ����Ⱦɫ
            col[j]=i;
            fa[j]=j-1;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<col[i]<<endl;
    }
    return 0;
}

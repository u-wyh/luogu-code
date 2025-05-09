#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int fa[MAXN];
int n,m;

int found(int x){
    return x==fa[x]?x:fa[x]=found(fa[x]);//���ڵ�һ�����Լ��ұ�
}

void un(int x,int y){
    fa[found(y)]=found(x);
}

int main()
{
    cin>>n>>m;
    int black=n;
    for(int i=1;i<=n+1;i++){
        fa[i]=i;
    }
    while(m--){
        int l,r;
        cin>>l>>r;
        int t=found(l);
        while(t<=r){
            un(t+1,t);//����ұ߱�Ϊ��ɫ  ��Ҫ�ϲ�  ��ô��--
            black--;
            t=found(t);
        }
        cout<<black<<endl;
    }
    return 0;
}

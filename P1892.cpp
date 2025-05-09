#include<bits/stdc++.h>
using namespace std;

int n,m,fa[2005];

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<=2*n;i++){
        fa[i]=i;
    }
    char s;
    int a,b;
    while(m--){
        cin>>s>>a>>b;
        if(s=='F'){
            un(a,b);
            //un(a+n,b+n);
        }
        if(s=='E'){
            un(b+n,a);
            un(a+n,b);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
/*
Ϊʲô��Ҫun(a+n,b+n)
����2��3�ĵ��ˣ�4��5�ĵ��ˣ�3��4������
���ǲ���˵3�� 5����2���ǵ���  �������ǲ���˵2��5������
��ô���ֻ��5����  ���Һϲ���a+n,b+n
�ͻ��У�
2��3�ĵ���  2��8  3��7 ����
4��5�ĵ���  5��9  4��10����
3��4������  9��8����
�����Ƴ���2��8��9��5  ��2��5����   ���Դ���
*/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

int tree[MAXN];
//�������ʵ������һ���������
int n,m;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //ÿһ�ζ������Լ����Ҳ��1
    }
}
//��������������������iλ�ü���v

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
    }
    return ans;
}
//�����������������������1��i���ֵ��ۼӺ�  ��ô���൱���������ʵ��ֵ

int main()
{
    cin>>n>>m;
    for(int i=1,op,x,y;i<=m;i++){
        cin>>op;
        if(op==0){
            cin>>x>>y;
            add(x,1);
            add(y+1,-1);
        }else if(op==1){
            cin>>x;
            cout<<sum(x)<<endl;
        }
    }
    return 0;
}

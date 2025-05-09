#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
int n,L,R;

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

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
    }
    return ans;
}
//�����������Ǵ�1��i�������ֵĺ�

int query(int l,int r){
    return sum(r)-sum(l-1);
}

int main()
{
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        add(i,v);
        //���ǳ�ʼʱ��Ϊ��״�������������ȫ����0   ֱ�ӵ���add����������״����
    }
    int ans=0;
    for(int i=1,j=1;i<=n,j<=n;i++){
        while(query(i,j)<L){
            j++;
        }
        if(query(i,j)>=L&&query(i,j)<=R){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
